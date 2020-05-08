//
//  Pho.c
//  
//
//  Created by Iho Lopez on 27/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//#include <gmp.h>
//gcc new.c -lm -lgmp


#define MAX 100000000

#define LMT 10000
bool isprime[MAX];

void sieve()    //Sieve of Eratosthenes
{
    memset(isprime, true, sizeof(isprime));
    
  unsigned long long int i, k, j;
  /* mpz_t i,k,j;
    
    mpz_init(i);
    mpz_init(k);
    mpz_init(j);*/
    
    isprime[1] = false;
    for (i=4; i <= MAX; i+=2)
    {//i=4;    mpz_init(i,4);
        isprime[i] = false;
    }
    for (i = 3; i <= LMT; i+=2)
    {
        if(isprime[i])
            for (j = i*i, k = i<<1; j <= MAX; j+=k)
            {
                isprime[j] = false;
            }
    }
}

unsigned long long int abso(unsigned long long int a)     //fn to return absolute value
{
    /*mpz_t a;
    mpz_init(a);*/
    return a>0?a:-a;
}
unsigned long long int gcd( long long int a, long long int b)//mpz_t a, mpz_t b)    //Euclidean GCD recursive fn
{
    //mpz_t a, b;
   // mpz_init(a);
    //mpz_init(b);
    
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}


unsigned long long int pollard_rho(unsigned long long int n)  //pollard rho implementation
{
    //mpz_t n;
  //  mpz_init(n);
    if(n%2==0)
        return 2;
    //mpz_t x,c,y,g;
   // mpz_init(x);
    //mpz_t c;
   // mpz_t y;
    //mpz_t g;
   // mpz_init(c);
   // mpz_init(y);
   // mpz_init(g);
   unsigned long long int x = rand()%n+1;
  unsigned long long  int c = rand()%n+1;
   unsigned long long int y = x;
   unsigned long long int g = 1;
    
    //fn is f(x) = x*x + c
    while(g==1)
    {
        x = ((x*x)%n + c)%n;
        y = ((y*y)%n + c)%n;
        y = ((y*y)%n + c)%n;
        g = gcd(abso(x-y),n);
    }
    return g;
}

unsigned long long int factors[MAX/100], total;

void factorize(unsigned long long int n)   //fn to factorize the number
{
    if(n == 1)
        return;
    
    if(isprime[n])      //if n is prime,store it
    {
        factors[total++] = n;
        return;
    }
    unsigned long long int divisor = pollard_rho(n);   //get a divisor of n
    factorize(divisor);
    factorize(n/divisor);
}

int main()  //Driver Program
{
    srand(time(NULL));
    sieve();
    
    unsigned long long int n;
    //printf("Enter N: ");
    
    scanf("%lld",&n);
    
    total = 0;
    factorize(n);
    
    printf("The two factors are: ");
    for (unsigned long long int i = 0; i < total; ++i)
    {
        //printf("The two factors are: ");
        printf("%llu ",factors[i] );
    }
    printf("\n");
    return 0;
}




