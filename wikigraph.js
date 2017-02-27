const wg = require('./build/Release/wiki-graph-node')

wikiGraph = new wg.WikiGraph('./data/wiki_pages_compressed.txt', './data/wiki_links_compressed.txt')
console.log("Grafo montado com sucesso!")

module.exports = {
    path: function(from, to) {
        return wikiGraph.path(from, to)
    }
}
