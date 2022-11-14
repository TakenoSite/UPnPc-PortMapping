c = gcc
product_name = upnpc

strDir = ./src/str/
coreDir = ./src/core/

main:str core upnpc
	$(c) -Wall -O2 -c main.c 
	$(c) -Wall -O2 -o $(product_name) main.o\
		$(strDir)header_split.o \
		$(strDir)status.o \
		$(strDir)tag_item.o \
		$(coreDir)GetGatewayIPaddress.o \
		$(coreDir)SearchUPnPProtocol.o \
		$(coreDir)UPnPSoap.o \
		./src/UPnPc.o

		rm  main.o\
		$(strDir)header_split.o \
		$(strDir)status.o \
		$(strDir)tag_item.o \
		$(coreDir)GetGatewayIPaddress.o \
		$(coreDir)SearchUPnPProtocol.o \
		$(coreDir)UPnPSoap.o \
		./src/UPnPc.o


str:
	$(c) -Wall -O2 -c $(strDir)header_split.c -o $(strDir)header_split.o
	$(c) -Wall -O2 -c $(strDir)status.c -o $(strDir)status.o
	$(c) -Wall -O2 -c $(strDir)tag_item.c -o $(strDir)tag_item.o
	
core:
	$(c) -Wall -O2 -c $(coreDir)GetGatewayIPaddress.c -o  $(coreDir)GetGatewayIPaddress.o
	$(c) -Wall -O2 -c $(coreDir)SearchUPnPProtocol.c -o  $(coreDir)SearchUPnPProtocol.o
	$(c) -Wall -O2 -c $(coreDir)UPnPSoap.c -o  $(coreDir)UPnPSoap.o

upnpc:
	$(c) -Wall -O2 -c ./src/UPnPc.c -o  ./src/UPnPc.o 
