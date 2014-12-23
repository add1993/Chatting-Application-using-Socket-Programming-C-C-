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

#define MYPORT 4950

main(int argc, char *argv[]) 
{  
	struct sockaddr_in server, client;
	socklen_t len;
	
	if (argc != 3) {
		printf("Error in Arguments\n");
		exit(0);
	}

	bzero((char *)&server, sizeof(server));
	bzero((char *)&client, sizeof(client));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));	

    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    
	if (sock_desc == -1) {
        perror("Cannot Create Socket!\n");
        return 0;
    } else {
		printf("Socket Created\n");
	}
  
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0) {
        perror("Cannot Bind Socket!\n");
        close(sock_desc);  
        return 0;
    } else {
		printf("Server Binding Complete\n");
	}
	int s;
	len = sizeof(client);
	while (1) {
		char buf[100] = "";
		if (s = recvfrom(sock_desc, buf, 100 , 0, (struct sockaddr *)&client, &len) != -1) {
			if (strcmp(buf, "exit") == 0) {
				break;
			} else {
				printf("%s\n", buf);
			}
		} else {
			perror("Receive\n");
		}
	}
	printf("Got packets from %s\n",inet_ntoa(client.sin_addr));
	close(sock_desc);   
    printf("Server Disconnected\n");

    return 0;  
} 
		 
		
		
 

