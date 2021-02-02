#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

#include "stdio.h"
#include "word.h"
#include "triplet.h"
#include "insert.h"
#include "delete.h"
#include "match.h"
#include "utils/exportDataToJSON.h"
#include <string.h>
#include <unistd.h>


int main() {
    initTriplets(&triplets);
    initWordsSet(&words);

    char *s = malloc((1024) * sizeof(char));
    char *p = malloc((1024) * sizeof(char));
    char *o = malloc((1024) * sizeof(char));


    printf("Début de la compilation\n\n");

    //insert
    insert("SOP2020", "has teacher", "PCM");
    insert("SOP2020", "topic is", "C");
    insert("SOP2020", "has teacher", "PCM");
    insert("PCM", "lastname", "Cudre");
    insert("PCM", "firstname", "Phillipe");
    insert("PCM", "lastname", "Mauroux");
    insert("SOP2020", "has", "Exam");
    insert("SOP2020", "has", "Exercices");
    insert("UniFR", "teach", "SOP2020");
    insert("UniFR", "teach", "Software Engineering");
    insert("Software Engineering", "has", "Exercices");
    insert("Software Engineering", "has", "Exam");

    // test insert avec print
    printTriplets();
    printWordsSet();

    exportDataToJSON();
    printf("\n");

    // test counting
    countTriplet("SOP2020");

    // test match
    printf("MATCH FUNCTION : \n");
    int v = match("SOP2020", p, o, 1);
    printf("int: %i ; s: %s ; p: %s ; o: %s \n", v, s, p, o);
    printf("\n");

    // deleteTriplets
    printf("DELETE FUNCTION:\n");
    deleteAllTripletsWithString("SOP2020");
    printf("\n");

    // test deleteTriplets avec print
    printTriplets();
    printWordsSet();

    printf("Fin de la compilation\n");
    return 0;
}
