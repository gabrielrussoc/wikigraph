var express = require('express')
var router = express.Router();

const telegram_game = require('../src/js/telegram_game');
const graph = require('../src/js/wikigraph')
const elasticsearch = require('../src/js/elasticsearch')

elasticsearch.init().then(function() {
    console.log("Indice criado com sucesso");
}, function(err) {
    console.log("Erro na criação do indice\n" + err);
});

/* GET home page. */
router.get('/', function(req, res, next) {
    const t_user_id = req.query.t_user_id;
    const t_inline_message_id = req.query.t_inline_message_id;
    const t_game = typeof t_user_id !== 'undefined' && t_user_id != '';

    if(t_game) {
        const t_highscore = telegram_game.get_highscore(t_user_id, t_inline_message_id);
    }

    const data = {
        title: 'WikiGraph',
        t_user_id: t_user_id,
        t_inline_message_id: t_inline_message_id,
        t_game: t_game,
    };
    if(t_game) {
        t_highscore.on('end', (highscore) => {
            data.t_highscore = highscore;
            res.render('index', data);
        });
    } else {
        res.render('index', data);
    }
});

router.get('/path', function(req, res, next) {
    const from = req.query.from;
    const to = req.query.to;
    const path = graph.path(from, to);
    const success = path.length > 0 && path[0] != '';

    const t_user_id = req.query.t_user_id;
    const t_inline_message_id = req.query.t_inline_message_id;
    const t_game = typeof t_user_id !== 'undefined' && t_user_id != '';

    if(t_game) {
        telegram_game.set_game_score(t_user_id, t_inline_message_id, path.length - 1);
        const t_highscore = telegram_game.get_highscore(t_user_id, t_inline_message_id);
    }

    const data = {
        title: 'WikiGraph',
        t_user_id: t_user_id,
        t_inline_message_id: t_inline_message_id,
        t_game: t_game,
        path: path,
        success: success
    };

    if(t_game) {
        t_highscore.on('end', (highscore) => {
            data.t_highscore = highscore;
            res.render('index', data);
        });
    } else {
        res.render('index', data);
    }
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
