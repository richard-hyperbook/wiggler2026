const raspi = require('raspi');
const I2C = require('raspi-i2c').I2C;
const sleep = require('sleep-promise');
const prompt = require('prompt-sync')();
 
raspi.init(()  => {go();})

const i2c = new I2C();

const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

async function go(){
  while(true){   
  const name = prompt('?');
  console.log(name);
    if (name == 'a'){
      i2c.writeByteSync(0x20,0,0xFF);
    } else {
      i2c.writeByteSync(0x20,0x2,0xFF);
    }
 
  }
}


