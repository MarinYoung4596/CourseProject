/**
 * client.c
 */
#include "unp.h"
#include "sys.h"

#ifndef SERV_ADDR
#define SERV_ADDR "127.0.0.1"
#endif

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serverAddr;
	
	if (argc != 2)
	{
		printf("usage: ./client <ipaddress>\n");
    	exit(0);
	}
	/* create a new Socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket error!");
		exit(1);
	}
	/* set address */
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; //IPv4 protocol
	serverAddr.sin_port = htons(SERV_PORT);
	//serverAddr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	if (inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
    }
	/* connect */
	int errConnect = connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (errConnect < 0)
	{
		perror("connect error!");
		exit(1);
	}
	/* if object accepted */
	str_cli(stdin, sockfd);
	
	/* close socket */
	close(sockfd);
	return 0;
}

void str_cli(FILE *fp, int sockfd)
{
	char sendBuff[BUFF_SIZE], recvBuff[BUFF_SIZE];
	int maxfd, errSel, stdinEOF;
	fd_set rset;
	int n;
	
	stdinEOF = 0;
	FD_ZERO(&rset);
	for ( ; ; )
	{	
		memset(sendBuff, 0, sizeof(sendBuff));
		memset(recvBuff, 0, sizeof(recvBuff));
		
		if (stdinEOF == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfd = fileno(fp) > sockfd ? fileno(fp) : sockfd;
		errSel = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (errSel < 0)
		{
			perror("sel error!");
			exit(1);
		}
		if (FD_ISSET(sockfd, &rset)) /* socket is readable */
		{
			n = Read(sockfd, recvBuff, BUFF_SIZE);
			if (n == 0)
			{
				if (stdinEOF == 1) 
					return; /* normal termination */
				else 
				{
					printf("str_cli: server terminated prematurely");
					return;
				}
			}
			Write(fileno(stdout), recvBuff, n);
		}
		if (FD_ISSET(fileno(fp), &rset)) /* input is readable */
		{
			n = Read(fileno(fp), sendBuff, BUFF_SIZE);

			if (n == 0)
			{
				stdinEOF = 1;
				shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			Write(sockfd, sendBuff, n) == -1;
		}
	}
}
