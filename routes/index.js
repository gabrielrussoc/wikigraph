var express = require('express')
var router = express.Router();

const graph = require('../src/js/wikigraph')

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'WikiGraph' });
});

router.get('/path', function(req, res, next) {
  var from = req.query.origem;
  var to = req.query.destino;
  res.render('index', { title: 'WikiGraph', path: graph.path(from, to) });
});

module.exports = router;
