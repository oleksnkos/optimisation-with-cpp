#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>

//Function product
std::function<double(double)> product(double (*f)(double), double (*g)(double)){
    return [f, g](double x){
        return f(x) * g(x);
    };
}

//Integration via Simpson's rule as the error is O(h^4)
double simpsonIntegr(std::function<double(double)> f, double a, double b, int n){
    
    if(n % 2 == 1) n++; //Number of partitions has to be even

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for(int i = 1; i < n; i++){

        int c = (i % 2 == 0) ? 2 : 4; //4 if odd, 2 if even
        sum += c * f(a + h * i);
    }

    sum *= (h / 3);

    return sum;
}

//Function inner product
double integrInnerProd(double (*f)(double), double (*g)(double), double a=-1, double b=1, int n = 100000){
    return simpsonIntegr(product(f, g), a, b, n);
}

//Induced norm
double inducedNorm(double (*f)(double), double a=-1, double b=1, int n=100000){
    return std::sqrt(integrInnerProd(f, f, a, b, n));
}


double f(double x){
    return sin(x);
}

double g(double x){
    return pow(x, 2);
}



int main(){

    double in = integrInnerProd(f, g, 2, 5);
    std::cout << in << ", " << simpsonIntegr(product(f, g), 2, 5, 100000) <<'\n';

    double indn = inducedNorm(f, 2, 5);
    std::cout << indn << ", " << std::sqrt(integrInnerProd(f, f, 2, 5)) <<'\n';

    return 0;
}