#pragma once

#include <eosio/chain/wasm_interface.hpp>
#include <eosio/chain/webassembly/wavm.hpp>
#include <eosio/chain/webassembly/binaryen.hpp>
#include <eosio/chain/webassembly/runtime_interface.hpp>
#include <eosio/chain/wasm_eosio_injection.hpp>
#include <eosio/chain/transaction_context.hpp>
#include <fc/scoped_exit.hpp>

#include "IR/Module.h"
#include "Runtime/Intrinsics.h"
#include "Platform/Platform.h"
#include "WAST/WAST.h"
#include "IR/Validate.h"

using namespace fc;
using namespace eosio::chain::webassembly;
using namespace IR;
using namespace Runtime;

namespace eosio { namespace chain {

   struct wasm_interface_impl {
      wasm_interface_impl(wasm_interface::vm_type vm) {
         if(vm == wasm_interface::vm_type::wavm)
            runtime_interface = std::make_unique<webassembly::wavm::wavm_runtime>();
         else if(vm == wasm_interface::vm_type::binaryen)
            runtime_interface = std::make_unique<webassembly::binaryen::binaryen_runtime>();
         else
            FC_THROW("wasm_interface_impl fall through");
      }

      std::vector<uint8_t> parse_initial_memory(const Module& module) {
         std::vector<uint8_t> mem_image;

         for(const DataSegment& data_segment : module.dataSegments) {
            FC_ASSERT(data_segment.baseOffset.type == InitializerExpression::Type::i32_const);
            FC_ASSERT(module.memories.defs.size());
            const U32 base_offset = data_segment.baseOffset.i32;
            const Uptr memory_size = (module.memories.defs[0].type.size.min << IR::numBytesPerPageLog2);
            if(base_offset >= memory_size || base_offset + data_segment.data.size() > memory_size)
               FC_THROW_EXCEPTION(wasm_execution_error, "WASM data segment outside of valid memory range");
            if(base_offset + data_segment.data.size() > mem_image.size())
               mem_image.resize(base_offset + data_segment.data.size(), 0x00);
            memcpy(mem_image.data() + base_offset, data_segment.data.data(), data_segment.data.size());
         }

         return mem_image;
      }

      std::unique_ptr<wasm_instantiated_module_interface>& get_instantiated_module( const digest_type& code_id,
                                                                                    const shared_string& code,
                                                                                    transaction_context& trx_context )
      {
         auto it = instantiation_cache.find(code_id);
         if(it == instantiation_cache.end()) {
            auto timer_pause = fc::make_scoped_exit([&](){
               trx_context.resume_billing_timer();
            });
            trx_context.pause_billing_timer();
            IR::Module module;
            try {
               Serialization::MemoryInputStream stream((const U8*)code.data(), code.size());
               WASM::serialize(stream, module);
               module.userSections.clear();
            } catch(const Serialization::FatalSerializationException& e) {
               EOS_ASSERT(false, wasm_serialization_error, e.message.c_str());
            } catch(const IR::ValidationException& e) {
               EOS_ASSERT(false, wasm_serialization_error, e.message.c_str());
            }

            wasm_injections::wasm_binary_injection injector(module);
            injector.inject();

            std::vector<U8> bytes;
            try {
               Serialization::ArrayOutputStream outstream;
               WASM::serialize(outstream, module);
               bytes = outstream.getBytes();
            } catch(const Serialization::FatalSerializationException& e) {
               EOS_ASSERT(false, wasm_serialization_error, e.message.c_str());
            } catch(const IR::ValidationException& e) {
               EOS_ASSERT(false, wasm_serialization_error, e.message.c_str());
            }
            it = instantiation_cache.emplace(code_id, runtime_interface->instantiate_module((const char*)bytes.data(), bytes.size(), parse_initial_memory(module))).first;
         }
         return it->second;
      }

