#include<iostream>
#include<jni.h>
#include "ClientJNI.h"
#include <string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>


using namespace std;

JNIEXPORT void JNICALL Java_ClientJNI_request_1token
  (JNIEnv *env, jobject thisObject, jstring ip_port) {
    const char* ip_portCharPointer = env->GetStringUTFChars(ip_port, NULL);
    string ip_port_combined = ip_portCharPointer;
    string ip_addr, port;
    string delimiter = ":";
    size_t pos = 0;
    string token;
    while ((pos = ip_port_combined.find(delimiter)) != std::string::npos) {
        token = ip_port_combined.substr(0, pos);
        ip_addr = token;
        ip_port_combined.erase(0, pos + delimiter.length());
    }
    port = ip_port_combined;
    const char * ip_addr_cc = ip_addr.c_str();

    char buffer1[256], buffer2[256];
    struct sockaddr_in my_addr, my_addr1;
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    printf("Error in client creating\n");
    else
        printf("Client Created\n");
         
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(stoi(port));
    my_addr.sin_addr.s_addr = inet_addr(ip_addr_cc);
    my_addr1.sin_family = AF_INET;
    my_addr1.sin_addr.s_addr = INADDR_ANY;
    my_addr1.sin_port = htons(stoi(port));
    my_addr1.sin_addr.s_addr = inet_addr(ip_addr_cc);
    if (bind(client, (struct sockaddr*) &my_addr1, sizeof(struct sockaddr_in)) == 0)
        printf("Binded Correctly\n");
    else
        printf("Unable to bind\n");
     
    socklen_t addr_size = sizeof my_addr;
    int con = connect(client, (struct sockaddr*) &my_addr, sizeof my_addr);
    if (con == 0)
        printf("Client Connected\n");
    else
        printf("Error in Connection\n");
 
    strcpy(buffer2, "Request for token");
    send(client, buffer2, 256, 0);
    recv(client, buffer1, 256, 0);
    printf("Server : %s\n", buffer1);
}