/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */
/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */
/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */
/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */
/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */
/* WALIDACJA WARTOŚCI (UJEMNE STRONY ITP) */

const libraryStore = [];

/* trzeba zmienić strzałkę na function, bo this jest czymś innym. */
String.prototype.capitalize = function () {
  return this.length === 0 ? "" : this[0].toUpperCase() + this.slice(1);
};

function capitalize(string) {
  return string.length === 0 ? "" : string[0].toUpperCase() + string.slice(1);
}

/* Zadanie 1 */
console.log(capitalize("alice")); // 'Alice'
console.log(capitalize("")); // ''

console.log("alice".capitalize()); // 'Alice'
console.log("".capitalize()); // ''

function capitalizeSentence(sentence) {
  return sentence
    .split(" ")
    .map((word) => capitalize(word))
    .join(" ");
}

/* Zadanie 2 */
console.log(capitalizeSentence("alice")); // 'Alice'
console.log(capitalizeSentence("alice in Wonderland")); // 'Alice In Wonderland'

class Media {
  _title;
  _ratings;
  _available;

  constructor({ title }) {
    if (title === undefined) throw new Error("Title not provided");
    if (!(title instanceof String || typeof title === "string"))
      throw new TypeError("Title must be a string");

    this._title = capitalizeSentence(title);
    this._ratings = [];
    this._available = true;
  }

  get title() {
    return this._title;
  }

  get ratings() {
    return this._ratings;
  }

  get available() {
    return this._available;
  }

  addRating(rating) {
    if (rating === undefined) throw new Error("Rating not provided");
    if (!(rating instanceof Number || typeof rating === "number"))
      throw new TypeError("Rating must be a number");

    this._ratings.push(rating);
  }

  orderMedia() {
    return new Promise((resolve, reject) => {
      if (this._available) {
        setTimeout(() => {
          this._available = false;
          resolve();
        }, 1000);
        return;
      }

      reject("Not available");
    });
  }

  returnMedia() {
    return new Promise((resolve, reject) => {
      if (!this._available) {
        setTimeout(() => {
          this._available = true;
          resolve();
        }, 1000);
        return;
      }

      reject("Already returned");
    });
  }
}

/* Zadanie 3 */
const media = new Media({ title: "alice in wonderland" });
console.log(media.title); // 'Alice In Wonderland'
console.log(media.ratings); // []
console.log(media.available); // true

media.addRating(9);
media.addRating(8.5);
console.log(media.ratings); // [9, 8.5]

media.title = "not alice";
media.ratings = [1, 1];
media.available = false;
console.log(media.title); // 'Alice In Wonderland'
console.log(media.ratings); // [9, 8.5]
console.log(media.available); // true

/* Zadanie 4 */
media.orderMedia().then(() => console.log("order media: " + media.available)); // false
media.returnMedia().catch(() => console.log("return media: " + media.available)); // true

class Book extends Media {
  _author;
  _pages;

  constructor({ author, pages, ...props }) {
    if (author === undefined) throw new Error("Author not provided");
    if (pages === undefined) throw new Error("Pages not provided");

    if (!(author instanceof String || typeof author === "string"))
      throw new TypeError("Author must be a string");
    if (!(pages instanceof Number || typeof pages === "number"))
      throw new TypeError("Pages must be a number");

    super(props);
    this._author = capitalizeSentence(author);
    this._pages = pages;
  }

  get author() {
    return this._author;
  }

  get pages() {
    return this._pages;
  }

  orderBook() {
    return super.orderMedia();
  }

  returnBook() {
    return super.returnMedia();
  }
}

/* Zadanie 5 */
const book = new Book({
  title: "alice's adventures in wonderland",
  author: "lewis carroll",
  pages: 136,
});

console.log(book.title); // "Alice's Adventures In Wonderland"
console.log(book.ratings); // []
console.log(book.available); // true
console.log(book.author); // 'Lewis Carroll'
console.log(book.pages); // 136

book.addRating(9);
book.addRating(8.5);
console.log(book.ratings); // [9, 8.5]

