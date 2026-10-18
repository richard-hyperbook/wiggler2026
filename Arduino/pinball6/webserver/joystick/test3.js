const Raspi = require('raspi-io');
const five = require('johnny-five');
const board = new five.Board({
  io: new Raspi()
});
 
board.on('ready', () => {
  new five.Pin('SDA');
  board.io.i2cWrite(0x20, 0x5, 'hello');
});
