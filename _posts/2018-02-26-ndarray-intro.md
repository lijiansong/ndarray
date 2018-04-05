---
layout: page 
title: NDArray Introduction
---  
 
NDArray is a c++11 based template library. It is designed to simplify the expression between NDArrays( i.e. tensor). In deep learning applications, tensor can be seen everywhere. More details about tensor, see this wiki [page](https://en.wikipedia.org/wiki/Tensor).

 
## Key Feature

Firstly, during the implementation of NDArray, many [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) new features is used, e.g. Rvalue references, variadic templates, initializer lists,  type_traits and etc.
Besides, NDArray provides much flexibility, because its design concept comes from [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) container and [Eigen](https://bitbucket.org/eigen/).
NDArray provides both static and dynamic containers. Here, `static` means if each dimension of NDArray is known during compiling time. While each dimension of dynamic ndarray is variable at compiling time.

## Installation


## Examples and Usage


## Project Dependencies


## PostScript

The long term goal of NDArray is to develop something that is like numpy library. But with feature support that any ranks of NDArray can be run in CPU, GPU or some ASIC platforms.

Notice: NDArray is under development, now it only supports static NDArray, dynamic NDArray will be posted later.
