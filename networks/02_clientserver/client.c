#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <endian.h>
#include <locale.h>

#define MAX_ARGUMENTS 4
#define MAX_FILE_SIZE 133143986176
#define MAX_COUNT_OF_DATA_BLOCKS 133143986
#define NOTHING 0
#define PORT_INDEX 3
#define ADDRESS_INDEX 2
#define FILE_INDEX 1
#define ERROR -1
#define SUCCESS 0
#define DELIM "/"
#define NO_OFFSET 0
#define NO_FLAGS 0
#define NO_BYTES 0
#define SIZE_OF_TERMINATION 1
#define LOCALE "C.UTF-8"

int sendFile(int server, char* filePath);
char* getFileName(char* filePath);
int connectServer(int server, char* node, char* service);
int closeSocket(int server);
int closeFile(int file);

int main(int argc, char** argv){
	if(!setlocale(LC_ALL, LOCALE)){
		fprintf(stderr, "Can't set UTF_8 locale\n");
		return EXIT_FAILURE;
	}
	if(argc < MAX_ARGUMENTS){
		fprintf(stderr, "Too few arguments. Usage: client [file name] [adrress/domen] [port]\n");
		return EXIT_FAILURE;
	}
	int server = socket(AF_INET, SOCK_STREAM, NOTHING);
	if(server == ERROR){
		perror("Can't create socket");
		return EXIT_FAILURE;
	}
	if(connectServer(server, argv[ADDRESS_INDEX], argv[PORT_INDEX]) == ERROR){
		closeSocket(server);
		return EXIT_FAILURE;
	}
	if(sendFile(server, argv[FILE_INDEX]) == ERROR){
		closeSocket(server);
		return EXIT_FAILURE;
	}
	if(closeSocket(server) == ERROR){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int sendFile(int server, char* filePath){
	int file = open(filePath, O_RDONLY);
	if(file == ERROR){
		perror("Can't open file");
		return ERROR;
	}
	char* fileName = getFileName(filePath);
	if(!fileName){
		closeFile(file);
		return ERROR;
	}
	uint16_t nameSize = strlen(fileName);
	if(nameSize == 0){
		closeFile(file);
		return ERROR;
	}
	nameSize = htole16(nameSize);
	uint64_t fileSize = lseek(file, NO_OFFSET, SEEK_END);
	if(fileSize == ERROR){
		perror("Can't get size of file");
		closeFile(file);
		return ERROR;
	}
	fileSize = htole64(fileSize);
	if(lseek(file, NO_OFFSET, SEEK_SET) == ERROR){
		perror("Can't return to beginning of file");
		closeFile(file);
		return ERROR;
	}
	if(send(server, &nameSize, sizeof(nameSize), NO_FLAGS) == ERROR){
		perror("Can't send size of file name");
		closeFile(file);
		return ERROR;
	}
	if(send(server, fileName, nameSize, NO_FLAGS) == ERROR){
		perror("Can't send file name");
		closeFile(file);
		return ERROR;
	}
	if(send(server, &fileSize, sizeof(fileSize), NO_FLAGS) == ERROR){
		perror("Can't send size file size");
		closeFile(file);
		return ERROR;
	}
	char data[MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS];
	ssize_t bytes = read(file, data, sizeof(char) * (MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS));
	while(bytes > NO_BYTES){
		if(send(server, data, (size_t)bytes, NO_FLAGS) == ERROR){
			perror("Can't send block of file");
			closeFile(file);
			return ERROR;
		}
		bytes = read(file, data, (size_t)(MAX_FILE_SIZE / MAX_COUNT_OF_DATA_BLOCKS));
	}
	if(bytes == ERROR){
		perror("Can't read file");
		closeFile(file);
		return ERROR;
	}
	uint8_t successCode;
	if(recv(server, &successCode, sizeof(successCode), NO_FLAGS) == ERROR){
		perror("Can't recieve success code");
		closeFile(file);
		return ERROR;
	}
	if(successCode == ERROR){
		fprintf(stderr, "Server failed\n");
		closeFile(file);
		return ERROR;
	}
	printf("Server success\n");
	if(closeFile(file) == ERROR){
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

int connectServer(int server, char* node, char* service){
	struct addrinfo *address;
	int code = getaddrinfo(node, service, NULL, &address);
	if(code != SUCCESS){
		fprintf(stderr, "Can't get information about server: %s\n", gai_strerror(code));
		return ERROR;
	} else if(!address) {
		fprintf(stderr, "Can't find such server: %s %s\n", node, service);
		return ERROR;
	}
	if(connect(server, address->ai_addr, address->ai_addrlen) == ERROR){
		perror("Can't connect to server");
		freeaddrinfo(address);
		return ERROR;
	}
	return SUCCESS;
}

int closeSocket(int server){
	if(close(server) == ERROR){
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
