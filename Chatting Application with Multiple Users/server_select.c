#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	struct sockaddr_in their_addr;
	fd_set master, read_fds;
	char buf[100];
	int s, newfd, i, fdmax, nbytes, j;
	socklen_t len;
	
	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error in socket\n");
		exit(0);
	} else {
		printf("Socket Created\n");
	}

	bzero((char*)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(atoi(argv[1]));

	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("Error in binding");
		exit(0);
	} else {
		printf("Binding successful\n");
	}

	if (listen(s, 10) == -1) {
		perror("Error in listening\n");
		exit(0);
	} else {
		printf("Listening\n");
	} 

	FD_SET(s, &master);
	fdmax = s;
	bzero((char*)&their_addr, sizeof(their_addr));
	while (1) {

		read_fds = master;

		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("Error in Select\n");
		} else {
			//printf("Select Successful\n");
		}

		for (i = 0; i <= fdmax; i++) {
			//printf("Inside For\n");
			if (FD_ISSET(i, &read_fds)) {
				if (i == s) {
					len = sizeof(their_addr);
					//printf("Before Accept\n");	
					if (newfd = accept(s, (struct sockaddr *)&their_addr, &len) < 0) {
						perror("Error in accepting \n");
					} else { 
						FD_SET(newfd, &master);
						if (newfd > fdmax) { 
							fdmax = newfd;
						}
						//printf("Inside Accept\n");
						printf("SelectServer: New connection from %s on ""socket %d\n", inet_ntoa(their_addr.sin_addr), newfd);
					}
				} else {
					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						if (nbytes == 0) {
							printf("SelectServer: Socket %d Hung Up\n", i);
						} else {
							perror("Recv\n");
						}
						close(i);
						FD_CLR(i, &master);
					} else {
						for(j = 0; j <= fdmax; j++) {
							if (FD_ISSET(j, &master)) {
								if (j != s && j != i) {
									if (send(j, buf, sizeof(buf)+1, 0) == -1) {
										perror("send");
									}
								}	
							}
						}
					}
				}
			}
		}
	}
		
	close(s);	
	return 0;
}