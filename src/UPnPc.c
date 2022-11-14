#include "core/UPnPSoap.h"
#include "core/SearchUPnPProtocol.h"
#include <stdio.h>
#include <string.h>

char UPnPProtocolHost[32];
char UPnPProtocolPort[32];
short IntUPnPProtocolPort;

int add_port_mapping(
		short NEW_EXTRANL_PORT,
		short NEW_INTERNAL_PORT,
		char* NEW_INTERNAL_CLIENT,
		char* NEW_PROTOCOL,
		short LEASE_DURATION,
		char* DESCRIPTION
		){
	
	int UPnPProtocolStatus = GetUPnPProtocol(
		UPnPProtocolHost,
		UPnPProtocolPort
	);
	if (UPnPProtocolStatus  < 0){ 
		printf("\
			\rIGD not found.\
			\rPlease check your router configuration, or use UDP port scan to see if port 1900 or 3000 is open.\
			\r\nDefualt Gateway IPAddress: %s", UPnPProtocolHost);
		
		return -1;
	}else if(UPnPProtocolStatus == -2){
		printf("I found IGD, but UPnP Protocol URL is not found.");	
		return -2;
	}else printf("IGD we found the \nIP: %s\nPORT: %s\n\n", UPnPProtocolHost, UPnPProtocolPort);
	
	sscanf(
		UPnPProtocolPort,
		"%hd",
		&IntUPnPProtocolPort
	);	
	
	int AddPortMappingStatus =  AddPortMapping(
		NEW_EXTRANL_PORT,
		NEW_INTERNAL_PORT,
		NEW_INTERNAL_CLIENT,
		NEW_PROTOCOL,
		LEASE_DURATION,
		DESCRIPTION,
		UPnPProtocolHost,
		IntUPnPProtocolPort
	);

	return AddPortMappingStatus;
};

int delete_port_mapping(
		short NEW_EXTRANL_PORT,
		char* NEW_PROTOCOL
		){

	int UPnPProtocolStatus = GetUPnPProtocol(
			UPnPProtocolHost,
			UPnPProtocolPort
	);

	if (UPnPProtocolStatus  < 0){ 
		printf("\
			\rIGD not found.\
			\rPlease check your router configuration, or use UDP port scan to see if port 1900 or 3000 is open.\
			\r\nDefualt Gateway IPAddress: %s", UPnPProtocolHost);
		
		return -1;
	}else if(UPnPProtocolStatus == -2){
		printf("I found IGD, but UPnP Protocol URL is not found.");	
		return -2;
	}else printf("IGD we found the \nIP: %s\nPORT: %s\n\n", UPnPProtocolHost, UPnPProtocolPort);
	
	sscanf(
		UPnPProtocolPort,
		"%hd",
		&IntUPnPProtocolPort
	);	
		
	int AddPortMappingStatus =  DeletePortMapping(
		NEW_EXTRANL_PORT,
		NEW_PROTOCOL,
		UPnPProtocolHost,
		IntUPnPProtocolPort
	);

	return AddPortMappingStatus;
}

int get_port_mapping(){
	int UPnPProtocolStatus = GetUPnPProtocol(
			UPnPProtocolHost,
			UPnPProtocolPort
	);

	if (UPnPProtocolStatus  < 0){ 
		printf("\
			\rIGD not found.\
			\rPlease check your router configuration, or use UDP port scan to see if port 1900 or 3000 is open.\
			\r\nDefualt Gateway IPAddress: %s", UPnPProtocolHost);
		
		return -1;
	}else if(UPnPProtocolStatus == -2){
		printf("I found IGD, but UPnP Protocol URL is not found.");	
		return -2;
	}else printf("IGD we found the \nIP: %s\nPORT: %s\n\n", UPnPProtocolHost, UPnPProtocolPort);
	
	sscanf(
		UPnPProtocolPort,
		"%hd",
		&IntUPnPProtocolPort
	);
	
	int GetGenericPortMappingEntryStatus = GetGenericPortMappingEntry(
			UPnPProtocolHost,
			IntUPnPProtocolPort
	);

	return GetGenericPortMappingEntryStatus;
}

int get_external_ip_address(){
	int UPnPProtocolStatus = GetUPnPProtocol(
			UPnPProtocolHost,
			UPnPProtocolPort
	);
	
	if (UPnPProtocolStatus  == -1){ 
		printf("\
			\rIGD not found.\
			\rPlease check your router configuration, or use UDP port scan to see if port 1900 or 3000 is open.\
			\r\nDefualt Gateway IPAddress: %s", UPnPProtocolHost);
		
		return -1;
	}else if(UPnPProtocolStatus == -2){
		printf("I found IGD, but UPnP Protocol URL is not found.");	
		return -2;
	}else printf("IGD we found the \nIP: %s\nPORT: %s\n\n", UPnPProtocolHost, UPnPProtocolPort);

	sscanf(
		UPnPProtocolPort,
		"%hd",
		&IntUPnPProtocolPort
	);
		
	int GetExternalIPAddressStatus = GetExternalIPAddress(
		UPnPProtocolHost,
		IntUPnPProtocolPort
	);
	return GetExternalIPAddressStatus;
}

// end
