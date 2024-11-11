#include <iostream>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

// int getaddrinfo(const char *node, ex: "www.example.com" or IP
//                 const char  *service, ex: "http" or port number
//                 const struct addrinfo *hints,  have some infos to fill as needed
//                 struct addrinfo **res); pointer to a linked list to the addresses list

int main(int argc, char *argv[]){
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];//ver 

    if(argc!=2){
        cerr<<"usage: showip hostname\n"; //cerr is to cout errors
    }
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if( (status = getaddrinfo(argv[1],NULL,&hints,&res)) !=0 ){
        cerr<<"getaddrinfo:"<<gai_strerror(status)<<"\n"; //addr and name of the error
    }

    cout<<"IP addr for:"<<argv[1]<<"\n";

    for(p = res;p != NULL;p = p->ai_next){
        void *addr;
        string ipver;

        if(p->ai_family == AF_INET){ //IPV4
            struct  sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }else{
            struct  sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        //convert ip to string and print
        inet_ntop(p->ai_family,addr,ipstr,sizeof ipstr);
        cout<<ipver<<":"<<ipstr<<"\n";
    }

    freeaddrinfo(res);

    return 0;
}