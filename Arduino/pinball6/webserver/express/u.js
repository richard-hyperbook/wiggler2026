
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

// connect to raspberry pi pico via USB serial
const port = new SerialPort({
  autoOpen: false, // don't auto open, we want to control this
  path: '/dev/ttyS0', // Pi Pico USB Mini to Raspberry Pi 4 USB A
  // path: '/dev/cu.usbmodem14401', // Pi Pico USB Mini to MacBook Pro USB C
  baudRate: 9600,
});

port.on('open', () => {

  // create line parser
  const parser = port.pipe(new ReadlineParser({
      delimiter: '+',
  }));

  // listen for new lines received
  parser.on('data', (data) => {
      console.log(data);
  });

  // send ping command
  port.write("ping");
  port.write("\n");

});

port.open();