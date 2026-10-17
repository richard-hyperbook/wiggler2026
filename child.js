const { spawn } = require('child_process');

const childProcess = spawn('chromium --display=:0.0 http://192.168.1.166:3000 --kiosk', [], {shell: true });

childProcess.stdout.on('data', (data) => {
  console.log(`stdout: ${data}`);
});

childProcess.stderr.on('data', (data) => {
  console.error(`stderr: ${data}`);
});

childProcess.on('close', (code) => {
  console.log(`child process exited with code ${code}`);
});
