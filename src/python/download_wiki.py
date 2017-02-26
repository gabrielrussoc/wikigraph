#!/usr/bin/python3
import requests
import json
import sys

def get_pages(filename):
    base = {'action': 'query', 'list': 'allpages', 'apnamespace': '0', 'aplimit': 'max', 'apcontinue' : '', 'apfilterredir': 'nonredirects', 'format': 'json'}
    url = 'https://pt.wikipedia.org/w/api.php'
    
    txt = open(filename, "w")
    count = 0
    
    while True:
        json_obj = json.loads(requests.get(url, params = base).text)
    
        for page in json_obj['query']['allpages']:
            pid = page['pageid']
            title = page['title']
            txt.write(str(pid) + ':' + title + '\n')
            count += 1
    
        print('Escrevi ' + str(count) + ' ids!')
    
        if 'continue' in json_obj:
            base['apcontinue'] = json_obj['continue']['apcontinue']
        else:
            break
    
    txt.close()

def get_links(filename):
    base = {'action': 'query', 'list': 'alllinks', 'alnamespace': '0', 'allimit': 'max', 'alprop': 'ids|title', 'alfrom': 'Honda Civic GX', 'format': 'json'}
    url = 'https://pt.wikipedia.org/w/api.php'
    
    txt = open(filename, "w")
    
    while True:
        json_obj = json.loads(requests.get(url, params = base).text)
    
        for page in json_obj['query']['alllinks']:
            fromid = page['fromid']
            title = page['title']
            txt.write(str(fromid) + ':' + title + '\n')
    
        print('Escrevi ' + title)
    
        if 'continue' in json_obj:
            base['alcontinue'] = json_obj['continue']['alcontinue']
        else:
            break
    txt.close()

def main():
    if len(sys.argv) != 3:
        sys.stderr.write('Uso: ' + sys.argv[0] + ' [-p filename] [-l filename]\n')
        sys.exit(-1)

    filename = sys.argv[2]
    if sys.argv[1] == '-p':
        get_pages(filename)
    elif sys.argv[1] == '-l':
        get_links(filename)
    else:
        sys.stderr.write('Parametro ' + sys.argv[1] + ' desconhecido\n')
        sys.exit(-1)

if __name__ == '__main__':
    main()
