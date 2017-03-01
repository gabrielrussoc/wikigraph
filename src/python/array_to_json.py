#!/usr/bin/python3

import sys
import json

def jsonfy(array_file):
    out = open('array.json', 'w')
    out.write(json.dumps([line.strip() for line in array_file]))

def main():
    if len(sys.argv) != 2:
        sys.stderr.write('Uso: ' + sys.argv[0] + ' array_file\n')
        sys.exit(-1)

    try:
        array_file = open(sys.argv[1], 'r')
    except:
        sys.stderr.write('Falha ao abrir o arquivo\n')
        sys.exit(-1)

    jsonfy(array_file)
    array_file.close()

if __name__ == '__main__':
    main()
