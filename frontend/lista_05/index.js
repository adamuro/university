let products = [];

/**
 * Generates id.
 * @returns randomly generated id
 */
function generateId() {
  return Math.floor(Math.random() * 1000000);
}

/**
 * Creates product object with given attributes.
 * @param {string} name name of new product
 * @param {number} quantity quantity of new product
 * @param {string} purchaseDate date on which the product should be bought
 * @param {boolean} purchased information about state of the product
 * @returns created product object (without id and index).
 */
function createProduct(name, quantity, purchaseDate, purchased) {
  return {
    name: name,
    quantity: quantity || 0,
    purchaseDate: isNaN(new Date(purchaseDate)) ? new Date() : new Date(purchaseDate),
    purchased: purchased || false,
  };
}

/**
 * Finds product with given id.
 * @param {number} id
 * @returns product with given id.
 */
function findProduct(id) {
  return products.find((product) => product.id === id);
}

/**
 * Checks if dates have the same year, month and day fields.
 * @param {Date} dateFirst first date
 * @param {Date} dateSecond second date
 * @returns information if given dates are on the same day
 */
function areDatesTheSameDay(dateFirst, dateSecond) {
  return (
    dateFirst.getFullYear() === dateSecond.getFullYear() &&
    dateFirst.getMonth() === dateSecond.getMonth() &&
    dateFirst.getDate() === dateSecond.getDate()
  );
}

/**
 * Adds a new product to the list of products.
 * @param {string} name name of new product
 * @param {number} quantity quantity of new product
 * @param {string} purchaseDate date on which the product should be bought
 * @param {boolean} purchased information about state of the product
 * @returns id of added product
 */
function addProduct(name, quantity, purchaseDate, purchased) {
  const product = createProduct(name, quantity, purchaseDate, purchased);
  const id = generateId();
  const index = products.length;
  products.push({ id, index, ...product });
  return id;
}

/**
 * Removes product from the list of products.
 * @param {number} id id of removed product
 */
function removeProduct(id) {
  const removedProductIndex = findProduct(id).index;
  products = products.filter((product) => product.id !== id);
  products = products.map((product) =>
    product.index > removedProductIndex ? { ...product, index: product.index - 1 } : product
  );
}

/**
 * Updates product with given attributes.
 * @param {number} id id of product to be updated
 * @param {string} name name of updated product
 * @param {number} quantity quantity of updated product
 * @param {string} purchaseDate date on which the product should be bought
 * @param {boolean} purchased information about state of the product
 */
function updateProduct(id, name, quantity, purchaseDate, purchased) {
  const product = createProduct(name, quantity, purchaseDate, purchased);
  products = products.map((prev) => (prev.id === id ? { id, index: prev.index, ...product } : prev));
}

/**
 * Swaps indices of products with given ids.
 * @param {number} idFirst id of first product
 * @param {number} idSecond id of second product
 */
function swapProducts(idFirst, idSecond) {
  const productFirst = findProduct(idFirst);
  const productSecond = findProduct(idSecond);

  products = products.map((product) => {
    if (product.id === idFirst) return { ...product, index: productSecond.index };
    if (product.id === idSecond) return { ...product, index: productFirst.index };
    return product;
  });
}

/**
 * Finds products which should be purchase on day indicated by given date.
 * @param {Date} date date indicating the day on which products should be purchased
 * @returns products which should be purchased on given day
 */
function findProductsWhichShouldBePurchasedOnDay(date) {
  return products.filter((product) => areDatesTheSameDay(date, product.purchaseDate));
}

/**
 * Finds products which should be purchased today (any hour).
 * @returns products which purchase date is today (any hour)
 */
function findProductsWhichShouldBePurchasedToday() {
  const today = new Date();
  return products.filter((product) => areDatesTheSameDay(today, product.purchaseDate));
}

/**
 * Sets product price. If the product was not purchased it does nothing.
 * @param {*} id id of the product
 * @param {*} price price of the product
 */
function setProductPrice(id, price) {
  products = products.map((product) =>
    product.id === id && product.purchased ? { ...product, price } : product
  );
}

/**
 * Calculates total price of products purchased on given day (any hour).\
 * Price is multiplied by quantity.
 * @param {Date} date date indicating day for which the price is calculated
 * @returns total price of products purchased on given day
 */
function calcProductsPurchasedOnDateTotalPrice(date) {
  return findProductsWhichShouldBePurchasedOnDay(date).reduce(
    (sum, product) => sum + ((product.purchased && product.price) || 0) * product.quantity,
    0
  );
}

/**
 * Formats products with given ids using given formatting function.\
 * Products which ids were not passed as argument are not included in the result.
 * @param {(product) => any} formatter formatting function that takes product as it's only argument
 * @param {...number} ids ids of products which should be formatted
 * @returns formatted products
 */
function formatProducts(formatter, ...ids) {
  return products.filter((product) => ids.includes(product.id)).map(formatter);
}

/* Prezentacja 👀 */
console.log("Let's gooo! 🔥🔥🔥");
console.log("> Add three products 🏭");
addProduct("one");
addProduct("two");
addProduct("three");
console.table(products);

const id1 = products[0].id;
const id2 = products[1].id;
const id3 = products[2].id;

console.log("> Update second product ⚡");
updateProduct(id2, "two updated");
console.table(products);

console.log("> Swap first and third product 🔄");
swapProducts(id1, id3);
console.table(products);

console.log("> Remove second product ❌");
removeProduct(id2);
console.table(products);

console.log("> Add product with tommorow's purchase date 📅");
addProduct("tomorrow", 1, "2022-11-21");
console.table(products);

console.log("> Find products which should be purchased today 📆");
const shouldBePurchasedToday = findProductsWhichShouldBePurchasedToday();
console.table(shouldBePurchasedToday);

console.log("> Add two products which were purchased yesterday 🕓");
addProduct("purchased 1", 3, "2022-11-19", true);
addProduct("purchased 2", 2, "2022-11-19", true);
console.table(products);

const idPurchased1 = products[3].id;
const idPurchased2 = products[4].id;

console.log("> Set previously added products prices 💯");
setProductPrice(idPurchased1, 21.15);
setProductPrice(idPurchased2, 7.77);
console.table(products);

console.log("> Try to set price of product which was not purchased ✋");
setProductPrice(id1, 1.23);
setProductPrice(id2, 3.21);
console.table(products);

console.log("> Calculate sum of added products prices 🧮");
const totalPrice = calcProductsPurchasedOnDateTotalPrice(new Date("2022-11-19"));
console.log(totalPrice);

console.log("> Format purchased products (multiply price) 🔮");
const formattedProducts = formatProducts(
  ({ price, ...product }) => ({ ...product, price: (price * 5).toFixed(2) }),
  idPurchased1,
  idPurchased2
);
console.table(formattedProducts);
console.log("Thanks! 🦝");
