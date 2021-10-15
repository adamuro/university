const fibonacciRecursion = (number) => {
  if (number === 0 || number === 1) return 1;
  
  return fibonacciRecursion(number - 2) + fibonacciRecursion(number - 1)
}

const fibonacciIteration = (number) => {
  let fibonacciA = 1;
  let fibonacciB = 1;

  for(let i = 1; i < number; i++) {
    const nextFibonacci = fibonacciA + fibonacciB;
    fibonacciA = fibonacciB;
    fibonacciB = nextFibonacci;
  }

  return fibonacciB;
}

for(i = 10; i < 45; i++) {
  const recursionLabel = `Rekurencja, i = ${i}`;
  console.time(recursionLabel);
  const recursionResult = fibonacciRecursion(i);
  console.timeEnd(recursionLabel);
  console.log(recursionResult);

  const iterationLabel = `Iteracja, i = ${i}`;
  console.time(iterationLabel);
  const iterationResult = fibonacciIteration(i);
  console.timeEnd(iterationLabel);
  console.log(iterationResult)
}