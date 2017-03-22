//
//  main.c
//  
//
//  Created by Nguyễn Đức Thọ on 3/22/17.
//
//

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
//int main(){
//    struct hostent* h;
//    h = gethostbyname("google.com.vn");
//    printf( "IP Address: %s ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
//    return 0;
//}
int main( int argc, char *argv[] ) {
    int i;
    
    char hostName[100];
    
    if ( argc == 1 ) {
        printf("Nhap hostname\n");
        scanf("%s",hostName);
            struct hostent* h;
            h = gethostbyname(hostName);
        printf( "IPAddress of :%s",hostName );
            printf( "\n %s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
    } else {
        printf( "IPAddress of :%s",argv[1] );
        
            struct hostent* h;
            h = gethostbyname(argv[1]);
            printf( "\n%s\n ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
    }
    
    return 0;
}
