#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#define MAX 255
#define PORT 8080
#define SA struct sockaddr


int serverScore =0;
int clientScore =0;
int turn = 1;
// Function designed for chat between client and server.
void func(int sockfd)
{

	// wait for server to press enter
	char buff[MAX];
	int n = 0;

while(1)
{
        while ((buff[n++] = getchar()) != '\n') ;
	// if msg contains "Exit" then server exit
	if (strncmp("exit", buff, 4) == 0) { 
	    printf("Server Exit...\n"); 
		 clientScore = 0;
		serverScore = 0;
	    return;
	}

        int temp = (rand() % 6) + 1;
        printf("Rolling dice ... ");
        // print buffer which contains the client contents
        serverScore = serverScore + temp;
        printf("Server Score :%d |Server TotalScore:%d  |Client Total:%d\n",temp,serverScore,clientScore );

if(serverScore >= 100)
{
	bzero(buff, MAX);
	sprintf(buff, "%s", "Server won the game... Now closing the client connection\n");
	write(sockfd, buff, MAX);

	printf("Server won the game... Now closing the client connection\n");
		 clientScore = 0;
		serverScore = 0;
	return;
}

	bzero(buff, MAX);
	sprintf(buff, "%d", serverScore);
	write(sockfd, buff, MAX);
	
	read(sockfd, buff, MAX);
	// if msg contains "Exit" then client exit
	if (strncmp("exit", buff, 4) == 0) { 
	    printf("Client closed the connection...\n");
		 clientScore = 0;
		serverScore = 0;
	    return; 
	}
	// if msg contains "client won" then client exit
	if (strncmp("Client won the game... Now closing the client connection", buff, 56) == 0) { 
	    printf("Client won the game and closed the connection...\n");
		clientScore = 0;
		serverScore = 0;
	    return; 
	}

	clientScore = atoi(buff);

	printf("\t Client Score:\t%d\n", clientScore);
}

}

// Driver function
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("The usage of program is incorrect.\n usage:./a.out portno (ex: ./a.out 8080)\n");
		return -1;
	}
    int sockfd, connfd, len, portNumber, sd;
    struct sockaddr_in servAdd, cli;
srand(time(0));

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servAdd, sizeof(servAdd));

    // assign IP, PORT
sd = socket(AF_INET, SOCK_STREAM, 0);
servAdd.sin_family = AF_INET;
servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
sscanf(argv[1], "%d", &portNumber);
servAdd.sin_port = htons((uint16_t)portNumber);
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servAdd, sizeof(servAdd))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

while(1)
{
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else{
        printf("Client is now connected. Game on: Hit Enter to play your dice...\n");
      }

    // Function for chatting between client and server
    func(connfd);
}
    // After chatting close the socket
    close(sockfd);
}


