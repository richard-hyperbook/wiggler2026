// Libs
const joystick = require('joystick');

// Init PS3 controller, 0 = /dev/input/js0
const ps3Controller = new joystick(0);

// On button press
ps3Controller.on('button', button => {
  console.log(button.number, button.value);
});

// On axis movement
//ps3Controller.on('axis', axis => {
//  console.log({ axis });
//});

const { version, Chip, Line } = require("node-libgpiod");

global.chip = new Chip(0);
global.line = new Line(chip, 17); 
let count = 10;

console.log(version());
line.requestOutputMode();

const blink = () => {
  if(count){
    line.setValue(count-- % 2);
    setTimeout(blink,1000);
  } // else line.release(); 
  // not needed, libgpiod releases resources on process exit  
};

setTimeout(blink,1000);
