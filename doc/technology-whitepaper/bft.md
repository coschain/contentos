# DPOS & BFT

------


## 单纯使用DPOS共识算法面临的问题
contentos由被选举出的21个witness节点轮流出块, 每一个产生的区块在被2/3以上的witness节点确认后被认为是不可回滚的区块，所以一笔交易的确认时间为14个区块产生时间， 即最少42秒。这是因为dpos中没有一种对当前产生区块的确认机制，一个区块被其他witness确认的唯一途径是在这个区块的基础上产生新的区块。

## pBFT
想要详细了解pBFT，请点击[http://pmg.csail.mit.edu/papers/osdi99.pdf](http://pmg.csail.mit.edu/papers/osdi99.pdf)
### pBFT概述
1. 预准备阶段：对于每个主节点收到的消息m，主节点向所有其他backup节点广播预准备消息`<<PRE-PREPARE,v,n,d>,m>`。其中v为当前视图，n为当前消息的序号，d为消息m的摘要。
2. 准备阶段：节点i收到并认可预请求消息后，向所有其他节点广播准备消息`<PREPARE,v,n,d,i>`。其中i为节点的唯一标识。当节点收到至少2f个其他节点发来的准备消息后，则认为准备阶段的状态prepared(m,v,n,i)为真，可以进入下一阶段。总节点个数为3f+1，其中f为最大的容错节点个数。
3. 提交阶段：节点i向所有其他节点广播`<COMMIT,v,n,D(m),i>`，当节点收到超过2f个其他节点发来的提交确认，则认为消息被成功提交。

## pBFT算法在DPOS上的适配
要想将pBFT协议集成到DPOS，我们需要做如下修改：
1. 主节点是有21个witness节点轮流担任的，因此我们不需要视图v来确认当前的主节点。
2. 消息序号即为最新的block_num。
3. 消息m即为新的block。
4. 需要添加前一个区块的头部信息prev_header，来确认当前生成的新徐快是在哪个分叉上。

总上，pBFT的三阶段协议的消息格式如下：`<<PRE-PREPARE, block_num, prev_header, d>, block>`
`<PREPARE, block_num, d, i>`
`<COMMIT, block_num, d, i>`
