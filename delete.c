/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include "delete.h"
#include "triplet.h"
#include "word.h"


/* --------------------
 * deletes all triplets at the index given in parameter
 *
 *  @params
 *      int index: value of the index that has to be deleted
 */

void deleteTripletsAtIndex(int index) {
    if (index < triplets.top) {
        for (int i = index; i < triplets.top; i++) {

            // overwrites all triplets starting from the index with the value above
            triplets.t[i].s = triplets.t[i + 1].s;
            triplets.t[i].p = triplets.t[i + 1].p;
            triplets.t[i].o = triplets.t[i + 1].o;
        }

        triplets.top -= 1;
        reallocTriplets(&triplets);
    } else fprintf(stderr, "ERROR: Can't deleteTriplets Triplet at index %d. There no such index.\n", index);
}

/* --------------------
 * deletes the words at the index given in parameter
 *
 *  @params
 *      int index: value of the index that has to be deleted
 */

void deleteWords(char *a) {
    if (findIndexOfWord(a) != -1) {
        for (int i = findIndexOfWord(a); i < words.top; i++) {

            // overwrites all words starting from the index with the value above
            words.word[i] = words.word[i + 1];
        }

        words.top -= 1;
        reallocWordsSet(&words);
    }
}

/* --------------------
 * finds out if all three of them exist and erase them
 *
 *  @params
 *      char *s: address of the subject
 *      char *p: address of the predica
 *      char *o: address of the object
 */

void deleteTriplets(char *s, char *p, char *o) {
    for (int i = 0; i < triplets.top; i++) {
        if ((strcmp(triplets.t[i].s, s) == 0)
            && (strcmp(triplets.t[i].p, p) == 0)
            && (strcmp(triplets.t[i].o, o) == 0)) {
            deleteTripletsAtIndex(i);
        } else if (i == triplets.top - 1) {
            fprintf(stderr, "ERROR deleteTriplets(): There no such Triplet '%s', '%s', '%s'.\n", s, p, o);
        }
    }
}

/* Delete all triplets with a specific word and deleteTriplets the word in the words
 * param char *a - address of the word that has to be deleted in the triplets
 */

/* --------------------
 * delete all triplets that contains a specific word
 *
 *  @params
 *      char *input: address of the input to search for
 *
 *  @note: prints on console if deletion is made or not
 */

void deleteAllTripletsWithString(char *input) {
    if (findIndexOfWord(input) != -1) {
        for (int i = 0; i < triplets.top; i++) {
            if ((strcmp(triplets.t[i].s, input) == 0)
                    || (strcmp(triplets.t[i].p, input) == 0)
                    || (strcmp(triplets.t[i].o, input) == 0)) {
                printf("SUCCESS: Triplet '%s', '%s', '%s' was deleted \n",
                       triplets.t[i].s, triplets.t[i].p, triplets.t[i].o);
                deleteTripletsAtIndex(i);
                i -= 1;
            }
        }
        // free the word from words
        deleteWords(input);
    } else {
        fprintf(stderr, "ERROR deleteAllTripletsWithString(): '%s', doesn't exist in words.\n", input);
    }
}

/* Delete all data and free the memory */

void deleteAll() {
    freeTriplets(&triplets);
    freeWordsSet(&words);
}
