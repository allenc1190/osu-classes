#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LENGTH 2048
#define MAX_ARGS 512

bool check = true;
int stats;
char userInp[MAX_LENGTH];
char inpArr[MAX_ARGS] = {0};
bool checkBg = false;
bool checkSignal = false;
int count;
int count2 = 0;
char *args[MAX_ARGS];
bool checkSig = false;
int procCount = 0;
int bgProc[MAX_ARGS];



//^C
void catchSIGINT(int signo){
	printf(" terminated by signal %d\n", signo);
	fflush(stdout);
}

//^Z
void catchSIGTSTP(){
	if (checkSignal == false){
		checkSig = false;
		checkBg = false;
		checkSignal = true;

		printf(" Entering foreground-only mode (& is now ignored)\n");
		fflush(stdout);
		checkSig = true;
	}
	else{
		checkSignal = false;
		printf(" Exiting foreground-only mode\n");
		fflush(stdout);
		checkSig = true;
	}
}


void execCmd(){
	int idx = 0;
	int idx2 = 0;
	int errCheck = 0;
	bool redir = false;
	int opendir;

	//adding commands to an array
	args[idx] = strtok(userInp, " ");
	while(args[idx] != NULL){
		idx++;
		args[idx] = strtok(NULL, " ");
	}

	//check if user wnats to redirect or not
	while(idx != 0){
		if(strcmp(args[idx2], "<") == 0){
			//open read only
			opendir = open(args[idx2+1], O_RDONLY);
			if(opendir < 0){
				printf("cannot open %s for input\n", args[idx2+1]);
				fflush(stdout);
			}
			else{
				errCheck = 0;
				redir = true;
			}
		}

		else if(strcmp(args[idx2], ">") == 0){
			//open and write file
			opendir = open(args[idx2+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			errCheck = 1;
			redir = true;
		}

		//after redirecting it resets array and all another exec
		if(redir == true){
			dup2(opendir, errCheck);
			args[idx2] = 0;
			execvp(args[0], args);
			close(opendir);
		}

		//resets check values
		idx2 = 1;
		idx--;
		errCheck = 0;
		redir = false;
	}

	//arg doesn't exist
	if((stats=execvp(args[0], args)) != 0){
		printf("%s: no such file or directory\n", userInp);
		exit(stats);
	}
}

//killing proc
void killCmd(){
	for(int i = 0; i < procCount; i++){
		kill(bgProc[i], SIGKILL);
	}
}

void forking(){
	int child = 0;
	
	//spawns child
	pid_t spawnPid = -5;
	spawnPid = fork();

	if(spawnPid == 0){
		if(checkSig == true){
			if(strcmp(userInp, "kill") != 0){
				killCmd();
			}
		}
		execCmd();
	}

	else if(spawnPid < 0){
		printf("Error\n");
		fflush(stdout);
	}

	else{
		//check bg process
		if(checkBg == false){
			waitpid(spawnPid, &child, 0);
			if(WIFEXITED(child)){
				stats = WEXITSTATUS(child);
			}
		}
		else{
			bgProc[procCount] = spawnPid;
			procCount++;

			waitpid(spawnPid, &child, WNOHANG);
			checkBg = false;

			printf("background pid is %d\n", spawnPid);
			fflush(stdout);
		}
	}
}

//checks if bg running
void checkBgProc(){
	char bgArgs[MAX_LENGTH] = {0};
	int length = (strlen(userInp));

	checkBg = true;
	
	strncpy(bgArgs, userInp, length);
	strcpy(userInp, bgArgs);
}

void userInput(){
	//char inpArr[MAX_ARGS] = {0};

	//user input
	strncpy(inpArr, userInp, MAX_ARGS);
	printf(": ");
	fflush(stdout);
	fgets(userInp, sizeof(userInp), stdin);
	
	//remove new line
	userInp[strlen(userInp)-1] = '\0';

	//check if user enters exit
	if(strcmp(userInp, "exit") == 0){
		printf("Exiting program\n");
		check = false;
	}

	//check if user enters status
	else if(strcmp(userInp, "status") == 0){
		printf("exit value %d\n", stats);
		fflush(stdout);
	}

	//check if user enters cd
	else if(strcmp(userInp, "cd") == 0){
		if(args[1] == NULL) {
				chdir(getenv("HOME"));
			} 
			else{
				chdir(args[1]);
			}
			fflush(stdout);
	}

	//check if user enters comment
	else if(strncmp(userInp, "#", 1) == 0 || strcmp(userInp, " ") == 0){
	}

	else{
		forking();
	}

	//reset bg
	checkBg = false;
}


int main(){
	//signal handlers
	struct sigaction sigintt = {0};
	sigintt.sa_handler = catchSIGINT;
	sigfillset(&sigintt.sa_mask);
	sigaction(SIGINT, &sigintt, NULL);

	struct sigaction sigtstpp = {0};
	sigtstpp.sa_handler = catchSIGTSTP;
	sigfillset(&sigtstpp.sa_mask);
	sigaction(SIGTSTP, &sigtstpp, NULL);

	while(check){
		userInput();
		
	}
}