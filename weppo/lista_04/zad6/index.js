const fs = require('fs');
const readline = require('readline');

const readStream = fs.createReadStream('./logs.txt');
const rl = readline.createInterface({
  input: readStream,
});

const summary = {};
rl.on('line', (line) => {
  const ip = line.split(' ')[1];
  summary[ip] = summary[ip] ?? 0;
  summary[ip] += 1;
});

rl.on('close', () => {
  const result = [];
  for (const [ip, requests] of Object.entries(summary)) {
    result.push({ ip, requests });
  }

  result.sort((a, b) => b.requests - a.requests);
  result.splice(3);
  
  for (const ipr of result) {
    console.log(`${ipr.ip} ${ipr.requests}`);
  }
});
