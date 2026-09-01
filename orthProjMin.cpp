#include <iostream>
#include <cmath>
#include <algorithm>

//Implementing integration via Simpson's rule as error is O(h^4)
double simpsonIntegr(double (*f)(double), double a, double b, int n){
    
    if(n % 2 == 1) n++;

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for(int i = 1; i < n; i++){

        int c = (i % 2 == 0) ? 2 : 4; //4 if odd, 2 if even
        sum += c * f(a + h * i);
    }

    sum *= (h / 3);

    return sum;
}

double f(double x){
    return sin(x) + pow(x, 2);
}

int main(){

    double approxIntegr = simpsonIntegr(f, 2, 5, 1000);
    std::cout << approxIntegr;

    return 0;
}