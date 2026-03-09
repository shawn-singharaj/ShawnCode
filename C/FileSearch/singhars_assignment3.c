#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

char* pick_largest_smallest_file(int largest){
   // open directory
  DIR* currDir = opendir(".");
  struct dirent *entry;

  // metadata of directory
  struct stat fileStats;

  off_t max = 0;
  off_t min = 10000000;
  char temp[256] = "";

  // loop thru directory
  while((entry = readdir(currDir)) != NULL){
    // get metadata of each item in directory
    stat(entry->d_name, &fileStats);

    // if searching for largest file
    if(largest == 1){
      if(fileStats.st_size >= max && strncmp(entry->d_name, "movies_", 7) == 0){
        max = fileStats.st_size;
        strcpy(temp, entry->d_name);
      }
    }

    // if searching for smallest file
    else if(largest == 0 && strncmp(entry->d_name, "movies_", 7) == 0){
      if(fileStats.st_size <= min){
        min = fileStats.st_size;
        strcpy(temp, entry->d_name);
      }
    }
  }

  closedir(currDir);

  if (strlen(temp) == 0) {
    printf("No valid movie files found.\n");
    return NULL;
  }


  char* selectedFile = strdup(temp);
  return selectedFile;
}

char* find_user_input(char* input, int* valid_File){
  DIR* currDir = opendir(".");
  struct dirent *entry;
  char* selectedFile = NULL;

  while((entry = readdir(currDir)) != NULL){
    if(strcmp(entry->d_name, input) == 0){
        selectedFile = strdup(entry->d_name);  
        *valid_File = 1;
        break;  
    }
  }

  if (selectedFile == NULL) {
      printf("The file '%s' was not found. Try again.\n", input);
      *valid_File = 0;
  }
  
  printf("Processing from chosen file named %s", selectedFile);
  closedir(currDir);
  return selectedFile;
}

int get_year(char* line){
  char *savePtr1;

  char *token = strtok_r(line, ",", &savePtr1);
  token = strtok_r(NULL, ",", &savePtr1);
  int year = atoi(token);
  return year;
}

void parse_file(char* selectedFile){
  FILE *read_file = fopen(selectedFile, "r");
  char *line  = NULL;
  size_t len = 0;

  int randNum = rand() % 10000;

  char dir_name[256];
  sprintf(dir_name, "singhars.movies.%d", randNum);
  printf("\nCreated directory with name %s", dir_name);

  mode_t rwxr_x___ = 0750;
  mode_t rw_r____ = 0640;

  // make directory
  if (mkdir(dir_name, rwxr_x___) != 0) {
      perror("mkdir");
      free(line);
      fclose(read_file);
      return;
  }
  // write to file in new directory
  char directory_path[256];
  int num_lines = 0;
  int year, fd;

  // go thru each line of file
  while(getline(&line, &len, read_file) != -1){
    if(num_lines > 0){ // skip over first line
      year = get_year(line);
      
      // define directory path to create file
      sprintf(directory_path, "%s/%d.txt", dir_name, year);
      fd = open(directory_path, O_WRONLY | O_CREAT | O_APPEND, rw_r____);
      if (fd == -1) {
        perror("open year file");
        continue;
      }
      // write the whole line to the file
      int how_many = write(fd, line, strlen(line));
      if (line[strlen(line) - 1] != '\n') {
          write(fd, "\n", 1);
      }
      //printf("Wrote %d bytes to the file called %s\n", how_many, directory_path);
      close(fd);
    }

    num_lines++;
  }

  free(line);
  fclose(read_file);
}

int main(void){
 
  srand(time(NULL));

  int user_input, user_input2;
  int valid_File = 1;
  char* selectedFile;
  char user_search[256];

  do{
        printf("\n1. Select file to process\n2. Exit the program");
        printf("\nEnter a choice from 1 to 2: ");
        scanf("%d", &user_input);

        if(user_input == 1){
           do{
              printf("\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file");
              printf("\nEnter 3 to specify the name of a file");
              printf("\nEnter a choice from 1 to 3: ");
              scanf("%d", &user_input2);

              if(user_input2 == 1){
                selectedFile = pick_largest_smallest_file(1);
                printf("Processing from chosen file named %s", selectedFile);
                parse_file(selectedFile);
                free(selectedFile);
                break;
              }

              if(user_input2 == 2){
                selectedFile = pick_largest_smallest_file(0);
                printf("Processing from chosen file named %s", selectedFile);
                parse_file(selectedFile);
                free(selectedFile);
                break;
              }
              // exit this loop if good
              if(user_input2 == 3){
                printf("\nEnter the complete file name: ");
                scanf("%s", user_search);
                selectedFile = find_user_input(user_search, &valid_File);
                if(valid_File == 1){
                  parse_file(selectedFile);
                  free(selectedFile);
                  break;
                }
              }

              if(user_input2 > 3 || user_input2 < 1){
                printf("try again");
              }
           }while(1);
        }

        if(user_input == 2){
            return EXIT_SUCCESS;
        }

        if(user_input > 2 || user_input < 1 ){
            printf("You entered an incorrect choice. Try again.\n");
        }

    }while(user_input != 2);
 
  return 0;
}