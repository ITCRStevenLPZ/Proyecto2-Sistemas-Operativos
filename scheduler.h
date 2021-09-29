/*
 * Instituto Tecnologico de Costa Rica
 * Escuela de Ingenieria en Computacion
 * Sistemas Operativos
 *
 * Segundo proyecto de Sistemas Operativos
 * Ronald Esquivel Lopez
 * Ricardo Murillo Jimenez
 * Dylan Gonzalez
 *
 * Programa: Scheduler Header
 * Archivo:  scheduler.h
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <string.h>
#include "corrutinas.h"

#define H_SIZE 1000
#define V_SIZE 800

#define ANCHO 600 //ancho de la barra de progreso
#define ALTO  17 // alto de la barra de progreso

#define ESPACIO 10 //espacio entre barras de progreso


void RenderString(float x, float y, void *font, const char* string, const char* id,int r, int g, int b);

void dibujar_escena(); //funcion encargada de recorrer toda la lista enlazada de hilos y dibujar de cada uno una barra de progreso

#endif