book.title = "not alice";
book.ratings = [1, 1];
book.available = false;
book.author = "Charles Dickens";
book.pages = 500;
console.log(book.title); // "Alice's Adventures In Wonderland"
console.log(book.ratings); // [9, 8.5]
console.log(book.available); // true
console.log(book.author); // 'Lewis Carroll'
console.log(book.pages); // 136

book.orderBook().then(() => console.log("order book: " + book.available)); // false
book.returnBook().catch(() => console.log("return book: " + book.available)); // true

class Movie extends Media {
  _director;
  _length;

  constructor({ director, length, ...props }) {
    if (director === undefined) throw new Error("Director not provided");
    if (length === undefined) throw new Error("Length not provided");

    if (!(director instanceof String || typeof director === "string"))
      throw new TypeError("Director must be a string");
    if (!(length instanceof Number || typeof length === "number"))
      throw new TypeError("Length must be a number");

    super(props);
    this._director = capitalizeSentence(director);
    this._length = length;
  }

  get director() {
    return this._director;
  }

  get length() {
    return this._length;
  }

  orderMovie() {
    return super.orderMedia();
  }

  returnMovie() {
    return super.returnMedia();
  }
}

/* Zadanie 6 */
const movie = new Movie({
  title: "alice in wonderland",
  director: "tim burton",
  length: 108,
});

console.log(movie.title); // 'Alice In Wonderland'
console.log(movie.ratings); // []
console.log(movie.available); // true
console.log(movie.director); // 'Tim Burton'
console.log(movie.length); // 108

movie.addRating(9);
movie.addRating(8.5);
console.log(movie.ratings); // [9, 8.5]

movie.title = "not alice";
movie.ratings = [1, 1];
movie.available = false;
movie.director = "Tommy Wiseau";
movie.length = 500;
console.log(movie.title); // 'Alice In Wonderland'
console.log(movie.ratings); // [9, 8.5]
console.log(movie.available); // true
console.log(movie.director); // 'Tim Burton'
console.log(movie.length); // 108

movie.orderMovie().then(() => console.log("order movie: " + movie.available)); // false
movie.returnMovie().catch(() => console.log("return movie: " + movie.available)); // true

/* Zadanie 7 */
try {
  new Media();
} catch (error) {
  console.log(error);
}
try {
  new Media({ title: 123 });
} catch (error) {
  console.log(error);
}
try {
  new Book({ title: 123 });
} catch (error) {
  console.log(error);
}
try {
  new Book({ title: "alice's adventures in wonderland" });
} catch (error) {
  console.log(error);
}
try {
  new Book({
    title: "alice's adventures in wonderland",
    author: "Lewis Carroll",
    pages: -10,
  });
} catch (error) {
  console.log(error);
}
try {
  new Book({
    title: "alice's adventures in wonderland",
    author: "Lewis Carroll",
  });
} catch (error) {
  console.log(error);
}
try {
  new Movie({ title: 123 });
} catch (error) {
  console.log(error);
}
try {
  new Movie({ title: "Alice in wonderland" });
} catch (error) {
  console.log(error);
}
try {
  new Movie({
    title: "Alice in wonderland",
    director: "tim burton",
    length: -10,
  });
} catch (error) {
  console.log(error);
}
try {
  new Movie({
    title: "Alice in wonderland",
    director: "tim burton",
  });
} catch (error) {
  console.log(error);
}
try {
  new Media({
    title: "Alice in wonderland",
  }).addRating(0);
} catch (error) {
  console.log(error);
}

// const addToLibrary = (props) => {
//   switch (props.type) {
//     case "book":
//       const media = new Book(props);
//       libraryStore.push(media);
//       return media;
//     case "movie":
//       const media = new Movie(props);
//       libraryStore.push(media);
//       return media;
//     default:
//       const media = new Media(props);
//       libraryStore.push(media);
//       return media;
//   }
// };

// function order(title) {
//   for (let i = 0; i < libraryStore.length; i++) {
//     if (libraryStore[i].title === title) {
//       libraryStore[i]
//         .orderMedia()
//         .then(console.log("Order completed!"))
//         .catch((e) => {
//           console.log("Sorry! " + e);
//         });
//     }
//   }
// }
