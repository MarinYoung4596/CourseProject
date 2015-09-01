/**
 * unp.h
 */
#ifndef UNP_H
#define UNP_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 50
#define MAX_LEN 15 /* max length of name & password*/
#define SERV_PORT 8000
#define BACKLOG 20 /* listen */
#define MAX_USER 20

#ifndef ERROR
#define ERR_USER_EXIST -1
#define ERR_ALREADY_LOGIN -1
#define ERR_PASSWORD -1
#define ERR_USER_NOT_EXIST -1
#define ERR_USER_NOT_FOUND -1
#define ERR_USER_BUSY -1
#define ERR_CMD -1
#endif

#ifndef BOOL
#define TRUE 1
#define FALSE 0
#endif

enum USER_STATE
{
	OFFLINE = 0, ONLINE, CALLING, TALKING
};

struct USER
{
	char name[MAX_LEN];
	//char pwd[MAX_LEN];
	enum USER_STATE status;/*status: 0:OFFLINE, 1:ONLINE, 2:CALLING, etc*/
	int sockfd;
	//struct USER *next;
};

/* server.c */
void userInitial();
int regist(int );
int login(int );
int addUser(int , const char *);
void delUser(int );
int sendUserList(int );
char *getSockName(int );
int selChatObj(int , const char *);
int sendChatReq(int , int );
int transMsg(int , int );

/* client.c */
void str_cli(FILE *, int );

/* sys.h */
ssize_t Send(int , const void *, size_t , int );
ssize_t Recv(int , void *, size_t , int );

ssize_t Write(int , const void *, size_t );
ssize_t Read(int , void *, size_t );

#endif
