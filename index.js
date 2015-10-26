'use strict';

var express = require('express');
var app = express();

var actionTriggered = false;

app.set('view engine', 'ejs');
app.use(express.static('public'));

app.get('/', function (req, res) {
  res.send("HELLO WORLD");
});

app.get('/light/1/color', function(req, res) {
  var color = 'r0,g0,b0';
  if (actionTriggered) {
    color = 'r0,g255,b0\n';
  }
  res.send(color);
});

app.post('/action', function(req, res) {
  actionTriggered = true;

  setTimeout(function() {
    actionTriggered = false;
  }, 1000);

  res.send("action triggered.");
})

var server = app.listen(process.env.PORT || 3000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Web app listening at http://%s:%s', host, port);
});
