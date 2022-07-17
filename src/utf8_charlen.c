/*
// https://www.cprogramming.com/tutorial/unicode.html

  Basic UTF-8 manipulation routines
  by Jeff Bezanson
  placed in the public domain Fall 2005

  modified for counting by Helmut Wollmersdorfer 2022
  - assumes valid UTF-8
  - uses lookup table

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>

#include "utf8_charlen.h"

static const char allBytesForUTF8[256] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4,5,5,5,5,6,6,6,6
};


static size_t jb_utf8_chars (const uint8_t * buf, size_t len) {

    // const uint8_t *data = uint8_t * buf;
    size_t offset  = 0; // offset in buf
    size_t counter = 0;

    while (offset < len) {
        uint8_t leading_byte = buf[offset];
        // printf("[jb_ascii_10] leading_byte: %u len: %u \n", leading_byte, allBytesForUTF8[leading_byte]);
        offset  += allBytesForUTF8[leading_byte];
        counter++;
    }

    return counter;
}


/*
http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
Colin Percival

modified by Helmut Wollmersdorfer 2022
*/


#define ONEMASK ((size_t)(-1) / 0xFF)

static size_t
cp_utf8_chars (const uint8_t * buf, size_t len) {

    size_t offset = 0; // offset in buf
	size_t continuations = 0;

    // n1 = floor(len / width)
    // ops = 2+2+6+5+1 = 16
    // O(n1 * 16)
    while (offset + sizeof(size_t) < len) { // 2
        // try the next block of size_t bytes
        size_t v;
        memcpy(&v, buf + offset, sizeof(size_t)); // 2
		v = ((v & (ONEMASK * 0x80)) >> 7) & ((~v) >> 6); // 6
	    continuations += (v * ONEMASK) >> ((sizeof(size_t) - 1) * 8); // 5
	    offset        += sizeof(size_t); // 1
    }

	// Take care of any left-over bytes.
	// n2 = (len % width)
	// ops = 1+1+4+1 = 7
	// O(n2 * 7)
	while (offset < len) { // 1
		uint8_t byte = buf[offset]; // 1

		// Is this byte NOT the first byte of a character?

		// continuations += (byte >> 7) & ((byte) >> 6); // 4, bitops variant
		if((signed)byte <= -65) { continuations++; } // 2, comparison variant
		offset++; // 1
	}

	return (len - continuations);
}


/*
https://github.com/simdutf/simdutf/blob/master/src/scalar/utf8.h

original utf32_length_from_utf8()
*/

/*
// variant counting code points
static size_t
sc_utf8_chars (const char * buf, size_t len) {
    size_t counter = 0;

    // O(n * 4)
    for (size_t i = 0; i < len; i++) { // 2
        // -65 is 0b10111111, anything larger in two-complement's should start a new code point.
        if(buf[i] > -65) { counter++; } // 2
    }
    return counter;
}
*/

// variant counting continuations
static size_t
sc_utf8_chars (const char * buf, size_t len) {
    // size_t counter = 0;
    size_t continuations = 0;

    // O(n * 4)
    for (size_t i = 0; i < len; i++) { // 2
        // -65 is 0b10111111, anything larger in two-complement's should start a new code point.
        if(buf[i] <= -65) { continuations++; } // 2
    }
    return (len - continuations);
}

/*
https://github.com/simdutf/simdutf/blob/master/src/scalar/utf8_to_utf32/valid_utf8_to_utf32.h

inline size_t convert_valid(const uint8_t * buf, size_t len)

modified for counting
*/

/*
static size_t
sv_utf8_chars (const uint8_t * buf, size_t len) {

    const uint8_t *data = uint8_t * buf;
    size_t offset = 0; // offset in buf
    size_t counter= 0;
    while (offset < len) {
        // try the next block of 8 ASCII bytes
        if (offset + 8 <= len) { // if it is safe to read 8 more bytes, check that they are ascii
            uint64_t v;
            memcpy(&v, data + offset, sizeof(uint64_t));
            if ((v & 0x8080808080808080) == 0) {
                offset += 8;
                counter += 8;
                continue;
            }
        }
        uint8_t leading_byte = data[offset]; // leading byte
        if (leading_byte < 0b10000000) {
            // one ASCII byte
            offset++;
            counter++;
        } else if ((leading_byte & 0b11100000) == 0b11000000) {
            // two-byte UTF-8
            if (offset + 1 >= len) { break; } // minimal bound checking
            offset += 2;
            counter++;
        } else if ((leading_byte & 0b11110000) == 0b11100000) {
            // three-byte UTF-8
            if (offset + 2 >= len) { break; } // minimal bound checking
            offset += 3;
        } else if ((leading_byte & 0b11111000) == 0b11110000) { // 0b11110000
            // 4-byte UTF-8 word.
            if(offset + 3 >= len) { break; } // minimal bound checking
            offset += 4;
        } else {
            // we may have a continuation but we do not do error checking
            return 0;
        }
    }
    return counter;
}
*/
