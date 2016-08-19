rm -rf build
mkdir build
cd build
cmake -DX64:BOOL=ON .. -DCMAKE_CXX_COMPILER=clang++ -G"MSYS Makefiles"
make