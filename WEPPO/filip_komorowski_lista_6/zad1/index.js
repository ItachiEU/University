//https://code.tutsplus.com/tutorials/file-upload-with-multer-in-node--cms-32088

const express = require('express')
const multer = require('multer')
const fs = require('fs')
const path = require('path')
const app = express();

app.get('/',function(req,res){
  res.sendFile(__dirname + '/index.html');
 
});

var storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'uploads')
  },
  filename: function (req, file, cb) {
    cb(null, file.fieldname + '-' + Date.now())
  }
})
 
var upload = multer({ storage: storage })

app.post('/uploadfile', upload.single('myFile'), (req, res, next) => {
  const file = req.file
  if (!file) {
    const error = new Error('Please upload a file')
    error.httpStatusCode = 400
    return next(error)
  }
    res.send(file)
  
})

app.use(express.static('public'))

app.listen(3000, function () {
    console.log('listening on port 3000!');
});