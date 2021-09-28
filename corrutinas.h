//Proyecto2 SO (Ronald Esquivel, Ricardo Murillo y Dylan Gonzalez)
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>

#define MAX_HILOS 25 //maxima cantidad de hilos creados (requerimiento del proyecto)
#define QUANTUM 100 //cantidad de iteraciones por turno

typedef struct hilo{ //Struct que respresenta un hilo del scheduler
    int id; //identificador del hilo
    int tiquetes; //tiquetes del hilo (Para Lottery Scheduling)
    int desechado; //flag que indica que el hilo ya termino su trabajo, y debe ser eliminado
    int corriendo; //flag que indica que el hilo ya se ha ejecutado
    int estado; //flag que indica si el hilo se encuantra en el CPU o no
    void (*funcion)(void*); //funcion del hilo
    void* param; //parametro del hilo
    sigjmp_buf buffer_hilo; //buffer de cada hilo
    struct hilo* siguiente; //por ser una lista doblemente enlazada (dinamico), este puntero indica al siguiente nodo o hilo
    struct hilo* anterior; //indica el nodo o hilo anterior
} hilo;

hilo* primero_lottery; //indica el primer hilo de lottery
hilo* ultimo_lottery; //indica el ultimo hilo de lottery

hilo* en_CPU; //hilo que se va a encontrar en el CPU

sigjmp_buf buffer_administrador; //buffer del hilo que administra los hilos

void agregar_hilo(hilo* nuevo_hilo); //funcion encargada de insertar un nuevo hilo a la lista de hilos
void crear_hilo(void* funcion, void* param, int tiquetes); //funcion encargada de crear el hilo y asignarle sus atributos
void borrar_hilo(hilo* a_borrar); //funcion encargada de borrar un hilo de la lista de hilos
void crear_hilo(void* funcion, void* param, int tiquetes); //funcion encargada de crear el hilo y asignarle sus atributos
void administrador_hilos(); //funcion encargada de administrar los hilos, decide, junto con lottery, cuales hilos van al CPU
void finalizar_hilo(); //funcion encargada de eliminar el hilo, aya que este ya termino con sus funciones
void pausar_hilo(); //funcion que se encarga de guardar el estado del hilo, y de ceder el procesador al hilo del administrador de hilos