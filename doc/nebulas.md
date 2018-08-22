Nebulas dpos
----------

### 使用go语言的区块链
- 本体 ont ``` 共识机制是VBFT ```
- 星云链 nebulas ``` dpos过渡，最终pod ```

### 实现dpos的几个要点
- 基于时间的统一的producer选取机制，基于时间判断是否到生产时刻，要考虑时间误差
- 产生block时的自身私钥（地址）验证，保证每个producer只有一个真正的生产node
- 投票机制，保存  账户——>得票信息
- producer数组更新时机，一般是21个producer都轮流生产之后，更新下一轮21个（每次更新可以随机打乱顺序）
- fork的处理（最长链胜出）
- irreversible block的设定（经过2/3+1 个producer认可的block为irreversible

### Nebulas dpos
#### dpos.go
```
func NewDpos() *Dpos {  创建dpos对象
func (dpos *Dpos) Setup(neblet core.Neblet) error {  初始化
func (dpos *Dpos) Start() {  启动dpos的loop
func (dpos *Dpos) Stop() {  停止loop
func (dpos *Dpos) EnableMining(passphrase string) error {  loop中的一个开关
func (dpos *Dpos) DisableMining() error {  loop中的一个开关
func (dpos *Dpos) Enable() bool {  loop中的一个开关
func less(a *core.Block, b *core.Block) bool {  比较两个block的height高度，用于ForkChoice
func (dpos *Dpos) ForkChoice() error {   fork处理，选择最长链
func (dpos *Dpos) UpdateLIB() {  更新irreversible
func (dpos *Dpos) Pending() bool {  返回是否在pending状态，pending状态不能产生block
func (dpos *Dpos) SuspendMining() {  设置pending = true (外层sync的时候会让loop停止)
func (dpos *Dpos) ResumeMining() {  设置pending = false
func verifyBlockSign(miner *core.Address, block *core.Block) error {  通过block的hash和签名导出producer地址，对比
func (dpos *Dpos) CheckDoubleMint(block *core.Block) bool {  检查同一时刻是否存在两个不同hash的block
func (dpos *Dpos) VerifyBlock(block *core.Block) error {  验证block，主要是验证签名
func (dpos *Dpos) unlock(passphrase string) error {  调用其他模块解锁账户
func (dpos *Dpos) newBlock(tail *core.Block, consensusState state.ConsensusState, deadlineInMs int64) (*core.Block, error) { 创建新block
func lastSlot(nowInMs int64) int64 {  返回当前最后一个slot的index
func nextSlot(nowInMs int64) int64 {  返回下一个slot的index
func deadline(nowInMs int64) int64 {  返回生产block的最大允许时间
func (dpos *Dpos) checkDeadline(tail *core.Block, nowInMs int64) (int64, error) {  检查生产block的时间，并且调用deadline
func (dpos *Dpos) checkProposer(tail *core.Block, nowInMs int64) (state.ConsensusState, error) {  检查是否是该由自己生产block
func (dpos *Dpos) pushAndBroadcast(tail *core.Block, block *core.Block) error {  调用其他模块广播
func (dpos *Dpos) mintBlock(now int64) error {  loop中调用这个，这个做一些检查：checkDeadline  checkProposer 然后 newBlock  pushAndBroadcast
func (dpos *Dpos) blockLoop() {  Start()调用这个，生产block的loop
```
#### dpos_state.go
```
func (dpos *Dpos) CheckTimeout(block *core.Block) bool {  判断block超时
func (ds *State) Dynasty() ([]byteutils.Hash, error) {  同TraverseDynasty
func FindProposer(now int64, miners []byteutils.Hash) (proposer byteutils.Hash, err error) {  根据时间找到该生产block的producer
func (ds *State) Proposer() byteutils.Hash {  返回选中的producer
func (ds *State) NextConsensusState(elapsedSecond int64, worldState state.WorldState) (state.ConsensusState, error) {  根据时间返回最新的consensus状态对象，该对象包含下次该由谁打包的决定信息
func TraverseDynasty(dynasty *trie.Trie) ([]byteutils.Hash, error) {  返回所有producer（放在trie结构里）
```

### 移植可行性
基于nebulas的go版本代码改造，删掉多余的功能，增加缺少的功能

#### 多余
- dynasty功能，dpos完全不需要，目前nebulas的dpos是他们的过渡策略，最终要使用pod（devotion）
- 星云链的dpos还带了一个lru缓存，存储block，检查同一时刻重复block（可有可无）

#### 缺少
- 投票机制，nebulas目前是指定的producer，轮流出块，没有投票机制。
- producer更新，每一轮（21个）按照得票数更新一次
- contentos的witness有个time_shared名额
- pre_transaction on_block 等通知过来的函数，主要是更新band_with （使用gas还需要band_with?）
- contentos有个producer的参与率判断
- contentos的producers可以决定一些参数： account_creation_fee  maximum_block_size  sbd_interest_rate

#### contentos共识相关文件
contentos的共识主要在两个文件中：
- witness_schedule.cpp  更新witness逻辑
- witness_plugin.cpp  生产loop逻辑
- database.cpp  irreversible的处理
- fork.cpp  fork的处理

### 难度
- 直接从xxx移植到yyy看似简单粗暴，但是两套代码逻辑是不一样的，直接迁移后需要调整结构的工作里可能远远大于迁移，而且这样搞bug不好控制。
结合nubulas和contentos各自的共识机制，按照需求重写出自己需要的dpos go语言代码，这样应该是最顺畅、最合理的。
