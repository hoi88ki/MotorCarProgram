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

	// Create a basic UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	// Initialize the memory
	memset(&servaddr, sizeof(servaddr), 0);
	// We want to use the Internet Address Family
	servaddr.sin_family = AF_INET;
	// Set Ip addr.
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	// Set default port to 8000
	servaddr.sin_port = htons(8000);
	
	// using stty to control input without pressing enter
	// use system call to make terminal send all keystrokes directly to stdin
	system ("/bin/stty raw");

	while((c=getchar())!= '.') {
		// change the character to lower case
		if(c>='A' && c<='Z')
			c+=32;
		// send out the command only when the character is control character
		sendto(sockfd, &c, 1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
	}

	/* use system call to set terminal behaviour to more normal behaviour */
	system ("/bin/stty cooked");

}

