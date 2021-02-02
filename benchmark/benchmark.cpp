#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include "smallrdf/src/RDF.h"
#include "smallrdf/src/RDFList.h"
#include "smallrdf/src/RDFNTriplesParser.h"

#define init(){initTriplets(&triplets); initWords(&words);}

/* PLEASE INSERT YOUR STORE */
#include "../word.c"
#include "../triplet.c"
#include "../insert.c"
#include "../match.c"

int main() {
    init();
    //load NT file in string
    std::ifstream t("data.nt");
    std::stringstream stream;
    stream << t.rdbuf();
    std::string buffer = stream.str();

    //prepare parser
    std::cout << "Parse data ..." << std::endl;
    RDFString input(buffer.c_str());
    NTriplesParser parser(&input, 0);


    //start insert timing
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    std::cout << "Insert data ..." << std::endl;
    const RDFQuad *quad = parser.parseQuad();

    while (quad != 0) {
        insert((char *) quad->subject->value->c_str(), (char *) quad->predicate->value->c_str(),
               (char *) quad->object->value->c_str());
        quad = parser.parseQuad();
    }

    //stop insert timing
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "# insert() took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";


    std::cout << "Run match queries ..." << std::endl;
    //start match1 timing
    t1 = std::chrono::high_resolution_clock::now();

    char *p = (char *) malloc(1024 * sizeof(char));
    char *o = (char *) malloc(1024 * sizeof(char));
    long i = 0;
    while (!match("https://ld.geo.admin.ch/transportation/stop/8577741", p, o, i)) {
        i++;
        std::cout << "## match " << i << " -> P: " << p << " O:" << o << std::endl;
        p[0] = o[0] = 0;
    }

    //stop match1 timing
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "# match(s, _, _, _) took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";


    //start match2 timing
    t1 = std::chrono::high_resolution_clock::now();

    char *s = (char *) malloc(1024 * sizeof(char));
    i = 0;
    while (!match(s, "http://schema.org/name", "Fribourg/Freiburg", i)) {
        i++;
        std::cout << "## match " << i << " -> S: " << s << std::endl;
    }

    //stop match2 timing
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "# match(_, p, o, 2) took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";

    //start match3 timing
    t1 = std::chrono::high_resolution_clock::now();

    if (!match("https://ld.geo.admin.ch/transportation/stop/8504100", "http://www.w3.org/2003/01/geo/wgs84_pos#lat",
               "46.8032675855973", 0)) {
        std::cout << "## triple found" << std::endl;
    }

    //stop match3 timing
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "# match(s, p, o, 0) took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";

    std::cout << "Finished" << std::endl;

}
