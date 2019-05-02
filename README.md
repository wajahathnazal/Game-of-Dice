# Game-of-Dice
Game of Dice ( Client and Server)
The server process and the client process will run on two different machines and the communication between the two processes is achieved using Sockets.

→The server task can be summarized as follows :
The server starts running before any client, and waits for connections.
When the server gets a client, forks and, let the child process take care of the client in a separate function, called serviceClient, while the parent process goes back to wait for the next client.
Then, the server’s child process will play with the client. However, this server’s child can be a player and a referee at the same time. In particular, it first gets in an infinite loop, then
1. checks who reached a score of 100 among the two (totals are 0 at the start).
2. depending of the scores’ totals, sends either "Game on: you can now play your dice" or "Game over: you lost the game" or, "Game over: you won the game"
3. closes its socket and exits, if game over was declared.
4. plays its dice, adds the obtained score to its total, then sends its score to the client.
5. reads the client obtained score and adds it to the client’s total.

→The client task can be summarized as follows :
• The client process connects to the server, gets in an infinite loop, then
1. reads a directive (sentence) from server and prints it on the screen.
2. reads the server obtained score, adds it to the server total and prints the server’s score and total on the screen.
3. if the read returns 0 (end-of-file), client closes its socket and exits.
4. asks the user to hit enter to play dice
5. plays its dice, adds the obtained score to its total and prints the obtained score and the total on the screen. 6. sends its score to the server.
