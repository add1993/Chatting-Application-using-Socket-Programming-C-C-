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

main() 
{ 
	int sock_des = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_des  == -1)  {
        perror("Cannot create socket!\n");
        return 0;
    } else {
		printf("Socket Created\n");
    }
	struct sockaddr_in server;  
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server.sin_port = htons(6000);

	if (connect(sock_des, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Cannot Connect to Server\n");
		return 0;
	} else {
		printf("Connected to Server\n");
	}

	while (1) {
		char buf[100]="";
		printf("Enter to Send \n");
		scanf("%s", buf);
		int len = strlen(buf);

		if (send(sock_des, buf, len, 0) != -1) {
			printf("Data Send\n");
			if (strcmp(buf, "exit") == 0) {
				break;
			}
		} else {
			perror("Writing\n");
		}
	}

	close(sock_des);  
    printf("Client Disconnected\n");

    return 0;  
} 

