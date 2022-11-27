#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

int main(int argc, char *argv[])
{
	int len,val,i=0;
	int left,right,id;
	char buf[30];
	
	key_t k = 1016;	
 	struct  sembuf p1,p5,p2,p4;
	time_t t;
	
	left=atoi(argv[2]);	
	right=atoi(argv[3]);
	p1.sem_num=left;  
	p1.sem_op=-1;  
	p1.sem_flg=0; 

	p5.sem_num=right; 
	p5.sem_op=-1;  
 	p5.sem_flg=0; 

	p2.sem_num=left; 
	p2.sem_op=+1;  
	p2.sem_flg=0;  

	p4.sem_num=right;  
	p4.sem_op=+1;  
 	p4.sem_flg=0;  



	id= semget(k, 3, IPC_CREAT|0777);
	
	if (id ==-1 )
	{
		write(1, "Create Error", 12);
		exit(0);
	}

	while (1)
	{
		
		write(1, argv[1], sizeof(argv[1])+2 );
		write(1,"\n",1);
		write(1,"^^^^^^^^^^^^^^^",15);
		write(1,"\n",1);
			
		if(left==0 && right==1)
		{
			write(1,"Cigarette is available\n",23);
		}
		else if(left==2 && right==3)
		{
			write(1,"Paper is available\n",19);
		}
		else
		{
			write(1,"Match is available\n",19);
		}
		
		sleep(rand()%3);
	
		val=semop(id,&p1,1);
		if (val == -1 )
		{
			write(1, " Error", 5);
			exit(0);
		}
		if(left==0 || left==4)
		{
			write(1,"Paper is available\n",18);
		}
		else if(left==2)
		{
			write(1,"Cigarette is available",23);
		}
		
		sleep(rand()%3);
		
		val=semop(id,&p5,1);
		write(1,"\n",1);
		if (val ==-1 )
		{
			write(1, "Error", 5);
			exit(0);
		}
		if(right==1 || right==3)
		{
			write(1,"Match is available\n",18);
		}
		else if(right==5)
		{
			write(1,"Cigarette is available\n",23);
		}
	
		write(1,"\n",1);
		write(1,"====SMOKING=====", 16);
		write(1,"\n",1);
		
		sleep(7);
	

		sleep(rand()%3);				
		write(1,"\n", 1);
		i++;
		
	}
	
}
	
       

