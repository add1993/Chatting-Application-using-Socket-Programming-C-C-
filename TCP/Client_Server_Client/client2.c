#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netdb.h> 

main(int argc, char *argv[]) 
{ 
	struct hostent *hp;
	int portno, sock_des, lb;

	if(argc != 3) {
		printf("Error in Given Arguments\n");	
	}
	portno = atoi(argv[2]);
	
	hp = gethostbyname(argv[1]);
	if (hp == NULL) {
		herror("Error in Connection\n");
	}
	
	struct sockaddr_in server, local;  
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET; 
	memcpy((char *) &server.sin_addr.s_addr, hp -> h_addr_list[0], hp -> h_length); 
    server.sin_port = htons(portno);

	memset(&local, 0, sizeof(local));  
    local.sin_family = AF_INET; 
	local.sin_addr.s_addr = INADDR_ANY; 
    local.sin_port = htons(9999);
	
	sock_des = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_des  == -1)  {
        perror("Cannot create socket!\n");
        return 0;
    } else {
		printf("Socket Created\n");
    }

	lb = bind(sock_des, (struct sockaddr*) &local, sizeof(local));

	if (lb < 0) {
		perror("Binding Local Client\n");
		exit(0);
	} else {
		printf("Local Client binding Successful\n");
	}
	
	while (1) {
		char buf[100]="";

		if (recv(sock_des , buf, 100, 0) != -1) {
			printf("Data Recieved  =  %s\n", buf);
			if (strcmp(buf, "exit") == 0) {
				break;
			}
		} else {
			perror("Error in Read\n");
			exit(0);
		}
	}

	close(sock_des);  
    printf("Client Disconnected\n");

    return 0;  
} 

