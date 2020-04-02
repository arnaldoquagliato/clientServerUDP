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
    addrCriteria.ai_socktype = SOCK_DGRAM;
    addrCriteria.ai_protocol = IPPROTO_UDP;
    
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
        
        if (bind(servSock, addr->ai_addr, addr->ai_addrlen) == 0){
            break;
            }

        close(servSock);
        
        servSock = -1;
        }

        freeaddrinfo(servAddr);

        printf("Criei o socket");
        return servSock;
    }



void HandleTCPClient(int clntSocket){
    char buffer[BUFSIZE];
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    ssize_t numBytesSent, numBytesRcvd;
    ssize_t fromlen;
    fromlen = sizeof(&addr)
    while (true){
        numBytesRcvd = recvfrom(clntSocket, buffer, BUFSIZE, 0, &addr, fromlen)
        if (numBytesRcvd < 0){
            perror("recv() falhou\n");
            exit(EXIT_FAILURE);
            }
        fputs("Client: ", stdout);
        fputs(buffer, stdout);
        fputc(’\n’, stdout);
        fputs("Server: ", stdout);
        read = getline(&line, &len, stdin);
        numBytesSent = sendto(clntSocket, line, len, 0, sockaddr, socklen_t addr_len);
        if (numBytesSent < 0){
            perror("send() falhou\n");exit(EXIT_FAILURE);
            }
        if (strcmp(line, "exit\n") == 0){
            free(line);
            break;
            }
        }
    }



int main(int argc, char const *argv[]){
    if (argc != 2){
        perror("Execucao correta: ./chat-server <porta>\n");
        return EXIT_FAILURE;
    }

    servSock = SetupUDPServerSocket(argv[1]);

    clntSock = HandleTCPClient(servSock);

    close(servSock);
    close(clntSock);

    return 0;

}