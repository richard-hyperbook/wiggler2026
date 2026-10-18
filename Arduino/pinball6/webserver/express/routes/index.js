var express = require('express');
var router = express.Router();

const raspi = require('raspi');
const Serial = require('raspi-serial').Serial;
const WebSocketServer = require('ws');
const fs = require('fs');
const joystick = require('joystick');
const I2C = require('raspi-i2c').I2C;
const sleep = require('sleep-promise');


const i2c = new I2C();
var serial;


// Creating a new websocket server
const wss = new WebSocketServer.Server({ port: 8080 })
// Creating connection using websocket
wss.on("connection", ws => {
    console.log("new client connected");
    // sending message to client
    ws.send("A0");
    ws.send("B0");
    ws.send("C0");
    ws.send("D0");
    ws.send("E0");
    ws.send("F0");
    ws.send("G0");
    ws.send("H0");
    ws.send("I0");
    ws.send("J0");
    ws.send("K0");
    ws.send("L0");
    ws.send("M0");
    ws.send("N0");
    ws.send("O0");
    ws.send("P0");
    ws.send("Q0");
    ws.send("R1");
    ws.send("S0");
    ws.send("T0");
    
    
    //on message from client
    ws.on("message", data => {
        console.log(`Client has sent us: ${data}`)
    });
    // handling what to do when clients disconnects from server
    ws.on("close", () => {
        console.log("the client has connected");
    });
    // handling client connection e
    ws.onerror = function () {
        console.log("Some Error occurred")
    }

var dd = '';

var SerialPort = require('serialport').SerialPort;
serial = new SerialPort({
    path: '/dev/ttyS0',
    baudRate: 9600,
    dataBits:8,
   // parity: 'none',
   // flowControl: false,
   // stopbits: 1,

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

// Init PS3 controller, 0 = /dev/input/js0
const ps3Controller = new joystick(0);

// On button press
let flags = 0x1E;
const masks = [2, 4, 8, 16];
const buttonNumbers = [4, 5, 6, 7];
raspi.init(() => {go();})

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
     serial.write('Z+');
    }
     console.log(flags);
     i2c.writeByteSync(0x20,flags,0xFF);
     await sleep(500);
     i2c.writeByteSync(0x20,0x1E,0xFF); 
    }
  }
}




});

});



console.log("(704)The WebSocket server is running on port 8080");

//left: calc(70px - 28.3px * #{title});
//        clip-path: inset(0% calc(28.3px * ( 9 - #{title})) 0% calc(28.3 * #{title}));

var incoming = 'YYY';
 
 
var p1m3 = 8;

var title = p1m3.toString();
var p1m3Left = (70 - (28.3 * p1m3)).toString();
var p1m3ClipRight = (28.3 * (9 - p1m3)).toString();
var p1m3ClipLeft = (28.3 * p1m3).toString();


/* GET home page. */
router.get('/', function(req, res, next) {
//   console.log('(706)' + req.url);
   const filePath = __dirname + '/wiggler.html';
  fs.readFile(filePath, (err, data) => {
//    console.log('(708)' + err);
//    console.log('(709)' + data);
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/html');
    res.end(data,  'utf8');
  });



});

module.exports = router;
