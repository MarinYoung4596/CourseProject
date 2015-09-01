/**
 *:server.c
 */
 
#include "unp.h"
#include "sys.h"

struct USER user[MAX_USER];	/* array linked list */
int nUser = 0;				/* count of reality user */

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in serverAddr, clientAddr;
    
    char recvBuff[BUFF_SIZE], name[MAX_LEN];
    int i, maxOfI, maxfd;
    fd_set watchset, rset;
    int errSel, errBind;
    int addrSize = sizeof(struct sockaddr_in);
    int isClientLogin = FALSE;/* flag: if client is login */
    int sockfd, dstfd;/* src socket and dst socket of communication objection*/
    
    /* create new socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        perror("Socket create error!");
        exit(1);
    }
    /* set address */
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERV_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* bind */
    errBind = bind(listenfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    if (errBind == -1)
    {
        perror("Bind error!");
        close(listenfd);
        exit(1);
    }
    printf("Bind ok!\n");
    /* listen */
    if (listen(listenfd, BACKLOG) == -1)
    {
        perror("Listen error!");
        close(listenfd);
        exit(1);
    }
    printf("Listening...\n");
    
    maxfd = listenfd;			/* userInitial */
    maxOfI = -1;				/* index into client[] array */
	userInitial(); 
    FD_ZERO(&watchset);			/* clear all bits in watchset */
    FD_SET(listenfd, &watchset);/* turn on the bit for listenfd in watchset */
    
    for( ; ; )
    {
    	rset = watchset;
    	
    	errSel = select(maxfd + 1, &rset, NULL, NULL, NULL);
    	if (errSel < 0)
    	{
    		perror("Server select error!");
    		exit(1);
    	}
    	/* if client connect request arrive (is the bit for listenfd on in rset?) */
    	if (FD_ISSET(listenfd, &rset))
    	{
    		/* create a new socket */
			connfd = accept(listenfd, (struct sockaddr *) &clientAddr, &addrSize);
			printf("\nNew coming socket!\n");
			Send(connfd, "Server connected!\n", 18, 0);
			isClientLogin = FALSE;
			if (connfd == -1)
			{
				perror("Accept error!");
				exit(1);
			}
			for (i = 0; i < MAX_USER; i ++)
			{
				if(user[i].sockfd == -1)
				{
					user[i].sockfd = connfd;/* save descriptor */
					break;
				}
			}
			if (i == MAX_USER)
			{
				printf("Too many users!");
				exit(0);
			}
			
			FD_SET(connfd, &watchset);/* add mew descriptor to set */
			maxfd = maxfd > connfd ? maxfd : connfd; /* for select */
			maxOfI = i > maxOfI ? i : maxOfI;/* max index of connected client */
			
			if (--errSel <= 0)
				continue;
		}
		
		for (i = 0; i <= maxOfI; i++)
		{
			if ( (sockfd = user[i].sockfd) == -1) 
				continue;
			if (FD_ISSET(sockfd, &rset))
			{
				memset(recvBuff, '\0', BUFF_SIZE);
				if (Recv(sockfd, recvBuff, BUFF_SIZE, 0) < 0)
				{
					close(sockfd);
					FD_CLR(sockfd, &watchset);
					user[i].sockfd = -1;
				}
				printf("CMD: %s", recvBuff);
				if (strncmp(recvBuff, "REGIST", 6) == 0)
				{
					regist(sockfd);
				}
				else if (strncmp(recvBuff, "LOGIN", 5) == 0)
				{
					if (isClientLogin == TRUE)
					{
						Send(sockfd, "You're online, can't login!\n", 28, 0);
						continue;
					}
					if (login(sockfd) != TRUE)
						continue;
					isClientLogin = TRUE;
				}
				else if (strncmp(recvBuff, "LIST", 4) == 0)
				{
					sendUserList(sockfd);
				}
				else if (strncmp(recvBuff, "CHAT", 4) == 0)
				{
					Send(sockfd, "NAME: ", 6, 0);
					Recv(sockfd, name, MAX_LEN, 0);
					if ((dstfd = selChatObj(sockfd, name)) < 0)
						continue;
					if (sendChatReq(sockfd, dstfd) != TRUE)
						continue;
					transMsg(sockfd, dstfd);
						
				}
				else if (strncmp(recvBuff, "EXIT", 4) == 0)
				{
					delUser(sockfd);
					FD_CLR(sockfd, &watchset);
					close(sockfd);
				}
				else
				{
					Send(sockfd, "Cmd error!\n", 11, 0);
				}
			}
		}
    }
    close(listenfd);
}

