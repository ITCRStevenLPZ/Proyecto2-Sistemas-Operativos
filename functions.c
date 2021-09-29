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
            //printf("i=%d / %Lf\n",i, fact);
        }
        //printf("Factorial of %d = %Lf \n", n, fact);
    }
    return fact;
} 

long double fact(int n)  
{  
  if (n == 0)  
    return 1;  
  else  
    return(n * fact(n-1));  
}  
    int n,i=1,f=1;
     
    
unsigned long long int factu(int x)
{
    
    int i=1;
    unsigned long long f = 1;
    while(i<=x)
    {
        f=f*i;
        printf("%d fact= %llu: \n",i,f);
        i++;
    }
    printf("f %llu: \n", f);
    return f;
}

long double power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
}
  
long double powerd (double x, int y)
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
long double pi(int n){  
    long double sum = 0;
    
    int i;
    for (i = 1; i <= n; i++)
    {
        long double pi = (1/(long double)powerd(i, 2));
        sum += pi;
        //printf("%d - %Lf \n", i, sum);
    }
    return sum;
}

//Ln
long double ln(double x, int n){
    long double sum = 0;
    
    int i;
    for (i = 1; i <= n; i++){

        int izq = pow(-1, i+1); //viene con más pero solo veo m 
        long double der = powerd(x,i)/(double)i;
        long double ln = (double)izq*der;
        //printf("ln = %.15Lf \n",der);
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
        long double res = powerd(x, i)/(long double)factorial(i);
        if (isnan(res) || isinf(res))
        {
            sum+=0;
        }else
        {
            sum += res;
        }
        
        //printf("%d - %.20Lf \n", i, sum);
    }
    return sum;
}


long double sinxt(double x, int n){
    long double sum = 0;
    
    int i;
    for (i = 0; i <= n; i++)
    {
        long double numerador = powerd(-1.0f, i) * powerd(x, (2*i+1)); 
        long double denominador = factorial(2*i+1);
        long double senx = numerador/(long double)denominador;
        //  printf("%d Hola %.15Lf\n", i, senx);
        if (isnan(senx) || isinf(senx)){
            sum+=0;
        }else{
            sum += senx;
        }
        //printf("%d - %Lf \n", i, sum);

    }
    printf("Senx es: %Lf\n", sum);
    long double toR = (sum*180)/M_PI;
    return toR;
}

int main(int argc, char const *argv[])
{   

    // Func Factorial
    //  printf("Factorial: %Lf \n", factorial(1754));//1754 = max
    //  printf("Factorial: %Lf \n", factorial(1754));//1754 = max

    // serie para pi
    //printf("pi es: %.25Lf\n", pi(1000000));
    
    // ln 1+x
    // printf("         %f\n", log(2));i    
    // printf("ln es: %.20Lf\n", ln(0.9f, 99999));
    // printf("%f \n", pow(-1, 3));

    // exp e x
    // printf("e a la x es: %.15Lf\n", ex(43, 10000));

    // sen x
    // printf("         %f\n", sin(25));


    printf("Senx es: %Lf\n", sinxt(35, 20));        


    /*
    long double numerador = powl(-1, 145) * powl(25, (2*145+1)); 
    long double denominador = factorial(2*145+1);
    long double senx = numerador/(double) denominador;
    printf("seno es %.15Lf\n", senx);   
    printf("Fact %LF\n", (long double)(powl(25, (2*145+1))));
    */
    return 0;
}
