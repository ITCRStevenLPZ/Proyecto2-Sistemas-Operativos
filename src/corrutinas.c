#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <unistd.h>
#include "corrutinas.h"


#define MAXTHREAD 25
jmp_buf thread[MAXTHREAD];
hilo hilos[MAXTHREAD];

jmp_buf mainBuff;
jmp_buf pruebaBuff;
jmp_buf pruebbBuff;
jmp_buf pruebcBuff;

int cantThreads;
int currenThread;

int cantBilletes[MAXTHREAD] = { [0 ... MAXTHREAD-1 ] = -1 };
int limitesSup[MAXTHREAD] = { [0 ... MAXTHREAD-1 ] = -1 };
int funcAcorrer[MAXTHREAD] = { [0 ... MAXTHREAD-1 ] = -1 };
int param[MAXTHREAD] = { [0 ... MAXTHREAD-1 ] = -1 };

int a = 0;
int b = 0;
int c = 0;


FILE *PARAM;
/*
Obtener paramtros
*/
void obtener_parametros(){ //funcion encargada de leer los parametros del parametros.txt, que van a aser usados durante todo el programa
	printf("leyendo params\n");
	fscanf(PARAM, "%d", &cantThreads);
	int i;
	for (i = 0; i < cantThreads; i++)
	{
		fscanf(PARAM, "%d %d %d %d", &hilos[i].numBoletos, &hilos[i].iteraciones, &hilos[i].numFunc, &hilos[i].parametro);
	}
}  


void prueba(void){
	printf("aaaa: %d\n", a);
	printf("Entré a prueba de a\n");
	if(setjmp(hilos[currenThread].thread)==0){//if(setjmp(pruebaBuff)==0){
		printf("iniciamos el caos en a\n");
	}else{

		printf("entré a if de prueba de a\n");
		int i;
		for (i = 1; i <= 15; i++)//sumar a x veces
		{
			printf("a mayus: %d\n", a);
			if (i%5==0)//romper ciclo. guardar, ir a main a x reps
			{
				longjmp(mainBuff, 1);
			}
			a++;
			printf("AC: %d\n", a);
		}
			
	}
	//longjmp(mainBuff, 1);/sirve
}

void pruebb(void){
	printf("bbbbbb: %d\n", b);
	printf("Entré a prueba de b\n");
	if(setjmp(hilos[currenThread].thread)==0){
		printf("iniciamos el caos en b\n");
	}else{

		printf("entré a if de prueba de b\n");
		int i;
		for (i = 1; i <= 15; i++)//sumar a x veces
		{
			printf("b mayus: %d\n", b);
			if (i%5==0)//romper ciclo. guardar, ir a main a x reps
			{
				longjmp(mainBuff, 1);
			}
			b++;
			printf("BC: %d\n", b);
		}
			
	}
	//longjmp(mainBuff, 1);/sirve
}

void pruebc(void){
	printf("cccccc: %d\n", c);
	printf("Entré a prueba en c\n");
	if(setjmp(hilos[currenThread].thread)==0){
		printf("iniciamos el caos en c\n");
	}else{

		printf("entré a if de prueba en c\n");
		int i;
		for (i = 1; i <= 15; i++)//sumar a x veces
		{
			printf("c mayus: %d\n", c);
			if (i%5==0)//romper ciclo. guardar, ir a main a x reps
			{
				longjmp(mainBuff, 1);
			}
			c++;
			printf("CC: %d\n", c);
		}
			
	}
	//longjmp(mainBuff, 1);/sirve
}


int main(){

	printf("Main\n");
	PARAM = fopen ("parametros.txt","r");
	if(PARAM == NULL){
		printf("No se puede abrir archivo\n") ;
	}else{
		obtener_parametros();
	}

	printf("Ya obtube parametros\n");
	int i;

	printf("cant %d\n", cantThreads);
	for (i = 0; i < cantThreads; i++){
		printf("params: boletos:%d iteraciones:%d func:%d parametro%d \n", hilos[i].numBoletos, hilos[i].iteraciones, hilos[i].numFunc, hilos[i].parametro);
	}

	if(setjmp(mainBuff)==0){
		for (i = 0; i < cantThreads; i++){
			currenThread = i;
			if (hilos[i].numFunc==1)
			{
				prueba();
			}else if (hilos[i].numFunc==2)
			{
				pruebb();
			}else
			{		
				pruebc();
			}
		}		
		printf("Entré al if, voy a llamar a prueba \n");
	}
	while (a<10){
			printf("I am inside the while +++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("a = %d\n", a);
			sleep(1);

			//generar random
			int num = (rand() % (3 - 1 + 1));
			currenThread = num;
			printf("el random sleccionado fue: %d\n", num);

			hilo currentHilo = hilos[num];
			
			if (currentHilo.numFunc==1)
			{
				printf("aa: %d\n", a);
				longjmp(currentHilo.thread, 1);
			}else if (currentHilo.numFunc==2)
			{
				printf("ab: %d\n", b);
				longjmp(currentHilo.thread, 1);
			}else{
				printf("ac: %d\n", c);
				longjmp(currentHilo.thread, 1);
			}
		}		
	


	/*
	printf("Hola, Estamos iniciando el programa, por favor espere.\n");
	if(setjmp(mainBuff)==0){
		printf("Entré al if, voy a llamar a prueba \n");
		prueba();
		pruebb();	
		pruebc();
	}
	while (a<10)
	{
		//generar random
		int num = (rand() % (3 - 1 + 1)) + 1;
		printf("el random sleccionado fue: %d\n", num);
		if (num==1)
		{
		printf("aa: %d\n", a);
		longjmp(pruebaBuff, 1);
		}else if (num==2)
		{
		printf("ab: %d\n", b);
		longjmp(pruebbBuff, 1);
		}else
		{
		printf("ac: %d\n", c);
		longjmp(pruebcBuff, 1);
		}
	}
	printf("este es a final: %d\n", a);
	printf("este es b final: %d\n", b);
	printf("este es c final: %d\n", c);
	*/
	return 0;
}
