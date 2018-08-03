//
//  benchmark.hpp
//  etest
//
//  Created by 戴硕 on 2018/8/3.
//

#ifndef benchmark_hpp
#define benchmark_hpp

#include <string>

void wasm_benchmark_init();
void report_wasm_expression(bool begin_or_end, uint64_t expression_id);
void report_wasm_call_import(bool begin_or_end, uint64_t import);
void report_wasm_import(uint64_t import, const std::string& name);
void wasm_benchmark_show_result();

#endif /* benchmark_hpp */
