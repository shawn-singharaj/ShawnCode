#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

#define INPUT_LENGTH 2048
#define MAX_ARGS 512
#define MAX_BG 100

pid_t bg_pids[MAX_BG];
int bg_count = 0;

int fg_exit_status = 0;
int fg_exit_signal = 0;

int foreground_only_mode = 0;

struct Command
{
	char *argv[MAX_ARGS + 1];
	int argc;
	char *input_file;
	char *output_file;
	int is_bg;
};

// Handle ctrl-z, just toggles global flag
void handle_sigtstp() {
    if (foreground_only_mode == 0) {
        printf("Entering foreground-only mode (& is now ignored)\n");
        foreground_only_mode = 1;
    } else {
        printf("Exiting foreground-only mode\n");
        foreground_only_mode = 0;
    }
    fflush(stdout);
}

struct Command *parse_cmd(char* input){

    // return null if comment or not a command
    if(input[0] == '\n' || input[0] == '#'){
        return NULL;
    }

    // create command object
    struct Command *cmd = (struct Command *) calloc(1, sizeof(struct Command));

    // tokenize input
    char *token = strtok(input, " \n");
    while(token){
        if(!strcmp(token,"<")){
            cmd->input_file = strdup(strtok(NULL, " \n"));
        }
        else if(!strcmp(token, ">")){
            cmd->output_file = strdup(strtok(NULL, " \n"));
        }
        else if(!strcmp(token, "&")){
            cmd->is_bg = 1;
        }
        else{
            cmd->argv[cmd->argc++] = strdup(token);
        }
        token=strtok(NULL, " \n");
    }
    return cmd;
}

void exit_cmd(struct Command* cmd){
    // go thru background processes saved and kill them
    for(int i = 0; i < bg_count; i++){
        kill(bg_pids[i], SIGKILL);
    }
    exit(0);
}

void cd_cmd(struct Command* cmd){
    // if just cd, go to HOME
    if(cmd->argc == 1){
        chdir(getenv("HOME"));
    }
    // otherwise, go to destination file/folder
    else{
        if(chdir(cmd->argv[1]) == -1){
            perror("cd");
        }
    }
}

void status_cmd(){
    // if signal, print exit signal
    if(fg_exit_signal != 0){
        printf("terminated with signal %d", fg_exit_signal);
        fflush(stdout);
    }
    // if no signal, print exits status
    else{
        printf("exit value %d", fg_exit_status);
        fflush(stdout);
    }
}

int setup_redirect(struct Command* cmd){
    // if there is an input file, open it
    if(cmd->input_file){
        int fd = open(cmd->input_file, O_RDONLY);
        if(fd == -1){
            perror(cmd->input_file);
            return -1;
        }
        dup2(fd, 0);
        close(fd);
    }
    // if background, open /dev/null
    else if(cmd->is_bg){
        int fd = open("/dev/null", O_RDONLY);
        if(fd != -1){
            dup2(fd, 0);
            close(fd);
        }
    }

    // if there is an output file, open it
    if(cmd->output_file){
        int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd == -1){
            perror(cmd->output_file);
            return -1;
        }
        dup2(fd, 1);
        close(fd);
    }
    // if background, open /dev/null
    else if(cmd->is_bg){
        int fd = open("/dev/null", O_WRONLY);
        if(fd != -1){
            dup2(fd, 1);
            close(fd);
        }
    }
    return 0;
}


void execute_cmd(struct Command* cmd){
    // ignore & if foreground only mode
    if(foreground_only_mode == 1){
        cmd->is_bg = 0;
    }
    
    // spawn child using fork
    pid_t spawnpid = fork();

    // foreground process
    switch (spawnpid) {
        case -1:
        perror("fork failed");
        exit(1);

        case 0:
        // Child process

        // set up child signal handler
        // foreground child
        if(cmd->is_bg ==  0){
            struct sigaction sa_fg = {0};
            sa_fg.sa_handler = SIG_DFL;
            sigaction(SIGINT, &sa_fg, NULL);
        }
        // background child
        else if(cmd->is_bg == 1){
            struct sigaction sa_bg = {0};
            sa_bg.sa_handler = SIG_IGN;
            sigaction(SIGINT, &sa_bg, NULL);
        }

        // ignore ctrl-z
        struct sigaction sa_tstp = {0};
        sa_tstp.sa_handler = SIG_IGN;
        sigaction(SIGTSTP, &sa_tstp, NULL);

        // setup redirection for < >
        if(setup_redirect(cmd) == -1){
            exit(1);
        }

        // execute command
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp failed");
        exit(1);

        default:
        // Parent process

        int child_status;
        // foreground child, wait
        if(cmd->is_bg == 0){
            // wait for child foreground process to terminate, save status/signal
            spawnpid = waitpid(spawnpid, &child_status, 0);
            // update exit status or exit signal globally 
            if(WIFEXITED(child_status)){
                fg_exit_status = WEXITSTATUS(child_status);
                fg_exit_signal = 0;
            }
            else{
                fg_exit_status = 0;
                fg_exit_signal = WTERMSIG(child_status);
            }
        }
        // background child, dont wait
        if(cmd->is_bg == 1){
            printf("background pid is %d\n", spawnpid);
            bg_pids[bg_count++] = spawnpid;
        }
        break;
        }
    }

void check_bg_processes(){
    int child_status;
    // go thru background processes
    for(int i = 0; i < bg_count; i++){
        int result = waitpid(bg_pids[i], &child_status, WNOHANG);
        if(result > 0){ // print out exited processes
            if(WIFEXITED(child_status)){
                printf("Background pid %d is done: exit value %d", result, WEXITSTATUS(child_status));
            }
            else if(WIFSIGNALED(child_status)){
                printf("Background pid %d is done: terminated by signal %d", result, WTERMSIG(child_status));            
            }
            // remove from array and go back so not to skip the shifted pid
            bg_pids[i] = bg_pids[bg_count-1];
            bg_count--;
            i--;
            }
    }
}

int main(void){

    // user input
    char input[INPUT_LENGTH];

    // command struct
    struct Command *cmd;

    // parent ignores ctrl-c
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);

    // parent will not ignore ctrl-z
    struct sigaction sa_tstp = {0};
    sa_tstp.sa_handler = handle_sigtstp;
    sa_tstp.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa_tstp, NULL);

    while(1){
        // always check background proccess
        check_bg_processes();

        printf("\n:");
        fflush(stdout);

        // get user input
        fgets(input, INPUT_LENGTH, stdin);

        cmd = parse_cmd(input);

        if(cmd == NULL){
            continue;
        }

        // built in commands
        if(strcmp(cmd->argv[0], "exit") == 0){
            exit_cmd(cmd);
        }
        else if(strcmp(cmd->argv[0], "status") == 0){
            status_cmd();
        }
        else if(strcmp(cmd->argv[0], "cd") == 0){
            cd_cmd(cmd);
            continue;
        } // every other command
        else{
            execute_cmd(cmd);
        }
    }

    return 0;
}