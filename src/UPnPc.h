#ifndef __UDPC_H__
#define __UDPC_H__

//-------------------------------------------------------//
// Use add_port_mapping to add a port using the protocol //
// lease duration is a time setting. 0 means unlimited.  //
//-------------------------------------------------------//

int add_port_mapping(
	short NEW_EXTRANL_PORT,
	short NEW_INTERNAL_PORT,
	char* NEW_INTERNAL_CLIENT,
	char* NEW_PROTOCOL,
	short LEASE_DURATION,
	char* DESCRIPTION
);

//-----------------------------------------------------------//
// To delete a port you have added, use delete_port_mapping. //
// new extranl port and the protocol used.                   //
//-----------------------------------------------------------//
int delete_port_mapping(
	short NEW_EXTRANL_PORT,
	char* NEW_PROTOCOL
);

//------------------------------------------------//
// Use get_port_mapping to check the mapped Port. //
//------------------------------------------------//
int get_port_mapping();


//------------------------------------------------//
// To check global IP, use get_extenal_ip_address //
//------------------------------------------------//
int get_external_ip_address();

#endif
