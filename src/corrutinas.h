
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

typedef struct corrutinas
{

    jmp_buf thread;
    int numBoletos;
    int iteraciones;
    int numFunc; //numero de función a correr
    int parametro; //solamente si es pi no lo ocupa

}hilo;
