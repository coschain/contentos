#!/usr/bin/env node
const Web3 = require('web3'); var web3 = new Web3();
web3.setProvider( new web3.providers.WebsocketProvider("wss://mainnet.infura.io/ws"));
//web3.setProvider( new web3.providers.WebsocketProvider("wss://ropsten.infura.io/ws"));
//web3 = new Web3(new Web3.providers.HttpProvider("https://mainnet.infura.io/7TQkEEEQfn8VV4jdCbUV "));

  function formatAddress(data) {
    var step1 = web3.utils.hexToBytes(data);
    for (var i = 0; i < step1.length; i++) if (step1[0] == 0) step1.splice(0, 1);
    return web3.utils.bytesToHex(step1);
  }

function decodeLogBuy(data){
    var byteArr = web3.utils.hexToBytes(data);
    for (var i = 0; i < byteArr.length; i++) {

    }
}

console.log('111');
web3.eth.getPastLogs({fromBlock:'0x1', toBlock:'latest', address:'0xd0a6E6C54DbC68Db5db3A091B171A77407Ff7ccf', topics:[web3.utils.sha3('LogBuy(uint256,address,uint256)')]}).then(function(error,result){
if (!error) {
        console.log('this:'+JSON.stringify(result, null, 4))
  console.log("transaction value: " + web3.utils.hexToNumberString(tx_data.data) );
    }
    else {
        console.log('error:'+error);
    }
});
console.log('222');
