//
//  benchmark.cpp
//  etest
//
//  Created by 戴硕 on 2018/8/3.
//

#include "benchmark.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <numeric>
#include <functional>
#include <algorithm>
#include <cassert>

namespace wasm_benchmark {
    using event = std::tuple<uint64_t, uint64_t, bool>;
    using events = std::vector<event>;
    using imports = std::map<uint64_t, std::string>;
    
    events g_intrinsic_events;
    events g_call_import_events;
    imports g_imports;
    
    void init() {
        const size_t reserve_size = 1000 * 10000;
        g_intrinsic_events.clear();
        g_call_import_events.clear();
        g_imports.clear();
        g_intrinsic_events.reserve(reserve_size);
        g_call_import_events.reserve(reserve_size);
    }
    
    uint64_t rdtsc(){
        unsigned int lo,hi;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        return ((uint64_t)hi << 32) | lo;
    }
    
    void record_event(bool begin_or_end, bool intrinsic_or_import, uint64_t who) {
        uint64_t ts = rdtsc();
        if (intrinsic_or_import) {
            g_intrinsic_events.emplace_back(ts, who, begin_or_end);
        } else {
            g_call_import_events.emplace_back(ts, who, begin_or_end);
        }
    }
    
    void register_import(uint64_t import, const std::string& name) {
        g_imports[import] = name;
    }
    
    enum WasmId {
        InvalidId = 0,
        BlockId,
        IfId,
        LoopId,
        BreakId,
        SwitchId,
        CallId,
        CallImportId,
        CallIndirectId,
        GetLocalId,
        SetLocalId,
        GetGlobalId,
        SetGlobalId,
        LoadId,
        StoreId,
        ConstId,
        UnaryId,
        BinaryId,
        SelectId,
        DropId,
        ReturnId,
        HostId,
        NopId,
        UnreachableId,
        NumExpressionIds
    };
    
    std::map<WasmId, std::string> g_wasm_names = {
        { BlockId,          "Block"         },
        { IfId,             "If"            },
        { LoopId,           "Loop"          },
        { BreakId,          "Break"         },
        { SwitchId,         "Switch"        },
        { CallId,           "Call"          },
        { CallImportId,     "CallImport"    },
        { CallIndirectId,   "CallIndirect"  },
        { GetLocalId,       "GetLocal"      },
        { SetLocalId,       "SetLocal"      },
        { GetGlobalId,      "GetGlobal"     },
        { SetGlobalId,      "SetGlobal"     },
        { LoadId,           "Load"          },
        { StoreId,          "Store"         },
        { ConstId,          "Const"         },
        { UnaryId,          "Unary"         },
        { BinaryId,         "Binary"        },
        { SelectId,         "Select"        },
        { DropId,           "Drop"          },
        { ReturnId,         "Return"        },
        { HostId,           "Host"          },
        { NopId,            "Nop"           },
    };
    
    struct intrinsic {
        intrinsic(uint64_t id) : _id(id) { }
        
        intrinsic& set_begin(uint64_t t) {
            _t_begin = t;
            return *this;
        }
        intrinsic& set_end(uint64_t t) {
            _t_end = t;
            return *this;
        }
        intrinsic& add_child(intrinsic& e) {
            _children.emplace_back(e);
            return *this;
        }
        uint64_t duration() const {
            return _t_end - _t_begin;
        }
        uint64_t cost() const {
            return duration() - std::accumulate( _children.begin(), _children.end(), 0,
                                                [](const uint64_t& r, const intrinsic& e) {
                                                    return r + e.duration();
                                                } );
        }

        uint64_t _id;
        uint64_t _t_begin;
        uint64_t _t_end;
        std::vector< std::reference_wrapper<intrinsic> > _children;
    };
    
