#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define MAX 1000
#define SIZE 1
#define NUMS_TO_GENERATE 1

int potencia(int exp){

	int valor=1;

	if(exp ==0)
		return 1;
	else
	if(exp == 1)
		return 10;
	else
	for(int i=0; i<exp; i++){

		valor= valor*10;
	}
	return valor;
}


int main()
{
  
   int fd[2];
   pid_t pidC;
   char buf[5];
   unsigned char num;
   int numAleatorio;
   
   int cifras[5];
   int i=0;
   char dato[5];
   char *ptr;
   
   char numero[4]; 

	int numeros[4];

	int tam;
	int valr;



   pipe(fd);
   pidC = fork();
   
   switch(pidC)   
   {
     case 0: //actividades dese el proceso hijo

	 close(fd[1]); 
         num = read(fd[0], buf, sizeof(buf) ); 
	    
		tam= buf[0];		

		for(int j=1; j < tam+1;j++){
			numero[j-1]= buf[j];
		}
					
		
		for(int j=0; j < tam;j++){			
			numeros[j]= numero[j]*1;			
		}	

		
		for(int j=0; j < tam;j++){				
			valr += numeros[j]*potencia(j);			
		}

		if(valr>0 && valr<500)	
		    printf("\nel valor menor a 500: %i\n", valr);
		else
		    if(valr>=500)	
			printf("\nel valor mayor o igual a 500: : %i\n", valr);
			

	 
         close(fd[0]);
	 exit(0);
         break;

     case -1:
         exit(EXIT_FAILURE);
         break;

     default: //actividades desde el proceso padre	

	
    	srand(time(NULL));
    		for (int i = 0; ; i++){
        		numAleatorio= (rand() % MAX);

			if(numAleatorio > 0){
			  // printf("%i\n", numAleatorio);
			   break;
			}
    		}
		
		while(numAleatorio>0){

			cifras[i]= numAleatorio % 10;
			numAleatorio= numAleatorio / 10;
			i++;
		}
			
		int a=i;

		dato[0]=i;

		for(int j=0; j<i; j++){
		
			dato[j+1]= cifras[j];
			//printf("%d\n", dato[j+1]);
			//a--;
		}		 	 

	
	 close(fd[0]);
         write(fd[1], dato, 5);
         close(fd[1]);
	 exit(0);
         break;    
   }

exit(0);
}


