#include "scheduler.h"

int Y = (V_SIZE - 30);

unsigned long long factorial(int x)
{
    unsigned long long aux = 1;
    while(x > 1) {
        aux *= x;
        x--;
    }
    return aux;
}

long double powerd (long double x, long int y)
{
    long double temp;
    if (y == 0)
    return 1;
    temp = powerd (x, y / 2);
    if ((y % 2) == 0) {
        return temp * temp;
    } else {
        if (y > 0)
            return x * temp * temp;
        else
            return (temp * temp) / x;
    }
}
//*+++++++++++++++++++funciones+++++++++++++++*

//pi 1,6349839
void pi(parametros* args){ //funcion que recorre en hilo, en este caso calcula el numero pi
    long double sum = 0;
    int i;

    for (i = 1; i <= args->M; i++){
        if(i % QUANTUM == 0){
            printf("CALCULO PI - Iteracion = %d - Resultado por ahora = %Lf \n", i, sum);
            en_CPU->i = i;
            en_CPU->sum = sum; //se guarda el entorno local
            glutPostRedisplay();
            dibujar_escena();
            if(sigsetjmp(en_CPU->buffer_hilo,1) == 0){
                siglongjmp(buffer_administrador,1);      // se pausa el hilo
            }
            i = en_CPU->i;
            sum = en_CPU->sum; //se asigna en el entorno local, el que se guardo antes de que se pausara
            args = en_CPU->param;
        }
        long double pi = (1/(double)powerd(i, 2));
        sum += pi;
    }

    en_CPU->desechado = 1; //se desecha el hilo, no hay necesidad de usarlo despues.
    glutPostRedisplay();
    dibujar_escena();
    finalizar_hilo();
}

//Ln
void ln(parametros* args){//funcion que recorre en hilo, en este caso calcula el lagoritmo natural de un numero X
    long double sum = 0;
    int i;
    for (i = 1; i <= args->M; i++){

        if(i % QUANTUM == 0){
            printf("CALCULO LN - Iteracion = %d - Resultado por ahora = %Lf \n", i, sum);
            en_CPU->i = i;
            en_CPU->sum = sum; //se guarda el entorno local
            glutPostRedisplay();            
            dibujar_escena();
            if(sigsetjmp(en_CPU->buffer_hilo,1) == 0){
                siglongjmp(buffer_administrador,1);      // se pausa el hilo
            }
            i = en_CPU->i;
            sum = en_CPU->sum; //se asigna en el entorno local, el que se guardo antes de que se pausara
            args = en_CPU->param;
        }

        long double agr = powerd(-1.0f, (((long double)(i)+1) * (powerd((long double)args->X,i)/i)));
         
        if(sum + agr != INFINITY && sum + agr != -INFINITY){
            sum += agr; //viene con más pero solo veo m
        }

    }
    en_CPU->desechado = 1; //se desecha el hilo, no hay necesidad de usarlo despues.
    glutPostRedisplay();
    dibujar_escena();
    finalizar_hilo();
}

void ex(parametros* args){//funcion que recorre en hilo, en este caso calcula e elevado a un numero X
    long double sum = 0;
    
    int i;
    for (i = 0; i <= args->M; i++)
    {
        if(i != 0 && i % QUANTUM == 0){
            printf("CALCULO EULER - Iteracion = %d - Resultado por ahora = %Lf \n", i, sum);
            en_CPU->i = i;
            en_CPU->sum = sum; //se guarda el entorno local
            glutPostRedisplay();
            dibujar_escena();
            if(sigsetjmp(en_CPU->buffer_hilo,1) == 0){
                siglongjmp(buffer_administrador,1);      // se pausa el hilo
            }
            i = en_CPU->i;
            sum = en_CPU->sum; //se asigna en el entorno local, el que se guardo antes de que se pausara
            args = en_CPU->param;
        }

        long double agr = (powerd((long double)args->X, i))/(long double)(factorial(i));

        if(sum + agr != INFINITY && sum + agr != -INFINITY){
            sum += agr; //viene con más pero solo veo m
        }

    }
    en_CPU->desechado = 1; //se desecha el hilo, no hay necesidad de usarlo despues.
    glutPostRedisplay();
    dibujar_escena();
    finalizar_hilo();
}


void sinxt(parametros* args){ //funcion que recorre en hilo, en este caso calcula el sen de un numero X
    long double sum = 0;
    
    int i;
    for (i = 0; i <= args->M; i++)
    {
        if(i != 0 && i % QUANTUM == 0){
            printf("CALCULO SENO - Iteracion = %d - Resultado por ahora = %.15Lf \n", i, sum);
            en_CPU->i = i;
            en_CPU->sum = sum; //se guarda el entorno local
            glutPostRedisplay();
            dibujar_escena();
            if(sigsetjmp(en_CPU->buffer_hilo,1) == 0){
                siglongjmp(buffer_administrador,1);      // se pausa el hilo
            }
            i = en_CPU->i;
            sum = en_CPU->sum; //se asigna en el entorno local, el que se guardo antes de que se pausara
            args = en_CPU->param;
        }

        long double agr = (powerd(-1.0f, i) * (powerd((long double)(args->X), ((2*i) + 1)))) / (long double)(factorial(2*i+1));

        if(sum + agr != INFINITY && sum + agr != -INFINITY){
            sum += agr; //viene con más pero solo veo m
        }
    }
    en_CPU->desechado = 1; //se desecha el hilo, no hay necesidad de usarlo despues.
    glutPostRedisplay();
    dibujar_escena();
    finalizar_hilo();
}

