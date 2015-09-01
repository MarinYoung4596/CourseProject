/**
 * sys.h
 */
#ifndef SYS_H
#define SYS_H
#include "unp.h"

ssize_t Send(int sockfd, const void *buf, size_t len, int flags)
{
	int nSend;
	nSend = send(sockfd, buf, len, flags);
	if (nSend == -1)
	{
		perror("send error!");
		exit(1);
	}
	return nSend;
}

ssize_t Recv(int sockfd, void *buf, size_t len, int flags)
{
	int nRecv;
	nRecv = recv(sockfd, buf, len, flags);
	if (nRecv == -1)
	{
		perror("recv error!");
		exit(1);
	}
	return nRecv;
}

ssize_t Write(int sockfd, const void *buf, size_t len)
{
	int nWrite;
	nWrite = write(sockfd, buf, len);
	if (nWrite == -1)
	{
		perror("write error!");
		exit(1);
	}
}

ssize_t Read(int sockfd, void *buf, size_t len)
{
	int nRead;
	nRead = read(sockfd, buf, len);
	if (nRead == -1)
	{
		perror("read error!");
		exit(1);
	}
	return nRead;
}

#endif
