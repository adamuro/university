const express = require('express');
const session = require('express-session');
const cookieParser = require('cookie-parser');
const FileStore = require('session-file-store')(session);

const fileStoreOptions = {};
const app = express();

const PORT = 3000;

app.set('view engine', 'ejs');

app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(cookieParser());
app.use(session({
  name: 'cookie',
  store: new FileStore(fileStoreOptions),
  secret: 'longsecretstring',
  saveUninitialized: false,
  resave: false,
}));

app.get('/', (req, res) => {
  if (req?.session.user) return res.redirect('user');

  res.render('index');
});

app.get('/user', (req, res) => {
  const user = req?.session.user;

  if (!user) return res.redirect('/');

  res.render('user', { user });
});

app.post('/login', (req, res) => {
  req.session.user = req.body.user
  res.redirect('user');
});

app.post('/logout', (req, res) => {
  req.session.destroy();
  res.clearCookie('cookie');
  res.redirect('/');
})

app.listen(PORT, () => console.log(`Listening on ${PORT}`));