#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int sockfd, clientfd;
    socklen_t clen;
    ssize_t messageSize;
    struct sockaddr_in saddr, caddr;
    char message[256];
    unsigned short port = 8782;
    //create socket()
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
    }
    //setsockopt() - reuse address/
    setsockopt(sockfd, SOL_SOCKET,
               SO_REUSEADDR, &(int){ 1 },
               sizeof(int));
    //fcntl() - nonblocking
    int fl = fcntl(sockfd, F_GETFL, 0);
    fl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, fl);
    //bind()
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    if ((bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)) {
        printf("Error binding\n");
    }
    //listen()
    if (listen(sockfd, 5) < 0) {
        printf("Error listening\n");
    }
    while(1){
        clen=sizeof(caddr);
        if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
            printf("Clientfd:%d\n",clientfd);
            printf("Error accepting connection\n");
        }else{
            //fcntl() - nonblocking
            int fl = fcntl(clientfd, F_GETFL, 0);
            fl |= O_NONBLOCK;
            fcntl(clientfd, F_SETFL, fl);
            while (1) {
                //Receive message
                messageSize = recv(clientfd, message, sizeof(message), 0);
                if (messageSize < 0){
                    printf("ERROR reading from socket");
                }else{
                    printf("@@@@@@@@@@@@ Client: %s\n",message);
                }
                //Send message
                scanf("%s",message) ;
                //Close Socket
                if (strcmp(message,"/dc") == 0 ){
                    int count;
                    shutdown(sockfd, 2);
                    close(sockfd);
                    return 0;
                }
                //messageSize = send(clientfd, message, strlen(message), 0);
                //if (messageSize < 0){
                //    printf("ERROR writing to socket");
                //}else{
                //    printf("@@@@@@@@@@@@ Server: %s\n",message);
            }
        }
    }
    
    return 0;
}

