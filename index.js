'use strict';

var express = require('express');
var app = express();

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

// Twit library for consuming twitter streams
// https://github.com/ttezel/twit
var Twit = require('twit');
var twit = new Twit({
  consumer_key: process.env.TWITTER_CONSUMER_KEY,
  consumer_secret: process.env.TWITTER_CONSUMER_SECRET,
  access_token: process.env.TWITTER_ACCESS_TOKEN,
  access_token_secret: process.env.TWITTER_ACCESS_TOKEN_SECRET
});

var friendsCount = 0;
var friendsStream = twit.stream('statuses/filter', { track: "#friends" });
friendsStream.on('tweet', function(tweet) {
    friendsCount++;
    pusher.trigger('smw2015_channel', 'friends_tweeted', {});
    console.log("'#friends' tweet found. id #" + tweet["id"] + ". " + friendsCount + " tweets so far.");
});

var adsCount = 0;
var adsStream = twit.stream('statuses/filter', { track: "#ads" });
adsStream.on('tweet', function(tweet) {
    adsCount++;
    pusher.trigger('smw2015_channel', 'ads_tweeted', {});
    console.log("'#ads' tweet found. id #" + tweet["id"] + ". " + adsCount + " tweets so far.");
});

var server = app.listen(process.env.PORT || 3000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Web app listening at http://%s:%s', host, port);
});
