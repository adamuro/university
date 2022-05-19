const prompt = require('prompt-sync')();

const defaultParameterParser = (parameterString) => parseInt(parameterString);
const readParameterGreaterOrEqual = (parameterName, parameterMinValue, parameterParser = defaultParameterParser) => {
  const parameterString = prompt(`Podaj wartość parametru ${parameterName}: `);
  const parameterValue = parameterParser(parameterString);
  if (parameterValue && parameterValue >= parameterMinValue) return parameterValue;
  
  throw new Error(`Niepoprawna wartość parametru ${parameterName}: ${parameterString}`);
};

const decimalPart = (x) => x - Math.floor(x);

const INTEGRAL_STEPS = 100000000;
const integral = (f, start, end) => {
  const step = (end - start) / INTEGRAL_STEPS;
  let result = 0;

  for (let x = start + step; x <= end; x += step)
    result += f(x) * step;

  return result;
};

const memoizedFactorial = () => {
  const cache = {};
  return (n) => {
    if (n < 0 || decimalPart(n) !== 0) throw new Error(`Niepoprawna wartość argumentu silni: ${n}`);
    if (n === 0) return 1;
    if (!cache[n]) cache[n] = n * factorial(n - 1);

    return cache[n];
  };
};
const factorial = memoizedFactorial();

const memoizedGammaFunction = () => {
  const cache = {};
  return (z) => {
    if (z === 1 / 2) return Math.sqrt(Math.PI);
    if (decimalPart(z) === 0) return factorial(z - 1);
    if (!cache[z]) {
      const numerator = Math.sqrt(Math.PI) * gammaFunction(2 * z);
      const denominator = Math.pow(2, (2 * z) - 1) * gammaFunction(z - (1 / 2));
      cache[z] = numerator / denominator;
    }

    return cache[z];
  };
};
const gammaFunction = memoizedGammaFunction();

const densityFunction = (n, x) => {
  const numerator = Math.pow(x, (n / 2) - 1) * Math.pow(Math.E, -(x / 2));
  const denominator = Math.pow(2, n / 2) * gammaFunction(n / 2);
  return numerator / denominator ;
};

const distributionFunction = (n, x) => {
  return integral((p) => densityFunction(n, p), 0, x);
};

try {
  const n = readParameterGreaterOrEqual('n', 1);
  const x = readParameterGreaterOrEqual('x', 0, parseFloat);
  const distributionFunctionValue = distributionFunction(n, x);
  console.log(`Obliczona wartość dystrybuanty: ${distributionFunctionValue}`);
} catch (error) {
  console.error(error.message);
}
