# Optimisation with C++

A collection of optimisation algorithms implemented from scratch in **C++**.

This project was created primarily as a learning project to practice numerical optimisation, gradient-based methods, C++ programming, and the mathematical concepts behind optimisation algorithms.

## Implemented Methods

- Gradient Descent (GD)
- Stochastic Gradient Descent (SGD)
- Mini-Batch Gradient Descent (MBGD)
- Numerical gradient approximation using central differences

## Tech Stack

- C++ Standard Library
- `<vector>`
- `<algorithm>`
- `<random>`
- `<functional>`
- `<cmath>`

## Project Structure

```text
optimisation-with-cpp/
├── GD.cpp
├── SGD.cpp
├── MB.cpp
├── orthProjMin.cpp
└── README.md
```

### Main Components

`GD.cpp` implements gradient descent for multivariable functions. The gradient is approximated numerically using the central difference method, allowing the algorithm to minimise functions without requiring an explicitly defined analytical gradient.

`SGD.cpp` implements stochastic gradient descent. Individual data points are selected during optimisation and used to update the model parameters based on their contribution to the loss.

`MB.cpp` implements mini-batch gradient descent. The dataset is shuffled and divided into smaller batches, with the average gradient of each batch used to update the model parameters.

## What I Practiced

The main purpose of this project was to practice:

- Gradient-based optimisation
- Gradient Descent
- Stochastic Gradient Descent
- Mini-Batch Gradient Descent
- Numerical gradient approximation
- Central difference derivatives
- Linear regression
- Loss functions
- Working with multidimensional data
- C++ vectors and standard library algorithms
- Random sampling and dataset shuffling
- Translating mathematical algorithms into C++ implementations
