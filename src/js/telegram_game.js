const https = require('https');
const EventEmitter = require('events');

const TELEGRAM_TOKEN = process.env.RUSSOBOT_TOKEN;

module.exports = {
    set_game_score: (user_id, inline_message_id, score) => {
        const url = encodeURI('https://api.telegram.org/bot' + TELEGRAM_TOKEN + '/setGameScore?' + 'user_id=' + user_id + '&score=' + score + '&inline_message_id=' + inline_message_id);
        https.get(url);
    },
    get_highscore: (user_id, inline_message_id) => {
        const url = encodeURI('https://api.telegram.org/bot' + TELEGRAM_TOKEN + '/getGameHighScores?' + 'user_id=' + user_id + '&inline_message_id=' + inline_message_id);
        const emitter = new EventEmitter();
        https.get(url, (res) => {
            res.setEncoding('utf8');
            var rawData = '';
            res.on('data', (chunk) => { rawData += chunk; });
            res.on('end', () => {
                const parsedData = JSON.parse(rawData);
                if(parsedData.result.length == 0) {
                    emitter.emit('end', 'nenhum');
                    return;
                }
                const top_player = parsedData.result[0];
                const highscore = top_player.user.first_name + ' ' + top_player.user.last_name + ' - ' + top_player.score;
                emitter.emit('end', highscore);
            });
        });
        return emitter;
    }
};
