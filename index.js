var Alexa = require('alexa-sdk');
var tinyreq = require('tinyreq');

var goodbyeMessage = "fine, bye bye!";

exports.handler = function(event, context, callback) {
  var alexa = Alexa.handler(event, context);
  alexa.registerHandlers(handlers);
  alexa.execute();
};

var handlers = {
  'OpenIntent': function() {
    var self = this;
    tinyreq('http://31.65.187.37/open', function(err, body) {
      if (err) {
        self.emit(':tell', 'error with request');
      } else {
        return self.emit(':tell', 'opened');
      }
    });
  },
  'CloseIntent': function() {
    var self = this;
    tinyreq('http://31.65.187.37/close', function(err, body) {
      if (err) {
        self.emit(':tell', 'error with request');
      } else {
        self.emit(':tell', 'closed');
      }
    });
  },
  'AMAZON.StopIntent': function () {
    this.emit(':tell', goodbyeMessage);
  }
};
