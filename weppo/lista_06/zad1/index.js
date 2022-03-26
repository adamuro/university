const express = require('express');
const multer = require('multer');

const upload = multer({ dest: './uploads' })
const app = express();

PORT = 3000;

app.use(express.static('public'));

app.post('/', upload.single('file'), (req, res) => {
  const { originalname, filename } = req.file;
  console.log(`Saved file ${originalname} as ${filename}`);
  res.redirect('/');
});

app.listen(PORT, () => console.log(`Listening on ${PORT}`));