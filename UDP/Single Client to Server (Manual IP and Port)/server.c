#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

main() 
{  
	struct sockaddr_in server;

    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    
	if (sock_desc == -1) {
        perror("Cannot Create Socket!\n");
        return 0;
    } else {
		printf("Socket Created\n");
	}
	  
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server.sin_port = htons(6000);
  
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0) {
        perror("Cannot Bind Socket!\n");
        close(sock_desc);  
        return 0;
    } else {
		printf("Server Binding Complete\n");
	}

    int s;
	while (1) {
		char buf[100] = "";
		if (s = recv(sock_desc, buf, 100, 0) != -1) {
			if (strcmp(buf, "exit") == 0) {
				break;
			} else {
				printf("%s\n", buf);
			}
		} else {
			perror("Receive\n");
		}
	}
	close(sock_desc);    

    printf("Server Disconnected\n");

    return 0;  
} 
		 
		
		
 

