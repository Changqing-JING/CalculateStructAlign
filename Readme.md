Calculate alignment of each C++ struct via LLVM pass

Install dependencies
```shell
sudo apt install cmake llvm llvm-dev build-essential clang
```

Build the llvm pass
```shell
cmake -B ./build .
cmake --build ./build
```

Run the example
```shell
make calculate-align
```