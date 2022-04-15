#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <locale.h>

#define NOTHING 0
#define NO_FLAGS 0
#define NO_BYTES 0
#define FIRST_ELEMENT 0
#define FIRST_ITERATION 0
#define PORT_INDEX 1
#define MIN_ARGUMENTS 2
#define ERROR -1
#define SUCCESS 0
#define MAX_QUEUE 10
#define TRUE 1
#define MAX_FILE_SIZE 133143986176
#define MAX_COUNT_OF_DATA_BLOCKS 133143986
#define MAX_NAME_SIZE 4096
#define LOADING_PERIOD 3
#define UPLOADS_PATH "./uploads/"
#define UPLOADS_PATH_SIZE 10
#define TERMINATION '\0'
#define SIZE_OF_TERMINATION 1
#define DELIM "/"
#define LOCALE "C.UTF-8"

void* loadFile(void* voidClinet);
int closeSocket(int sock);
int closeFile(int file);
void createPathName(char* pathName, char* fileName);
int loadFileName(int client, char* fileName, ssize_t *currentBytes, ssize_t *totalBytes, time_t primaryBegin, time_t *currentBegin, uint16_t nameSize);
int recFile(int client, int file, ssize_t *currentBytes, ssize_t *totalBytes, uint64_t remainBytes, time_t *currentBegin, time_t primaryBegin, ssize_t *writtenBytes);
char* getFileName(char* filePath);

