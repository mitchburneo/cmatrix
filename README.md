# Introduction
This repo contains implementations of matrix (two-dimensional array) based on doubly-linked list & binary file.
# Build
```bash
g++ cli.cpp utils/binfile.cpp -o cli
```
or
```bash
g++ cli.cpp utils/list.cpp -o cli
```
Also it is necessary to change cli.cpp to change matrix type:
```c++
#include "utils/list.h" // <-- include only this header to use doubly-linked list based two-dim array
// #include "utils/binfile.h" <-- include only this header to use binary file based two-dim array
```
# Usage
```bash
./cli recourses/data
```
