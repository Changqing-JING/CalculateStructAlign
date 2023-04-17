StructAlign.ll: examples/StructAlign.cpp
	clang++ --target=wasm32 -S -emit-llvm -o build/$@ $<

calculate-align-opt: StructAlign.ll
	opt -load-pass-plugin build/lib/libCalculateAlign.so -passes="calculate-align" -disable-output  build/$<

calculate-align: examples/StructAlign.cpp
	clang++ --target=wasm32 -c  -fpass-plugin=./build/lib/libCalculateAlign.so -o build/$@.wasm $<