    void collect_intrinsic_costs(intrinsic& e, std::map<uint64_t, std::vector<uint64_t>>& r) {
        if (r.find(e._id) == r.end()) {
            r[e._id] = std::vector<uint64_t>();
        }
        r[e._id].push_back(e.cost());
        for (auto c: e._children) {
            collect_intrinsic_costs(c, r);
        }
    }
    
    void show_intrinsic_result() {
        const uint64_t root_id = (uint64_t)(-1);
        const uint64_t import_id = (uint64_t)(-2);
        
        std::list<intrinsic> intrinsics;
        std::vector<std::reference_wrapper<intrinsic>> stack;
        
        intrinsics.emplace_back(root_id);
        stack.push_back(intrinsics.back());
        
        std::map<std::string, std::vector<uint64_t>> import_stats;
        std::vector< std::pair<std::string,uint64_t> > import_durations;
        for (size_t i = 0; i < g_call_import_events.size(); i+=2) {
            std::string name = g_imports[std::get<1>(g_call_import_events[i])];
            uint64_t duration = std::get<0>(g_call_import_events[i + 1]) - std::get<0>(g_call_import_events[i]);
            import_durations.push_back( std::make_pair(name, duration) );
            if (import_stats.find(name) == import_stats.end()) {
                import_stats[name] = std::vector<uint64_t>();
            }
            import_stats[name].push_back(duration);
        }
        
        size_t call_import_idx = 0;
        uint64_t t, who;
        bool begin;
        for (auto event: g_intrinsic_events) {
            std::tie(t, who, begin) = event;
            if (begin) {
                intrinsics.emplace_back(who);
                auto& e = intrinsics.back();
                e.set_begin(t);
                intrinsic& p = stack.back();
                p.add_child(e);
                stack.emplace_back(e);
            } else {
                intrinsic& e = stack.back();
                stack.pop_back();
                e.set_end(t);
                if (e._id == CallImportId) {
                    intrinsics.emplace_back(import_id);
                    auto n = intrinsics.back();
                    n.set_begin(t - import_durations[call_import_idx++].second);
                    n.set_end(t);
                    e.add_child(n);
                }
            }
        }
        assert(stack.size() == 1);
        
        std::map<uint64_t, std::vector<uint64_t>> costs;
        intrinsic& root = stack[0];
        for (auto e: root._children) {
            collect_intrinsic_costs(e, costs);
        }
        std::cout << "==== Intrinsics ====" << std::endl;
        for (auto i: costs) {
            uint64_t _id = i.first;
            if (_id == root_id || _id == import_id)
                continue;
            auto& values = i.second;
            std::sort(values.begin(), values.end());
            
            size_t mid = (values.size() - 1) / 2;
            uint64_t r = (values.size() % 2)? values[mid] : (values[mid] + values[mid + 1]) / 2;
            std::cout << g_wasm_names[(WasmId)_id] << "\t" << r << std::endl;
        }
        
        std::cout << "==== Imports ====" << std::endl;
        for (auto import: import_stats) {
            auto& values = import.second;
            std::sort(values.begin(), values.end());
            size_t mid = (values.size() - 1) / 2;
            uint64_t r = (values.size() % 2)? values[mid] : (values[mid] + values[mid + 1]) / 2;
            std::cout << import.first << "\t" << r << std::endl;
        }
    }
    
    void show_result() {

        show_intrinsic_result();
    }
}

uint64_t rdtsc() {
    return wasm_benchmark::rdtsc();
}

void wasm_benchmark_init() {
    wasm_benchmark::init();
}

void report_wasm_expression(bool begin_or_end, uint64_t expression_id) {
    wasm_benchmark::record_event(begin_or_end, true, expression_id);
}

void report_wasm_call_import(bool begin_or_end, uint64_t import) {
    wasm_benchmark::record_event(begin_or_end, false, import);
}

void report_wasm_import(uint64_t import, const std::string& name) {
    wasm_benchmark::register_import(import, name);
}

void wasm_benchmark_show_result() {
    wasm_benchmark::show_result();
}
