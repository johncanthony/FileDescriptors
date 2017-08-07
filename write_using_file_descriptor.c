/*
  Description:
 
 Write a character string to a file in three different ways: newly created, overwrite,append 
 
  Do Some "Light" Reading:
  http://man7.org/linux/man-pages/man2/open.2.html
  http://man7.org/linux/man-pages/man2/write.2.html
*/



#include <unistd.h>
#include <fcntl.h>

int STDOUT=1;
int LENGTH=2;

int main()
{



   /*
   =====EDIT THIS AREA using the information from the open() documentation for truncation and append
   */
    

   //Open file and obtain process specific file descriptor
   int fd = open("hello_world.txt", O_WRONLY | O_APPEND);


   /*
   =====END EDIT
   */

   //When open fails it will return a `-1` for the file descriptor, we need to catch this error
   if(fd<0)
      return 1;

   
   const char *message = "A whole new line!\n";
   int length;
   length = strlen(message)+1;

   if(write(fd,message,length) != length){
      write(2,"There was an error in writing\n",31);
      return 1;
   }
   else{
     write(STDOUT,"Line Written using file descriptor.\n",40);
   }


   close(fd);

   return 0;

}
