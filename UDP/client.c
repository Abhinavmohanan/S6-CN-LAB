#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>

int main(){
    int sock_fd;
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);
    if (sock_fd < 0){
        printf("Failed to create socket");
        return 0;
    }
    printf("\n Sending msg\n");
    sendto(sock_fd,"Hello from client",sizeof("Hello from client"),0,(struct sockaddr*) &serveraddr,sizeof(serveraddr));
    char buf[100];
    int len = sizeof(serveraddr);
    recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr*) &serveraddr,&len);
    printf("\n%s\n",buf);

    return 0;
}