/*
* The program uses website content as symbolic variables.  It checks if a text exists, and triggers the bomb.
*Evaluation:
--Triton: fail
--Angr:
--BAP:
*/
#include "utils.h"

int main(int argc, char** argv)
{
    int socket;
    char receiver[256];
    char get_msg[BUFSIZ] = "GET /index.html HTTP/1.1\r\nHost:cudroid.com\r\n\r\n";

    socket = open_socket("www.cudroid.com", "80");
    if(socket==-1)
	return -1;
    printf ("socket connect successful\n");

    int ret=send(socket,get_msg,strlen(get_msg),0);
    if(ret==-1)
	return -1;
    printf ("send msg successful\n");
    
    int trigger = 1;
    while(recv(socket,receiver,256,0)){
        if(strstr(receiver, "Hui"))
  	    trigger = 0;
    	//printf("%s", receiver);
    }
    if(trigger)
	Bomb();
    else
	Foobar();
    close(socket);
    return 0;
}
