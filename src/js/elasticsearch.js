var elasticsearch = require('elasticsearch');
var fs = require('fs')

var elasticClient = new elasticsearch.Client({
    host: 'localhost:9200',
    log: 'info'
});

var indexName = "wiki_articles";

function createIndex() {
    return elasticClient.indices.create({
        index: indexName,
        body: {
            settings: {
                number_of_shards: 1,
                number_of_replicas: 0
            }
        }
    });
}

function deleteIndex() {
    return elasticClient.indices.delete({
        index: indexName
    });
}

function indexExists() {
    return elasticClient.indices.exists({
        index: indexName
    });
}

function buildIndex() {
    return indexExists().then(function (exists) {
        if(!exists) {
            return createIndex().then(initMapping).then(addAll);
        }
    });
}

function initMapping() {
    return elasticClient.indices.putMapping({
        index: indexName,
        type: "document",
        body: {
            properties: {
                title: { type: "string" },
                suggest: {
                    type: "completion",
                    analyzer: "standard"
                }
            }
        }
    });
}

function addAll() {
    var articles = JSON.parse(fs.readFileSync('./data/articles.json', 'utf8'));
    var bulk_data = [];
    articles.map(function(article) {
        bulk_data.push({ index: {} });
        bulk_data.push({ title: article, suggest: article });
    });
    return elasticClient.bulk({
        index: indexName,
        type: 'document',
        requestTimeout: 3000000,
        refresh: true,
        body: bulk_data
    });
}

function getSuggestions(input) {
    return elasticClient.suggest({
        index: indexName,
        body: {
            articlesuggest: {
                prefix: input,
                completion: {
                    field: "suggest",
                    size: 6
                }
            }
        }
    });
}

module.exports = {
    init: buildIndex,
    suggest: getSuggestions
}
