# WikiGraph
Query distances between portuguese Wikipedia articles.

This is a personal project to deal with some simple and cool data structures.

The app is powered by Node.js and Express framework.

The heavy part is written in C++ and imported as an addon in Node. To fetch Wikipedia data, I used a
Python script and the Wikimedia API (it takes a lot to download everything right now).

It should be easy to port it to any language you want, but **ENGLISH IS HUGE**. Feel free to contact me.

## Setting it up

### nginx

The app runs on localhost:3000. One option is to redirect port 80 traffic to 3000 using nginx:

```
server {
    listen 80;
    server_name example.com;

    location / {
        proxy_set_header   X-Forwarded-For $remote_addr;
        proxy_set_header   Host $http_host;
        proxy_pass         "http://127.0.0.1:3000";
    }
}
```

### dependencies

npm and node are needed. working with
```
$ node --version
v4.2.6

$ npm --version
3.5.2
```

a C++ compilator is also needed. working with
```
$ g++ --version
g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609
```

elasticsearch running on localhost:9200. working with version 5.2.2 and java 8
since elasticsearch is needed only for the autocomplete, it might be a good idea to
start the app with a small graph and all the full `articles.json` to spare ram while building the index

the index is built only in the first run.

### downloading the data

to download the data, run 
```
src/python/download_wiki.py -p PAGES_FILE
src/python/download_wiki.py -l LINKS_FILE
src/python/compress_wiki.py PAGES_FILE LINKS_FILE
src/python/array_to_json.py wiki_pages_compressed.txt
```
then copy `wiki_pages_compressed.txt`, `wiki_links_compressed.txt` and `array.json` to `data`. Rename `array.json` to `articles.json`.
it might take a bit to download the links.
