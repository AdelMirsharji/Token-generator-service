#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TOKEN_LENGTH 20
const char tokenCharSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int tokenCharSetSize = (int)(sizeof(tokenCharSet)-1);
const char printLine[] = "-----------------------------------------------------";

const char *tokenGenerator(int length);

int main(int argc, char *argv[]){
    static int mySeed = 25011984;
    srand(time(NULL) * TOKEN_LENGTH + ++mySeed);
    char ip_addr[64];
    char *port;
    printf("%s\n",printLine);
    if(argc > 1){
        if(!strcmp(argv[1],"--bind")){
            if(argc < 3){
                printf("No ipaddr:port entered!\n");
            } 
            else{
                if(strchr(argv[2],':') != NULL){
                    strtok_r(argv[2], ":" , &port);
                    strcpy(ip_addr,argv[2]);
                    printf("Server is starting to run: ip_addr = %s port = %s\n", ip_addr,port);
                }
                else{
                    printf("Please enter IP ADDRESS and PORT in \"ipaddr:port\" format!\n");
                }
                
            }
        }
        else{
            printf("Unkown command(Use --bind ipaddr:port)\n");
        }
    }
    else{
            printf("No command(Use --bind ipaddr:port)\n");
    }
    // Two buffers for message communication
    char buffer1[256], buffer2[256];
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
        printf("Error in server creating\n");
    else
        printf("Server Created\n");
    struct sockaddr_in my_addr, peer_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    // This ip address will change according to the machine
    my_addr.sin_addr.s_addr = inet_addr(ip_addr);
    my_addr.sin_port = htons(atoi(port));
    if (bind(server, (struct sockaddr*) &my_addr, sizeof(my_addr)) == 0)
        printf("Binded Correctly\n");
    else
        printf("Unable to bind\n");
         
    if (listen(server, 3) == 0)
        printf("Listening ...\n");
    else
        printf("Unable to listen\n");

    printf("%s",printLine);
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    // Ip character array will store the ip address of client
    char *ip;

    // while loop is iterated infinitely to
    // accept infinite connection one by one
    while (1)
    {
        int acc = accept(server, (struct sockaddr*) &peer_addr, &addr_size);
        printf("Connection Established\n");
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, INET_ADDRSTRLEN);
     
        // "ntohs(peer_addr.sin_port)" function is
        // for finding port number of client
        printf("connection established with IP : %s and PORT : %d\n",
                                            ip, ntohs(peer_addr.sin_port));
 
        recv(acc, buffer2, 256, 0);
        printf("Client : %s\n", buffer2);
        strcpy(buffer1, tokenGenerator(TOKEN_LENGTH));
        send(acc, buffer1, 256, 0);
    }
}

const char *tokenGenerator(int length){
    char *randomString = malloc(length+1);
    if(length){
        if(randomString){
            static int index;
            for(int n = 0 ; n < length ; n++){
                index = rand() % tokenCharSetSize;
                randomString[n] = tokenCharSet[index];
            }
            randomString[length] = '\0';
        }
    }
    return randomString;
}