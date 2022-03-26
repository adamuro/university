const { stdin, stdout } = require('process');
const readline = require('readline');

const rl = readline.createInterface({
  input: stdin,
  output: stdout
});

rl.question('Jak masz na imię?\n', (name) => {
  rl.write(`Witaj ${name}\n`);
  rl.close();
});