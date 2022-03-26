const fs = require('fs');

const fileContent = fs.readFileSync('./zad1.js', 'utf-8');
console.log(fileContent);