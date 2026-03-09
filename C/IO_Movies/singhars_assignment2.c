#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <string.h>

/*
Struct: movie
*/
struct movie{
    char* title;
    int year;
    char* languages;
    double rating;
    struct movie* next;
};


// Take in current line being read in and tokenize line into struct
struct movie* createMovie(char* line){

    struct movie *new_movie = malloc(sizeof(struct movie));
    char *savePtr1;

    char *token = strtok_r(line, ",", &savePtr1);
    new_movie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(new_movie->title, token);

    token = strtok_r(NULL, ",", &savePtr1);
    new_movie->year = atoi(token);

    token = strtok_r(NULL, ",", &savePtr1);
    new_movie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(new_movie->languages, token);

    token = strtok_r(NULL, ",", &savePtr1);
    new_movie->rating = atof(token);

    new_movie->next = NULL;

    return new_movie;
}

/*
 * Function: processMovieFile
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 */
 struct movie* processMovieFile(char* filePath){
    char *currLine = NULL;
    size_t len = 0;
    int num_movies = -1;

    //struct movie *movies = malloc(sizeof(struct movie));

    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");
   
    struct movie *movie_head = NULL;
    //struct movie *movie_tail = NULL;

    // Read the file line by line
    while(getline(&currLine, &len, movieFile) != -1)
    {
        if(num_movies != -1){
            struct movie *new_movie = createMovie(currLine);

            //printf("%s", currLine);  
            // if first movie, create head
            if(num_movies == 0){
                movie_head = new_movie;
                //movie_tail = new_movie;
            } 

            if(num_movies >= 1){
                new_movie->next = movie_head;
                movie_head = new_movie;
                //movie_tail = new_movie;
            }
        }        
        num_movies++;
    }

    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);
    printf("\nProcessed file %s", filePath);
    printf(" and parsed data for %d", num_movies);
    printf(" movies.\n");

    return movie_head;
}

// free_list clears memory of the movie list.
void free_list(struct movie* temp){
    while(temp != NULL){
        struct movie *next = temp->next;  
        free(temp->title);
        free(temp->languages);
        free(temp);
        temp = next;
    }
}

void movies_by_year(struct movie* movie_head, int year){

    // loop thru list
    struct movie *current = movie_head;
    struct movie *movies_list = NULL;
    struct movie *tail = NULL;

    while(current != NULL){
        struct movie *next = current->next;
        
        if(current->year == year){
            // create a copy to be printed
            struct movie *copy = malloc(sizeof(struct movie));
            copy->title = current->title;
            copy->year = current->year;
            copy->languages = current->languages;
            copy->rating = current->rating;
            copy->next = NULL; 

            if(movies_list == NULL){
                movies_list = copy;
            }

            else{
                tail->next = copy;
            }

            tail = copy;
        }
        current = next;
    }

    // if no year, say no data about movies released in the year 
    if(movies_list == NULL){
        printf("No data about movies released in the year %d", year);
        return;
    }

    // print
    struct movie *temp = movies_list;
    while(temp != NULL){
        struct movie *next = temp->next;
        printf("%s\n", temp->title);
        temp = next;
    }

    struct movie *tmp = movies_list;
    while (tmp != NULL) {
        struct movie *next = tmp->next;
        free(tmp); // only free the struct
        tmp = next;
    }

    //(movies_list);
}

