var express = require('express')
var router = express.Router();

const graph = require('../src/js/wikigraph')
const elasticsearch = require('../src/js/elasticsearch')

elasticsearch.init().then(function() {
    console.log("Indice criado com sucesso");
}, function(err) {
    console.log("Erro na criação do indice\n" + err);
});

/* GET home page. */
router.get('/', function(req, res, next) {
    res.render('index', { title: 'WikiGraph' });
});

router.get('/path', function(req, res, next) {
    var from = req.query.from;
    var to = req.query.to;
    res.render('index', { title: 'WikiGraph', path: graph.path(from, to) });
});

router.get('/autocomplete', function(req, res, next) {
    var query = req.query.query;
    elasticsearch.suggest(query).then(function(matches) {
        var autocomplete = {};
        autocomplete.suggestions = matches.articlesuggest[0].options.map(function(match) {
            var article = match._source.title;
            return { value: article };
        });
        res.send(autocomplete);
    }, function(err) {
        console.log(err);
        res.status(500).send('Problema no autocomplete!')
    });
});

module.exports = router;
