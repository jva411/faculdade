const ponto = require('./ponto.js');

var p = new ponto.Ponto(0, 3);
var p2 = new ponto.Ponto(4, 0);
console.log(p.x + ' ' + p.y);
console.log(p2.x + ' ' + p2.y);
console.log(p.distance(p2));