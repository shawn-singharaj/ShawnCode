#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "Usage: %s keylength\n", argv[0]);
        return 1;
    }

    srand(time(0));
    int keylength = atoi(argv[1]);
    
    for(int i = 0; i < keylength; i++){
        int randomNum = rand() % 27;
        char newChar;
        if(randomNum == 26)
            newChar = ' ';
        else
            newChar = 'A' + randomNum;

        printf("%c", newChar); 
    }
    printf("\n");

    return 0;
}