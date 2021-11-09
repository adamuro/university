// https://stackoverflow.com/questions/899574/what-is-the-difference-between-typeof-and-instanceof-and-when-should-one-be-used

// instanceof operuje na typach reprezentowanych przez obiekty np.  String,   Object
// typeof     operuje na typach reprezentowanych przez napisy  np. 'string', 'object'

/* instanceof działa dla własnych typów, typeof w takich przypadkach zawsze zwraca 'object' */
const ClassFirst = function () {};
const ClassSecond = function () {};
const instance = new ClassFirst();
console.log(typeof instance); // object
console.log(typeof instance == 'ClassFirst'); // false
console.log(instance instanceof Object); // true
console.log(instance instanceof ClassFirst); // true
console.log(instance instanceof ClassSecond); // false

/* typeof działa dla prostych typów wbudowanych, instanceof nie */
console.log('example string' instanceof String); // false
console.log(typeof 'example string' == 'string'); // true

console.log('example string' instanceof Object); // false
console.log(typeof 'example string' == 'object'); // false

console.log(true instanceof Boolean); // false
console.log(typeof true == 'boolean'); // true

console.log(99.99 instanceof Number); // false
console.log(typeof 99.99 == 'number'); // true

console.log(function() {} instanceof Function); // true
console.log(typeof function() {} == 'function'); // true

/* instanceof działa dla złożonych typów wbudowanych, typeof nie */
console.log(/regularexpression/ instanceof RegExp); // true
console.log(typeof /regularexpression/); // object

console.log([] instanceof Array); // true
console.log(typeof []); //object

console.log({} instanceof Object); // true
console.log(typeof {}); // object
