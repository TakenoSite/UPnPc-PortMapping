#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../str/status.h"
#include "../str/tag_item.h"
#define RESPONSE_BUF 4096

/*Some parts have not been implemented.
 *urn:schemas-upnp-org:service:\
 *   WANPPPConnection:{1 <-- May need to be edited in some cases}
 */

int socket_h;
struct sockaddr_in s;
char *http_body;
char *http_header;
char *get_exet_soap;
char *add_port_soap;
char *delete_port_soap;
char *get_upnp_soap;
char buffor[RESPONSE_BUF];
int Request;

static int request(char* router_ip_address, short router_upnp_port){
	
	int status;
	socket_h = socket(AF_INET, SOCK_STREAM, 0);
	s.sin_addr.s_addr = inet_addr(router_ip_address);
	s.sin_family = AF_INET;
	s.sin_port = htons(router_upnp_port);
	if(connect(socket_h, (struct sockaddr *)&s, sizeof(s)) < 0) return -1;
	if(send(socket_h, http_body, strlen(http_body), 0) < 0) return -1;
	free(http_body);
	recv(socket_h, buffor, sizeof(buffor), 0);
	status = status_check(buffor);
	close(socket_h);
	
	return status;
}

static int header(

		char* router_ip_address,
		short router_upnp_port,
		short payload_length,
		char* mode
		){
	
	http_header = (char*)malloc(sizeof(char) * 256);
	if(http_header == NULL) return -1;

	sprintf(http_header,"\
POST /UD/?6 HTTP/1.1\r\n\
Host: %s:%d\r\n\
Content-Length: %d\r\n\
Content-Type: text/xml; charset='utf-8'\r\n\
Connection: Close\r\n\
SOAPACTION: 'urn:schemas-upnp-org:service:WANPPPConnection:1#%s'\r\n",router_ip_address, router_upnp_port, payload_length, mode);

	return 0;
};

int GetExternalIPAddress(
		char* router_ip_address,
		short router_upnp_port
		){
	char NewExternalIPAddress[32];

	get_exet_soap = (char*)malloc(sizeof(char) * 370);
	if(get_exet_soap == NULL) return -1;
	
	sprintf(get_exet_soap, "\
<?xml version='1.0'?>\r\n\
<s:Envelope xmlns:s='http://schemas.xmlsoap.org/soap/envelope/' s:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'>\r\n\
<s:Body>\r\n\
<u:GetExternalIPAddress xmlns:u='urn:schemas-upnp-org:service:WANPPPConnection:1'>\r\n\
</u:GetExternalIPAddress>\r\n\
</s:Body>\r\n\
</s:Envelope>\r\n\r\n");
	
	header(
		router_ip_address,
		router_upnp_port,
		strlen(get_exet_soap),
		"GetExternalIPAddress"
		);
	http_body = (char*)malloc(sizeof(char) + (strlen(http_header) + strlen(get_exet_soap) + 32));
	if(http_body == NULL) return -1;
	sprintf(http_body, "%s\r\n%s", http_header, get_exet_soap);
	free(http_header);
	free(get_exet_soap);
	Request = request(router_ip_address, router_upnp_port);
	if(Request != -1){
		if(Request == 200){
			tag_item_tag(buffor, "NewExternalIPAddress", NewExternalIPAddress);
			printf("NewExternalIPAddress\n200 OK\nAddr: %s",
					NewExternalIPAddress);
		}else{
			printf("NewExternalIPAddress\n %d Internal Server Error\n",
					Request);
			return -2;
		}
	}else{
		printf("UPnP Protocol Connecting Error\nRoterIP:%s RoterPORT:%d\n",
			 router_ip_address,
			 router_upnp_port);
		return -1;
	}
	return 0;

}

int AddPortMapping(
		
		short NEW_EXTRANL_PORT,
		short NEW_INTERNAL_PORT,
		char* NEW_INTERNAL_CLIENT,
		char* NEW_PROTOCOL,
		short LEASE_DURATION,
		char* DESCRIPTION,
		char*router_ip_address,
		short router_upnp_port

		){
	
	add_port_soap = (char*)malloc(sizeof(char) * 650);
	if(add_port_soap == NULL) return -1;

	sprintf(add_port_soap,"\
<?xml version='1.0'?>\r\n\
<s:Envelope xmlns:s='http://schemas.xmlsoap.org/soap/envelope/' s:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'>\r\n\
<s:Body>\r\n\
<m:AddPortMapping xmlns:m='urn:schemas-upnp-org:service:WANPPPConnection:1'>\r\n\
<NewRemoteHost></NewRemoteHost>\r\n\
<NewExternalPort>%d</NewExternalPort>\r\n\
<NewProtocol>%s</NewProtocol>\r\n\
<NewInternalPort>%d</NewInternalPort>\r\n\
<NewInternalClient>%s</NewInternalClient>\r\n\
<NewEnabled>1</NewEnabled>\r\n\
<NewPortMappingDescription>%s</NewPortMappingDescription>\r\n\
<NewLeaseDuration>%d</NewLeaseDuration>\r\n\
</m:AddPortMapping>\r\n\
</s:Body>\r\n\
</s:Envelope>\r\n\r\n",
	NEW_EXTRANL_PORT, 
	NEW_PROTOCOL, 
	NEW_INTERNAL_PORT, 
	NEW_INTERNAL_CLIENT, 
	DESCRIPTION, 
	LEASE_DURATION);	
	
	header(
		router_ip_address,
		router_upnp_port,
		strlen(add_port_soap),
		"AddPortMapping"
		);
	http_body = (char*)malloc(sizeof(char) * (strlen(http_header) + strlen(add_port_soap) + 32));
	if(http_body == NULL) return -1;
	
	sprintf(http_body,"%s\r\n%s",http_header,add_port_soap);
	free(http_header);
	free(add_port_soap);
	Request = request(router_ip_address,router_upnp_port);
	
	if(Request !=-1){
		if(Request == 200){
			printf("AddPortMapping\n200 OK\nIP: %s IN: %d EXT: %d PROTO: %s LEASE: %d DES: %s\n",
				NEW_INTERNAL_CLIENT,
				NEW_INTERNAL_PORT,
				NEW_EXTRANL_PORT,
				NEW_PROTOCOL,
				LEASE_DURATION,
				DESCRIPTION
				);
		}else{
			printf("AddPortMapping\n%d Internal Server Error\nIP: %s IN: %d EXT: %d PROTO: %s LEASE: %d DES: %s\n",
				Request,
				NEW_INTERNAL_CLIENT,
				NEW_INTERNAL_PORT,
				NEW_EXTRANL_PORT,
				NEW_PROTOCOL,
				LEASE_DURATION,
				DESCRIPTION
			);
			return -2;
		}
	}else{
		printf("UPnP Protocol Connecting Error\nRoterIP:%s RoterPORT:%d\n",
				router_ip_address,
				router_upnp_port);
		return -1;
	}
	return 0;
}

