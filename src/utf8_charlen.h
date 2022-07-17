#include <stdarg.h>

static size_t jb_utf8_chars (const uint8_t * buf, size_t len);


static size_t cp_utf8_chars (const uint8_t * buf, size_t len);

static size_t sc_utf8_chars (const char * buf, size_t len);
/*
static size_t sv_utf8_chars (const uint8_t * buf, size_t len);
*/
