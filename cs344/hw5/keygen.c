#include <stdio.h>
#include <stdlib.h>
#include <time.h>





int main(int argc, char* argv[]) {

	//convert the length to an integer.
	int length = atoi(argv[1]);
	char key[length+1];

	//array of upper case alpha plus the space character
	char* charArr ="ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	char letter;

	//seed the random number generator.
	srand(time(NULL));

	int i;
	
	//make sure the user supplied a length. 
	if(argc != 2){
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}

	else{
		for(i = 0; i < length; i++){
			int num = rand() % 27;
			key[i] = charArr[num];
		}

		key[length] = '\0';

		//print the key with an added newline character.
		printf("%s\n", key); 
		
	return 0;
	}
}