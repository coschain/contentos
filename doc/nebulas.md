Nebulas dpos
----------

### 实现dpos的几个要点
- 基于时间的统一的producer选取机制，基于时间判断是否到生产时刻，要考虑时间误差
- 产生block时的自身私钥（地址）验证，保证每个producer只有一个真正的生产node
- 投票机制，保存  账户——>得票信息
- producer数组更新时机，一般是21个producer都轮流生产之后，更新下一轮21个（每次更新可以随机打乱顺序）
- fork的处理（最长链胜出）
- irreversible block的设定（经过2/3+1 个producer认可的block为irreversible
- 星云链的dpos还带了一个lru缓存，存储block，检查同一时刻重复block

### 移植可行性
基于nebulas的go版本代码改造，删掉多余的功能，增加缺少的功能

####多余
- dynasty功能，dpos完全不需要，目前nebulas的dpos是他们的过渡策略，最终要使用pod（devotion）

####缺少
- 投票机制，nebulas目前是指定的producer，轮流出块，没有投票机制。
- producer更新，每一轮（21个）按照得票数更新一次
- contentos的witness有个time_shared名额
- pre_transaction on_block 等通知过来的函数，主要是更新band_with （使用gas还需要band_with?）
- contentos有个producer的参与率判断
- contentos的producers可以决定一些参数： account_creation_fee  maximum_block_size  sbd_interest_rate

####contentos共识相关文件
contentos的共识主要在两个文件中：
- witness_schedule.cpp  更新witness逻辑
- witness_plugin.cpp  生产loop逻辑
- database.cpp  irreversible的处理
- fork.cpp  fork的处理
