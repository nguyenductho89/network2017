
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int connectToServer(struct hostent *h ) {
    struct sockaddr_in saddr;
    int sockfd;
    unsigned short port = 8782;
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 0;
    }else{
    printf("Connect successfully!\n");
        return sockfd;
    }
}


int main( int argc, char *argv[] ){
    int i;
    ssize_t messageSize;
    int sockfd;
    char hostName[100];
    struct hostent* h;
    if ( argc == 1 ) {
        printf("Nhap hostname\n");
        scanf("%s",hostName);
        h = gethostbyname(hostName);
        
    } else {
        printf( "IPAddress of :%s",argv[1] );
        h = gethostbyname(argv[1]);
    }
    
    if (h == NULL) {
        printf("Unknown host\n");
    }
    printf( "IPAddress of :%s",hostName );
    printf( "\n%s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
    
    char message[256];
    sockfd = connectToServer(h);
    while (sockfd > 0) {        
        //Send message
        printf("...\n");
        scanf("%s",message) ;
        messageSize = send(sockfd, message, strlen(message), 0);
        if (messageSize < 0){
            printf("ERROR writing to socket");
        }else{
            printf("@@@@@@@@@@@@ Client: %s\n",message);
        }
        
        //Receive message
        messageSize = recv(sockfd, message, sizeof(message), 0);
        if (messageSize < 0){
            printf("ERROR reading from socket");
        }else{
            printf("@@@@@@@@@@@@ Server: %s\n",message);
        }
        
    }
    return 0;
}
