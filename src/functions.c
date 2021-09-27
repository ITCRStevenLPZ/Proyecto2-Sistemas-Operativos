#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ll Long Doule

long double factorial(int n){
    int i;
    long double fact = 1;
    if (n < 0)
        return -1;
    else {
        for (i = 1; i <= n; ++i) {
            fact *= i;
        }
        //printf("Factorial of %d = %Lf \n", n, fact);
    }
    return fact;
} 

//*+++++++++++++++++++funciones+++++++++++++++*

//pi 1,6349839
long double pi(int n){
    long double sum = 0;
    
    int i;
    for (i = 1; i <= n; i++)
    {
        long double pi = (1/(double)pow(i, 2));
        sum += pi;
        //printf("%d - %Lf \n", i, sum);
    }
    return sum;
}

//Ln
long double ln(int x, int n){
    long double sum = 0;
    
    int i;
    for (i = 1; i <= n; i++){

        int izq = pow(-1, i+1); //viene con más pero solo veo m 
        long double der = pow(x,i)/(double)i;
        long double ln = (double)izq*der;
        printf("ln = %.15Lf \n",der);
        //printf("%d - %Lf \n",i,  ln);
        sum += ln;
        //printf("%d - %Lf \n",i,  sum);
        //printf("\n"); 
        //printf("%d - %Lf \n", i, sum);
        
    }
    return sum;
}

long double ex(int x, int n){
    long double sum = 0;
    
    int i;
    for (i = 0; i <= n; i++)
    {
        sum +=  pow(x, i)/(factorial(i));
        printf("%d - %Lf \n", i, sum);
    }
    return sum;
}


long double sinxt(double x, int n){
    long double sum = 0;
    
    int i;
    for (i = 0; i <= n; i++)
    {
        long double numerador = pow(-1, i) * pow(x, (2*i+1)); 
        long double denominador = factorial(2*i+1);
        long double senx = numerador/(double) denominador;
        printf("%d Hola %.15Lf\n", i, senx);
        sum += senx;
        //printf("%d - %Lf \n", i, sum);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    // Func Factorial
    // printf("%d Fact %Lf\n", i,factorial(i));

    // serie para pi
    printf("pi es: %Lf\n", pi(100000));
    
    // ln 1+x
    // printf("         %f\n", log(2));
    printf("ln es: %.10Lf\n", ln(2, 10000));
    // printf("%f \n", pow(-1, 3));

    // exp e x
    printf("e a la x es: %Lf\n", ex(6, 65));

    // sen x
    //printf("         %f\n", sin(25));
    printf("Senx es: %Lf\n", sinxt(25, 30));

    return 0;
}
