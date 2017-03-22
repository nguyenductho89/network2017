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
int main(){
    struct hostent* h;
    h = gethostbyname("google.com.vn");
    printf( "IP Address: %s ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[0])));
    return 0;
}
