#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024
#define FILE_NAME_SIZE 512
#define SERV_PORT 8000

#ifndef SERV_ADDR
#define SERV_ADDR "127.0.0.1"
#endif

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: ./file_client <ipaddress>\n");
		exit(0);
	}
	
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
	}
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
	{
		printf("Create socket failed!\n");
		exit(1);
	}

	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Can't connect to server ip\n");
		exit(1);
	}

	char file_name[FILE_NAME_SIZE];
	memset(file_name, '\0', strlen(file_name));
	printf("Choose the file to upload:\t");
	scanf("%s", file_name);
	
	//debug
	printf("file_name: %s\tlength%d", file_name, strlen(file_name));
	
	int len = 0;
	if ((len = send(client_socket, file_name, strlen(file_name), 0)) < 0)
	{
		printf("Send file name failed!\n");
		exit(1);
	}
	
	
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("file %s not found!\n", file_name);
		close(client_socket);
		exit(1);
	}
	
	char buffer[MAX_SIZE];
	bzero(buffer, MAX_SIZE);
	while ((len = fread(buffer, sizeof(char), MAX_SIZE, fp)) > 0)
	{
		if (send(client_socket, buffer, len, 0) < 0)
		{
			printf("Send file %s failed!\n", file_name);
			break;
		}
		bzero(buffer, strlen(buffer));
	}
	
	close(fp);
	close(client_socket);
	printf("complete!\n");
	return 0;
}
