'use strict';

var express = require('express');
var app = express();

var actionTriggered = false;

app.set('view engine', 'ejs');
app.use(express.static('public'));

var Pusher = require('pusher');

var pusher = new Pusher({
  appId: '150497',
  key: process.env.PUSHER_KEY,
  secret: process.env.PUSHER_SECRET,
  encrypted: true
});
pusher.port = 443;

app.get('/', function (req, res) {
  res.send("HELLO WORLD");
});

app.get('/light/1/color', function(req, res) {
  var color = 'r0,g0,b0';
  if (actionTriggered) {
    color = 'r0,g255,b0\n';
    actionTriggered = !actionTriggered;
  }
  res.send(color);
});

// Twit library for consuming twitter streams
// https://github.com/ttezel/twit
var Twit = require('twit');
var twit = new Twit({
  consumer_key: process.env.TWITTER_CONSUMER_KEY,
  consumer_secret: process.env.TWITTER_CONSUMER_SECRET,
  access_token: process.env.TWITTER_ACCESS_TOKEN,
  access_token_secret: process.env.TWITTER_ACCESS_TOKEN_SECRET
});
var stream = twit.stream('statuses/filter', { track: "#" + process.env.HASHTAG });
console.info("Hashtag: ", process.env.HASHTAG);

stream.on('tweet', function(tweet) {
  console.info("Hashtag Tweeted: ", process.env.HASHTAG);
    pusher.trigger('smw2015_channel', 'hashtag_tweeted', {
      "hashtag": process.env.HASHTAG
    });
});

var server = app.listen(process.env.PORT || 3000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Web app listening at http://%s:%s', host, port);
});
