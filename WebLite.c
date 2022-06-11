#include "lib/sock.h"

int main(int argc, char **argv) {

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(80);

	Bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd, 3);

	int n;
	char recvline[5001];
	char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection: keep-alive\nContent-Language: en-US\n\n";
	//char buff3[]="<!DOCTYPE html><body><h1>Hello World!</body></html>";
	char content[1002];
	for( ; ; ){
		int connfd = accept(sockfd, ( struct sockaddr * ) NULL, NULL);
		while( (n = read(connfd, recvline, 5000)) > 0 ) {
			recvline[n] = 0;
			if (fputs(recvline, stdout) == EOF){
				printf("error");
				exit(-1);
			}
			FILE *fptr = fopen(argv[1],"r");
			int cnt=fread(content, sizeof(*content), 1000, fptr);
			content[cnt]=0;
			fclose(fptr);
			write(connfd, header, strlen(header));
			write(connfd, content, strlen(content));
			close(connfd);
		}
		close(connfd);
	}
	return 0;
}
