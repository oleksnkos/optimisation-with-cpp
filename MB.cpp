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

std::vector<double> subtract(double arr1[], double arr2[], int arrSize){
    std::vector<double> ans(arrSize);

    for(int i = 0; i < arrSize; i++){
        ans[i] = arr1[i] - arr2[i];
    }

    return ans;
}

std::vector<double> add(double arr1[], double arr2[], int arrSize){
    std::vector<double> ans(arrSize);

    for(int i = 0; i < arrSize; i++){
        ans[i] = arr1[i] + arr2[i];
    }

    return ans;
}

std::vector<double> grad(double (*func)(double*, double*), double coefs[], double arr[], int arrSize){
    double h = 1e-6;
    std::vector<double> ans(arrSize);
    std::vector<double> tempLeft(arr, arr + arrSize);
    std::vector<double> tempRight(arr, arr + arrSize);

    for(int i = 0; i < arrSize; i++){
        tempLeft[i] += h;
        tempRight[i] -= h;

        double di = (func(coefs, tempLeft.data()) - func(coefs, tempRight.data())) / (2 * h);
        ans[i] = di;

        tempLeft[i] -= h;
        tempRight[i] += h;
    }

    return ans;
}

std::vector<double> MB(double (*func)(double*, double*), std::vector<std::vector<double>>& batch, double startP[], int arrSize, int MBSize, double step, double tol=1e-6, int maxIter=10000){
    std::vector<double> ans(startP, startP + arrSize);

    std::random_device rd; 
    std::mt19937 gen(rd());

    int i = 0;

    while(i < maxIter){
        std::shuffle(batch.begin(), batch.end(), gen);
        std::vector<double> avGrad(arrSize, 0.0);

        for(int j = 0; j < MBSize; j++){
            std::vector<double> vec = grad(func, batch[j].data(), ans.data(), arrSize);
            avGrad = add(avGrad.data(), vec.data(), arrSize);
        }
        
        double coef = (1.0 / MBSize);
        avGrad = scalMalt(avGrad.data(), arrSize, coef);

        if(maxAbs(avGrad.data(), arrSize) <= tol){
            break;
        }

        avGrad = scalMalt(avGrad.data(), arrSize, step);

        ans = subtract(ans.data(), avGrad.data(), arrSize);

        i++;
    }

    return ans;
}

double L(double x[], double w[]){
    double ans = pow(w[0] * x[0] + w[1] - x[1], 2);
    return ans;
}

int main(){
    std::vector<std::vector<double>> coefs = {{2, 1}, {3, 4}, {5, 2.5}, {4, 2}, {6, 5}};
    double x[] = {4.5, 7};
    double nu = 0.01;

    std::vector<double> res = MB(L, coefs, x, 2, 3, nu);
    std::cout << "[" << res.data()[0] << ", " << res.data()[1] << "]\n";

    return 0;
}
