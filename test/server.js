var express = require('express');
var bodyParser = require('body-parser');

var app = express();

app.use(bodyParser.json());
app.get('/api/switch', getHandler);
app.post('/api/switch', switchHandler);
app.use('/', express.static('../data'));

app.listen(8085);

var state = false;

function getHandler(req, res) {
    var value = state ? 'on' : 'off';
    res.send("{ \"state\": \"" + value + "\" }");
}

function switchHandler(req, res) {
    console.log(req.body);
    var data = req.body;
    state = data.state === 'on';
    res.send('switch=' + data.state);
}
