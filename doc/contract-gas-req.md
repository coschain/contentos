# 合约gas计费需求

## 1. 目标

合约的部署执行消耗cpu和ram，需要收费。

eos的收费策略是“预付费”。用户先用eos换取cpu/net/ram资源，之后部署/执行合约消耗已获得的资源。对于cpu资源，eos的计量单位是时间（ms），这引入了不确定性：合约执行消耗的cpu时间是无法被验证的。

Contentos的收费策略要实现下面目标：

- G1：直接消费。用户执行合约操作后，系统自动收取cos，用户cos余额不足将导致合约操作失败。
- G2：确定计价。对合约操作消耗的cpu和ram进行可重复验证的确定统计。
- G3：确定价格浮动。系统根据确定的策略自动调整cpu和ram的价格，反映为资源紧缺时价格高，资源富余时价格低。

## 2. 需求

- R0：引入计价单位gas，gas/cos比例固定。1 gas = 0.000001 cos。
- R1-1：无论合约执行是否成功，都要扣费。扣费失败也算作合约执行失败。
- R1-2：如果用户余额小于扣费金额，要把余额全部扣除，然后按照扣费失败处理。
- R1-3：合约执行过程中，周期性检查用户余额是否足够支付当前累计费用，余额不足即终止执行，算作执行失败。
- R2-1：对合约消耗的cpu资源进行确定计价。
  - R2-1-1：cpu的计价单位是nop，代表wasm vm执行一条nop指令的用时。每种确定的wasm指令都可以折合成确定数量的nop，如call = 100 nop，set_local = 5 nop等。各指令对应的nop数量需要通过benchmark测试得出。
  - R2-1-2：对于注册到vm的自定义native函数（call_import），也要能折合成nop。此类函数的逻辑相对复杂，不应该对应固定的nop数，需要支持nop计价函数（基于参数和返回值的nop计算公式）。每个native函数的nop计算公式需要通过benchmark测试得出。
  - R2-1-3：vm执行合约过程中，对已执行过的每条指令实时累积其折合的nop数量。合约执行终止后，无论是否成功，累计的nop数量要可以获取到。
- R2-2：对合约消耗的ram资源进行确定计价。
  - R2-2-1：ram的计价单位是byte，即字节。合约的部署（setcode/setabi）以及修改数据库时实时统计数据用量。
  - R2-2-2：对于占用ram减小的情况，如：删除数据库记录、更新记录但数据变短等，按照字节数为0处理。
  - R2-2-3：合约部署消耗的字节数量乘以系数10，即比其他数据贵10倍。
- R3-1：确定nop的gas价格。
  - R3-1-1：实时统计最近100个blocks (~5分钟)，得到当前TPS。
  - R3-1-2：nop的gas价格是TPS的函数，如：1 nop = 3000 / (3000 - min(2999, TPS)) gas。

- R3-2：确定byte的gas价格。
  - R3-2-1：byte价格暂取固定值：1 byte = 10 gas。

## 3. 代码关键位置

- R1-1：vm_evaluator::do_apply()

- R1-2：vm_evaluator::do_apply()

- R1-3：transaction_context::checktime() 

- R2-1-1：各指令nop数定义：wasm_price.hpp:  #define WASM_PRICE_XXXXXId.  

  注册指令nop数：wasm_interface.cpp:  SET_BASIC_INTRINSIC_PRICES(...)

  注册到虚拟机：binaryen.cpp, binaryen_runtime::instantiate_module()

- R2-1-2：各Import的nop计算函数定义和实现：wasm_price.hpp & wasm_price.cpp

  注册Imports及其nop函数：wasm_interface.cpp: REGISTER_INTRINSICS_WITH_PRICE(...)

  注册到虚拟机：binaryen.cpp, binaryen_runtime::instantiate_module()

- R2-1-3：指令callback链：wasm-traversal.h:  wasm::Visitor::visit(),  report_on_exit

  -> wasm_interpreter.h, RuntimeExpressionRunner::reportVisit()

  -> binaryen.hpp, interpreter_interface::report()

- R2-2-1：*done by eos.*  transaction_context::add_ram_usage()

- R2-2-2：transaction_context::gas() 

- R2-2-3：*done by eos.*  apply_contento_setcode(), config::setcode_ram_bytes_multiplier 

- R3-1-1：contento::chain::database::tps(),  contento::chain::tps_stats::update(), contento::chain::tps_stats::tps()

- R3-1-2：vm_evaluator::do_apply(), transaction_context::init_bill()

- R3-2-1：vm_evaluator::do_apply(), transaction_context::init_bill()

