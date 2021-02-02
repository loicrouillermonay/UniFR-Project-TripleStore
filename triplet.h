/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#ifndef SOP2020_P01_TRIPLET_H
#define SOP2020_P01_TRIPLET_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Triple data structure */
typedef struct {
    char *s;
    char *p;
    char *o;
} Triplet;

/* Triplet pointer structure */
typedef struct {
    Triplet *t;
    int top;
} Triplet_ptr;

/* Triplet instantiation */
Triplet_ptr triplets;

void printTriplets();
void initTriplets(Triplet_ptr *a);
void reallocTriplets(Triplet_ptr *a);
void freeTriplets(Triplet_ptr *a);
int countTriplet(char *input);

#endif //SOP2020_P01_TRIPLET_H
