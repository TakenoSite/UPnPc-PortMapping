#include <stdio.h>
#include <unistd.h>
#include "src/UPnPc.h"

#define MAX_LEN 7

int main(int argc, char* argv[]){
	
	char *info[MAX_LEN];
	short extranl_port;
	short internal_port;
	short lease_duration;
	
	int opt;
	int i;

	while((opt = getopt(argc, argv, "hlga:d::"))!= -1){
		switch(opt){
			case 'h':
				printf("+UPnP-Protcol-Controle+\n\n%s\n%s\n%s\n%s\n",
						"add_port_mapping: -a {extranl} {internal} {client} {proto} {lease duration} {desription}",
						"delete_port_mapping: -d {extranl_port} {protocol}",
						"get_port_mapping : -l",
						"get_external_ip_address: -g");

				return 0;
			case 'a':
				puts("add_port_mapping...\n++++++++++++++++\n");
				for(i= 2; i < argc; i++){
					info[i-2] = argv[i]; 
				};
				if(i == 8){
					
					if(sscanf(info[0],"%hd",&extranl_port) == 0 \
						|| sscanf(info[1],"%hd", &internal_port) == 0 \
						|| sscanf(info[4],"%hd", &lease_duration) == 0 ){
						puts("Please enter in -a {extranl}{internal} {client} {proto} {lease duration} {desription}");
						return -1;
					}
					
					// Exec add port mapping
					add_port_mapping(
							extranl_port,
							internal_port,
							info[2],
							info[3],
							lease_duration,
							info[5]);
					
				}else{
					puts("Please enter in -a {extranl}{internal} {client} {proto} {lease duration} {desription}");
					return -1;
				}
				return 0;
			case 'd':
				puts("delete_port_mapping \n+++++++++++++++\n");
				for(i=2; i<argc; i++){
					info[i-2]= argv[i];
				};
				if(i == 4){
					if(sscanf(info[0], "%hd", &extranl_port) == 0){
						puts("Please enter in -d {extranl_port} {protocol}");
						return -1;
					}
					
					//Exec delete_port_mapping
					delete_port_mapping(
							extranl_port,
							info[1]
							);
				}else{
					puts("Please enter in -d {extranl_port} {protocol}");
					return -1;
				};

				break;
			case 'l':
				puts("get_port_mapping \n+++++++++++++++\n");
				get_port_mapping();
				return 0;
			case 'g':
				puts("get_external_ip \n+++++++++++++++\n");
				get_external_ip_address();
				return 0;
			default:
				return 0;
		}

	}

	printf("+UPnP-Protcol-Controle+\n\n%s\n%s\n%s\n%s\n",
					"add_port_mapping: -a {extranl} {internal} {client} {proto} {lease duration} {desription}",
					"delete_port_mapping: -d {extranl_port} {protocol}",
					"get_port_mapping : -l",
					"get_external_ip_address: -g");

	return 0;
	
}
