const prime = (number) => {
  for(let i = 2; i <= number / 2; i++)
    if (number % i === 0) return false;

  return true
}

for(let i = 2; i <= 100000; i++) {
  if (prime(i)) console.log(i);
}