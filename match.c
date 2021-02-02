/* SOP_2020_P01_cappuccino - Fast Small In-Memory Triple Datastructures
 * Loïc Rouiller-Monay, Vladimir Jovicic, Guillaume Bonvin, Jonathan Quendoz
 */

#include "triplet.h"

/* --------------------
 * provide a query function to find Triples in which one or multiple values can be fixed
 *
 *  @params
 *      char *s, *p, *o: Specifies pointers for the query variables and
 *                       the return variables. If we look for examples for
 *                       all triples where S is set to a specific string, we
 *                       only provide s and initialize the other strings with 0s.
 *
 *      long result:     Specifies which result shall be returned counting
 *                       from 0 upwards
 *
 *  @return: returns 0 if everything is working correctly
 *           returns 1 if there's no result found.
 *
 *  @note: prints result on console if a match is found
 */

int match(char *s, char *p, char *o, long result) {
    Triplet temp;
    int counterUpToTheResult = 0;

    for (int i = 0; i < triplets.top; i++) {

        // Each pointers of temp are set to the values to count up to the result.
        // In other words, for each s, p, o, it sets its value if it's provided, else, it sets the value from &triplets

        if (strcmp(s, "")) temp.s = s;
        else temp.s = triplets.t[i].s;
        if (strcmp(p, "")) temp.p = p;
        else temp.p = triplets.t[i].p;
        if (strcmp(o, "")) temp.o = o;
        else temp.o = triplets.t[i].o;

        // check if the triplet at index i from &triplets matches with temp
        if (strcmp(triplets.t[i].s, temp.s) == 0
            && strcmp(triplets.t[i].p, temp.p) == 0
            && strcmp(triplets.t[i].o, temp.o) == 0) {

            // check if the current match correspond to the desired result
            if (counterUpToTheResult == result) {
                if (strcmp(s, "") == 0) strcpy(s, temp.s);
                if (strcmp(p, "") == 0) strcpy(p, temp.p);
                if (strcmp(o, "") == 0) strcpy(o, temp.o);
                printf("MATCH FOUND : %s, %s, %s\n", s, p, o);
                return 0;
            } else {
                counterUpToTheResult++;
            }
        }
    }
    return 1;
}
