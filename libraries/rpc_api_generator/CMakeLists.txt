# Find an installed build of LLVM
find_package(LLVM 4.0 REQUIRED CONFIG)
set( CMAKE_CXX_STANDARD 14 )

file(GLOB HEADERS "include/contento/rpc_api_generator/*.hpp")

set(SOURCES ${HEADERS})

add_library( rpc_api_generator
             rpc_api_generator.cpp
             rpc_api_serializer.cpp
             ${HEADERS} )

target_include_directories(rpc_api_generator
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                  "${LLVM_INCLUDE_DIRS}")

target_link_libraries(rpc_api_generator fc
  clangRewrite
  clangTooling
  clangToolingCore
  clangFrontend
  clangDriver
  clangSerialization
  clangParse
  clangSema
  clangAnalysis
  clangAST
  clangBasic
  clangEdit
  clangLex
)

target_link_libraries(rpc_api_generator
  LLVMX86AsmParser # MC, MCParser, Support, X86CodeGen, X86Desc, X86Info
  LLVMX86CodeGen # Analysis, AsmPrinter, CodeGen, Core, MC, Support, Target, 
                 # X86AsmPrinter, X86Desc, X86Info, X86Utils
  LLVMX86Desc # MC, MCDisassembler, Object, Support, X86AsmPrinter, X86Info
  LLVMX86AsmPrinter # MC, Support, X86Utils
  LLVMX86Info # Support
  LLVMX86Utils # Core, Support
  LLVMCodeGen # Analysis, Core, MC, Scalar, Support, Target, TransformUtils
  LLVMipo
  LLVMScalarOpts
  LLVMInstCombine
  LLVMTransformUtils
  LLVMTarget # Analysis, MC, Core, Support
  LLVMAnalysis # Core, Support
  LLVMOption # Support
  LLVMMCDisassembler # MC, Support
  LLVMMCParser # MC, Support
  LLVMMC # Object, Support
  LLVMProfileData # Core, Support, Object
  LLVMObject # BitReader, Core, Support
  LLVMBitReader # Core, Support
  LLVMCore # BinaryFormat, Support
  #LLVMBinaryFormat # Support
  LLVMSupport # Demangle
  LLVMDemangle
)

if (USE_PCH)
  set_target_properties(rpc_api_generator PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(eos_utilities)
endif(USE_PCH)
