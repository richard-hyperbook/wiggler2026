// Libs
const raspi = require('raspi');
const joystick = require('joystick');
const I2C = require('raspi-i2c').I2C;

raspi.init(() => {go();})
const i2c = new I2C();

// Init PS3 controller, 0 = /dev/input/js0
const ps3Controller = new joystick(0);

// On button press
let flags = 0x1E;
const masks = [2, 4, 8, 16];
const buttonNumbers = [4, 5, 6, 7];

async function go(){
ps3Controller.on('button', button => {
  console.log(button.number, button.value);
  if(button.value == 1){
    for(let i = 0; i < 4; i++){
      if(button.number == buttonNumbers[i]){
        flags = flags & (~masks[i]);
      }
    }
    if (button.number == 9){
     flags = 0x1E;
    }
     console.log(flags);
     i2c.writeByteSync(0x20,flags,0xFF);
  }
});
}
