# Project TripleStore

Project TripleStore is a C programm that implements a triple data structure in memory.
The structure is optimized for fast access with arbitrary matching patterns.
The data structure runs as WebAssemly Code on any modern webbrowser with data vizualization.

## Goals
### Minimal Feature Set

- [x] Add new Triplets through a simple function with the following signature.
- [x] Allocate the memory dynamically with malloc.
- [x] Provide a query function to find Triples.
- [x] Implement a feature to delete triples.
- [x] Integrate the provided benchmark with your code and measure the performance.

##### For the WebAssembly project:
- [x] Show that your code works as WebAssembly in the web browser.
- [x] Render the content as a Graph Drawing. (E.g. with d3js).
- [ ] Create the same functionality in JavaScript and compare the speed.

### Additional Features (propositions)

- [ ] Optimize for speed of inserting.
- [x] Allow dynamic size of values.
- [x] Optimize for size in memory.
- [ ] Load data from N-Triples (https://en.wikipedia.org/wiki/N-Triples) files.
(e.g. http://classifications.data.admin.ch/municipality/2196?format=nt)
- [ ] Insert additional values (for example the date and time of insertion) into the database.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

```
// clone git directory on your local machine
$ git clone https://diuf-gitlab.unifr.ch/SOP_2020_P01_cappuccino/sop2020_p01.git

// go the downloaded directory
$ cd sop2020_p01
```

### Prerequisites

In order to compile the C code to WebAssembly, you need to install Emscripten.

/!\  for no reason it only works with emsdk at version 1.38.48 (emsdk-1.38.48)
```
// Go to folder
$ cd utils/emsdk-1.38.48

// Download and install the latest SDK tools.
$ ./emsdk install 1.38.48

// Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
$ ./emsdk activate 1.38.48

// Activate PATH and other environment variables in the current terminal
$ source ./emsdk_env.sh
```

The projects uses Node.js to build a web server

```
// Node.js installation
https://nodejs.org/en/download/

```

### Compiling C

```
// in the root directory
$ make
```

### Running with C

```
// in the root directory
$ ./Project_TripleStore

```

### Compiling to WebAssemly


```
// in the root directory
$ make WebAssembly

// alternative way (and you need admin privileges)
$ emcc main.c insert.c delete.c triplet.c word.c utils/exportDataToJSON.c match.c -s WASM=1 -s LINKABLE=1 -s EXPORTED_FUNCTIONS="['_main','_printWordsSet','_findIndexOfWord', '_initWordsSet','_reallocWordsSet','_freeWordsSet','_printTriplets','_initTriplets', '_reallocTriplets','_freeTriplets','_countTriplet','_match','_insert', '_deleteTriplets','_deleteTripletsAtIndex','_deleteAllTripletsWithString', '_deleteWords','_deleteAll','_exportDataToJSON']" -o WebAssembly/public/functions.html --bind --embed-file WebAssembly/public/d3js/data.json
```

### Running to WebAssembly & D3js

Unfortunately several browsers (including Chrome, Safari, and Internet Explorer) do not support file:// XHR requests, and can’t load extra files needed by the HTML (like a .wasm file, or packaged file data as mentioned lower down). For these browsers you’ll need to serve the files using a webserver.

```
// go to folder WebAssembly
$ cd WebAssembly

// start server on port 9090
$ npm run start
```

Then visit  http://localhost:9090


## Benchmark

### Running the benchmark

The benchmark does first load the content of the file data.nt.
Then three different match queries are issued

```
// go the the benchmark folder
$ cd benchmark

// start benchmark
$ make

```

### Memory Optimization Version - Benchmark Scores
##### Outputs
- insert() took 479'696 milliseconds ~ 7,9 minutes
- match(s,_,_,_) took 16 milliseconds
- match(s,p,o,2) took 7 milliseconds
- match(s,p,o,0) took 5 milliseconds

##### Memory Optimization  - Memory usage estimation : ~ 24.14 mb (= 4% of 486.88 mb)

The calculations below are more or less accurate estimates that do not take into account the memory occupied by other processes during program execution.

```
On 64-bit machine sizeof pointer is 64 bits ( 8 bytes).
There's 117'731 unique words in the words set of the benchmark
sizeof(Triplet) = 24 bytes
sizeof(Triplet_ptr) = 16 bytes
sizeof(WordSets) = 16 bytes
sizeof(int) = 4 bytes
sizeof(char) is (by definition) 1 byte
The average word length in benchmark is 27 chars
```
- struct Triplet : (157'672 lines * 24 bytes) + (157'672 lines * 3 colums * 27 (average word length) bytes) = 16.55560 megabytes
- struct Triplet_ptr : (157'672 lines * 16 bytes) = 2.522752 megabytes
- struct WordsSet : (117'731 words * 16 bytes) + (117'731 words * 27 bytes)  = 5.062433 megabytes

Total of memory usage : 24.14 mb

> Another more precise solution could be to use __FILE* status = fopen( "/proc/self/status", "r" );__ and then look after inserting all the data for the lines VmSize (current size in virtual memory) and VmPeak (maximum size in virtual memory) but it doesn't work on our work environments.

### Standard Version without any optimization - Benchmark Scores
##### Outputs
- insert() took 1419 milliseconds ~ 1,5 secondes
- match(s, _, _, _) took 63 milliseconds
- match(_, p, o, 2) took 11 milliseconds
- match(s, p, o, 0) took 6 milliseconds

##### Standard Version without any optimization  - Memory usage estimation : ~ 486.8 mb

The calculations below are more or less accurate estimates that do not take into account the memory occupied by other processes during program execution.

```
On 64-bit machine sizeof pointer is 64 bits ( 8 bytes)
Sizeof(char) is by definition 1 byte
Sizeof(Triplets_ptr) is 16 bytes
```
- struct Triplet : 157'672 lines * 3 colums * 1024 bytes = 484.368384 megabytes
- struct Triplet_ptr : (157'672 lines * 16 bytes) = 2.522752 megabytes

Total of memory usage: 486.88 mb

> Another more precise solution could be to use __FILE* status = fopen( "/proc/self/status", "r" );__ and then look after inserting all the data for the lines VmSize (current size in virtual memory) and VmPeak (maximum size in virtual memory) but it doesn't work on our work environments.

## Authors
- Loïc Rouiller-Monay
- Jonathan Quendoz
- Vladimir Jovicic
- Guillaume Bonvin
