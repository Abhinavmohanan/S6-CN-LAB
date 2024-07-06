#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>

int main(){
    int sock_fd;
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if (sock_fd < 0){
        printf("Failed to create socket");
        return 0;
    }
    if (connect(sock_fd,((struct sockaddr*) &serveraddr),sizeof(serveraddr)) != -1){
        send(sock_fd,"Hello from client",sizeof("Hello from client"),0);
        char buf[100];
        recv(sock_fd,buf,sizeof(buf),0);
        printf("\n%s\n",buf);
    }else{
        printf("Failed to connect");
    }

    return 0;
}