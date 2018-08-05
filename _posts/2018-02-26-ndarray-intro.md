---
layout: page 
title: NDArray Introduction
---  

NDArray is short for N Dimension Array, it is a C++11 based template library. It is designed to simplify the expressions between NDArrays( i.e. Tensor). Since in deep learning applications, tensor can be seen everywhere, it is necessary to wrap its operations to lower the difficulty and cost of application developers. Existing open source NDArray(i.e. Tensor) is [Eigen](https://bitbucket.org/eigen/), it has been integrated into many projects, such as
[TensorFlow](https://github.com/tensorflow/tensorflow).

More details about NDArray(Tensor), see this wiki [page](https://en.wikipedia.org/wiki/Tensor).

## 1. Key Feature

Firstly, during the implementation of NDArray, many [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) new features has been used, e.g. Rvalue references, variadic templates, initializer lists,  type_traits and etc.

Besides, NDArray provides much flexibility, because its design concept comes from [C++ STL](https://en.wikipedia.org/wiki/Standard_Template_Library) container and [Eigen](https://bitbucket.org/eigen/), and its implementation is template meta programming based.

NDArray provides both static and dynamic containers. Here, `static ndarray` means if each dimension of the  NDArray is known during compiling time. While each dimension of `dynamic ndarray` is variable at compiling time. And to guarantee performance, we take use of `lazy evaluation`.

## 2. Examples and Usage
Here is some code snippets of NDArray:

```
// Static NDArray
// 1. Static NDArray construction and builtin functions
using static_ndarray = ndarray::NDArray<int, 48, 3, 32, 32>;
static_ndarray _A;
auto dim_sizes_a = _A.dim_sizes();
dim_sizes_a[0];  // 48
dim_sizes_a[1];  // 3
dim_sizes_a[2];  // 32
dim_sizes_a[3];  // 32

_A.size();       // 48 * 3 * 32 * 32
_A.rank();       // 4
_A.dim_size(0);  // 48
_A.dim_size(1);  // 3
_A.dim_size(2);  // 32
_A.dim_size(3);  // 32

std::array<float, 6> _tmp{1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
ndarray::NDArray<float, 3, 2, 1, 1> _B(tmp);
_B.rank();       // 4
_B.size();       // 6
auto _C = B;
_C.rank();       // 4
_C.size();       // 6
_C[0];           // 1.f
_C(0, 0, 0, 0);  // 1.f

ndarray::NDArray<int, 2, 2, 1> A{1, 2, 3, 4};
ndarray::NDArray<int, 2, 2, 1> B{2, 4, 6, 8};

// 2. NDArray arithmatic operations
auto C = A + B;
C.rank();      // 3
C.size();      // 4
C(0, 0, 0);    // 3, 1 + 2
C[3];          // 12, 4 + 8
auto dim_sizes tmp = C.dim_sizes();
tmp[0];        // 2
tmp[1];        // 2
tmp[2];        // 1
C.dim_size(0); // 2
C.dim_size(1); // 2
C.dim_size(2); // 1

auto D = A - B;
auto E = A * B;

// NDArray support expression priority
auto F = A + A * B;
F(0, 0, 0); // 3, 1 + 1 * 2
auto G = (A + A) * B;
G(0, 0, 0); // 4, (1 + 1) * 2

// 3. global redution
ndarray::NDArray<float, 2, 3> H{1.f, -2.2f, -3.f, 2.2f, 3.f, 4.99f};
H.sum(); // 5.99f
H.max(); // 4.99f
H.min(); // -3.f

// 4. reshape
ndarray::NDArray<int, 1, 2, 3> I{1, 2, 3, 4, 5, 6};
auto J = I.reshape<3, 2>();
J.rank();         // 2
J.size();         // 6
J.dim_sizes()[0]; // 3
J.dim_sizes()[1]; // 2
J.dim_size(0);    // 3
J.dim_size(1);    // 2
J(0, 0);          // 1
J[5];             // 6

auto K = I.reshape<6>();
K.rank();         // 1
K.size();         // 6
K.dim_sizes()[0]; // 6
K(0);             // 1
K(5);             // 6

// 5. local reduction
...

// 6. slice
...

// Dynamic NDArray
// 7. Dynamic NDArray constructor and builtin functions
ndarray::NDArray<int> B(3);
B.rank(); // 3
ndarray::NDArray<int> C{32, 7, 32, 48};
auto dim_sizes_c = C.dim_sizes();
dim_sizes_c[0]; // 32
dim_sizes_c[1]; // 7
dim_sizes_c[2]; // 32
dim_sizes_c[3]; // 48
C.dim_size(0); // 32
C.dim_size(1); // 7
C.dim_size(2); // 32
C.dim_size(3); // 48
C.rank(); // 4
C.size(); // 32 * 7 * 32 * 48

std::vector<size_t> dim_size{1, , 1, 2, 3};
std::vector<float> data{1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
ndarray::NDArray<float> D(dim_size, data);
auto d_data = D.data();
auto dim = D.dim_sizes();
D.rank(); // 3
D.size(); // 6
D.dim_size(0); // 1
D.dim_size(1); // 2
D.dim_size(2); // 3
dim[0]; // 1
dim[1]; // 2
dim[2]; // 3
d_data[0]; // 1.f
d_data[1]; // 2.f
d_data[2]; // 3.f
d_data[3]; // 4.f
d_data[4]; // 5.f
d_data[5]; // 6.f

// 8. Other expressions for dynamic NDarray is similar to static NDArray
...

```

For more examples, please checkout its [test suites](https://github.com/lijiansong/ndarray/tree/master/examples)

## 3. Project Dependencies
The implementation of NDArray take uses of many c++11 new features, please make sure your compiler support C++11 features. I have tested it by clang(5.0.0) and g++(5.4.0).

Notice: if you want to build the test cases in the [examples](https://github.com/lijiansong/ndarray/tree/master/examples) directory, please make sure you have already installed [Boost C++ libraries](https://www.boost.org/), since the test cases is dependent on the [Boost Unit test framework](https://github.com/lijiansong/ndarray/blob/54d1f45e60b0051fed2688579092dcfd8ab609d1/examples/Makefile#L24).

## 4. Post Script

The long term goal of NDArray is to provide numpy style tensor expressions, but with feature support that any ranks of NDArray can be run in CPU, GPU or some ASIC platforms.

Notice: NDArray is under development.