void userInitial()
{
	int i;
	for (i = 0; i < MAX_USER; i++)
    {
    	memset(user[i].name, '\0', MAX_LEN);
    	//memset(user[i].pwd, '\0', MAX_LEN);
    	user[i].status = OFFLINE; 	
    	user[i].sockfd = -1;	/* -1 indicates available entry */
    }
}

int regist(int sockfd)
{
	char recvBuff[BUFF_SIZE];
	char name[MAX_LEN], pwd[MAX_LEN], tmp[MAX_LEN];
	FILE *fp;
	int nRecv;
	
	Send(sockfd, "NAME: ", 6, 0);
	memset(name, '\0', MAX_LEN);
	nRecv = Recv(sockfd, name, MAX_LEN, 0);
	fp = fopen("userData", "r");
	if (fp == NULL)
	{
		perror("Open file error!");
		exit(1);	
	}
	for ( ; fgets(recvBuff, sizeof(recvBuff), fp) != NULL; )
	{
		/* whether user already regist or not */
		if (strncmp(recvBuff, name, nRecv - 1) == 0)
		{
			Send(sockfd, "User exist!\n", 12, 0);
			fclose(fp);
			return ERR_USER_EXIST;
		}
	}
	fclose(fp);
	
	memset(tmp, '\0', sizeof(tmp));
	strncpy(tmp, name, nRecv - 1);/* discard rest of recvBuff: length=MAX_LEN-nRecv */

	Send(sockfd, "PASS: ", 6, 0);
	memset(pwd, '\0', MAX_LEN);
	nRecv = Recv(sockfd, pwd, MAX_LEN, 0);
	
	fp = fopen("userData","a");
	if (fp == NULL)
	{
		perror("Open file error!");
		exit(1);
	}
	memset(recvBuff, '\0', sizeof(recvBuff));
	strcpy(recvBuff, tmp);
	strcat(recvBuff, ":");
	strcat(recvBuff, pwd);
	fputs(recvBuff, fp);/* write user info into fp */
	fclose(fp);
	Send(sockfd, "Regist success!\n", 16, 0);
	return TRUE;
}

int login(int sockfd)
{
	char userName[MAX_LEN], password[MAX_LEN], recvBuff[BUFF_SIZE];
	int nName, nPass, n;
	FILE *fp;
	char *read, *p, *pwd;
	
	Send(sockfd, "NAME: ", 6, 0);
	memset(userName, '\0', sizeof(userName));
	nName = Recv(sockfd, userName, sizeof(userName), 0);
	for (n = nUser; n != 0; n--)
	{
		if (strncmp(user[n].name, userName, sizeof(userName)) == 0)
		{
			Send(sockfd, "You're already login!\n", 22, 0);
			return ERR_ALREADY_LOGIN;
		}
	}
	fp = fopen("userData", "r");
	if (fp == NULL)
	{
		perror("Open file error!");
		exit(1);
	}
	while ((read = fgets(recvBuff, sizeof(recvBuff), fp)) != NULL)
	{
		/* read a single line of fp to recvBuff */
		p = strchr(recvBuff, ':');
		pwd = p + 1;
		*p = '\0';
		if (strncmp(userName, recvBuff, nName - 1) == 0)
		{
			p = strchr(pwd, '\n');/* next line */
			*p = '\0';
			for (n = 0; n < 3; n++)
			{
				Send(sockfd, "PASS: ", 6, 0);
				memset(password, '\0', sizeof(password));
				nPass = Recv(sockfd, password, sizeof(password), 0);
				if (strncmp(password, pwd, nPass - 1) != 0)
				{
					Send(sockfd, "Password error!\n", 16, 0);
					continue;
				}
				Send(sockfd, "Login success!\n", 16, 0);
				addUser(sockfd, userName);
				fclose(fp);
				return TRUE;
			}
			Send(sockfd, "Password error 3 times, exit!\n", 30, 0);
			fclose(fp);
			return ERR_PASSWORD;
		}
	}
	if (read == NULL)
	{
		Send(sockfd, "User not exist, Regist first!\n", 30, 0);
		fclose(fp);
		return ERR_USER_NOT_EXIST;
	}
}

int addUser(int sockfd, const char *name)
{
	strncpy(user[nUser].name, name, strlen(name));
	user[nUser].status = ONLINE;
	user[nUser].sockfd = sockfd;
	nUser++;
	
	return TRUE;
}

