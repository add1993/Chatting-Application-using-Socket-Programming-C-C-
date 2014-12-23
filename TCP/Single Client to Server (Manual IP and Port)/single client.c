#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <arpa/inet.h> 
//#include <fcntl.h> 
#include <unistd.h> 

main() 
{  
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0), r; 
    if (sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

	struct sockaddr_in server;  
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server.sin_port = htons(5000); 

    if (connect(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0)
    {
        printf("cannot connect to server!\n");
        close(sock_desc);
    }

    char buf[100];
    while (1) {
		printf("Enter to Send \n");
		scanf("%s", buf);
		int len = strlen(buf);

		if (send(sock_desc, buf, len, 0) != -1) {
			printf("Data Send\n");
			if (strcmp(buf, "exit") == 0) {
				break;
			}
		} else {
			printf("Error in Writing to Server\n");
			exit(0);
		}
	}

	close(sock_desc);  
    printf("Client Disconnected\n");

    return 0;  
} 
  
