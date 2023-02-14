#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include <netinet/in.h>

#define MAX 70001

void error(char* msg) {
  perror(msg);
  exit(0);
}

//GETS FILE LENGTH
int getFileLen(char *fname){
	int len = 0;
	int chr;

	FILE* file = fopen(fname, "r");
	while(1){
		chr = fgetc(file);
		if(chr == EOF || chr == '\n'){
			break;
		}
		//CHECK FOR INVALID CHARACTERS
		else if(!isupper(chr) && chr != ' '){
			error("Invalid characters\n");
			exit(1);
		}
		else{
			len++;	
		}
	}
	fclose(file);
	//printf("%s has length of %d\n", fname, len);
	return len;
}



//given example code
void setupAddressStruct(struct sockaddr_in* address, int portNumber, char* hostname) {
  memset((char*) address, '\0', sizeof(*address)); 
  address->sin_family = AF_INET;
  address->sin_port = htons(portNumber);
  struct hostent* hostInfo = gethostbyname(hostname); 
  if(hostInfo == NULL) { 
    printf("CLIENT: ERROR, no such host\n"); 
    exit(1); 
  }
  memcpy((char*) &address->sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
}

int main(int argc, char **argv){
	int fileLen = getFileLen(argv[1]);
	int keyLen = getFileLen(argv[2]);
	
	int socketFD, portNumber, charsWritten, charsRead;
  	struct sockaddr_in serverAddress;
  	char buffer[MAX];

	long int msgSize, keySize;

	if(argc != 4){
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}

	if(fileLen > keyLen){
		error("Key length is too short\n");
	}

	portNumber = atoi(argv[3]);
	//printf("port = %d", portNumber);

	// Create a socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); 
	if(socketFD < 0){
		error("CLIENT: ERROR opening socket");
	}

	// Set up the server address struct
	setupAddressStruct(&serverAddress, portNumber, "localhost");

	// Connect to server
	if(connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
		error("CLIENT: ERROR connecting");
	}


	//OPEN PLAINTEXT 
	FILE* plaintext;
	char* line = NULL;
	size_t len = 0;
	ssize_t readLine;
	char msgSIzeA[MAX];

	plaintext = fopen(argv[1], "r");
	readLine = getline(&line, &len, plaintext);
	char msg[strlen(line)];
	strcpy(msg, line);
	fclose(plaintext);

	//OPEN KEY FILE
	FILE* keyFile;
	char* line2 = NULL;
	size_t len2 = 0;
	ssize_t readFile2;
	char keySizeA[MAX];

	keyFile = fopen(argv[2], "r");
	readFile2 = getline(&line2, &len2, keyFile);
	char key[strlen(line2)];
	strcpy(key, line2);
	fclose(keyFile);
	
	//SEND PLAINTEXT TO SERVER
	charsWritten = send(socketFD, msg, strlen(msg), 0);
	if(charsWritten < 0){
		error("CLIENT: ERROR writing to socket");
	}
	if(charsWritten < strlen(msg)){
	printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	//READS PLAINTEXT
	charsRead = read(socketFD, msg, MAX);
	if(charsRead < 0){
		error("CLIENT: ERROR reading from socket");
	}
  	//printf("CLIENT: %s", msg);

	//SENDS KEY TEXT
	charsWritten = send(socketFD, key, strlen(key), 0);
	if(charsWritten < 0){
		error("CLIENT: ERROR writing to socket");
	}
	
	if(charsWritten < strlen(key)){
		printf("CLIENT: WARNING: Not all data written to socket!\n");
	}

	//READS ENCRYPTED
	char finalenc[MAX];
	charsRead = read(socketFD, finalenc, MAX);
	if(charsRead < 0){
		error("CLIENT: ERROR reading from socket");
	}
	printf("%s", finalenc);

	close(socketFD); // Close the socket
	return 0;
}