void delUser(int sockfd)
{
	int i;
	for (i = nUser; sockfd != user[i].sockfd; i--);
	/* overwrite next user on current position */
	for (; user[i].sockfd != -1 && i < MAX_USER; i++)
	{
		memset(user[i].name, 0, sizeof(user[i].name));
		strcpy(user[i].name, user[i + 1].name);
		//strcpy(user[i].pwd, user[i + 1].pwd);
		user[i].status = user[i + 1].status;
		user[i].sockfd = user[i + 1].sockfd;
	}
	nUser--;
}

int sendUserList(int sockfd)
{
	int i;
	if (nUser == 0)
	{
		Send(sockfd, "No online user!\n", 16, 0);
		return ERR_USER_NOT_FOUND;
	}
	for (i = 0; i < nUser; i++)
	{
		Send(sockfd, user[i].name, sizeof(user[i].name), 0);
	}
	return TRUE;
}

char *getSockName(int sockfd)
{
	int i;
	for (i = nUser; i != 0; i--)
	{
		if (user[i].sockfd == sockfd)
			return user[i].name;
	}
}

int selChatObj(int sockfd, const char *dstName)
{
	/* find sockfd of chat object */
	char *recvBuff;
	int i;
	for (i = 0; i < nUser; i++)
	{
		if (strncmp(user[i].name, dstName, sizeof(dstName)) == 0)
		{
			if (user[i].status == CALLING || user[i].status == TALKING)
			{
				sprintf(recvBuff, "%s busy now!", dstName);
				Send(sockfd, recvBuff, sizeof(recvBuff), 0);
				return ERR_USER_BUSY;
			}
			return user[i].sockfd;
		}
	}
	Send(sockfd, "User not found!\n", 16, 0);
	return ERR_USER_NOT_FOUND;
}

int sendChatReq(int srcfd, int dstfd)
{
	char recvBuff[2]; //*srcName;
	int n, i, srcP, dstP;
	for (i = 0; i < nUser; i++)
	{
		if (user[i].sockfd == srcfd)
		{
			//strncpy(srcName, user[i].name, strlen(user[i].name));
			srcP = i;
		}
		if (user[i].sockfd == dstfd)
			dstP = i;
	}
	//memset(recvBuff, '\0', sizeof(recvBuff));
	//sprintf(recvBuff, "%s request to talk, accept?(y/n): ", srcName);
Again:
	Send(dstfd,"request to talk, accept?(y/n) ", 30, 0);
	memset(recvBuff, 0, sizeof(recvBuff));
	n = Recv(dstfd, recvBuff, 2, 0);
	if (strncmp(recvBuff, "y\n", n) == 0 || strncmp(recvBuff, "Y\n", n) == 0)
	{
		Send(srcfd, "Accepted!\n", 10, 0);
		user[srcP].status = user[dstP].status = TALKING;
		return TRUE;
	}
	else if (strncmp(recvBuff, "n\n", n) == 0 || strncmp(recvBuff, "N\n", n) == 0)
	{
		Send(srcfd, "Rejected!\n", 10, 0);
		return FALSE;
	}
	else
	{
		Send(srcfd, "Command error!\n", 15, 0);
		goto Again;
	}
}

int transMsg(int srcfd, int dstfd)
{
	char recvBuff[BUFF_SIZE];
	fd_set rset;
	int maxfd, errSel;

	FD_ZERO(&rset);
	for ( ; ; )
	{
		memset(recvBuff, 0, sizeof(recvBuff));
		FD_SET(srcfd, &rset);
		FD_SET(dstfd, &rset);
		maxfd = srcfd > dstfd ? srcfd : dstfd;
		
		errSel = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (errSel < 0)
		{
			perror("Sel error!");
			exit(1);
		}
		if (FD_ISSET(srcfd, &rset))
		{
			Recv(srcfd, recvBuff, sizeof(recvBuff), 0);
			if (strncmp(recvBuff, "exit", 4) == 0)
			{
				FD_CLR(srcfd, &rset);
				FD_CLR(dstfd, &rset);
				return 0;
			}
			Send(dstfd, recvBuff, sizeof(recvBuff), 0);
		}
		if (FD_ISSET(dstfd, &rset))
		{
			Recv(dstfd, recvBuff, sizeof(recvBuff), 0);
			if (strncmp(recvBuff, "exit", 4) == 0)
			{
				FD_CLR(srcfd, &rset);
				FD_CLR(dstfd, &rset);
				return 0;
			}
			Send(srcfd, recvBuff, sizeof(recvBuff), 0);
		}
	}
}
