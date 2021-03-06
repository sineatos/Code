#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while (fgets(sendline, MAXLINE, fp) != NULL){
		write(sockfd, sendline, strlen(sendline));
		if (read(sockfd, recvline, MAXLINE) < 0)
			perror("str_cli: server terminated prematurely");

		fputs(recvline, stdout);
	}
}
int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	if (argc != 2)
		perror("usage: tcpcli <IPaddress>");
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9877);
	inet_pton(AF_INET,argv[1], &servaddr.sin_addr);
	connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	exit(0);
    return 0;
}
