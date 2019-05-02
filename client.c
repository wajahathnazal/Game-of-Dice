
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX 255
#define PORT 8080
#define SA struct sockaddr
int clientScore = 0;
int turn =0;

void func(int sockfd)
{
    char buff[MAX];
    char scoreBuff[4];
    int n;

while(1) 
{

bzero(buff, MAX);
read(sockfd, buff, sizeof(buff));
// if msg contains "Exit" then client exit
if (strncmp("exit", buff, 4) == 0) { 
    printf("Client Exit...\n"); 
    return; 
}
	// if msg contains "client won" then client exit
	if (strncmp("Server won the game... Now closing the client connection", buff, 56) == 0) { 
	    printf("Server won the game and now closed the connection...\n");
	    return; 
	}

int serverScore = atoi(buff);
printf("Server TotalScore:\t%d\n", serverScore);

bzero(buff, MAX);
n = 0;
while ((buff[n++] = getchar()) != '\n');
// if msg contains "Exit" then client exit
if (strncmp("exit", buff, 4) == 0) { 
    printf("Client Exit...\n"); 
	
	write(sockfd, buff, MAX);
    return; 
}

int temp =(rand() % 6) + 1;
clientScore += temp;
bzero(buff, MAX);
sprintf(buff, "%d", clientScore);
printf("Client Score:\t%d\t|Client Total:\t:%d\n", temp, clientScore);

if(clientScore >= 100)
{
	bzero(buff, MAX);
	sprintf(buff, "%s", "Client won the game... Now closing the client connection\n");
	write(sockfd, buff, MAX);

	printf("Client won the game... Now closing the client connection\n");
	return;
}

write(sockfd, buff, MAX);

}

}

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("The usage of program is inccorrect.\n  usage:./a.out ip portno (ex: ./a.out 127.0.0.1 8080)\n");
		return -1;
	}

    int sockfd, connfd, server, portNumber;
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
servAdd.sin_family = AF_INET;
sscanf(argv[2], "%d", &portNumber);
servAdd.sin_port = htons((uint16_t)portNumber);
if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
fprintf(stderr, " inet_pton() has failed\n");
exit(2);
}
if(connect(sockfd, (struct sockaddr *) &servAdd, sizeof(servAdd))==0){
	printf("Client now connected to the server\n");
}
else{
fprintf(stderr, "connect() has failed: Recheck your IP address and port number, exiting\n");
exit(3);
}
 func(sockfd);
    // close the socket
    close(sockfd);
}


