/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#ifndef SOP2020_P01_DELETE_H
#define SOP2020_P01_DELETE_H

#include "word.h"

void deleteTriplets(char* s, char*p, char* o);
void deleteTripletsAtIndex(int index);
void deleteAllTripletsWithString(char* input);
void deleteWords(char* a);
void deleteAll();

#endif //SOP2020_P01_DELETE_H
