#ifndef __UPNP_SOAP_H_
#define __UPNP_SOAP_H_

int GetExternalIPAddress(
	char* router_ip_address,
	short router_upnp_port
);

int AddPortMapping(
	short NEW_EXTRANL_PORT,
	short NEW_INTERNAL_PORT,
	char* NEW_INTERNAL_CLIENT,
	char* NEW_PROTOCOL,
	short LEASE_DURATION,
	char* DESCRIPTION,
	char*router_ip_address,
	short router_upnp_port

);

int DeletePortMapping(
	short NEW_EXTRANL_PORT,
	char* NEW_PROTOCOL,
	char* router_ip_address,
	short router_upnp_port
);


int GetGenericPortMappingEntry(
	char* router_ip_address,
	short router_upnp_port
);


#endif
