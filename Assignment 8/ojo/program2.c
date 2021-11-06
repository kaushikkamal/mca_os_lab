#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <unistd.h>

int main()
{
   int fd;
   int id, res;
   char buffer[50];
   key_t key;
   struct sembuf sbuf;
   size_t nsem = 1;

   key = 4455;

   id = semget(key, 1, 0666); //grab the semaphore set 

   if (id < 0)
   {
      exit(1); 
   }

   res = semctl(id, 1, GETVAL); // get the semaphore value

   if (res < 0)
   {
      printf("File is locked\n");
      exit(1); 
   }

   fd = open("data.txt", O_RDONLY); // open file in Read only mode
   if (fd < 0)                      // check if file is opened or not
   {
      exit(1); // exit unsuccessfully
   }

   read(fd, buffer, sizeof(buffer));             
   printf("\nData from data.txt: %s\n", buffer); 
   close(fd);                                   

   sbuf.sem_num = 0;
   sbuf.sem_op = 1; // releasing resouces
   sbuf.sem_flg = 0;

   res = semop(id, &sbuf, nsem);
   if (res == -1)
   {
      exit(1);
   }

   return 0;
}