/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#ifndef SOP2020_P01_WORD_H
#define SOP2020_P01_WORD_H


/* Word pointer structure */
typedef struct {
    char **word;
    int top;
} WordsSet;

/* Words instantiation */
WordsSet words;

void printWordsSet();
int findIndexOfWord(char *input);
void initWordsSet(WordsSet *a);
void reallocWordsSet(WordsSet *a);
void freeWordsSet(WordsSet *a);

#endif //SOP2020_P01_WORD_H
