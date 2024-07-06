#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>

void main(){
    int sock_fd;
    struct sockaddr_in serveraddr,clientaddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);

    if (sock_fd < 0){
        printf("Failed to create socket");
        return;
    }
    bind(sock_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("Connected \n");
    char buf[100];
    int len = sizeof(clientaddr);
    recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr*)&clientaddr,&len);
    printf("\n%s\n",buf);
    sendto(sock_fd,"Connected succesfully",sizeof("Connected succesfully"),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
}