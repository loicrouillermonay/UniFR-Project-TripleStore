/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include "triplet.h"
#include "word.h"

/* --------------------
 * add new triplet
 *
 *  @params
 *      char *s: address of the subject
 *      char *p: address of the predica
 *      char *o: address of the object
 *
 *  @return: returns 0 if everything is working correctly
 */

int insert(char *s, char *p, char *o) {
    reallocTriplets(&triplets);

    // Check if *s is in the words, else add it
    if (findIndexOfWord(s) != -1) {
        triplets.t[triplets.top].s = words.word[findIndexOfWord(s)];
    } else {
        reallocWordsSet(&words);
        words.word[words.top] = (char *) malloc(strlen(s) * sizeof(char));
        strcpy(words.word[words.top], s);
        triplets.t[triplets.top].s = words.word[words.top];
        words.top++;
    }

    // Check if *p is in the words, else add it
    if (findIndexOfWord(p) != -1) {
        triplets.t[triplets.top].p = words.word[findIndexOfWord(p)];
    } else {
        reallocWordsSet(&words);
        words.word[words.top] = (char *) malloc(strlen(p) * sizeof(char));
        strcpy(words.word[words.top], p);
        triplets.t[triplets.top].p = words.word[words.top];
        words.top++;
    }

    // Check if *o is in the words, else add it
    if (findIndexOfWord(o) != -1) {
        triplets.t[triplets.top].o = words.word[findIndexOfWord(o)];
    } else {
        reallocWordsSet(&words);
        words.word[words.top] = (char *) malloc(strlen(o) * sizeof(char));
        strcpy(words.word[words.top], o);
        triplets.t[triplets.top].o = words.word[words.top];
        words.top++;
    }

    triplets.top++;
    return 0;
}
