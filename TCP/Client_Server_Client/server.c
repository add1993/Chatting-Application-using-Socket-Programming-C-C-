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
	struct sockaddr_in server1,server2;
	
	if (argc != 4) {
		printf("Error in Arguments\n");
		exit(0);
	}

	bzero((char *)&server1, sizeof(server1));
	server1.sin_family = AF_INET;
	server1.sin_addr.s_addr = inet_addr(argv[1]);
	server1.sin_port = htons(atoi(argv[2]));

	bzero((char *)&server2, sizeof(server2));
	server2.sin_family = AF_INET;
	server2.sin_addr.s_addr = inet_addr(argv[1]);
	server2.sin_port = htons(atoi(argv[3]));	

    int sock_desc1 = socket(AF_INET, SOCK_STREAM, 0);
    int sock_desc2 = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_desc1 == -1) {
        printf("Cannot Create Socket 1!\n");
        return 0;
    } else {
		printf("Socket 1 Created\n");
	}

	if (sock_desc2 == -1) {
        printf("Cannot Create Socket 2!\n");
        return 0;
    } else {
		printf("Socket 2 Created\n");
	}
  
    if (bind(sock_desc1, (struct sockaddr*)&server1, sizeof(server1)) != 0) {
        printf("Cannot Bind Socket 1!\n");
        close(sock_desc1);  
        return 0;
    } else {
		printf("Server Sock 1 Binding Complete\n");
	}

	if (bind(sock_desc2, (struct sockaddr*)&server2, sizeof(server2)) != 0) {
        printf("Cannot Bind Socket 2!\n");
        close(sock_desc2);  
        return 0;
    } else {
		printf("Server Sock 2 Binding Complete\n");
	}

    if (listen(sock_desc1, 20) != 0) {
        perror("Cannot Listen on Socket!\n");
        close(sock_desc1);  
        return 0;
    } else {
		printf("Listening\n");
	}
	
	int k1, k2;
	struct sockaddr_in client1, client2;
	socklen_t len1 = sizeof(client1);
	memset(&client1, 0, sizeof(client1));
	socklen_t len2 = sizeof(client2);
	memset(&client2, 0, sizeof(client2));
	
		printf("Accepting 1...\n");
		k1 = accept(sock_desc1, (struct sockaddr*)&client1, &len1);
		if (k1 != -1) {
			printf("Connection 1 Accepted\n");
		} else {
			printf("Connection 1 not Accepted\n");
			exit(0);
		}

		int s;
	while (1) { 
		char buf[100] = "";
		if (s = recv(k1 , buf, 100, 0) != -1) {
			 sendto(sock_desc2 , buf, strlen(buf)+1, 0, (struct sockaddr*)&client2, sizeof(client2));
  	   
			if (strcmp(buf, "exit") == 0) {
				break;
			} 			
		}
	}
	close(sock_desc1);   
	close(sock_desc2);  
    
    return 0;  
} 
		 
		
		
 