      std::unique_ptr<wasm_runtime_interface> runtime_interface;
      map<digest_type, std::unique_ptr<wasm_instantiated_module_interface>> instantiation_cache;
   };



#define _REGISTER_INTRINSIC_EXPLICIT_WITH_PRICE(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME, SIG)\
    _REGISTER_WAVM_INTRINSIC(CLS, MOD, METHOD, WASM_SIG, NAME, SIG)\
    _REGISTER_BINARYEN_INTRINSIC_WITH_PRICE(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME, SIG)

#define _REGISTER_INTRINSIC_WITH_PRICE4(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME, SIG)\
    _REGISTER_INTRINSIC_EXPLICIT_WITH_PRICE(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME, SIG )

#define _REGISTER_INTRINSIC_WITH_PRICE3(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME)\
    _REGISTER_INTRINSIC_EXPLICIT_WITH_PRICE(PRICE, CLS, MOD, METHOD, WASM_SIG, NAME, decltype(&CLS::METHOD) )

#define _REGISTER_INTRINSIC_WITH_PRICE2(PRICE, CLS, MOD, METHOD, WASM_SIG)\
    _REGISTER_INTRINSIC_EXPLICIT_WITH_PRICE(PRICE, CLS, MOD, METHOD, WASM_SIG, BOOST_PP_STRINGIZE(METHOD), decltype(&CLS::METHOD) )

#define _REGISTER_INTRINSIC_WITH_PRICE1(PRICE, CLS, MOD, METHOD)\
    static_assert(false, "Cannot register " BOOST_PP_STRINGIZE(CLS) ":" BOOST_PP_STRINGIZE(METHOD) " without a signature");

#define _REGISTER_INTRINSIC_WITH_PRICE0(PRICE, CLS, MOD, METHOD)\
    static_assert(false, "Cannot register " BOOST_PP_STRINGIZE(CLS) ":<unknown> without a method name and signature");

#define _UNWRAP_SEQ(...) __VA_ARGS__

#define _EXPAND_ARGS(PRICE, CLS, MOD, INFO)\
( PRICE, CLS, MOD, _UNWRAP_SEQ INFO )

#define _GET_INFO(INFO, PRICE)  INFO
#define _GET_PRICE(INFO, PRICE) PRICE

#define _REGISTER_INTRINSIC_WITH_PRICE_IN_MOD(CLS, MOD, INFO_PRICE)\
    BOOST_PP_CAT(BOOST_PP_OVERLOAD(_REGISTER_INTRINSIC_WITH_PRICE, _UNWRAP_SEQ _GET_INFO INFO_PRICE)\
                 _EXPAND_ARGS(_GET_PRICE INFO_PRICE, CLS, MOD, _GET_INFO INFO_PRICE), BOOST_PP_EMPTY())

#define _REGISTER_INTRINSIC_WITH_PRICE(R, CLS, INFO_PRICE)\
    _REGISTER_INTRINSIC_WITH_PRICE_IN_MOD(CLS, "env", INFO_PRICE)

#define REGISTER_INTRINSICS_WITH_PRICE(CLS, MEMBERS)\
    BOOST_PP_SEQ_FOR_EACH(_REGISTER_INTRINSIC_WITH_PRICE, CLS, _WRAPPED_SEQ(MEMBERS))

#define _REGISTER_INJECTED_INTRINSIC_WITH_PRICE(R, CLS, INFO_PRICE)\
    _REGISTER_INTRINSIC_WITH_PRICE_IN_MOD(CLS, EOSIO_INJECTED_MODULE_NAME, INFO_PRICE)

#define REGISTER_INJECTED_INTRINSICS_WITH_PRICE(CLS, MEMBERS)\
    BOOST_PP_SEQ_FOR_EACH(_REGISTER_INJECTED_INTRINSIC_WITH_PRICE, CLS, _WRAPPED_SEQ(MEMBERS))


//
// Backwards compatibility.
// We still keep supporting old macros REGISTER_INTRINSICS & REGISTER_INJECTED_INTRINSICS.
// Intrinsics defined by old macros have a price of zero.
//
#define _INFO_PRICE_1(...)  ((__VA_ARGS__),nullptr) _INFO_PRICE_2
#define _INFO_PRICE_2(...)  ((__VA_ARGS__),nullptr) _INFO_PRICE_1
#define _INFO_PRICE_1_END
#define _INFO_PRICE_2_END
#define _ADD_PRICE(INFO)    BOOST_PP_CAT(_INFO_PRICE_1 INFO, _END)

#define REGISTER_INTRINSICS(CLS, MEMBERS)\
    REGISTER_INTRINSICS_WITH_PRICE(CLS, _ADD_PRICE(MEMBERS))

#define REGISTER_INJECTED_INTRINSICS(CLS, MEMBERS)\
    REGISTER_INJECTED_INTRINSICS_WITH_PRICE(CLS, _ADD_PRICE(MEMBERS))

#define SET_BASIC_INTRINSIC_PRICE(ID, PRICE)  _SET_BINARYEN_BASIC_INTRINSIC_PRICE(ID, PRICE)

} } // eosio::chain
