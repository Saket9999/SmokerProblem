#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           }a,b;

int main(int argc, char *argv[])
{
	int id,val,i;
	unsigned short arr[6]={0,0,0,0,0,0};
	struct sembuf p2,p3,p4 ;
	key_t k = 1016;	
	
	id= semget(k,  6, IPC_CREAT|0777);
/*	arr[atoi(argv[1])]=1;
	arr[atoi(argv[2])]=1;
	*/
		a.array=arr;
	
			
	p2.sem_num=atoi(argv[1]);  /* semaphore number */
	p2.sem_op=+1;   /* semaphore operation */
	p2.sem_flg=0;
	
	p3.sem_num=atoi(argv[2]);  /* semaphore number */
	p3.sem_op=+1;   /* semaphore operation */
	p3.sem_flg=0;
	
/*	p4.sem_num=2;  
	p4.sem_op=+1;  
	p4.sem_flg=0;
	*/
	 
	if (id == -1)
	{
		write(1, "Create Error", 12);
		exit(0);
	}
	
	val= semctl(id, 6, SETALL, a);

	if (val <0 )
	{
		write(1, "Set Error", 10);
		exit(0);
	}
	
	if(argc!=0)
	{
	
		semop(id,&p2,1);
		semop(id,&p3,1);
	}
	
	for(i=0; i< 6; i++)
	{
		val= semctl(id,i, GETVAL, b);

		if (val <0 )
		{
			write(1, "Get Error", 10);
			exit(0);
		}
	
		printf("\n Sem Val at %d position is %d", i,val);	
	}
}
        
// (0,4) (4,3) (3,2) (2, 1) (1,0) 
