/*
  Description:

  Lets use file descriptors and sys calls to implement the bash 'cat' function, shall we. 

  Do Some "Light" Reading:
  http://man7.org/linux/man-pages/man2/open.2.html
  http://man7.org/linux/man-pages/man2/write.2.html
  http://man7.org/linux/man-pages/man2/read.2.html
  http://man7.org/linux/man-pages/man2/stat.2.html
*/



#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int STDOUT=1;
int STDERR=2;

int LENGTH=0;

int main(int argc, char *argv[])
{

   int size=0;
   char c;
   int buff_ind=0;

   //Lets do some quick and dirty checks to make sure the file name is at least there
   if(argc !=2){
 
     write(STDOUT,"Need file name \n",20);
     return -1;

    }

   //Open file and obtain process specific file descriptor
   //Still only using O_RDONLY flag to open the file since we are not writing to it* 
   int fd = open(argv[1],O_RDONLY);

   //When open fails it will return a `-1` for the file descriptor, we need to catch this error
   if(fd<0)
      return 1;

   //Its time to get the file size for size of the read and write using the stat() and stat struct
   // Do note how very trusting we are in this scenario where we do not attempt any exception handling on the stat() call
   struct stat file_info;
  
   //Lets populate the file_info struct using the stat() syscall 
   stat(argv[1], &file_info);

   size = file_info.st_size;
   char buff[size];

   //Use the read to build strings and dump them out to the screen
   read(fd, &buff, sizeof(buff));
   write(STDOUT_FILENO,buff,sizeof(buff));
       
   
   //Close the file
   close(fd);


   return 0;

}
