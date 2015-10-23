'use strict';

var express = require('express');
var app = express();

app.set('view engine', 'ejs');
app.use(express.static('public'));

app.get('/', function (req, res) {
  res.send("HELLO WORLD");
});

var server = app.listen(process.env.PORT || 3000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Web app listening at http://%s:%s', host, port);
});
