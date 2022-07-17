#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "src/utf8_charlen.h"
#include "src/utf8_charlen.c"

#define _UTF8_CHARLEN_FOR_PERL

MODULE = Wollmers::Utf8::XS  PACKAGE = Wollmers::Utf8::XS

PROTOTYPES: DISABLE

int
jb_chars(s1)
    SV *    s1
    CODE:
{
    STRLEN m;
    // SvPVbyte
    unsigned char *a = (unsigned char*)SvPV (s1, m);

    RETVAL = jb_utf8_chars (a, m);
}
    OUTPUT:
        RETVAL

int
cp_chars(s1)
    SV *    s1
    CODE:
{
    STRLEN m;
    // SvPVbyte
    unsigned char *a = (unsigned char*)SvPV (s1, m);

    RETVAL = cp_utf8_chars (a, m);
}
    OUTPUT:
        RETVAL

int
sc_chars(s1)
    SV *    s1
    CODE:
{
    STRLEN m;
    // SvPVbyte
    char *a = (char*)SvPV (s1, m);

    RETVAL = sc_utf8_chars (a, m);
}
    OUTPUT:
        RETVAL

