/* levtest.c
 *
 * Copyright (C) 2020-2022, Helmut Wollmersdorfer, all rights reserved.
 *
*/

#ifndef _UTF8_TEST
#define _UTF8_TEST
#endif

#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "utf8_charlen.h"
#include "utf8_charlen.c"

int main (void) {
    clock_t tic;
    clock_t toc;
    double elapsed;
    double total = 0;
    double rate;
    double el_rate;


    int bench_on = 1;

    size_t count;
    size_t megacount;
    size_t iters     = 1000000;
    size_t megaiters = 1;

    char ascii_str1[] = "Choerephon";
    char ascii_str2[] = "Chrerrplzo";
    size_t ascii_len1 = strlen(ascii_str1);
    size_t ascii_len2 = strlen(ascii_str2);

    char utf_str1[] = "Chöerephon";
    char utf_str2[] = "Chöerrplzö";

    size_t utf_len1 = strlen(utf_str1);
    size_t utf_len2 = strlen(utf_str2);

    size_t char_len, char_len1, char_len2;

    if (1) {
    char_len = jb_utf8_chars ((unsigned char*)ascii_str1, ascii_len1);
    printf("[jb_ascii_10] bytes: %u chars: %u expect: 10\n", ascii_len1, char_len);

    char_len = jb_utf8_chars ((unsigned char*)utf_str1, utf_len1);;
    printf("[jb_utf8_10]  bytes: %u chars: %u expect:  10\n", utf_len1, char_len);

    }


    char ascii_str1_l52[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int  ascii_len1_l52   = strlen(ascii_str1_l52);
    char ascii_str2_l52[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int  ascii_len2_l52   = strlen(ascii_str2_l52);

    char utf_str1_l52[]   = "äbcdefghijklmnöpqrstÜvwxyzÄBCDEFGHIJKLMNÖPQRSTÜVWXYZ";
    int  utf_len1_l52     = strlen(utf_str1_l52);
    char utf_str2_l52[]   = "ÄBCDEFGHIJKLMNÖPQRSTÜVWXYZäbcdefghijklmnöpqrstÜvwxyz";
    int  utf_len2_l52     = strlen(utf_str2_l52);


    if (1) {
    char_len = jb_utf8_chars ((unsigned char*)ascii_str1_l52, ascii_len1_l52);
    printf("[jb_ascii_52] bytes: %u chars: %u expect: 10\n", ascii_len1_l52, char_len);

    char_len = jb_utf8_chars ((unsigned char*)utf_str1_l52, utf_len1_l52);;
    printf("[jb_utf8_52]  bytes: %u chars: %u expect:  10\n", utf_len1_l52, char_len);
    }

    /* ########## jb_ascii_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)ascii_str1, ascii_len1);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)ascii_str2, ascii_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * ascii_len2;

    printf("[jb_ascii_10]  iters: %u M Elapsed: %f s Rate: %.1f (M/sec) elRate %.1f %u\n",
        megaiters, elapsed, rate, el_rate, ((distance+distance2)/2));
}

    printf("Total: %f seconds\n", total);

    return 0;

}
