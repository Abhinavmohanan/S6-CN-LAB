#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

typedef struct {
    int type; // 0 = seq , 1 = ack
    int no; // based on type can be seqno or ackno
}frame; 

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
    int n;
    if ((n = connect(sock_fd,((struct sockaddr*) &serveraddr),sizeof(serveraddr))) != -1){
        int k;    
        printf("Enter no. of frames :");
        scanf("%d",&k);
        int frameno = 1;
        send(sock_fd,&k,sizeof(k),0);
        while(frameno <= k){
            frame f;
            f.type = 0;
            f.no = frameno;
            printf("Sent frame %d\n",frameno);
            printf("Waiting for ack\n");
            sleep(3);
            if (frameno%2 != 0){
                send(sock_fd,&f,sizeof(f),0);
            }else{
                printf("Packet lost\n");
            }

            if (frameno%3 == 0 || frameno%2 == 0){
                printf("Ack not recieved, resending\n");
                send(sock_fd,&f,sizeof(f),0);
            }
            if (frameno%6 == 0){
                send(sock_fd,&f,sizeof(f),0);
            }
            recv(sock_fd,&f,sizeof(f),0);
            printf("Ack [%d] recieved \n",f.no);
            frameno++;
        }
    }else{
        printf("Failed to connect %d \n ",n);
    }

    return 0;
}