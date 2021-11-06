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
   
   key = 1233;

   id = semget(key, 1, 0666 | IPC_CREAT); //grab the semaphore set
   if (id < 0)
   {
      exit(1); // exit unsuccessfully
   }

   printf("Press enter to lock: ");
   getchar();

   res = semop(id, &sbuf, nsem); // perform operation on semaphore

   // set to allocate resource
   sbuf.sem_num = 0;
   sbuf.sem_op = -1; // entered ccritical section
   sbuf.sem_flg = 0;
   // set to allocate resource

   if (res == -1)
   {
      exit(1); // exit unsuccessfully
   }

   printf("Locked\n");

   fd = open("data.txt", O_RDONLY); // open file in Read only mode
   if (fd < 0)                      // check if file is opened or not
   {
      exit(1); // exit unsuccessfully
   }

   read(fd, buffer, sizeof(buffer));               // read from file
   printf("\nData from data.txt: %s\n\n", buffer); // print the read message
   close(fd);                                      // close the file

   printf("Press enter to unlock: ");
   getchar();

   sbuf.sem_num = 0;
   sbuf.sem_op = 1; // releasing resouces
   sbuf.sem_flg = 0;

   res = semop(id, &sbuf, nsem);
   if (res == -1)
   {
      exit(1);
   }
   printf("Unlocked\n");

   semctl(id, 1, IPC_RMID); // remove the semaphore

   return 0;
}