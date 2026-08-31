#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <functional>



double maxAbs(double arr[], int arrSize){
    double m = std::abs(arr[0]);

    for(int i = 1; i < arrSize; i++){
        if(std::abs(arr[i]) > m){
            m = std::abs(arr[i]);
        }
    }

    return m;
}

std::vector<double> scalMalt(double arr[], int arrSize, double c){
    std::vector<double> ans(arr, arr + arrSize);

    for(int i = 0; i < arrSize; i++){
        ans.data()[i] *= c;
    }

    return ans;
}

std::vector<double> minus(double arr1[], double arr2[], int arrSize){
    std::vector<double> ans(arrSize);

    for(int i = 0; i < arrSize; i++){
        ans[i] = arr1[i] - arr2[i];
    }

    return ans;
}

//Using const, so the function is not changed as we used & to make it not copy function all over again, which makes changes possible
std::vector<double> grad(const std::function<double(double*)>& func, double arr[], int arrSize){
    double h = 1e-6;
    std::vector<double> ans(arrSize);
    std::vector<double> tempLeft(arr, arr + arrSize);
    std::vector<double> tempRight(arr, arr + arrSize);

    for(int i = 0; i < arrSize; i++){
        tempLeft[i] += h;
        tempRight[i] -= h;

        double di = (func(tempLeft.data()) - func(tempRight.data())) / (2 * h);
        ans[i] = di;

        tempLeft[i] -= h;
        tempRight[i] += h;
    }

    return ans;
}

//Passing a vector of function as an argument using functional
std::vector<double> SGD(std::vector<std::function<double(double*)>> funcArr, int funcArrSize, double* startP, int arrSize, double step, double tol=1e-6, int maxIter=10000){
    std::vector<double> ans(startP, startP + arrSize); //Start with the startP

    std::random_device rd; 
    std::mt19937 gen(rd());

    int i = 0;

    while(i < maxIter){
        std::uniform_int_distribution<int> dist(0, funcArrSize - 1);
        int randNum = dist(gen); //Generating random number

        std::vector<double> vec = grad(funcArr[randNum], ans.data(), arrSize);

        if(maxAbs(vec.data(), arrSize) <= tol){
            break;
        }

        vec = scalMalt(vec.data(), arrSize, step);
        ans = minus(ans.data(), vec.data(), arrSize);

        i++;
    }

    return ans;
}



double f0(double* x){
    double ans = pow((x[0] + 7.5 * x[1] - 3), 2);
    return ans;
}

double f1(double* x){
    double ans = pow((2 * x[0] + x[1] - 4), 4);
    return ans;
}

double f2(double* x){
    double ans = pow((2 * x[0] + 2 * x[1] -6), 2);
    return ans;
}



int main(){
    std::vector<std::function<double(double*)>> L;
    L.push_back(f0); // Pushing functions
    L.push_back(f1); //    into our
    L.push_back(f2); // function array

    double x0[] = {1.22, -3.87};
    double nu = 0.01;

    std::vector<double> res = SGD(L, 3, x0, 2, nu);

    std::cout << "[" << res[0] << ", " << res[1] << "]\n";

    return 0;
}