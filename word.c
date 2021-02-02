/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include <stdio.h>
#include "word.h"
#include "stdlib.h"
#include "string.h"

/* --------------------
 * dynamically allocates memory for a word structure
 *
 *  @params
 *      WordsSet *a: address where the allocation in memory is done
 */

void initWordsSet(WordsSet *a) {
    a->word = (char **) malloc(sizeof(char *));
    a->top = 0;
}

/* --------------------
 * dynamically reallocates memory for a word structure
 *
 *  @params
 *      WordsSet *a: address where the allocation in memory is done
 */

void reallocWordsSet(WordsSet *a) {
    a->word = (char *) realloc(a->word, (a->top + 1) * sizeof(char *));
}

/* --------------------
 * deallocate allocated memory for a word structure
 *
 *  @params
 *      WordsSet *a: address to deallocate
 */

void freeWordsSet(WordsSet *a) {
    free(a->word);
    a->word = NULL;
    a->top = 0;
}

/* --------------------
 * find the index of a word in words set
 *
 *  @params
 *      char *input: input to search for
 *
 *  @return: returns the index as int
 *           returns -1 if input isn't found
 */

int findIndexOfWord(char *input) {
    for (int i = 0; i < words.top; i++)
        if (strcmp(input, words.word[i]) == 0) {
            return i;
        }
    return -1;
}

/* --------------------
 * displays all the contents of the words structure set
 *
 *  @note: prints result on console
 */

void printWordsSet() {
    printf("The words in the words are: \n \n");
    for (int i = 0; i < words.top; i++) {
        printf("%d: %s\n", i, words.word[i]);
    }
    printf("\n");
}

/* --------------------
 * counts the number of times that the input appears in the words set
 *
 *  @params
 *      char *input: input to search and count for
 *
 *  @return: returns the number of times as an int
 *
 *  @note: prints result on console
 */