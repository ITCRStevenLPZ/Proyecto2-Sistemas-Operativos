//Proyecto2 SO (Ronald Esquivel, Ricardo Murillo y Dylan Gonzalez)
#include "corrutinas.h"

int contador_id = 0; // variable global que sirve para asignar los ids diferentes a cada hilo.

int tiquetes_totales = 0; //tiquetes totales en toda la ejecucion, basicamente es la suma de todos los tiquetes individuales

void agregar_hilo(hilo* nuevo_hilo){ //funcion encargada de insertar un nuevo hilo a la lista de hilos

    if(primero_lottery == NULL){
        nuevo_hilo->siguiente = NULL;
        nuevo_hilo->anterior = NULL;
        primero_lottery = nuevo_hilo;
        ultimo_lottery = nuevo_hilo;
    }

    else{
        ultimo_lottery->siguiente = nuevo_hilo;
        nuevo_hilo->anterior = ultimo_lottery;
        nuevo_hilo->siguiente = NULL;
        ultimo_lottery = nuevo_hilo;
    }
}

void borrar_hilo(hilo* a_borrar){ //funcion encargada de borrar un hilo de la lista de hilos

    if(primero_lottery == a_borrar){
        primero_lottery = a_borrar->siguiente;

        if(primero_lottery != NULL){
            primero_lottery->anterior = NULL;
        }
    }

    else if(ultimo_lottery == a_borrar){
        ultimo_lottery = a_borrar->anterior;
        ultimo_lottery->siguiente = NULL;
    }

    else{
        a_borrar->anterior->siguiente = a_borrar->siguiente;
        a_borrar->siguiente->anterior = a_borrar->anterior;
    }
}


void agregar_lottery(hilo* nuevo_hilo){ //funcion encargada de agregar el hilo al sorteo de Lottery   
    
    agregar_hilo(nuevo_hilo);
    tiquetes_totales += nuevo_hilo->tiquetes;
}


void crear_hilo(void* funcion, void* param, int tiquetes){ //funcion encargada de crear el hilo y asignarle sus atributos
    hilo* nodo =(hilo*)malloc(sizeof(hilo));

    nodo->id = contador_id++;
    nodo->tiquetes = tiquetes;
    nodo->funcion = funcion;
    nodo->param = param;
    nodo->corriendo = 0;
    nodo->desechado = 0;

    agregar_lottery(nodo);
}



void administrador_hilos(){ //funcion encargada de administrar los hilos, decide, junto con lottery, cuales hilos van al CPU

    //The last thread that used the CPU is marked as ready
    if(en_CPU != NULL && en_CPU->estado == 2){
        en_CPU->estado = 1;
    }

    if(primero_lottery == NULL){ //cuando no hay mas hilos, termina
        en_CPU = NULL;
        exit(0);
    }
    else{
        //en_CPU = sorteo(lottery_threads, ticket_amount);
    }

    //If the selected thread is no ready to run, calculates a new thread
    if(en_CPU->estado != 1){

        administrador_hilos();

    }else{

        en_CPU->estado = 2;

        if (sigsetjmp(buffer_administrador,1) != 0) { //quiere decir que el thread en el CPU se pauso o termino su ejecucion
            administrador_hilos();
        }

        //If the thread has not started its execution
        if(en_CPU->corriendo == 0){
            en_CPU->corriendo = 1;
            (*en_CPU->funcion)(en_CPU->param);
        }

        //When the thread context has to be restored
        else{
            siglongjmp(en_CPU->buffer_hilo,1);
        }
    }
}


void finalizar_hilo(){ //funcion encargada de eliminar el hilo, aya que este ya termino con sus funciones
    if(en_CPU != NULL){

        tiquetes_totales -= en_CPU->tiquetes;
        borrar_hilo(en_CPU);

        if(en_CPU->desechado == 1){
            free(en_CPU);
        }

        siglongjmp(buffer_administrador, 1);
    }
}

void pausar_hilo(){ //funcion que se encarga de guardar el estado del hilo, y de ceder el procesador al hilo del administrador de hilos

    if(sigsetjmp(en_CPU->buffer_hilo,1) == 0){
        siglongjmp(buffer_administrador,1);
    }
}


void prueba(void* M){ //funcion de prueba que va a recorrer el hilo
    int m = *((int *)M);
    long double sum = 0;
    int i;
    for (i = 1; i <= m; i++){
        if(i+1 % QUANTUM == 0){
            pausar_hilo();
        }
        long double pi = (1/(double)pow(i, 2));
        sum += pi;
        //printf("%d - %Lf \n", i, sum);
    }
    finalizar_hilo();
}

int main(){
    srand(time(NULL));
    int* M = (int*)malloc(sizeof(int));
    *M = 60000;
    crear_hilo(&prueba, (void*) M, 50);
    return 0;
    }
