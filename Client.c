/*
 *  Author: Ivan Yung
 *  Date: 26/06/2015
 *  
 *  UDP Client used to connect motorcar
 */


#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	int sockfd, n, c;
	struct sockaddr_in servaddr, cliaddr;
	char buffer[1000];


    	// Check we have the right number of arguments
    	if (argc != 2) {
    		printf("usage: %s <IP Address>\n", argv[0]);
		exit(1);
	}

	/* use system call to make terminal send all keystrokes directly to stdin */
	system ("/bin/stty raw");

	// Create a basic UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	// Initialize the memory
	memset(&servaddr, sizeof(servaddr), 0);
	// We want to use the Internet Address Family
	servaddr.sin_family = AF_INET;
	// Here we set the IP address
	// Note: we call inet_addr to convert the string representation into an integer representation
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	// Do something similar with the port - but we also need it in Big Endian format
	servaddr.sin_port = htons(8000);
	
	while((c=getchar())!= '.') {
		/* type a period to break out of the loop, since CTRL-D won't work raw */
		putchar(c);
		// send out the command
		sendto(sockfd, &c, 1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
	}

	/* use system call to set terminal behaviour to more normal behaviour */
	system ("/bin/stty cooked");

}
