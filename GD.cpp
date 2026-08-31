#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>



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

std::vector<double> grad(double (*func)(double*), double arr[], int arrSize){
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

std::vector<double> GD(double (*func)(double*), double startP[], int arrSize, double step, double tol=1e-6, int maxIter=10000){
    std::vector<double> ans(startP, startP + arrSize);
    int i = 0;

    while(i < maxIter){
        std::vector<double> vec = grad(func, ans.data(), arrSize);

        if(maxAbs(vec.data(), arrSize) <= tol){
            break;
        }

        vec = scalMalt(vec.data(), arrSize, step);
        ans = minus(ans.data(), vec.data(), arrSize);

        i++;
    }

    return ans;
}



double f(double x[]){
    double ans = pow(x[0], 2) + pow(x[1], 4) + 5 * x[0] - x[1];

    return ans;
}



int main(){
    double vec0[] = {1.4, 6.78};
    double vec1[] = {3.53, 2.65};
    double scal = 1.33;

    //std::cout << "[" << grad(f, vec0, 2)[0] << ", " << grad(f, vec0, 2)[1] << "]\n";
    //std::cout << "[" << minus(vec0, vec1, 2)[0] << ", " << minus(vec0, vec1, 2)[1] << "]\n";
    //std::cout << "[" << scalMalt(vec0, 2, scal)[0] << ", " << scalMalt(vec0, 2, scal)[1] << "]\n";

    std::vector<double> res = GD(f, vec1, 2, 0.01);

    std::cout << "[" << res[0] << ", " << res[1] << "]\n";

    return 0;
}