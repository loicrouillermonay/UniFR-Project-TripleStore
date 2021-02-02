SRCS = main.c insert.c word.c triplet.c match.c delete.c utils/exportDataToJSON.c
OBJS = $(SRCS:.c=.o)
MAIN = program

all: Project_TripleStore

Project_TripleStore: build/insert.o build/delete.o build/triplet.o build/word.o build/match.o build/exportDataToJSON.o build/main.o
	gcc -o Project_TripleStore build/insert.o build/delete.o build/triplet.o build/word.o build/match.o build/exportDataToJSON.o build/main.o

build/triplet.o: triplet.c
	gcc -o build/triplet.o -c triplet.c -W -Wall -ansi -pedantic

build/word.o: word.c
	gcc -o build/word.o -c word.c -W -Wall -ansi -pedantic

build/insert.o: insert.c
	gcc -o build/insert.o -c insert.c -W -Wall -ansi -pedantic

build/delete.o: delete.c
	gcc -o build/delete.o -c delete.c -W -Wall -ansi -pedantic

build/match.o: match.c
	gcc -o build/match.o -c match.c -W -Wall -ansi -pedantic

build/exportDataToJSON.o: utils/exportDataToJSON.c
	gcc -o build/exportDataToJSON.o -c utils/exportDataToJSON.c -W -Wall -ansi -pedantic

build/main.o: main.c
	gcc -o build/main.o -c main.c -W -Wall -ansi -pedantic

WebAssembly:
	emcc main.c insert.c delete.c triplet.c word.c utils/exportDataToJSON.c match.c -s WASM=1 -s LINKABLE=1 -s EXPORTED_FUNCTIONS="['_main','_printWordsSet','_findIndexOfWord', '_initWordsSet','_reallocWordsSet','_freeWordsSet','_printTriplets','_initTriplets', '_reallocTriplets','_freeTriplets','_countTriplet','_match','_insert', '_deleteTriplets','_deleteTripletsAtIndex','_deleteAllTripletsWithString', '_deleteWords','_deleteAll','_exportDataToJSON']" -o WebAssembly/public/functions.html --bind --embed-file WebAssembly/public/d3js/data.json
