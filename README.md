# Proyecto2-Sistemas-Operativos
El propósito de este proyecto es darle familia- ridad con el manejo avanzado de hilos y algunos aspectos de harware que se debe considerar.
Es importante que no se utilice la bibliote- ca pthread, sino que se implemente una solución propia que permita la creación de las corrutinas necesarias para poder llevar a cabo y tener control de qué procesos van al procesador.
La idea inicial de tener este proyecto es exponer al estudiante a un espacio donde hayan múltiples procesos y que éstos deban ser calendarizados por un lottery scheduler.
Para ello, en cierta computadora se tienen que hacer ciertos procesos en paralelo, entre ellos obtener una exponenciación de e, calcular logaritmo neperiano, seno y desde luego, el famoso cálculo de π. Cada uno de ellos son calculados con la serie de Taylor correspondiente (y desde luego almacenados en long doubles).
