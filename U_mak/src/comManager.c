/*
 * comManager.c
 *
 *  Created on: Sep 18, 2021
 *      Author: elmas
 *
 *      See: https://www.geeksforgeeks.org/socket-programming-cc/
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "config.h"
#include "comManager.h"


#define SERVER_ADDR			"0.0.0.0"
#define SERVER_PORT			1903
#define ACK					0x06


static int socket_fd;

int comInit(void)
{
	int ret;
	struct sockaddr_in address;

	//create socket
	socket_fd=socket(AF_INET,SOCK_STREAM,0);

	if(socket_fd>-1)
	{
		ret=SUCCESS;
	}

	if(ret==SUCCESS)
	{
		address.sin_family=AF_INET;
		address.sin_port=htons(SERVER_PORT);
		inet_pton(AF_INET,SERVER_ADDR,&address.sin_addr);
		ret=connect(socket_fd,&address,sizeof(address));
	}
	return ret;
}

int comSendEvent(Event* event)
{
	int ret=SUCCESS;
	char buff[128];
	int valRead;

	send(socket_fd,event,13,0);

	valRead=read(socket_fd,buff,128);

	if(buff[0]!=ACK)
	{
		ret=ERROR;
	}

	return ret;
}

int comClose(void)
{
	close(socket_fd);
}