void highest_rated_movies(struct movie* movie_head){
    struct movie *current = movie_head;
    struct movie *movies_list = NULL;
    struct movie *tail = NULL;
   
    while(current != NULL){
        struct movie *next = current->next;
        
        struct movie *list_current = movies_list;

        int found = 0;

        // add current movie to final movies_list only if 1. there isnt another movie in its year
        // 2. its rating is higher than the other in its year, it replaces it.
        while(list_current != NULL){
           
            // if we find a movie in it's year already in final list
            if(list_current->year == current->year){
                found = 1;
                // AND it's rating is higher than the movie in the final list
                if(current->rating > list_current->rating){
                    
                    list_current->title = current->title; // final list's movie replaced with current in bigger list
                    list_current->year = current->year;
                    list_current->languages = current->languages;
                    list_current->rating = current->rating;
                }
                // else, move on 
            }
            break;           

            list_current = list_current->next;
        }

        if(found == 0){
             // no other movie in its year has been found, add it by default
            struct movie *copy = malloc(sizeof(struct movie));
            copy->title = current->title;
            copy->year = current->year;
            copy->languages = current->languages;
            copy->rating = current->rating;
            copy->next = NULL;

            if (movies_list == NULL) {
                // first node
                movies_list = copy;
                tail = copy;
            } else {
                // append to the end
                tail->next = copy;
                tail = copy;
            }  
        }
        current = next;
    }

    // print
    struct movie *temp = movies_list;
    while(temp != NULL){
        struct movie *next = temp->next;
        printf("%d, ", temp->year);
        printf("%s: ", temp->title);
        printf("%.1f\n", temp->rating);
        temp = next;
    }

    struct movie *tmp = movies_list;
    while (tmp != NULL) {
        struct movie *next = tmp->next;
        free(tmp); 
        tmp = next;
    }
    //free_list(movies_list);
}

int parseLanguages(char* movie_languages, char* language){
    char* copy = strdup(movie_languages);
    // create copy, get rid of [ ]
    char *start = copy;
    size_t len = strlen(movie_languages);
    if (movie_languages[0] == '[' && movie_languages[len-1] == ']') {
        movie_languages[len-1] = '\0'; 
        start++;                       
    }

    char *savePtr1;
    char *token = strtok_r(start, ";", &savePtr1);

    while (token != NULL) {
        if (strcmp(token, language) == 0) {
            free(copy);
            return 1; // if language match found, return 1
        }
        token = strtok_r(NULL, ";", &savePtr1);
    }

    free(copy);
    
    return 0;    // return 0
    
}

void movies_by_language(struct movie* movie_head, char* language){
    struct movie *current = movie_head;
    struct movie *movies_list = NULL;
    struct movie *tail = NULL;

    while(current != NULL){
        struct movie *next = current->next;

        if(parseLanguages(current->languages, language) == 1){
            // create a copy to be printed
            struct movie *copy = malloc(sizeof(struct movie));
            copy->title = current->title;
            copy->year = current->year;
            copy->languages = current->languages;
            copy->rating = current->rating;
            copy->next = NULL; 

            if(movies_list == NULL){
                movies_list = copy;
            }

            else{
                tail->next = copy;
            }

            tail = copy;
        }
        current = next;
    }

    // if no year, say no data about movies released in the language
    if(movies_list == NULL){
        printf("No data about movies released in %s", language);
        return;
    }

    // print
    struct movie *temp = movies_list;
    while(temp != NULL){
        struct movie *next = temp->next;
        printf("%s\n", temp->title);
        temp = next;
    }

    struct movie *tmp = movies_list;
    while (tmp != NULL) {
        struct movie *next = tmp->next;
        free(tmp); // only free the struct, not the strings
        tmp = next;
    }
}

/**
 * 
 */
int main ( int argc, char **argv ){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *movie_head = processMovieFile(argv[1]);

    int user_input;
    int user_year;
    char user_language[20];

    do{
        printf("\n1. Show movies released in the specified year\n2. Show highest rated movie for each year");
        printf("\n3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\nEnter a choice from 1 to 4: ");
        scanf("%d", &user_input);

        if(user_input == 1){
            do{
                printf("\nEnter the year for which you want to see movies (1900-2021): ");
                scanf("%d", &user_year);

                if(user_year < 1900 || user_year > 2021){
                    printf("Invalid input, try again.\n");
                }
            }while(user_year < 1900 || user_year > 2021);

            movies_by_year(movie_head, user_year);
        }

        if(user_input == 2){
            highest_rated_movies(movie_head);
        }

        if(user_input == 3){
            printf("\nEnter a language for which you want to see movies: ");
            scanf("%s", user_language);
            movies_by_language(movie_head, user_language);
        }

        if(user_input == 4){
            return EXIT_SUCCESS;
        }

        if(user_input > 4 || user_input < 1 ){
            printf("You entered an incorrect choice. Try again.\n");
        }

    }while(user_input != 4);

    free_list(movie_head);

    return EXIT_SUCCESS;
}