void dibujar_escena(){ //funcion encargada de recorrer toda la lista enlazada de hilos y dibujar de cada uno una barra de progreso
    
    hilo* actual = primero_lottery;

    while(actual != NULL){ 
    	double progreso;

    	if(actual-> desechado == 1){
    		progreso = 1;
    	}else{
    		progreso = (double) actual->i / (double) actual->param->M;
    	}
        
        int pos_Y = actual->pos_Y;

        //printf("PINTO\n");

        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glVertex2f(ESPACIO,pos_Y);
        glVertex2f(ESPACIO + ANCHO, pos_Y);
        glVertex2f(ESPACIO + ANCHO, pos_Y + ALTO);
        glVertex2f(ESPACIO, pos_Y + ALTO);
        glEnd();

        char* frase;

        char* hilo_id;
        sprintf(hilo_id, "%d", actual->id);


        if(actual->fun_id == 1){

        	frase = "FUN - PI, ID del Hilo: ";
        	RenderString(ESPACIO, pos_Y, GLUT_BITMAP_TIMES_ROMAN_10, frase, hilo_id, 255, 255, 255);
        	glColor3f(1,0,0);

        }else if(actual->fun_id == 2){

        	frase = "FUN - LN, ID del Hilo: ";
        	RenderString(ESPACIO, pos_Y, GLUT_BITMAP_TIMES_ROMAN_10, frase, hilo_id, 255, 255, 255);
        	glColor3f(0,1,0);

        }else if(actual->fun_id == 3){

        	frase = "FUN - EX, ID del Hilo: ";
        	RenderString(ESPACIO, pos_Y, GLUT_BITMAP_TIMES_ROMAN_10, frase, hilo_id, 255, 255, 255);
        	glColor3f(0,0,1);

        }else{

        	frase = "FUN - SEN, ID del Hilo: ";
        	RenderString(ESPACIO, pos_Y, GLUT_BITMAP_TIMES_ROMAN_10, frase, hilo_id, 255, 255, 255);
        	glColor3f(1,0,1);

        }

        glBegin(GL_QUADS);
        glVertex2f(ESPACIO,pos_Y);
        glVertex2f(ESPACIO+(progreso * ANCHO), pos_Y);
        glVertex2f(ESPACIO+(progreso * ANCHO), pos_Y+ALTO);
        glVertex2f(ESPACIO, pos_Y+ALTO);
        glEnd();

        actual = actual->siguiente;
    }
    
    //sleep(1);
    glFlush();
}

void RenderString(float x, float y, void *font, const char* string, const char* id,int r, int g, int b)
{  
  char *c;

  glColor3f(r, g, b); 
  glRasterPos2f(x + ANCHO + ESPACIO, y + (ALTO/2));
  glutBitmapString(font, string);

  glRasterPos2f(x + ANCHO + ESPACIO + 150, y + (ALTO/2));
  glutBitmapString(font, id);

  glEnd();
}

int main(int argc, char** argv){
    srand(time(NULL));
    tiquetes_totales = 0;
    contador_id = 0;
    en_CPU = NULL;

    int procesos, i;

    scanf("%d", &procesos);

    for(i = 0; i < procesos; i++){
    	int tiquetes, m, tipo_funcion, x;
    	scanf("%d %d %d %d", &tiquetes, &m, &tipo_funcion, &x);
    	
    	if(tipo_funcion == 1){

    		parametros* param =(parametros*)malloc(sizeof(parametros));
    		param->M = m;
    		crear_hilo(&pi, (parametros*) param, tiquetes, Y, tipo_funcion);

    	}else if(tipo_funcion == 2){

    		parametros* param =(parametros*)malloc(sizeof(parametros));
    		param->M = m;
    		param->X = x;
    		crear_hilo(&ln, (parametros*) param, tiquetes, Y, tipo_funcion);

    	}else if(tipo_funcion == 3){

    		parametros* param =(parametros*)malloc(sizeof(parametros));
    		param->M = m;
    		param->X = x;
    		crear_hilo(&ex, (parametros*) param, tiquetes, Y, tipo_funcion);

    	}else if(tipo_funcion == 4){

    		parametros* param =(parametros*)malloc(sizeof(parametros));
    		param->M = m;
    		param->X = x;
    		crear_hilo(&sinxt, (parametros*) param, tiquetes, Y, tipo_funcion);

    	}

    	Y-= (ESPACIO + ALTO);

    }

    glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(H_SIZE,V_SIZE);
  	glutCreateWindow("Scheduler: Thre-rribles");
  	glClear(GL_COLOR_BUFFER_BIT);
  	gluOrtho2D(-0.5, H_SIZE +0.5, -0.5, V_SIZE + 0.5);
  	glutDisplayFunc(dibujar_escena);

  	administrador_hilos();

  	glutMainLoop();

    
    return 0;
}