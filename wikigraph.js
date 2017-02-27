const wg = require('./build/Release/wiki-graph-node')

wikiGraph = new wg.WikiGraph('./data/wiki_pages_compressed.txt', './data/wiki_links_compressed.txt')

module.exports = {
    path: function() {
        return wikiGraph.path('Capivara', 'Barack Obama')
    }
}
