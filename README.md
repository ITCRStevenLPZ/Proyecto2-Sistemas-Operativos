# Proyecto2-Sistemas-Operativos
El propósito de este proyecto es darle familiaridad con el manejo avanzado de hilos y algunos aspectos de harware que se debe considerar.
Es importante que **no se utilice la biblioteca pthread**, sino que se implemente una solución propia que permita la creación de las **corrutinas** necesarias para poder llevar a cabo y tener control de qué procesos van al procesador.
La idea inicial de tener este proyecto es exponer al estudiante a un espacio donde hayan múltiples procesos y que éstos deban ser calendarizados por un **lottery scheduler**.
Para ello, en cierta computadora se tienen que hacer ciertos **procesos en paralelo**, entre ellos obtener una **exponenciación de e**, calcular **logaritmo neperiano**, **seno** y desde luego, el famoso **cálculo de π**. Cada uno de ellos son calculados con la **serie de Taylor** correspondiente (y desde luego almacenados en long doubles).

Para poder ejecutar el programa se debe instalar la libreria GLUT (esperando que las demás bibliotecas necesarias esten instaladas). Sólamente ingresando el comando:

    sudo apt-get install freeglut3
    
Para ejecutar el programa, primero debe ser compilado, con el comando:

    make

Para despues ejecutarlo con:

    ./scheduler
    
Luego dentro del programa se le solicitará de entrada la cantidad de procesos n. En donde, por cada n líneas el primer valor es la **cantidad de tiquetes para Lottery Scheduling**, el segundo valor es **M (iteraciones de la serie de Taylor)**, el cuarto valor es el **tipo de funcion (pi = 1, ln = 2, ex = 3 o sen = 4)** y el último valor que indica el **x**, o valor de entrada de las funciones para su cálculo (**menos en pi**). Un ejemplo de entrada es el siguiente:

     25
     10 15000 1
     20 500 2 29
     30 10000 3 100
     10 70000 4 87
     10 15000 1
     20 500 2 29
     30 10000 3 100
     10 70000 4 87
     10 15000 1
     20 500 2 29
     30 10000 3 100
     10 70000 4 87
     10 15000 1
     20 1000 2 29
     90 7000 3 100
     10 1000 4 87
     10 15000 1
     80 1000 2 29
     30 4000 3 100
     10 25000 4 87
     36 15000 1
     20 1000 2 29
     30 10000 3 100
     10 10000 4 87
     100 22000 1
