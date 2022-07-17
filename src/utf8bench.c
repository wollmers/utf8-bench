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
    // double b_rate;


    int bench_on = 1;

    size_t count;
    size_t megacount;
    size_t iters     = 1000000;
    size_t megaiters = 100;

    char ascii_str1_l7[] = "Choerep";
    char ascii_str2_l7[] = "Chrerrp";
    size_t ascii_len1_l7 = strlen(ascii_str1_l7);
    size_t ascii_len2_l7 = strlen(ascii_str2_l7);

    char ascii_str1_l8[] = "Choereph";
    char ascii_str2_l8[] = "Chrerrpl";
    size_t ascii_len1_l8 = strlen(ascii_str1_l8);
    size_t ascii_len2_l8 = strlen(ascii_str2_l8);

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
    char_len = jb_utf8_chars ((unsigned char*)ascii_str1_l7, ascii_len1_l7);
    printf("[jb_ascii_l7] bytes: %u chars: %u expect: 7\n", (unsigned)ascii_len1_l7, (unsigned)char_len);

    char_len = jb_utf8_chars ((unsigned char*)ascii_str1_l8, ascii_len1_l8);
    printf("[jb_ascii_l8] bytes: %u chars: %u expect: 8\n", (unsigned)ascii_len1_l8, (unsigned)char_len);

    char_len = jb_utf8_chars ((unsigned char*)ascii_str1, ascii_len1);
    printf("[jb_ascii_10] bytes: %u chars: %u expect: 10\n", (unsigned)ascii_len1, (unsigned)char_len);

    char_len = jb_utf8_chars ((unsigned char*)utf_str1, utf_len1);
    printf("[jb_utf8_10]  bytes: %u chars: %u expect: 10\n", (unsigned)utf_len1, (unsigned)char_len);

    char_len = cp_utf8_chars ((unsigned char*)ascii_str1, ascii_len1);
    printf("[cp_ascii_10] bytes: %u chars: %u expect: 10\n", (unsigned)ascii_len1, (unsigned)char_len);

    char_len = cp_utf8_chars ((unsigned char*)utf_str1, utf_len1);
    printf("[cp_utf8_10]  bytes: %u chars: %u expect: 10\n", (unsigned)utf_len1, (unsigned)char_len);

    char_len = sc_utf8_chars ((char*)ascii_str1, ascii_len1);
    printf("[sc_ascii_10] bytes: %u chars: %u expect: 10\n", (unsigned)ascii_len1, (unsigned)char_len);

    char_len = sc_utf8_chars ((char*)utf_str1, utf_len1);
    printf("[sc_utf8_10]  bytes: %u chars: %u expect: 10\n", (unsigned)utf_len1, (unsigned)char_len);

    }

    // bytes: 52
    // 56 = 6 * 8 + 4
    char ascii_str1_l52[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int  ascii_len1_l52   = strlen(ascii_str1_l52);
    char ascii_str2_l52[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int  ascii_len2_l52   = strlen(ascii_str2_l52);

    // bytes: 58
    // 58 = 7 * 8 + 2
    char utf_str1_l52[]   = "äbcdefghijklmnöpqrstÜvwxyzÄBCDEFGHIJKLMNÖPQRSTÜVWXYZ";
    int  utf_len1_l52     = strlen(utf_str1_l52);
    char utf_str2_l52[]   = "ÄBCDEFGHIJKLMNÖPQRSTÜVWXYZäbcdefghijklmnöpqrstÜvwxyz";
    int  utf_len2_l52     = strlen(utf_str2_l52);

    // bytes: 116 chars: 104 expect: 104
    // 116 = 14 * 8 + 4
    char utf_str1_l104[]   =
    "äbcdefghijklmnöpqrstÜvwxyzÄBCDEFGHIJKLMNÖPQRSTÜVWXYZäbcdefghijklmnöpqrstÜvwxyzÄBCDEFGHIJKLMNÖPQRSTÜVWXYZ";
    int  utf_len1_l104     = strlen(utf_str1_l104);
    char utf_str2_l104[]   =
    "ÄBCDEFGHIJKLMNÖPQRSTÜVWXYZäbcdefghijklmnöpqrstÜvwxyzÄBCDEFGHIJKLMNÖPQRSTÜVWXYZäbcdefghijklmnöpqrstÜvwxyz";
    int  utf_len2_l104     = strlen(utf_str2_l104);

    if (1) {
    char_len = jb_utf8_chars ((unsigned char*)ascii_str1_l52, ascii_len1_l52);
    printf("[jb_ascii_52] bytes: %u chars: %u expect: 52\n", (unsigned)ascii_len1_l52, (unsigned)char_len);

    char_len = jb_utf8_chars ((unsigned char*)utf_str1_l52, utf_len1_l52);
    printf("[jb_utf8_52]  bytes: %u chars: %u expect: 52\n", (unsigned)utf_len1_l52, (unsigned)char_len);

    char_len = jb_utf8_chars ((unsigned char*)utf_str1_l104, utf_len1_l104);
    printf("[jb_utf8_104] bytes: %u chars: %u expect: 104\n", (unsigned)utf_len1_l104, (unsigned)char_len);

    char_len = cp_utf8_chars ((unsigned char*)ascii_str1_l52, ascii_len1_l52);
    printf("[cp_ascii_52] bytes: %u chars: %u expect: 52\n", (unsigned)ascii_len1_l52, (unsigned)char_len);

    char_len = cp_utf8_chars ((unsigned char*)utf_str1_l52, utf_len1_l52);
    printf("[cp_utf8_52]  bytes: %u chars: %u expect: 52\n", (unsigned)utf_len1_l52, (unsigned)char_len);

    char_len = sc_utf8_chars ((char*)ascii_str1_l52, ascii_len1_l52);
    printf("[sc_ascii_52] bytes: %u chars: %u expect: 52\n", (unsigned)ascii_len1_l52, (unsigned)char_len);

    char_len = sc_utf8_chars ((char*)utf_str1_l52, utf_len1_l52);
    printf("[sc_utf8_52]  bytes: %u chars: %u expect: 52\n", (unsigned)utf_len1_l52, (unsigned)char_len);
    }

    /* ########## jb_ascii_l7 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)ascii_str1_l7, ascii_len1_l7);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)ascii_str2_l7, ascii_len2_l7);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;
    // b_rate  = rate * ascii_len2;

    printf("[jb_ascii_l7] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_ascii_l8 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)ascii_str1_l8, ascii_len1_l8);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)ascii_str2_l8, ascii_len2_l8);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;
    // b_rate  = rate * ascii_len2;

    printf("[jb_ascii_l8] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_ascii_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

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
    el_rate = rate * char_len2;
    // b_rate  = rate * ascii_len2;

    printf("[jb_ascii_10] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_utf_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)utf_str1, utf_len1);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)utf_str2, utf_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[jb_utf_10]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_ascii_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)ascii_str1_l52, ascii_len1_l52);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)ascii_str2_l52, ascii_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[jb_ascii_52] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_utf_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)utf_str1_l52, utf_len1_l52);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)utf_str2_l52, utf_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[jb_utf_52]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## jb_utf_104 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    megaiters = 2;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = jb_utf8_chars ((unsigned char*)utf_str1_l104, utf_len1_l104);
        }
        else {
          char_len2 = jb_utf8_chars ((unsigned char*)utf_str2_l104, utf_len2_l104);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[jb_utf_104]  iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));

    megaiters = 100;
}

    /* ########## cp_ascii_l7 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)ascii_str1_l7, ascii_len1_l7);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)ascii_str2_l7, ascii_len2_l7);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_ascii_l7] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_ascii_l8 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)ascii_str1_l8, ascii_len1_l8);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)ascii_str2_l8, ascii_len2_l8);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_ascii_l8] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_ascii_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)ascii_str1, ascii_len1);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)ascii_str2, ascii_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_ascii_10] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_utf_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)utf_str1, utf_len1);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)utf_str2, utf_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_utf_10]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_ascii_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)ascii_str1_l52, ascii_len1_l52);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)ascii_str2_l52, ascii_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_ascii_52] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_utf_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)utf_str1_l52, utf_len1_l52);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)utf_str2_l52, utf_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_utf_52]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## cp_utf_104 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = cp_utf8_chars ((unsigned char*)utf_str1_l104, utf_len1_l104);
        }
        else {
          char_len2 = cp_utf8_chars ((unsigned char*)utf_str2_l104, utf_len2_l104);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[cp_utf_104]  iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_ascii_l7 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)ascii_str1_l7, ascii_len1_l7);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)ascii_str2_l7, ascii_len2_l7);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_ascii_l7] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_ascii_l8 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)ascii_str1_l8, ascii_len1_l8);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)ascii_str2_l8, ascii_len2_l8);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_ascii_l8] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_ascii_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)ascii_str1, ascii_len1);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)ascii_str2, ascii_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_ascii_10] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_utf_10 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)utf_str1, utf_len1);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)utf_str2, utf_len2);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_utf_10]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_ascii_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)ascii_str1_l52, ascii_len1_l52);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)ascii_str2_l52, ascii_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_ascii_52] iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_utf_52 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)utf_str1_l52, utf_len1_l52);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)utf_str2_l52, utf_len2_l52);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_utf_52]   iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    /* ########## sc_utf_104 ########## */
if ( 1 && bench_on ) {
    tic = clock();

    // megaiters = 20;

    for (megacount = 0; megacount < megaiters; megacount++) {
      for (count = 0; count < iters; count++) {
        if (count % 2) {
          char_len1 = sc_utf8_chars ((char*)utf_str1_l104, utf_len1_l104);
        }
        else {
          char_len2 = sc_utf8_chars ((char*)utf_str2_l104, utf_len2_l104);
        }
      }
    }

    toc = clock();
    elapsed = (double)(toc - tic) / (double)CLOCKS_PER_SEC;
    total += elapsed;
    rate    = (double)megaiters / (double)elapsed;
    el_rate = rate * char_len2;

    printf("[sc_utf_104]  iters: %u M s: %f Mops/s: %.1f Mchr/s: %.1f %u\n",
        (unsigned)megaiters, elapsed, rate, el_rate, (unsigned)((char_len1+char_len2)/2));
}

    printf("Total: %f seconds\n", total);

    return 0;

}
