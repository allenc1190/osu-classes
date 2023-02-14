#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/*
code from HW1 to grab data from file
*/
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
	//printf("TEST\n");
	currMovie->title = calloc(strlen(token) + 1, sizeof(char));
  //printf("%s", currMovie->title);
	strcpy(currMovie->title, token);

	//storing the movie year
	token = strtok_r(NULL, ",", &ptr1);
	//printf("TEST2\n");
  //printf("%s", token);
	currMovie->year = atoi(token);
	

	//storing the movie languages
	token = strtok_r(NULL, ",", &ptr1);
	//printf("TEST3\n");
	currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->languages, token);

	//storing the movie ratings
	token = strtok_r(NULL, ",", &ptr1);
	//printf("TEST4\n");
	currMovie->rating = atof(token);

	currMovie->next = NULL;

	return currMovie;
}

struct movie *readFile(char *filePath){
	char *token;
	char buffer[100];

//printf("\n1. %s\n", filePath);
//printf("TEST5\n");
	token = malloc(100 * sizeof(char));
	strcpy(token, filePath);
	FILE *data = fopen(token, "r");
	
	struct movie *head = NULL;
	struct movie *tail = NULL;

	fgets(buffer, sizeof buffer, data);

	while(fgets(buffer, sizeof buffer, data) != NULL){
		//printf("TEST6\n");
		struct movie *newNode = createMovie(buffer);

		if(head == NULL){
			head = newNode;
			tail = newNode;
		}
		else{
			tail->next = newNode;
			tail = newNode;
		}
	}
	//printf("TEST7\n");

		fclose(data);
		free(token);

	return head;
}

/*
creates text files names based on year and writes data into .txt files
*/
void compare(struct movie *movies, char dirc[]){
	struct movie *token = movies;
  bool again = false;
	char note[100];
  int file;
	char dir_n[100];

  //printf("\n%d\n", token->year);
  
  if(movies->next != NULL) {
    sprintf(dir_n, "%s/%d.txt", dirc, token->year);
    file = open(dir_n, O_RDWR | O_CREAT | O_TRUNC, 0640);

    while(movies != NULL){
      if(token->year == movies->year){
        sprintf(note, "%s\n", movies->title);
        again = true;
        write(file, note, strlen(movies->title) + 1);
      }
      movies = movies->next;
    } 
  }
}

/*
opens up .csv file and grab the year
*/
void createList(char f_csv[], char f_name[]){
  //printf("\n1.|| %s..\n", f_csv);
	struct movie *movies = readFile(f_csv);
	int year[100];
	int a = 0;
	int s = 0;

  //printf("\n1..%s\n ", f_name);

	compare(movies, f_name);
	year[a] = movies->year;
	a++;

	while(movies != NULL){
		for(int i = 0; i < a; i++){
			if(movies->year == year[i]){
				s = 1;
			}
		}

		if(s == 1){
			movies = movies->next;;
		}
		else{
			compare(movies, f_name);
			year[a] = movies->year;
			a++;
			movies = movies->next;
		}
		s = 0;

	}
}

void printOpt(){
	printf("1. Select file to process\n");
	printf("2. Exit the program\n");
}

int choice1(){
	int num;

	printf("Enter a choice 1 or 2: ");
	scanf("%d", &num);
	printf("\n");

	return num;
}

void printOpt2(int num){
	printf("Which file do you want to process?\n");
	printf("Enter 1 to pick the largest file\n");
	printf("Enter 2 to pick the smallest file\n");
	printf("Enter 3 to specify the name of a file\n");
}

int choice2(){
	int num2;

	printf("Enter a choice from 1 to 3: ");
	scanf("%d", &num2);
	printf("\n");

	return num2;
}

/*
creates a new directory based on onid name
*/
char *createDir(){
	DIR* currDir = opendir(".");
	int ran;
	int check;
  int file;

	char *newName = malloc(100);
	char newDir[20] = "chanall.movies.";

	srand(time(NULL));
	ran = rand();
	ran = ran % 100000;

  sprintf(newName, "%s%d", newDir, ran);
	
	check = mkdir(newName, 0750);

	printf("Created directory with the name %s\n", newName);
	
  //printf("%s\n", newName);
	return newName; 	
}

