#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>

typedef struct {
    int type; // 0 = seq , 1 = ack
    int no; // based on type can be seqno or ackno
}frame; 

void main(){
    int sock_fd,client_sock_fd;
    struct sockaddr_in serveraddr,clientaddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

    if (sock_fd < 0){
        printf("Failed to create socket");
        return;
    }
    bind(sock_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(sock_fd,5);
    client_sock_fd = accept(sock_fd,NULL,NULL);
    if (client_sock_fd > 0){
        int frameno = 1,k;
        frame f;
        printf("Connected \n");
        recv(client_sock_fd,&k,sizeof(k),0);
        printf("Recieving %d frames\n",k);
        while(frameno <= k){
            printf("Waiting for frame %d\n",frameno);
            recv(client_sock_fd,&f,sizeof(f),0);
            if (f.no == frameno){
                printf("Frame %d receieved\n",f.no);
                frame ack;
                ack.type = 1;
                ack.no = f.no+1;
                if(frameno%3 != 0){
                    send(client_sock_fd,&ack,sizeof(ack),0);
                    printf("Send ack for frame %d \n",f.no);
                }
                frameno++;
            }else if(f.no < frameno){
                printf("\nDuplicate packet %d, discarded\n",f.no);
                frame ack;
                ack.type = 1;
                ack.no = f.no+1;
                send(client_sock_fd,&ack,sizeof(ack),0);
            }
        }
    }
}