#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int TCP_PortScan(char* host, short min, short max){
	int SOCK;
	struct sockaddr_in scan;
	
	for(min; min < max+1; min++){
		SOCK = socket(AF_INET, SOL_SOCKET, 0);
		if(SOCK < 0) return -1;

		scan.sin_addr.s_addr = inet_addr(host);
		scan.sin_family = AF_INET;
		scan.sin_port = htons(min);
		printf("%d\n", min);
		if(connect(SOCK, (struct sockaddr *)&scan, sizeof(scan)) !< 0){
			printf("%d open\n", min);
		};
		close(SOCK);	
	}
	return 0;
};

