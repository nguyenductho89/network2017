#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

void conectToServer(struct hostent *h) {
    struct sockaddr_in saddr;
    int sockfd;
    unsigned short port = 80;
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        
    }
    
    
}


int main( int argc, char *argv[] ){
    
        int i;
        char hostName[100];
        if ( argc == 1 ) {
            printf("Nhap hostname\n");
            scanf("%s",hostName);
            struct hostent* h;
            h = gethostbyname(hostName);
            if (h == NULL) {
                printf("Unknown host\n");
                
            }
            printf( "IPAddress of :%s",hostName );
            printf( "\n %s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
            
            conectToServer(h);
        } else {
            printf( "IPAddress of :%s",argv[1] );
            struct hostent* h;
            h = gethostbyname(argv[1]);
            if (h == NULL) {
                printf("Unknown host\n");
                
            }
            printf( "\n%s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
            conectToServer(h);
            
            
        }
    
    
      return 0;
}



//int main( int argc, char *argv[] ) {
//    int i;
//    char hostName[100];
//    if ( argc == 1 ) {
//        printf("Nhap hostname\n");
//        scanf("%s",hostName);
//        struct hostent* h;
//        h = gethostbyname(hostName);
//        printf( "IPAddress of :%s",hostName );
//        printf( "\n %s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
//    } else {
//        printf( "IPAddress of :%s",argv[1] );
//        struct hostent* h;
//        h = gethostbyname(argv[1]);
//        printf( "\n%s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
//    }
//    return 0;
