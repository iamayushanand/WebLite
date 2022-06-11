#include "sock.h"

int Socket(int domain, int type, int protocol) {
	int sockfd;
	if((sockfd=socket(domain, type, protocol))<0) {
		printf("Error in socket initialization\n returned: %d\n",sockfd);
		exit(-1);
	}
	return sockfd;
}

int Bind(int sockfd, struct sockaddr* addr, int sz) {
	int n;
	if((n=bind(sockfd,addr, sz))<0) {
		printf("Error occured while binding\n");
		printf("returned: %d",n);
		exit(-1);
	}	
	return n;
}
