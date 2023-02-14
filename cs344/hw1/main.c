#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct movie{
	char *title;
	int year;
	char *languages;
	float rating;

	struct movie *next;
};

struct movie *createMovie(char *currLine){
	struct movie *currMovie = malloc(sizeof(struct movie));

	char *ptr1;

	//storing the movie title
	char *token = strtok_r(currLine, ",", &ptr1);
	currMovie->title = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->title, token);

	//storing the movie year
	token = strtok_r(NULL, ",", &ptr1);
	currMovie->year = atoi(token);

	//storing the movie languages
	token = strtok_r(NULL, ",", &ptr1);
	currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->languages, token);

	//storing the movie ratings
	token = strtok_r(NULL, ",", &ptr1);
	currMovie->rating = atof(token);

	currMovie->next = NULL;

	return currMovie;
}

struct movie *readFile(char *filePath, int *count){
	//opens and reads the movie file
	FILE *movieFile = fopen(filePath, "r");

	//char *currLine = NULL;
	//size_t len = 0;
	//ssize_t nread;
	//char *token;
	int count2 = 0;
	char buffer[100];

	struct movie *head = NULL;
	struct movie *tail = NULL;

	//while ((nread = getline(&currLine, &len, movieFile)) != -1){
	//skips first line of file
	fgets(buffer, sizeof buffer, movieFile);
	
	//reads every line and counts each movie
	while(fgets(buffer, sizeof buffer, movieFile) != NULL){
		struct movie *newNode = createMovie(buffer);

		if(head == NULL){
			head = newNode;
			tail = newNode;
		}
		else{
			tail->next = newNode;
			tail = newNode;
		}
		count2++;
	}

	printf("Processed file movie_sample_1.csv and parsed data for %d movies\n", count2);
	*count = count2;
	fclose(movieFile);

	return head;
}

void printOpt(){
	printf("1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year \n");
	printf("3. Show the title and year of release of all movies in a specific language\n");
	printf("4. Exit from the program\n");
}

int choice(){
	int num;
	while(num <= 0 || num > 4){
		printf("Enter a number between 1-4: ");
		scanf("%d", &num);
		//printf("entered: %d\n", num);
	}

	return num;
}

void year(struct movie *movie){
	int num2;
	bool again = false;

	//printf("num entered %d\n", num2);
	printf("Enter the year for which you want to see movies: ");
	scanf("%d", &num2);

	//keep running if data exists in movies file
	while(movie != NULL){
		//compares movie year to the user input year
		if(movie->year == num2){
			printf("%s\n", movie->title);
			again = true;
		}
		//checks the next movie in the next line
		movie = movie->next;
	}
	
	if(again == false){
		printf("No movies were released in the year %d\n", num2);
	}
}

void compareRate(struct movie *movie){
	struct movie *token = movie;
  bool again = false;

  if(movie->next != NULL){
		movie = movie->next;
    while(movie != NULL){
      if(token->year == movie->year){
				//prevents printing double for best rated movie in same year
        again = true;;

				//compares rating from temp to movie
        if(token->rating > movie->rating){
					//printf("CHECK ");
          printf("%d %.1f %s\n", token->year, token->rating ,token->title);

          break;
        }
				else{
					//printf("CHECK2 ");
          printf("%d %.1f %s\n", movie->year, movie->rating ,movie->title);

          break;
        }
      }
      movie = movie->next;
    }
  }

  if(again == false){
		//printf("CHECK3 ");
    printf("%d %.1f %s\n", token->year, token->rating ,token->title);
  }
}

void ratings(struct movie *movie){
	int year[100];
	int i = 0;
	int j = 0;

	compareRate(movie);
	year[i] = movie->year;
	i++;

	while(movie != NULL){
		for(int k = 0; k < i; k++){
			//compares movie year to a specific movie
			if(movie->year == year[k]){
				j = 1;
			}
		}

		if(j == 1){
			movie = movie->next;
		}

		else{
			compareRate(movie);
			year[i] = movie->year;
			i++;
			movie = movie->next;
		}
		j = 0;
	}
}



void language(struct movie *movie, char lang[], int *valid){
  char movieLang[strlen(movie->languages)];
	char token[strlen(movie->languages)];
  int j = 0;

	//printf("Enter the language for which you want to see movies: ");
	//scanf("%s", lang);

  strcpy(movieLang, movie->languages);
  memmove(movieLang, movieLang + 1, strlen(movieLang));
  movieLang[strlen(movieLang)-1] = '\0';

	for(int k = 0; k < strlen(movie->languages); k++){
		token[k] = '\0';
	}

	j = 0;

  for(int i = 0; i < strlen(movieLang); i++){
    if(movieLang[i] != ';'){
      token[j] = movieLang[i];
      j++;

			if(strcmp(lang, token) == 0){
				printf("%d %s\n", movie->year, movie->title); *valid = 1;
			}
    }

		else{
      for(int k = 0; k < strlen(movie->languages); k++){
				token[k] = '\0';
				}
      j = 0;
    }
  }
}

void check(struct movie *movie, int count, char lang[]) {
  int valid = 0;

	//checks to see if language exists for each movie
	while(movie != NULL) {
		language(movie, lang, &valid);
		movie = movie->next;
	}
	
	if(valid == 0) {
		printf("No data about movies released in %s\n", lang);
	}
}

void inChoice(struct movie *movie, int count){
	char lang[100];
	int num;
	int num2;

	//user option paths
	while(num != 4){
		printOpt();
		num = choice();

		if (num == 1) {
			//printf("in choice 1\n")
			year(movie);
		}

		else if (num == 2){
			//printf("in choice 2\n");
			ratings(movie);
		}

		else if (num == 3){
			//printf("in choice3\n");
			printf("Enter the language for which you want to see movies (Case sensitive. First letter capitalized): ");
			scanf("%s", lang);
			
			check(movie, count, lang);
		}

		else if (num == 4){
			printf("Leaving program\n");
			exit(0);
		}
	}
}

int main(int argc, char *argv[]){
  //int num;
	int count = 0;
	struct movie *movie = readFile(argv[1], &count);

	if (argc < 2) {
		printf("enter the file you want to read\n");
		return EXIT_FAILURE;
	}
	
	inChoice(movie, count);

}