#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int servSock, clntSock;

static const int MAXPENDING = 5;
static const int BUFSIZE = 512;

int SetupUDPServerSocket(const char *service){

    struct addrinfo addrCriteria;

    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_flags = AI_PASSIVE;
    addrCriteria.ai_socktype = SOCK_STREAM;
    
    struct addrinfo *servAddr;

    int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
    if (rtnVal != 0){
        perror("getaddrinfo() falhou\n");
        exit(EXIT_FAILURE);
        }
    int servSock = -1;
    for (struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next){
        servSock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (servSock < 0)
        continue;
        
        if ((bind(servSock, addr->ai_addr, addr->ai_addrlen) == 0) && (listen(servSock, MAXPENDING) == 0)){
            break;
            }

        close(servSock);
        
        servSock = -1;
        }

        freeaddrinfo(servAddr);

        printf("Criei o socket");
        return servSock;
    }

int main(int argc, char const *argv[]){
    if (argc != 2){
        perror("Execucao correta: ./chat-server <porta>\n");
        return EXIT_FAILURE;
    }

    servSock = SetupUDPServerSocket(argv[1]);


}