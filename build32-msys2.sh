export CC=/mingw32/bin/clang
export CXX=/mingw32/bin/clang++

rm -rf build32
mkdir build32
cd build32
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DX64:BOOL=OFF .. -G"MSYS Makefiles"
make -f4