int main(int argc, char** argv){
	if(!setlocale(LC_ALL, LOCALE)){
		fprintf(stderr, "Can't set UTF_8 locale\n");
		return EXIT_FAILURE;
	}
	if(argc < MIN_ARGUMENTS){
		perror("Too few argements. Usage: server [port]\n");
		return EXIT_FAILURE;
	}
	int listener = socket(AF_INET, SOCK_STREAM, NOTHING);
	if(listener == ERROR){
		perror("Can't open socket");
		return EXIT_FAILURE;
	}
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[PORT_INDEX]));
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&address, sizeof(address)) == ERROR){
		perror("Can't bind socket");
		closeSocket(listener);
		return EXIT_FAILURE;
	}
	if(listen(listener, MAX_QUEUE) == ERROR){
		perror("Can't make socket listen");
		closeSocket(listener);
		return EXIT_FAILURE;
	}
	int client, code;
	pthread_t someCurrentThread;
	while(TRUE){
		client = accept(listener, NULL, NULL);
		if(client == ERROR){
			perror("Can't make socket listen");
			closeSocket(listener);
			pthread_exit(EXIT_FAILURE);
			return EXIT_FAILURE;
		}
		code = pthread_create(&someCurrentThread, NULL, loadFile, client);
		if(code != SUCCESS){
			perror("Can't make thread for loading");
			pthread_exit(EXIT_FAILURE);
			return EXIT_FAILURE;
		}
	}
	if(closeSocket(listener) == ERROR){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void* loadFile(void* voidClient){
	int client = (int)voidClient;
	uint16_t nameSize;
	time_t primaryBegin, currentBegin;
	ssize_t currentBytes = NO_BYTES, totalBytes = NO_BYTES;
	primaryBegin = currentBegin = time(NULL);
	ssize_t bytes = recv(client, &nameSize, sizeof(nameSize), MSG_WAITALL);
	if(bytes == ERROR){
		closeSocket(client);
		return EXIT_FAILURE;
	}
	nameSize = le16toh(nameSize);
	currentBytes += bytes;
	totalBytes += bytes;
	char fileName[MAX_NAME_SIZE];
	if(loadFileName(client, fileName, &currentBytes, &totalBytes, primaryBegin, &currentBegin, nameSize) == ERROR){
		fprintf(stderr, "Can't recieve file name\n");
		closeSocket(client);
		return EXIT_FAILURE;
	}
	char pathName[UPLOADS_PATH_SIZE + MAX_NAME_SIZE + SIZE_OF_TERMINATION];
	createPathName(pathName, fileName);
	int file = open(pathName, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(file == ERROR){
		perror("Can't open file");
		closeSocket(client);
		return EXIT_FAILURE;
	}
	uint64_t fileSize;
	bytes = recv(client, &fileSize, sizeof(fileSize), MSG_WAITALL);
	if(bytes == ERROR){
		fprintf(stderr, "Can't recieve file size\n");
		closeSocket(client);
		closeFile(file);
		return EXIT_FAILURE;
	}
	fileSize = le64toh(fileSize);
	currentBytes += bytes;
	totalBytes += bytes;
	ssize_t writtenBytes = NO_BYTES;
	if(recFile(client, file, &currentBytes, &totalBytes, fileSize, &currentBegin, primaryBegin, &writtenBytes) == ERROR){
		fprintf(stderr, "Can't recieve file");
		closeSocket(client);
		closeFile(file);
		return EXIT_FAILURE;
	}
	printf("written: %ld\n", writtenBytes);
	uint8_t successCode = (writtenBytes == fileSize) ? SUCCESS : ERROR;
	if(send(client, &successCode, sizeof(successCode), NO_FLAGS) == ERROR){
		perror("Can't send success code");
		closeFile(file);
		closeSocket(client);
		return EXIT_FAILURE;
	}
	time_t end = time(NULL);
	time_t badExpr = currentBytes / (end - currentBegin);
	if(currentBegin == end){
		printf("Without delay: %ld\n", currentBytes);
	}
	else{
		printf("Instant speed: %ld\n", currentBytes / (end - currentBegin));
	}
	if(primaryBegin == end){ 
		printf("Without delay: %ld\n", totalBytes);
	}
	else{
		printf("Average speed: %ld\n", totalBytes / (end - primaryBegin));
	}
	if(closeSocket(client) == ERROR){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void createPathName(char* pathName, char* filePath){
	char path[] = UPLOADS_PATH;
	int i = FIRST_ELEMENT;
	for(; i < UPLOADS_PATH_SIZE; ++i){
		pathName[i] = path[i];
	}
	char* fileName = getFileName(filePath);
	for(int j = FIRST_ITERATION; j < MAX_NAME_SIZE && fileName[j]; ++i, ++j){
		pathName[i] = fileName[j];
	}
	pathName[i] = TERMINATION;
	return;
}

int closeSocket(int sock){
	if(close(sock) == ERROR){
		perror("Can't close socket");
		return ERROR;
	}
	return SUCCESS;
}

int closeFile(int file){
	if(close(file) == ERROR){
		perror("Can't close file");
		return ERROR;
	}
	return SUCCESS;
}

int loadFileName(int client, char* fileName, ssize_t *currentBytes, ssize_t *totalBytes, time_t primaryBegin, time_t *currentBegin, uint16_t nameSize){
	time_t end;
	size_t currentPosition = FIRST_ELEMENT;
	ssize_t bytes = recv(client, fileName + currentPosition, nameSize, MSG_WAITALL);
	while(bytes > NO_BYTES){
		*currentBytes += bytes;
		*totalBytes += bytes;
		nameSize -= bytes;
		currentPosition += bytes;
		if(!nameSize){
			break;
		}
		bytes = recv(client, fileName + currentPosition, nameSize, MSG_WAITALL);
		end = time(NULL);
		if(end - *currentBegin > LOADING_PERIOD){
			printf("Instant speed: %ld\nAverage speed: %ld\n",
				*currentBytes / (end - *currentBegin),
				*totalBytes / (end - primaryBegin));
			*currentBegin = end;
			*currentBytes = NO_BYTES;
		}
	}
	if(bytes == ERROR){
		return ERROR;
	}
	return SUCCESS;
}

int recFile(int client, int file, ssize_t *currentBytes, ssize_t *totalBytes, uint64_t remainBytes, time_t *currentBegin, time_t primaryBegin, ssize_t *writtenBytes){
	char data[MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS];
	ssize_t bytes = recv(client, data, MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS, NO_FLAGS);
	time_t end;
	while(bytes > NO_BYTES){
		*currentBytes += bytes;
		*totalBytes += bytes;
		remainBytes -= bytes;
		end = time(NULL);
		if(end - *currentBegin > LOADING_PERIOD){
			printf("Instant speed: %ld\nAverage speed: %ld\n",
			*currentBytes / (end - *currentBegin),
			*totalBytes / (end - primaryBegin));
			*currentBegin = end;
			*currentBytes = NO_BYTES;
		}
		bytes = write(file, data, bytes);
		if(bytes == ERROR){
			return ERROR;
		}
		*writtenBytes += bytes;
		if(!remainBytes){
			break;
		}
		bytes = recv(client, data, MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS, NO_FLAGS);
	}
	if(bytes == ERROR || remainBytes){
		return ERROR;
	}
	return SUCCESS;
}

char* getFileName(char* filePath){
	char* fileName = strtok(filePath, DELIM);
	char* nextName = strtok(NULL, DELIM);
	while(nextName){
		fileName = nextName;
		nextName = strtok(NULL, DELIM);
	}
	return fileName;
}
