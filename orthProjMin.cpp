#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <vector>

//Function product
std::function<double(double)> product(std::function<double(double)> f, std::function<double(double)> g){
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
double integrInnerProd(std::function<double(double)> f, std::function<double(double)> g, double a=-1, double b=1, int n = 100000){
    return simpsonIntegr(product(f, g), a, b, n);
}

//Induced norm
double inducedNorm(std::function<double(double)> f, double a=-1, double b=1, int n=100000){
    return std::sqrt(integrInnerProd(f, f, a, b, n));
}

//Gramm-Schmidt orthonormalisation fo finding a new basis
std::vector<std::function<double(double)>> orthNorm(std::vector<std::function<double(double)>> basis){

    int dim = basis.size();
    std::vector<std::function<double(double)>> orthNormBasis; //Empty ortho-normal basis

    for(int i = 0; i < dim; i++){
        if(orthNormBasis.size() == 0){ //First basis vector

            std::function<double(double)> v0 = basis[0];
            double normV0 = inducedNorm(v0);

            std::function<double(double)> e0 = 
                [v0, normV0](double x){
                    return v0(x) / normV0;
                };

            orthNormBasis.push_back(e0);
            continue;
        }

        std::function<double(double)> vi = basis[i];
        std::vector<double> innerProds;

        for(int j = 0; j < orthNormBasis.size(); j++){
            innerProds.push_back(
                integrInnerProd(vi, orthNormBasis[j])
            );
        }

        std::function<double(double)> ui = 
            [vi, orthNormBasis, innerProds](double x){ //First we create an orthogonal vector

                double result = vi(x);

                for(int j = 0; j < orthNormBasis.size(); j++){
                    result -= innerProds[j] * orthNormBasis[j](x);
                }

                return result; 
            };

        double normUi = inducedNorm(ui);

        std::function<double(double)> ej = 
            [ui, normUi](double x){ //Then we normalise it
                return ui(x) / normUi;
            };

        orthNormBasis.push_back(ej);
    }

    return orthNormBasis;
}


double f3(double x){
    return pow(x, 3);
}

double f2(double x){
    return pow(x, 2);
}

double f1(double x){
    return x;
}

double f0(double x){
    return 1;
}



int main(){

    double in = integrInnerProd(f3, f2, 2, 5);
    std::cout << in << ", " << simpsonIntegr(product(f3, f2), 2, 5, 100000) <<'\n';

    double indn = inducedNorm(f3, 2, 5);
    std::cout << indn << ", " << std::sqrt(integrInnerProd(f3, f3, 2, 5)) <<'\n';

    std::vector<std::function<double(double)>> V;
    V.push_back(f3);
    V.push_back(f2);
    V.push_back(f1);
    V.push_back(f0);
    std::vector<std::function<double(double)>> orthNormV = orthNorm(V);
    std::cout << orthNormV[0](3) << ", " << orthNormV[1](4) << "\n";

    return 0;
}