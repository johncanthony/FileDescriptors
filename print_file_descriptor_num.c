/*
  Description:
 
  Open a file using the system call open. This will provide us with a file descriptor that
  is specific to the process that handles the execution of this code
  
  http://man7.org/linux/man-pages/man2/open.2.html
  '''
   A call to open() creates a new open file description, an entry in the
   system-wide table of open files.  The open file description records
   the file offset and the file status flags (see below).  A file
   descriptor is a reference to an open file description; this reference
   is unaffected if pathname is subsequently removed or modified to
   refer to a different file.  For further details on open file
   descriptions, see NOTES.
  '''

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



   //Open file and obtain process specific file descriptor
   //*keep in mind we are using the O_RDONLY flag to open the file only for reading* 
   int fd = open("hello_world.txt",O_RDONLY);

   //When open fails it will return a `-1` for the file descriptor, we need to catch this error
   if(fd<0)
      return 1;

   //Convert the fd integer to something that can be handled by write
   char fd_hr[11]={0x0};
   sprintf(fd_hr,"%d",fd);

   // We could have simply imported stdio.h and used printf(), but this is about sys calls and file descriptors damn it!
   // Note we are passing the file descriptor of 1 for STDOUT to print to the terminal
   write(STDOUT, fd_hr, sizeof(fd_hr));
   write(STDOUT, "\n", 3);


   return 0;

}
