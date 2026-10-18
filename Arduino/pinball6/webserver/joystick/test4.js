const raspi = require('raspi');
const I2C = require('raspi-i2c').I2C;
 const sleep = require('sleep-promise');
 
raspi.init(()  => {go();})

async function go(){
  const i2c = new I2C();
  while(true){  
  console.log(i2c.readByteSync(0x20)); 
  
  i2c.writeByteSync(0x20,0,0xFF);
  await sleep(500)
  console.log(i2c.readByteSync(0x20));
  i2c.writeByteSync(0x20,0x2,0xFF);
  await sleep(500);
  }
}

//function sleep(ms) {
//     var x = 0;
//     var y = 0;
//     var z = 0;
//     for(i=0; i< 50000; i++){
//      x++;
//      y=y+3;
//      z=x*y;
 //    }
 //   return z;
//  }
 // console.log('Start');
  //It will execute after 2 seconds
 // sleep(2000, () => {
 //   console.log('End after 2 seconds');
 // });