int DeletePortMapping(
		short NEW_EXTRANL_PORT,
		char* NEW_PROTOCOL,
		char* router_ip_address,
		short router_upnp_port
		){
	
	delete_port_soap = (char*)malloc(sizeof(char)*450);
	if(delete_port_soap ==NULL) return -1;

	sprintf(delete_port_soap,"\
<?xml version='1.0'?>\r\n\
<s:Envelope xmlns:s='http://schemas.xmlsoap.org/soap/envelope/' s:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'>\r\n\
<s:Body>\r\n\
<m:DeletePortMapping xmlns:m='urn:schemas-upnp-org:service:WANPPPConnection:1'>\r\n\
<NewRemoteHost></NewRemoteHost>\r\n\
<NewExternalPort>%d</NewExternalPort>\r\n\
<NewProtocol>%s</NewProtocol>\r\n\
</m:DeletePortMapping>\r\n\
</s:Body>\r\n\
</s:Envelope>\r\n\r\n",NEW_EXTRANL_PORT, NEW_PROTOCOL);

	header(
		router_ip_address,
		router_upnp_port,
		strlen(delete_port_soap),
		"DeletePortMapping"
		);

	http_body = (char*)malloc(sizeof(char) * (strlen(delete_port_soap) + strlen(http_header) + 32));
	if(http_body == NULL) return -1;

	sprintf(http_body, "%s\r\n%s", http_header, delete_port_soap);
	free(http_header); 
	free(delete_port_soap);
	
	Request = request(router_ip_address, router_upnp_port);
	if(Request  != -1){
		if(Request == 200){
			printf("DeletePortMapping\n200 OK\n DEL: %d PROTO: %s",
					NEW_EXTRANL_PORT,
					NEW_PROTOCOL
					);
		}else{
			printf("DeletePortMapping\n %d Internal Server Error\n",
					Request);
			return -2;
		}
	}else{
		printf("UPnP Protocol Connecting Error\nRoterIP:%s RoterPORT:%d\n",
				router_ip_address,
				router_upnp_port);
		return -1;
	}

	return 0;
}

int GetGenericPortMappingEntry(
	char* router_ip_address,
	short router_upnp_port
){

	short Count = 0;
	char NewInternalClient[32];
	char NewExternalPort[24];
	char NewInternalPort[24];
	char NewProtocol[16];

	while (1){
		get_upnp_soap = (char*)malloc(sizeof(char)*386);
		if(get_upnp_soap == NULL) return -1;
		sprintf(get_upnp_soap,"\
<?xml version='1.0'?>\r\n\
<s:Envelope xmlns:s='http://schemas.xmlsoap.org/soap/envelope/' s:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'>\r\n\
<s:Body>\r\n\
<m:GetGenericPortMappingEntry xmlns:m='urn:schemas-upnp-org:service:WANPPPConnection:1'>\r\n\
<NewPortMappingIndex>%d</NewPortMappingIndex>\r\n\
</m:GetGenericPortMappingEntry>\r\n\
</s:Body>\r\n\
</s:Envelope>\r\n\
	" , Count) ;

		header(
			router_ip_address,
			router_upnp_port,
			strlen(get_upnp_soap),
			"GetGenericPortMappingEntry"
		);
		
		http_body = (char*)malloc(sizeof(char) * (strlen(get_upnp_soap) + strlen(http_header) + 32));
		if(http_body == NULL) return 0;
		sprintf(http_body, "%s\r\n%s", http_header, get_upnp_soap);
		free(http_header); 
		free(get_upnp_soap);
		Request = request( router_ip_address, router_upnp_port);
		if(Request != -1){
			if(Request == 200){
				
				tag_item_tag(buffor, "NewInternalClient", NewInternalClient);
				tag_item_tag(buffor, "NewInternalPort", NewInternalPort);
				tag_item_tag(buffor, "NewExternalPort", NewExternalPort);
				tag_item_tag(buffor, "NewProtocol", NewProtocol);
				
				printf("IP: %s IN: %s EXT: %s PROTO: %s\n",
						NewInternalClient,
						NewInternalPort,
						NewExternalPort,
						NewProtocol);
				//puts(buffor);
				Count ++;
			}else{
				return -2;
			}
		}else{
			printf("UPnP Protocol Connecting Error\nRoterIP:%s RoterPORT:%d\n",
				router_ip_address,
				router_upnp_port);
			return -1;
		};
	};
	return 0;
}
