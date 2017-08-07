/*
  Description:
 
  Open a socket using the system call socket(). This will provide us with a file descriptor that
  is specific to the process that handles the execution of this code. 
  
  Just a little more "light" reading
  http://man7.org/linux/man-pages/man2/open.2.html
  http://man7.org/linux/man-pages/man2/write.2.html
  http://man7.org/linux/man-pages/man2/socket.2.html
  http://man7.org/linux/man-pages/man2/stat.2.html
*/

#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int STDOUT = 1;

int main()
{

   struct sockaddr_in sa;
   //Open socket .... receive bacon .. no .. receive file descriptor 'sd'
   //PF_INET - use ip4, SOCK_STREAM - tcp, 0 - only use one protocol 
   int sd = socket(PF_INET, SOCK_STREAM, 0);


   //The usual checking to make sure we actually obtained a file descriptor
   if (sd<0)
      printf("error");


   memset(&sa, 0, sizeof(struct sockaddr_in));

   sa.sin_family = AF_INET;
   sa.sin_port   = htons(80);

   //Addresses are important, and we need the bytes in the correct order
   
   inet_aton("216.58.194.46",&sa.sin_addr);
   //inet_aton("127.0.0.1",&sa.sin_addr);
   
 
   //We need to go ahead and make the connection on the socket file descriptor  
   if (connect(sd, (struct sockaddr*)&sa, sizeof(sa))<0) {
      perror("connect");
      exit(0);
   }

   //Next we need to build our request, and send it to the server using the write() command

   //For all of you in the audience, you should know that there needs to be the double carriage return (\r\n\r\n) at the end of this.
   //Go ahead and try it for yourself and waste an hour of your time like I did.
   const char *message = "GET / HTTP/1.1\r\n\r\n";
   int length;
   length = strlen(message)+1;
   
   if(write(sd, message, length) > 0)
      write(1, message, length);
  

   //And now we use the file descriptor to read all that good stuff from Google 1024 chars at a time
   //I am sure there is a better way of determining the response size, but I am not a C programmer and this
   //was for science anyway 
   int size=1024;
   char buff[size]; 
  
   while(read(sd,&buff,size) >  0 ){
  	write(STDOUT,buff,size);
   }

  

   close(sd);
}

