
const raspi = require('raspi');
const Serial = require('raspi-serial').Serial;
const sleep = require('sleep-promise');

console.log("[1]");
var serial;
var dd;

var SerialPort = require('serialport').SerialPort;
serial = new SerialPort({
    path: '/dev/ttyS0',
    baudRate: 9600,
    //dataBits:8,
    //parity: 'none',
    //flowControl: false,
    //stopbits: 2,

});

  serial.on ('open', function (){
    serial.on('readable',() => {
      var buffer = serial.read();
      var d = buffer.toString('ascii');
      console.log('>' + d);
      dd = dd + d;
      var index = dd.indexOf("+");
      if(index != -1){
            var before = dd.substring(0, index); 
            console.log('?' + before + '/');
            ws.send(before);
            dd = dd.substring(index + 1);
   //         serial.write(buffer.toString('utf8'));
    }
  });

});


