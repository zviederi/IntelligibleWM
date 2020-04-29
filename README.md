# Intelligible Warehouse Management Tool

Warehouse management software. Software to manage your stock items and etc. #WIP

# Developer hints

How to build: 

```
mkdir build && cd build
cmake --help # choose Generator
cmake -G "Visual Studio 15 2017 Win64" .. # "-DCMAKE_BUILD_TYPE=Release" 
cmake --build . --target install # --config Release
```

Visual Code my custom tasks shortcuts:
- ~~Build and install project: Ctrl+Alt+B~~
- ~~Run program: Ctrl+Alt+R~~


# Credits

The following third party libraries/tools/drivers have been used in the IWM:

- [Qt](https://www.qt.io/download) - cross platform framework, licensed under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).
- [cmake](www.cmake.org) - cross platform project build system, licensed under [BSD license](https://gitlab.kitware.com/cmake/cmake/raw/master/Copyright.txt).
- [mongocxx](http://mongocxx.org/) - C++ Driver for MongoDB, licensed under [Apache License 2.0](https://github.com/mongodb/mongo-cxx-driver/blob/master/LICENSE).    