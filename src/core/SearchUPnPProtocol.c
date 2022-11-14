#include "GetGatewayIPaddress.h"
#include "../str/header_split.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>
#include <stdio.h>

#define RESPONSE_BUFFOR 1024
#define IPV4_BUFFOR	32
#define MESSAGE_BUFFOR 196 

char gatewayipv4[IPV4_BUFFOR];
char upnp_protcol_utl[MESSAGE_BUFFOR];


int GetUPnPProtocol(char* resolve_host, char* resolve_port){
	getgatewayIP(gatewayipv4);
	struct sockaddr_in ssdp;
    char message[MESSAGE_BUFFOR];
	char buffor[RESPONSE_BUFFOR];
	int sock_ssdp;
	int UPnPPort[] = {1900, 3000};	
	char *host;
	char *port;

	struct timeval tv; 
	fd_set readfds;
	int timecount; 

	for(int i=0; i < 2; i++){
		sprintf(message, "\
M-SEARCH * HTTP/1.1\r\n\
MX: 3\r\n\
HOST: %s:%d\r\n\
MAN: 'ssdp:discover'\r\n\
ST: urn:schemas-upnp-org:service:WANIPConnection:1\r\n\r\n",
		gatewayipv4, UPnPPort[i]);

		sock_ssdp = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_ssdp < 0) return -1;
		
		ssdp.sin_addr.s_addr = inet_addr(gatewayipv4);
		ssdp.sin_family = AF_INET;
		ssdp.sin_port = htons(UPnPPort[i]);
		sendto(sock_ssdp, message, sizeof(message), 0, (struct sockaddr *)&ssdp, sizeof(ssdp));
		
		tv.tv_sec = 2;
		tv.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(sock_ssdp, &readfds);
		timecount = select(sock_ssdp + 1, &readfds, NULL, NULL, &tv);
		
		if(timecount != 0){
			recv(sock_ssdp, buffor, sizeof(buffor), 0);
			if(HeaderSplit_to_Url(buffor, "http://", upnp_protcol_utl) < 0) return -2;
			char *ptr = strtok(upnp_protcol_utl, "/");
			ptr = strtok(NULL, "/");
			host = strtok(ptr, ":");
			port = strtok(NULL, ":");
			
			break;
		};
	}
	
	if(timecount != 0){
		sprintf(resolve_host, "%s", host);
		sprintf(resolve_port, "%s", port);
		return 0;
	}else{
		return -1;
	}
	
}
