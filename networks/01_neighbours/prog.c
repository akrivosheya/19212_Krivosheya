#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>

#define PORT 4321
#define LOOP_BACK "127.0.0.1"
#define LOOP_BACK6 1
#define SUCCESS 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define FIRST_GENERATION 1
#define TIME_FOR_GENERATION 5
#define TIMEOUT 1

typedef struct relatives{
	int ID;
	int currentGeneration;
	struct relatives *next;
} relatives_t;

int configSocket(int sock, char* multGroup);
int configSocket6(int sock, char* multGroup);
int checkList(relatives_t **current, int ID, int generationToDestroy, int *changedList);
void destroyOldGeneration(relatives_t **current, int generationToDestroy, int *changed);
void printList(relatives_t *current);
void freeList(relatives_t *current);
void searchRelatives(char* addr);
void searchRelatives6(char* addr);

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr, "Wrong arguments!\nUsage: a.out [multicast address]\n");
		return 0;
	}
	if(argv[1][0] == 'f' || argv[1][0] == 'F'){
		searchRelatives6(argv[1]);
	}
	else{
		searchRelatives(argv[1]);
	}
	return 0;
}

void searchRelatives(char* addr){
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("Can't create socket");
		return;
	}
        if(!configSocket(sock, addr)){
		perror("Can't config socket");
		return;
	}
	struct sockaddr_in group;
	group.sin_family = AF_INET;
	group.sin_addr.s_addr = inet_addr(addr);
	group.sin_port = htons(PORT);
	int noErrors = TRUE;
	int generationToDestroy = !FIRST_GENERATION, currentGenerationTime = 0, changedList = FALSE;
	int ID, selfID = time(NULL);
	printf("self %d\n", selfID);
	relatives_t *list = NULL;
	time_t begin;
	while(noErrors){
		if(currentGenerationTime > TIME_FOR_GENERATION){
		destroyOldGeneration(&list, generationToDestroy, &changedList);
			if(changedList){
				printList(list);
				changedList = !changedList;
			}
			generationToDestroy = !generationToDestroy;
			currentGenerationTime = 0;
		}
		if(sendto(sock, &selfID, sizeof(selfID), 0, (struct sockaddr*)&group, sizeof(group)) < 0){
			perror("Can't send datagramms");
			break;
		}
		begin = time(NULL);
		while(time(NULL) - begin < TIMEOUT){
			if(recv(sock, &ID, sizeof(ID), 0) < 0 && errno != EAGAIN){
				perror("Can't read socket");
				noErrors = !noErrors;
				break;
			}
			else{
				if(ID != selfID){
					if(!checkList(&list, ID, generationToDestroy, &changedList)){
						fprintf(stderr, "Can't work anymore with list: no memory\n");
						break;
					}
					if(changedList){
						printList(list);
						changedList = !changedList;
					}
				}
			}
		}
		++currentGenerationTime;
	}
	close(sock);
	freeList(list);
}

void searchRelatives6(char* addr){
	int sock = socket(AF_INET6, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("Can't create socket");
		return;
	}
        if(!configSocket6(sock, addr)){
		perror("Can't config socket");
		return;
	}
	struct sockaddr_in6 group = {AF_INET6, htons(PORT)};
	inet_pton(AF_INET6, addr, &group.sin6_addr);
	int noErrors = TRUE;
	int generationToDestroy = !FIRST_GENERATION, currentGenerationTime = 0, changedList = FALSE;
	int ID, selfID = time(NULL);
	printf("self %d\n", selfID);
	relatives_t *list = NULL;
	time_t begin;
	while(noErrors){
		if(currentGenerationTime > TIME_FOR_GENERATION){
			destroyOldGeneration(&list, generationToDestroy, &changedList);
			if(changedList){
				printList(list);
				changedList = !changedList;
			}
			generationToDestroy = !generationToDestroy;
			currentGenerationTime = 0;
		}
		if(sendto(sock, &selfID, sizeof(selfID), 0, (struct sockaddr*)&group, sizeof(group)) < 0){
			perror("Can't send datagramms");
			break;
		}
		begin = time(NULL);
		while(time(NULL) - begin < TIMEOUT){
			if(recv(sock, &ID, sizeof(ID), 0) < 0 && errno != EAGAIN){
				perror("Can't read socket");
				noErrors = !noErrors;
				break;
			}
			else{
				if(ID != selfID){
					if(!checkList(&list, ID, generationToDestroy, &changedList)){
						fprintf(stderr, "Can't work anymore with list: no memory\n");
						break;
					}
					if(changedList){
						printList(list);
						changedList = !changedList;
					}
				}
			}
		}
		++currentGenerationTime;
	}
	close(sock);
        freeList(list);
}

