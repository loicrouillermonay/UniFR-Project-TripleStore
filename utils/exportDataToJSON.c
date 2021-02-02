/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include "../word.h"
#include "../triplet.h"

void exportDataToJSON() {
    FILE *outfile;

    // check if file exists then deletes it
    if (access("./WebAssembly/public/d3js/data.json", F_OK) != -1) {
        remove("./WebAssembly/public/d3js/data.json");
    }

    // open file for writing
    outfile = fopen("./WebAssembly/public/d3js/data.json", "w");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opend file...\n");
        exit(1);
    }


    // JSON struct elements
    char *node = "{\"nodes\": [";
    char *n_1 = "{\"id\": \"";
    char *n_2 = "\", \"group\": 1},";
    char *n_3 = "\", \"group\": 1}";
    char *link = "],\"links\": [";
    char *l_1 = "{\"source\": \"";
    char *l_2 = "\", \"target\": \"";
    char *l_3 = "\", \"value\": 1},";
    char *l_4 = "\", \"value\": 1}]}";


    // word temp
    WordsSet temp_wordsSet;
    initWordsSet(&temp_wordsSet);

    // query data for the "node" section of JSON
    for (int z = 0; z < triplets.top; ++z) {
        int sExist = 0;
        int oExist = 0;
        for (int i = 0; i < temp_wordsSet.top; i++) {
            if (strcmp(temp_wordsSet.word[i], triplets.t[z].s) == 0) {
                sExist = 1;
            }
            if (strcmp(temp_wordsSet.word[i], triplets.t[z].o) == 0) {
                oExist = 1;
            }
        }

        /* If *s is new, it is added to the words and its address is noted in the triplet structure. */
        if (!sExist) {
            reallocWordsSet(&temp_wordsSet);
            temp_wordsSet.word[temp_wordsSet.top] = (char *) malloc((strlen(triplets.t[z].o) + 1) * sizeof(char));
            strcpy(temp_wordsSet.word[temp_wordsSet.top], triplets.t[z].s);
            temp_wordsSet.top++;
        }

        /* If *o is new, it is added to the words and its address is noted in the triplet structure. */
        if (!oExist) {
            reallocWordsSet(&temp_wordsSet);
            temp_wordsSet.word[temp_wordsSet.top] = (char *) malloc((strlen(triplets.t[z].o) + 1) * sizeof(char));
            strcpy(temp_wordsSet.word[temp_wordsSet.top], triplets.t[z].o);
            temp_wordsSet.top++;
        }
    }

    // convert nodes to JSON
    fwrite(node, 1, strlen(node), outfile);
    for (int n = 0; n < temp_wordsSet.top; ++n) {
        fwrite(n_1, 1, strlen(n_1), outfile);
        fwrite(temp_wordsSet.word[n], 1, strlen(temp_wordsSet.word[n]), outfile);
        if (n != temp_wordsSet.top - 1) {
            fwrite(n_2, 1, strlen(n_2), outfile);
        } else {
            fwrite(n_3, 1, strlen(n_3), outfile);
        }
    }

    // convert link to JSON
    fwrite(link, 1, strlen(link), outfile);
    for (int (i) = 0; (i) < triplets.top; ++(i)) {
        fwrite(l_1, 1, strlen(l_1), outfile);
        fwrite(triplets.t[i].s, 1, strlen(triplets.t[i].s), outfile);
        fwrite(l_2, 1, strlen(l_2), outfile);
        fwrite(triplets.t[i].o, 1, strlen(triplets.t[i].o), outfile);
        if (i != triplets.top - 1) {
            fwrite(l_3, 1, strlen(l_3), outfile);
        } else {
            fwrite(l_4, 1, strlen(l_4), outfile);
        }
    }

    if (fwrite != 0) {
        printf("contents to file written successfully !\n\n");
    } else {
        printf("error writing file !\n\n");
    }

    // close file
    fclose(outfile);
}
