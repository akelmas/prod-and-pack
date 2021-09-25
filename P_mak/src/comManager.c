/*
 * comManager.c
 *
 *  Created on: Sep 22, 2021
 *      Author: elmas
 *         See: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
 */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "config.h"
#include "comManager.h"

#define SERVER_PORT			5001

static int socket_fd;
static int conn_fd;

int comInit(void)
{
	int ret;
	struct sockaddr_in address;
	struct sockaddr_in client_address;


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
		address.sin_addr.s_addr=INADDR_ANY;

		ret=bind(socket_fd,(struct sockaddr *)&address,sizeof(address));
	}

	while(1)
	{
		unsigned char buffer[128];
		int len;
		int i;
		int addrlen=sizeof(client_address);

		ret=listen(socket_fd,5);

		if(ret==SUCCESS)
		{
			conn_fd=accept(socket_fd,(struct sockaddr *)&client_address,(socklen_t *)&addrlen);
		}

		if(ret==SUCCESS)
		{
			len = read(conn_fd,buffer,sizeof(buffer));
			buffer[len]=0;

			//TODO process received data

		}



	}

	return ret;
}

