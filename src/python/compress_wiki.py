#!/usr/bin/python3
import sys

# Compress wiki pages and links.
# Write the results on  wiki_pages_compressed.txt and wiki_links_compressed.txt
# The first page of the resulting pages file has id 1
# All the links use ids from the resulting pages file
#
# pages should be in the format
# pageid:pagename
#
# links should be in the format
# fromid:linkname
def compress(pages, links):
    print('Comprimindo...')
    fp = open('wiki_pages_compressed.txt', 'w', encoding='utf-8')
    fl = open('wiki_links_compressed.txt', 'w', encoding='utf-8')
    nid = {}
    ids = {}
    c = 1
    for page in pages:
        page = page.strip().split(':', 1)
        nid[page[0]] = c
        ids[page[1]] = c
        c += 1
        fp.write(page[1] + '\n')

    for link in links:
        link = link.strip().split(':', 1)
        if link[0] in nid and link[1] in ids:
            fl.write(str(nid[link[0]]) + ' ' + str(ids[link[1]]) + '\n')

    fp.close()
    fl.close()

def main():
    if len(sys.argv) != 3:
        sys.stderr.write('Uso: ' + sys.argv[0] + ' pages links\n')
        sys.exit(-1)

    try:
        pages = open(sys.argv[1], 'r', encoding='utf-8')
    except:
        sys.stderr.write('Falha ao abrir o arquivo de paginas\n')
        sys.exit(-1)

    try:
        links = open(sys.argv[2], 'r', encoding='utf-8')
    except:
        sys.stderr.write('Falha ao abrir o arquivo de paginas\n')
        sys.exit(-1)

    compress(pages, links)
    pages.close()
    links.close()

if __name__ == '__main__':
    main()
