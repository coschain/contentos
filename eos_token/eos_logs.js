#!/usr/bin/env node
const Web3 = require('web3'); var web3 = new Web3();
web3.setProvider( new web3.providers.WebsocketProvider("wss://mainnet.infura.io/ws"));
//web3.setProvider( new web3.providers.WebsocketProvider("wss://ropsten.infura.io/ws"));
//web3 = new Web3(new Web3.providers.HttpProvider("https://mainnet.infura.io/7TQkEEEQfn8VV4jdCbUV "));

/*
const filter = web3.eth.filter({
  fromBlock: 0,
  toBlock: 1,
  address: '0xd0a6E6C54DbC68Db5db3A091B171A77407Ff7ccf',
  topics: [web3.sha3('newtest(string,uint256,string,string,uint256)')]
})

filter.watch((error, result) => {
    if(error){
        console.log('error:'+error);
    } else {
        console.log('result:'+result);
    }
})
*/


var subscription = web3.eth.subscribe('logs', 
    {fromBlock:'0x1', toBlock:'latest', address:'0xd0a6E6C54DbC68Db5db3A091B171A77407Ff7ccf', topics:[web3.utils.sha3('LogBuy(uint256,address,uint256)')]},/*function(){}*/
function(error, result){
    if (!error) {
        console.log('this:'+JSON.stringify(result, null, 4))
    }
    else {
        console.log('error:'+error);
    }
})
.on("data", function(tx_data){

 /* function formatAddress(data) {
    var step1 = web3.utils.hexToBytes(data);
    for (var i = 0; i < step1.length; i++) if (step1[0] == 0) step1.splice(0, 1);
    return web3.utils.bytesToHex(step1);
  }*/
    //console.log(tx_data);
  //console.log( "------------------------------" );

  //console.log("Contract address:" + tx_data.address);
  //console.log("transaction value: " + web3.utils.hexToNumberString(tx_data.data) );
  //console.log("from: " + formatAddress(tx_data.topics['1']));
  //console.log("to: " + formatAddress(tx_data.topics['1']) ) ;
})
.on("changed", function(c){
    console.log('changed log:'+c);
});

console.log('111');

subscription.unsubscribe(function(error, success){
    if(success)
        console.log('Successfully unsubscribed!');
});
console.log('222');

//easyvote
/*
(function wait () {
    setTimeout(wait, 1000);
})();
*/
