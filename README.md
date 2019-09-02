# Intelligible Warehouse Manager

New warehouse manager software...! Work in progress...!

How to build:

```
mkdir build && cd build
cmake --help # choose Generators
cmake -G "Visual Studio 15 2017 Win64" .. # "-DCMAKE_BUILD_TYPE=Release" 
cmake --build . --target install # --config Release
```