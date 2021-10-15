for(let i = 1; i <= 100000; i++) {
  const digits = i.toString().split('').map((digitChar) => parseInt(digitChar));
  const digitsSum = digits.reduce((sum, digit) => sum + digit);
  const digitsDivisibility = digits.every((digit) => i % digit === 0);
  const digitsSumDivisibility = i % digitsSum === 0;
  if (digitsDivisibility && digitsSumDivisibility) {
    console.log(i);
  }
}