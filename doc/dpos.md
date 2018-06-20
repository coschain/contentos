Dpos
----------------

- dpos即委托权益证明(Delegated Proof of Stake)，每个拥有COC的用户可以进行投票，每人最多投30票，得票最多的前20个节点负责生产区块，还有一个名额是得票20名以外的节点轮流生产。这21个节点被称作witness，他们的权利是完全相等的。dpos每3秒产生一个区块，由21个witness轮流产生，每产生一轮（21个block）就会按照最新的得票数重新选择前20个witness，还有1个轮流名额，并且会随机21个witness的排列顺序，witness每产生一个block会获得COC奖励。
- 每个witness只能在被安排的顺序下产生block，如果某个witness作恶，想一直产生block，其他witness会丢弃其产生的block，因为所有witness都知道每个时间点该由谁来产生block。
- dpos也是最长链胜出，当有分叉的时候，诚实节点会选择最长的block chain作为正确链。
- irreversible确认机制，witness每3秒产生一个block，确认时间需要45秒（即irreversible状态），45秒是15个witness的生产间隔，即有2/3以上的witness认可这个block，原因是就算剩下的少数派（小于1/3）witness都是恶意witness，也无法在这个block之前搞出更长的链（颠覆这个block），所以最长链必然包含这个block。当然，前提是大于2/3的witness是诚实节点。
- 拥有COC的持币用户是区块链生态的受益者，他们会把票投给信赖的节点，那些节点能够维护好整个区款链的健康与稳定。当有恶意节点出现时，持币用户就会通过投票淘汰恶意witness，推举出新的witness。
- witness通过打包block会获得COC奖励，witness之间是竞争关系，如果作恶就会被其他witness替换，失去奖励收益，想作恶的witness要权衡作恶和奖励之间哪个收益更大。
- dpos对比pow，在pow模式下矿工们在挖一个新的区块时，对SHA-256密码散列函数进行运算，当找到符合规则的散列值即获得打包权，这种模式造成大量的资源浪费，而且网络性能低下，每秒交易仅仅量维持在个位数。dpos解决了pow的缺点，无需挖矿浪费能源，产生block的速度更快，每秒交易量大幅提升。
