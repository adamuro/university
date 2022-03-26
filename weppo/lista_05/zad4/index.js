const express = require('express');
const app = express();

app.use(express.urlencoded({ extended:true }));
app.set('view engine', 'ejs');

let data = {};

app.get('/', (req, res) => {
  res.render('index');
});

app.get('/print', (req, res) => {
  res.render('print', data);
});

app.post('/', (req, res) => {
  const { name, surname, className } = req.body;

  for (let i = 1; i <= 10; i ++) {
    req.body[`exercise${i}`] = parseInt(req.body[`exercise${i}`]) || 0;
  }

  if (!name || !surname || !className) {
    res.render('index', req.body );
  } else {
    data = req.body;
    res.redirect('/print');
  }
});

app.listen(3000);