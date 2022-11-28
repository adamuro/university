const libraryStore = [];

/* trzeba zmienić strzałkę na function, bo this jest czymś innym. */
String.prototype.capitalize = function () {
  return this.length === 0 ? "" : this[0].toUpperCase() + this.slice(1);
};

function capitalize(string) {
  return string.length === 0 ? "" : string[0].toUpperCase() + string.slice(1);
}

/* Zadanie 1 */
console.log("> 1");
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
console.log("> 2");
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
    if (rating < 1 || rating > 10)
      throw new RangeError("Rating must be in range 1-10");

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
console.log("> 3");
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
console.log("> 4");
async function testOrderMedia() {
  try {
    await media.orderMedia();
    console.log(media.available); // false

    await media.returnMedia();
    console.log(media.available); // true
  } catch (e) {}
}

testOrderMedia();

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
    if (pages < 1) throw new RangeError("Pages must be positive");

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
console.log("> 5");
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

async function testOrderBook() {
  try {
    await book.orderBook();
    console.log(book.available); // false

    await book.returnBook();
    console.log(book.available); // true
  } catch (e) {}
}

testOrderBook();

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
    if (length < 1) throw new RangeError("Length must be positive");

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
console.log("> 6");
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

async function testOrderMovie() {
  try {
    await movie.orderMovie();
    console.log(movie.available); // false

    await movie.returnMovie();
    console.log(movie.available); // true
  } catch (e) {}
}

testOrderBook();

/* Zadanie 7 */
console.log("> 7");
try {
  new Media();
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Media({ title: 123 });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Book({ title: 123 });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Book({ title: "alice's adventures in wonderland" });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Book({
    title: "alice's adventures in wonderland",
    author: "Lewis Carroll",
    pages: -10,
  });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Book({
    title: "alice's adventures in wonderland",
    author: "Lewis Carroll",
  });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Movie({ title: 123 });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Movie({ title: "Alice in wonderland" });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Movie({
    title: "Alice in wonderland",
    director: "tim burton",
    length: -10,
  });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Movie({
    title: "Alice in wonderland",
    director: "tim burton",
  });
  console.log("no error");
} catch (error) {
  console.log(error.message);
}
try {
  new Media({
    title: "Alice in wonderland",
  }).addRating(0);
  console.log("no error");
} catch (error) {
  console.log(error.message);
}

const addToLibrary = (props) => {
  let media;
  try {
    switch (props.type) {
      case "book":
        media = new Book(props);
        libraryStore.push(media);
        return media;
      case "movie":
        media = new Movie(props);
        libraryStore.push(media);
        return media;
      default:
        media = new Media(props);
        libraryStore.push(media);
        return media;
    }
  } catch (error) {
    console.log(error.message);
  }
};

/* Zadanie 8 */
console.log("> 8");
const bookLib = addToLibrary({
  type: "book",
  title: "alice's adventures in wonderland",
  author: "lewis carroll",
  pages: 136,
});
const movieLib = addToLibrary({
  type: "movie",
  title: "alice in wonderland",
  director: "tim burton",
  length: 108,
});
const mediaLib = addToLibrary({
  title: "Media",
});

console.log(libraryStore);

const book1 = addToLibrary({
  type: "book",
  author: "lewis carroll",
  pages: 136,
}); // Wrong title
const book2 = addToLibrary({
  type: "book",
  title: "alice's adventures in wonderland",
  pages: 136,
}); // Wrong author
const book3 = addToLibrary({
  type: "book",
  title: "alice's adventures in wonderland",
  author: "lewis carroll",
}); // Wrong pages
const book4 = addToLibrary({
  type: "book",
  title: "alice's adventures in wonderland",
  author: "lewis carroll",
  pages: -10,
}); // Wrong pages
const movie1 = addToLibrary({
  type: "movie",
  director: "tim burton",
  length: 108,
}); // Wrong title
const movie2 = addToLibrary({
  type: "movie",
  title: "alice in wonderland",
  length: 108,
}); // Wrong director
const movie3 = addToLibrary({
  type: "movie",
  title: "alice in wonderland",
  director: "tim burton",
}); // Wrong length
const movie4 = addToLibrary({
  type: "movie",
  title: "alice in wonderland",
  director: "tim burton",
  length: -10,
}); // Wrong length
const media2 = addToLibrary({
  title: 123,
}); // Wrong title

/* Zadanie 9 */
console.log("> 9");
function bulkAddToLibrary(propsArray) {
  return propsArray.map((props) => addToLibrary(props));
}

const [bookBulk, movieBulk, mediaBulk] = bulkAddToLibrary([
  {
    type: "book",
    title: "alice's adventures in wonderland",
    author: "lewis carroll",
    pages: 136,
  },
  {
    type: "movie",
    title: "alice in wonderland",
    director: "tim burton",
    length: 108,
  },
  {
    title: "Media",
  },
]);

console.log(libraryStore);
/*
[ Book { _title: 'Alice\'s Adventures In Wonderland',
    _ratings: [],
    _available: true,
    _author: 'Lewis Carroll',
    _pages: 136 
  },
  Movie { _title: 'Alice In Wonderland',
    _ratings: [],
    _available: true,
    _director: 'Tim Burton',
    _length: 108 
  },
  Media { _title: 'Media', _ratings: [], _available: true }
]
*/

// async function order(title) {
//   libraryStore.forEach(async (item) => {
//     console.log(item);
//     if (item.title === title) {
//       try {
//         await item.orderMedia();
//         console.log("Order completed!");
//       } catch (error) {
//         console.log("Sorry! " + error);
//       }
//     }
//   });
// }
