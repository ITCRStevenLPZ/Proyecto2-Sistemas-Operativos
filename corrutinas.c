//Proyecto2 SO (Ronald Esquivel, Ricardo Murillo y Dylan Gonzalez)
#include "corrutinas.h"

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


hilo* sorteo(){ //funcion encargada de sortear el siguiente hilo a entrar al CPU. Es una implementacion simple de Lottery Shecduling

    int resultado_sorteo = (rand() % (tiquetes_totales));

    hilo* actual = primero_lottery;

    if(actual == NULL){
        printf("SORTEO - NO HAY HILOS EN LA LISTA\n");
        return NULL;
    }else{
        printf("SORTEO - SE REALIZA EL SORTEO\n");
        int tiquetes_de_actual = actual->tiquetes;

        while(tiquetes_de_actual <= resultado_sorteo){ //este while determina el hilo ganador
            actual = actual->siguiente;
            tiquetes_de_actual += actual->tiquetes;
        }
        return actual;
    }


}



void crear_hilo(void* funcion, parametros* param, int tiquetes, int pos_Y, int fun_id){ //funcion encargada de crear el hilo y asignarle sus atributos
    hilo* nodo =(hilo*)malloc(sizeof(hilo));
    nodo->pos_Y = pos_Y;
    nodo->fun_id = fun_id;
    nodo->estado = 1; //el hilo esta listo
    nodo->id = contador_id++;
    nodo->tiquetes = tiquetes;
    nodo->funcion = funcion;
    nodo->param = param;
    nodo->corriendo = 0;
    nodo->desechado = 0;
    nodo->i = 0;

    agregar_lottery(nodo);
}



void administrador_hilos(){ //funcion encargada de administrar los hilos, decide, junto con lottery, cuales hilos van al CPU

    printf("ADMIN - ENTRO\n");
    if(en_CPU != NULL && en_CPU->estado == 2){
        en_CPU->estado = 1;
    }

    if(primero_lottery == NULL){ //cuando no hay mas hilos, termina
        printf("ADMIN - NO HAY HILOS EN LA LISTA\n");
        en_CPU = NULL;
        exit(0);
    }
    else{
        en_CPU = sorteo(); //se sortea el hilo que va a ir al CPU
    }

    
    if(en_CPU->estado != 1){
        administrador_hilos();

    }else{
        
        en_CPU->estado = 2; //el nodo esta en run

        if (sigsetjmp(buffer_administrador,1) != 0) { //quiere decir que el thread en el CPU se pauso o termino su ejecucion
            administrador_hilos();
        }

        if(en_CPU->corriendo == 0){
            en_CPU->corriendo = 1;
            (*en_CPU->funcion)(en_CPU->param);
        }else{
            siglongjmp(en_CPU->buffer_hilo,1);
        }
    }
}


void finalizar_hilo(){ //funcion encargada de eliminar el hilo, aya que este ya termino con sus funciones
    if(en_CPU != NULL){

        tiquetes_totales -= en_CPU->tiquetes;
        printf("FINALIZAR - SE ELIMINA EL HILO CON ID %d\n", en_CPU->id);
        borrar_hilo(en_CPU);
        if(en_CPU->desechado == 1){
            free(en_CPU);
        }

        siglongjmp(buffer_administrador, 1);
    }
}


