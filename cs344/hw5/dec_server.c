#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX 70001


// Error function used for reporting issues (from example code)
void error(const char *msg) {
  perror(msg);
  exit(1);
} 

// Set up the address struct for the server socket (from example code)
void setupAddressStruct(struct sockaddr_in* address, int portNumber){
 
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);
  // Allow a client at any address to connect to this server
  address->sin_addr.s_addr = INADDR_ANY;
}

//DECRYPTS TEXT
char* decrypt(char* msg, char* key){
  const char bank[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  int msgLength = strlen(msg);
  int keyLength = strlen(key);
  int i = 0;

  char *decryptedMsg = malloc(sizeof(char)* msgLength), afterDecrypt[strlen(msg)-1];

  //printf("\nMSG LEN == %d\nKEY LEN == %d\n", msgLength, keyLength);
  //printf("MSG ==== %s\nKEY==== %s\n", msg, key);


  while(i < msgLength - 1){
    if(msg[i] == ' ' && key[i] == ' '){
      if(((msg[i] - 6) - (key[i] - 6) > 0)){
        afterDecrypt[i] = (bank[((msg[i] - 6) - (key[i] - 6)) %27]);
      }
      else{
        afterDecrypt[i] = (bank[((((msg[i] - 6) - (key[i] - 6)) + 27) % 27)]);
      }
    }

		else if(msg[i] != ' ' && key[i] == ' '){
        if((msg[i] - 65) - (key[i] - 6) > 0){
          afterDecrypt[i] = (bank[((msg[i] - 65) - (key[i] - 6)) % 27]);
        }
        else{
          afterDecrypt[i] = (bank[((((msg[i] - 65) - (key[i] - 6) + 27)) % 27)]);
        }
		}
		
		else if(msg[i] == ' ' && key[i] != ' '){
			if((msg[i] - 65) - (key[i] - 6) > 0){
				afterDecrypt[i] = (bank[((msg[i] - 6) - (key[i] - 65)) % 27]);
			}
			else{
				afterDecrypt[i] = (bank[((((msg[i] - 6) - (key[i] - 65)) + 27) % 27)]);
			}
		}

		else{
			if((msg[i] - 65) - (key[i] - 65) > 0){
				afterDecrypt[i] = (bank[((msg[i] - 65) - (key[i] - 65)) % 27]);
			}
			else{
				afterDecrypt[i] = (bank[((((msg[i] - 65) - (key[i] - 65) + 27)) % 27)]);
			}
		}

    i++;
  }

  afterDecrypt[msgLength - 1] = '\n';
  afterDecrypt[msgLength] = '\0';
  strcpy(decryptedMsg, afterDecrypt);
  //printf("ENCRYPTED == %s\n", encryptedMsg);

  return decryptedMsg;
}


int main(int argc, char *argv[]){
  int connectionSocket, charsRead, charsWritten;
  char buffer[MAX];
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);
  pid_t pid;
  char key[MAX] = "";
  char msg[MAX] = "";
  
  // Check usage & args (from example code)
  if (argc < 2) { 
    fprintf(stderr,"USAGE: %s port\n", argv[0]); 
    exit(1);
  } 
  
  // Create the socket that will listen for connections
  int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    error("ERROR opening socket");
  }

  // Set up the address struct for the server socket
  setupAddressStruct(&serverAddress, atoi(argv[1]));

  // Associate the socket to the port
  if (bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
    error("ERROR on binding");
  }

  // Start listening for connetions. Allow up to 5 connections to queue up
  listen(listenSocket, 5); 
  
  // Accept a connection, blocking if one is not available until one connects
  while(1){
    // Accept the connection request which creates a connection socket
    connectionSocket = accept(listenSocket, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); 
    if(connectionSocket < 0){
      error("ERROR on accept");
    }

    printf("SERVER: Connected to client running at host %d port %d\n", ntohs(clientAddress.sin_addr.s_addr), ntohs(clientAddress.sin_port));
    pid = fork();

    if(pid < 0){
      error("Unable to fork");
    }

    if(pid == 0) {
      //RECEIVE PLAINTEXT
			memset(buffer, '\0', MAX);
			charsRead = recv(connectionSocket, buffer, MAX, 0);
			if(charsRead < 0){
        error("ERROR reading from socket");
      }
      strcpy(msg, buffer);
      //printf("=BUFFER1| %s", buffer);

      //SUCCESS
			charsWritten = write(connectionSocket, "Received enc", 12);
      if(charsWritten < 0){
				error("ERROR writing to client from the server.");
			}

      //RECEIVE KEY
      memset(buffer, '\0', MAX);
			charsRead = recv(connectionSocket, buffer, MAX, 0);
			if(charsRead < 0){
        error("ERROR reading from socket");
      }
      strcpy(key, buffer);

      //SENDING DECRYPTED TO CLIENT
			char* finaldec = decrypt(msg, key);
			//printf("FINALENC == %s\n", finalenc);
			charsRead = write(connectionSocket, finaldec, strlen(finaldec));
			if(charsRead < 0){
        error("ERROR reading from socket");
      }
      //printf("=BUFFER2| %s", buffer);

		}
		close(connectionSocket); // Close the existing socket which is connected to the client
    }
  
  // Close the listening socket
  close(listenSocket); 
  return 0;
}
