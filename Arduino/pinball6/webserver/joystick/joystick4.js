// Libs
const raspi = require('raspi');
const joystick = require('joystick');
const I2C = require('raspi-i2c').I2C;
const sleep = require('sleep-promise');
const Serial = require('raspi-serial').Serial;

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
  gogo(button);
});

async function gogo(button){
  console.log(button.number, button.value);
  if(button.value == 1){
    for(let i = 0; i < 4; i++){
      if(button.number == buttonNumbers[i]){
        flags = 0x1E & (~masks[i]);
        break;
      }
    }
    if (button.number == 9){
     flags = 0x1E;
    }
     console.log(flags);
     i2c.writeByteSync(0x20,flags,0xFF);
     await sleep(5000);
     i2c.writeByteSync(0x20,0x1E,0xFF); 
    }
  }
}

var SerialPort = require('serialport').SerialPort;
const serial = new SerialPort({
    path: '/dev/ttyS0',
    baudRate: 9600 
});

  serial.on ('open', function (){
    console.log('(X1)');
    serial.on('readable',() => {
      console.log('(X2)');
      var buffer = serial.read();
      var d = buffer.toString('ascii');
            console.log(d);
            console.log('(x3)');
   //         serial.write(buffer.toString('utf8'));
   
  });
});