/*
finds the largest sized files in bytes and extracts data from it
*/
void largest(){
	DIR* currDir = opendir(".");
	struct dirent *aDir;
  struct stat byte;
	char *dname;
	unsigned int size = 0;
	int j = 0;

	
	while((aDir = readdir(currDir)) != NULL){
		//printf("1|%s\n", aDir->d_name);
		char token[strlen(aDir->d_name)];
    for(int i = 0; i < 7; i++){
			token[i] = aDir->d_name[i];
		}

		/*
		checks if the first 7 characters are "movies_"
		*/
		if(strcmp("movies_", token) == 0){
			for(int i = 0; i < 6; i++){
				//printf("\n1. %s", &token[i]);
				token[i] = '\0';
			}

			for(int k = strlen(aDir->d_name) - 1; k > strlen(aDir->d_name) - 5; k--){
				token[j] = aDir->d_name[k];
				j++;
			}

			//compares if extension is a .csv file. Reads the characters backwards
			if(strcmp("vsc.", token) == 0){
				if(!stat(aDir->d_name, &byte)){
					if((unsigned int)byte.st_size > size) {
						size = (unsigned int)byte.st_size;
            dname = aDir->d_name;
					}
				}
			}
		}

    /*if (!stat(aDir->d_name, &byte)){
		  printf("\n%s |%u\n", aDir->d_name, (unsigned int)byte.st_size); //byte
    }*/

	}

  char *n = createDir();
  //printf("%s\n", n);
	printf("Now processing the chosen file named %s\n", dname);
	createList(dname, n);

	closedir(currDir);
}

/*
same as large but the opposite
*/
void small(){
	DIR* currDir = opendir(".");
	struct dirent *aDir;
  struct stat byte;
	char *dname;
	unsigned int size = 100000;
	int j = 0;

	
	while((aDir = readdir(currDir)) != NULL){
		//printf("1|%s\n", aDir->d_name);
		char token[strlen(aDir->d_name)];
    for(int i = 0; i < 7; i++){
			token[i] = aDir->d_name[i];
		}

		if(strcmp("movies_", token) == 0){
			for(int i = 0; i < 6; i++){
				//printf("\n1. %s", &token[i]);
				token[i] = '\0';
			}

			for(int k = strlen(aDir->d_name) - 1; k > strlen(aDir->d_name) - 5; k--){
				token[j] = aDir->d_name[k];
				j++;
			}

			if(strcmp("vsc.", token) == 0){
				if(!stat(aDir->d_name, &byte)){
					if((unsigned int)byte.st_size < size) {
						size = (unsigned int)byte.st_size;
            dname = aDir->d_name;

					}
				}
			}
		}

    /*if (!stat(aDir->d_name, &byte)){
		  printf("\n%s |%u\n", aDir->d_name, (unsigned int)byte.st_size); //byte
    }*/
	}

  char *n = createDir();
  //printf("%s\n", n);
	printf("Now processing the chosen file named %s\n", dname);
	createList(dname, n);

	closedir(currDir);
}

/*
gets the file the user wants and creates directory with the txt files in new directory
*/
char checkFile(){
	char *newName = malloc(100);
	char fileName[100];

	printf("Enter the complete file name: ");
	scanf("%s", fileName);
	//printf("\n\n%s\n\n", fileName);

	FILE *movieFile;
	movieFile = fopen(fileName, "r");

	
	if(movieFile){
		printf("Now processing the chosen file named %s\n", fileName);
		char *n = createDir();
		if(movieFile){
		createList(fileName, n);
	}
 
		fclose(movieFile);
	}
	else{
		printf("The file %s was not found. Try again.\n\n", fileName);

	}

	return *fileName;

}

/*
choose largest, smallest, or choose file
*/
void mainChoice(int num2){

	if(num2 == 1){
		//printf("in choice 1\n");
		largest();
		//createDir();
	}
	else if(num2 == 2){
		//printf("in choice 2\n");
		small();
		//createDir();
	}
	else if(num2 == 3){
		//printf("in choice 3\n");
		checkFile();
		//createDir();
	}
}

void inChoice(int num2){
	int num;

	while(num != 2){
		printOpt();
		num = choice1();

		if(num == 1){
			//printf("in choice 1\n");
				printOpt2(num);
				num2 = choice2();
				mainChoice(num2);
		}

		else if(num == 2){
			printf("Leaving program...\n");
			exit(0);
		}
	}
}

int main(int argc, char *argv[]){
	int num2;
	inChoice(num2);
	
}