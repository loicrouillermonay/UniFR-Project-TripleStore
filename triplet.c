/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include "triplet.h"

/* --------------------
 * dynamically allocates memory for a triplet structure
 *
 *  @params
 *      Triplet_ptr *a: address where the allocation in memory is done
 */

void initTriplets(Triplet_ptr *a) {
    a->t = (Triplet *) malloc(sizeof(Triplet));
    a->top = 0;
}

/* --------------------
 * dynamically reallocates memory for a triplet structure
 *
 *  @params
 *      Triplet_ptr *a: address where the allocation in memory is done
 */

void reallocTriplets(Triplet_ptr *a) {
    a->t = (Triplet *) realloc(a->t, (a->top + 1) * sizeof(Triplet));
}

/* --------------------
 * deallocate allocated memory for a triplet structure
 *
 *  @params
 *      Triplet_ptr *a: address to deallocate
 */

void freeTriplets(Triplet_ptr *a) {
    free(a->t);
    a->t = NULL;
    a->top = 0;
}

/* --------------------
 * displays all the contents of the triplet structure set
 *
 *  @note: prints result on console
 */

void printTriplets() {
    printf("Stored triplets are: \n \n");

    for (int i = 0; i < triplets.top; i++) {
        printf("%d: %s, %s, %s\n", i, triplets.t[i].s, triplets.t[i].p, triplets.t[i].o);
    }

    printf("\n");
}

/* --------------------
 * counts the number of times that the input appears in the triplets set
 *
 *  @params
 *      char *input: input to search and count for
 *
 *  @return: returns the number of times as an int
 *
 *  @note: prints result on console
 */

int countTriplet(char *input) {
    int count = 0;

    for (int i = 0; i < triplets.top; i++) {
        if (strcmp(triplets.t[i].s, input) == 0) ++count;
        if (strcmp(triplets.t[i].p, input) == 0) ++count;
        if (strcmp(triplets.t[i].o, input) == 0) ++count;
    }

    if (count) {
        printf("The input '%s' appears %d time(s) in the Triplet.\n\n", input, count);
    } else {
        printf("The input '%s' doesn't exist in the Triplet.\n\n", input);
    }

    return count;
}