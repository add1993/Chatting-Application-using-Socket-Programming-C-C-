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
	struct sockaddr_in server;
	
	if (argc != 3) {
		printf("Error in Arguments\n");
		exit(0);
	}

	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));	

    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    
	if (sock_desc == -1) {
        printf("Cannot Create Socket!\n");
        return 0;
    } else {
		printf("Socket Created\n");
	}
  
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0) {
        printf("Cannot Bind Socket!\n");
        close(sock_desc);  
        return 0;
    } else {
		printf("Server Binding Complete\n");
	}

    if (listen(sock_desc, 20) != 0) {
        printf("Cannot Listen on Socket!\n");
        close(sock_desc);  
        return 0;
    } else {
		printf("Listening\n");
	}
	
	int k;
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	memset(&client, 0, sizeof(client)); 
	k = accept(sock_desc, (struct sockaddr*)&client, &len);
  
	if (k != -1) {
		printf("Connection Accepted\n");
	} else {
		printf("Connection not Accepted\n");
		exit(0);
	}

	int s;
	while (1) {
		char buf[100] = "";
		if (s = recv(k , buf, 100, 0) != -1) {
			if (strcmp(buf, "exit") == 0) {
				break;
			} else {
				printf("%s\n", buf);
			}
		}
	}
	close(sock_desc);  
    close(k);  

    printf("Server Disconnected\n");

    return 0;  
} 
		 
		
		
 

