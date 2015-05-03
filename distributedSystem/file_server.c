/*
 * file_server.c
 * Code By MarinYoung@163.com
 * Last Modified: 2015/5/1
 */
#include <netinet/in.h>	// sockaddr_in
#include <sys/socket.h>	// socket
#include <sys/types.h>	// socket
#include <string.h>		// bzero, memset
#include <stdio.h>
#include <stdlib.h>		// exit


#define BACKLOG 20		// thread listen
#define SERV_PORT 8000
#define MAX_SIZE 1024
#define FILE_NAME_SIZE 512

int main(int argc, char **argv)
{
	/*set address*/
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERV_PORT);
	
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		printf("Socket create error!\n");
		exit(1);
	}

	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("Bind error!\n");
		close(server_socket);
		exit(1);
	}
	printf("Bind ok!\n");

	if (listen(server_socket, BACKLOG) == -1)
	{
		printf("Listen error!\n");
		close(server_socket);
		exit(1);
	}
	printf("Listening...\n");

	while(1)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);

		int connect_fd = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
		if (connect_fd == -1)
		{
			printf("Server accept failed!\n");
			break;
		}

		char buffer[MAX_SIZE];
		memset(buffer, '\0', strlen(buffer));
		int len =  recv(connect_fd, buffer, MAX_SIZE, 0);
		if (len < 0)
		{
			printf("Server receive data failed!\n");
			break;
		}

		char *file_name = (char *)malloc(len);
		strncpy(file_name, buffer, len);
		
		FILE *fp = fopen(file_name, "w");
		if (fp == NULL)
		{
			printf("open file %s failed!\n", file_name);
			close(connect_fd);
			exit(1);
		}
		// else
		bzero(buffer, MAX_SIZE);
		while((len = recv(connect_fd, buffer, MAX_SIZE, 0)) > 0)
		{
			if (fwrite(buffer, sizeof(char), len, fp) < len)
			{
				printf("file\t%s write failed!\n", file_name);
				break;
			}
			bzero(buffer, MAX_SIZE);
		}
		printf("%s uploaded!\n", file_name);
		
		fclose(fp);
		free(file_name);
		close(connect_fd);
	}
	close(server_socket);
	
	return 0;
}
