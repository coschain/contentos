TEMP_DIR="/tmp"
CPU_CORE=$( sysctl -in machdep.cpu.core_count )

printf "\\n\\tChecking LLVM with WASM support.\\n"
if [ ! -d /usr/local/wasm/bin ]; then
	if ! cd "${TEMP_DIR}"
	then
		printf "\\tUnable to enter directory %s.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! mkdir "${TEMP_DIR}/wasm-compiler"
	then
		printf "\\tUnable to create directory %s/wasm-compiler.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! cd "${TEMP_DIR}/wasm-compiler"
	then
		printf "\\tUnable to enter directory %s/wasm-compiler.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! git clone --depth 1 --single-branch --branch release_40 https://github.com/llvm-mirror/llvm.git
	then
		printf "\\tUnable to clone llvm repo @ https://github.com/llvm-mirror/llvm.git.\\n"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! cd "${TEMP_DIR}/wasm-compiler/llvm/tools"
	then
		printf "\\tUnable to enter directory %s/wasm-compiler/llvm/tools.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! git clone --depth 1 --single-branch --branch release_40 https://github.com/llvm-mirror/clang.git
	then
		printf "\\tUnable to clone clang repo @ https://github.com/llvm-mirror/clang.git.\\n"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! cd "${TEMP_DIR}/wasm-compiler/llvm"
	then
		printf "\\tUnable to enter directory %s/wasm-compiler/llvm.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! mkdir "${TEMP_DIR}/wasm-compiler/llvm/build"
	then
		printf "\\tUnable to create directory %s/wasm-compiler/llvm/build.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! cd "${TEMP_DIR}/wasm-compiler/llvm/build"
	then
		printf "\\tUnable to enter directory %s/wasm-compiler/llvm/build.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local/wasm \
	-DLLVM_TARGETS_TO_BUILD= -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=WebAssembly \
	-DCMAKE_BUILD_TYPE=Release ../
	then
		printf "\\tError compiling LLVM/Clang with WASM support.\\n"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! sudo make -j"${CPU_CORE}" install
	then
		printf "\\tCompiling LLVM/Clang with WASM support has exited with the error above.\\n"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	if ! sudo rm -rf "${TEMP_DIR}/wasm-compiler"
	then
		printf "\\tUnable to remove directory %s/wasm-compiler.\\n" "${TEMP_DIR}"
		printf "\\tExiting now.\\n\\n"
		exit 1;
	fi
	printf "\\tSuccessfully installed LLVM/Clang with WASM support @ /usr/local/wasm/bin/.\\n"
else
	printf "\\tWASM found at /usr/local/wasm/bin/.\\n"
fi
