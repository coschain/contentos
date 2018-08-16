
# toolchains

1. cosiocc <=== eosiocpp
2. /usr/local/cosiolib  ===> sdk-dir

`cosiocc -o XXX XXXX` complie contract file

`cosiocc -g XXX XXXX` complie contract abi

# install cmd
	cd build
	1.first install sdk-dir
		cd contracts
		make		// must succes then can continue
		sudo make install
		cd ..
	2. install cosio-wast2wasm
		cd libraries/wasm-jit
		make install
		cd ../../
	3. install cosio-s2wasm
		cd externals/binaryen/
		make install
		cd ../../
	4. install cosiocc
		cd tools/
		make install
		cd ../
		

