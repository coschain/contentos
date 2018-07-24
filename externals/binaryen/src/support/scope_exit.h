
#ifndef wasm_support_scope_exit_h
#define wasm_support_scope_exit_h

#include <functional>

namespace wasm {

    struct scope_exit {
        
        scope_exit( std::function<void()>&& func ) : _func(std::move(func)) {
            
        }
        
        ~scope_exit() {
            _func();
        }
        
        scope_exit(const scope_exit&) = delete;
        scope_exit& operator=(const scope_exit&) = delete;
        
        std::function<void()> _func;
    };

} // namespace wasm


#endif  // wasm_support_scope_exit_h