int configSocket(int sock, char* multGroup){
	struct timeval timeOut;
	timeOut.tv_sec = TIMEOUT;
	timeOut.tv_usec = 0;
	if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeOut, sizeof(timeOut)) < 0){
		close(sock);
		return ERROR;
	}

	struct in_addr localInterf;
	localInterf.s_addr = inet_addr(LOOP_BACK);
	if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterf, sizeof(localInterf)) < 0){
		close(sock);
		return ERROR;
	}

	int reuse = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0){
		close(sock);
		return ERROR;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		close(sock);
		return ERROR;
	}

	printf("%s\n", multGroup);

	struct ip_mreq group;
	group.imr_multiaddr.s_addr = inet_addr(multGroup);
	group.imr_interface.s_addr = inet_addr(LOOP_BACK);
	if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&group, sizeof(group)) < 0){
		close(sock);
		return ERROR;
	}

	return SUCCESS;
}

int configSocket6(int sock, char* multGroup){
	struct timeval timeOut;
	timeOut.tv_sec = TIMEOUT;
	timeOut.tv_usec = 0;
	if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeOut, sizeof(timeOut)) < 0){
		close(sock);
		return ERROR;
	}

	int reuse = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0){
		close(sock);
		return ERROR;
	}

	struct sockaddr_in6 address = {AF_INET6, htons(PORT)};
	if(bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0){
		close(sock);
		return ERROR;
	}

	struct ipv6_mreq group;
	group.ipv6mr_interface = 1;
	inet_pton(AF_INET6, multGroup, &group.ipv6mr_multiaddr);
	if(setsockopt(sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &group, sizeof(group)) < 0){
		close(sock);
		return ERROR;
	}
	printf("OK\n");

	return SUCCESS;
}

int checkList(relatives_t **current, int ID, int generationToDestroy, int *changedList){
	if(!(*current)){
		*current = (relatives_t*)malloc(sizeof(relatives_t));
		if(!(*current)){
			return ERROR;
		}
		(*current)->ID = ID;
		(*current)->currentGeneration = !generationToDestroy;
		(*current)->next = NULL;
		*changedList = TRUE;
	}
	else if((*current)->ID == ID){
		(*current)->currentGeneration = !generationToDestroy;
	}
	else{
		return checkList(&((*current)->next), ID, generationToDestroy, changedList);
	}
	return SUCCESS;
}

void destroyOldGeneration(relatives_t **current, int generationToDestroy, int *changed){
	if(!(*current)){
		return;
	}
	if((*current)->currentGeneration == generationToDestroy){
		relatives_t *toFree = *current;
		*current = (*current)->next;
		free(toFree);
		destroyOldGeneration(current, generationToDestroy, changed);
		*changed = TRUE;
	}
	else{
		destroyOldGeneration(&((*current)->next), generationToDestroy, changed);
	}
	return;
}

void printList(relatives_t *current){
	printf("\n");
	if(!current){
		printf("But nobody came...\n");
		return;
	}
	printf("New list:\n");
	for(; current; current = current->next){
		printf("%d\n", current->ID);
	}
	return;
}

void freeList(relatives_t *garbage){
	for(; garbage; garbage = garbage->next){
		free(garbage);
	}
}
