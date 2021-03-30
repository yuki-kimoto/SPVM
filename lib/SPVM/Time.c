#include "spvm_native.h"

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

static const char* MFILE = "SPVM/Time.c";

int32_t SPNATIVE__SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  time_t time = (time_t)stack[0].lval;
  struct tm* resultp = localtime(&time);

  void* obj_time_info = env->new_object_by_name(env, "SPVM::Time::Info", &e, MFILE, __LINE__);
  if (e) { return e; }

  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "sec", resultp->tm_sec, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "min", resultp->tm_min, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "hour", resultp->tm_hour, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mday", resultp->tm_mday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mon", resultp->tm_mon, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "year", resultp->tm_year, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "wday", resultp->tm_wday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "yday", resultp->tm_yday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp->tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Time__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;

  time_t time = (time_t)stack[0].lval;
  struct tm* resultp = gmtime(&time);

  void* obj_time_info = env->new_object_by_name(env, "SPVM::Time::Info", &e, MFILE, __LINE__);
  if (e) { return e; }

  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "sec", resultp->tm_sec, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "min", resultp->tm_min, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "hour", resultp->tm_hour, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mday", resultp->tm_mday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mon", resultp->tm_mon, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "year", resultp->tm_year, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "wday", resultp->tm_wday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "yday", resultp->tm_yday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp->tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

// https://code.woboq.org/userspace/glibc/timezone/private.h.html
#define SECSPERMIN        60
#define MINSPERHOUR        60
#define HOURSPERDAY        24
#define DAYSPERWEEK        7
#define DAYSPERNYEAR        365
#define DAYSPERLYEAR        366
#define SECSPERHOUR        (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY        ((int_fast32_t) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR        12
#define TM_SUNDAY        0
#define TM_MONDAY        1
#define TM_TUESDAY        2
#define TM_WEDNESDAY        3
#define TM_THURSDAY        4
#define TM_FRIDAY        5
#define TM_SATURDAY        6
#define TM_JANUARY        0
#define TM_FEBRUARY        1
#define TM_MARCH        2
#define TM_APRIL        3
#define TM_MAY                4
#define TM_JUNE                5
#define TM_JULY                6
#define TM_AUGUST        7
#define TM_SEPTEMBER        8
#define TM_OCTOBER        9
#define TM_NOVEMBER        10
#define TM_DECEMBER        11
#define TM_YEAR_BASE        1900
#define EPOCH_YEAR        1970
#define EPOCH_WDAY        TM_THURSDAY
#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))
/*
** Since everything in isleap is modulo 400 (or a factor of 400), we know that
**        isleap(y) == isleap(y % 400)
** and so
**        isleap(a + b) == isleap((a + b) % 400)
** or
**        isleap(a + b) == isleap(a % 400 + b % 400)
** This is true even if % means modulo rather than Fortran remainder
** (which is allowed by C89 but not by C99 or later).
** We use this to avoid addition overflow problems.
*/
#define isleap_sum(a, b)        isleap((a) % 400 + (b) % 400)



#ifndef isleap
/* Nonzero if YEAR is a leap year (every 4 years,
   except every 100th isn't, and every 400th is).  */
# define isleap(year) \
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif

/*
 * We do not implement alternate representations. However, we always
 * check whether a given modifier is allowed for a certain conversion.
 */
#define ALT_E     0x01
#define ALT_O     0x02
#define LEGAL_ALT(x)    { if (alt_format & ~(x)) return NULL; }

#define S_YEAR      (1 << 0)
#define S_MON     (1 << 1)
#define S_YDAY      (1 << 2)
#define S_MDAY      (1 << 3)
#define S_WDAY      (1 << 4)
#define S_HOUR      (1 << 5)

#define HAVE_MDAY(s)    (s & S_MDAY)
#define HAVE_MON(s)   (s & S_MON)
#define HAVE_WDAY(s)    (s & S_WDAY)
#define HAVE_YDAY(s)    (s & S_YDAY)
#define HAVE_YEAR(s)    (s & S_YEAR)
#define HAVE_HOUR(s)    (s & S_HOUR)

static char utc[] = { "UTC" };
/* RFC-822/RFC-2822 */
static const char * const nast[5] = {
       "EST",    "CST",    "MST",    "PST",    "\0\0\0"
};
static const char * const nadt[5] = {
       "EDT",    "CDT",    "MDT",    "PDT",    "\0\0\0"
};

/*
 * Table to determine the ordinal date for the start of a month.
 * Ref: http://en.wikipedia.org/wiki/ISO_week_date
 */
static const int start_of_month[2][13] = {
  /* non-leap year */
  { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
  /* leap year */
  { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

/*
 * Calculate the week day of the first day of a year. Valid for
 * the Gregorian calendar, which began Sept 14, 1752 in the UK
 * and its colonies. Ref:
 * http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
 */

static int
first_wday_of(int yr)
{
  return ((2 * (3 - (yr / 100) % 4)) + (yr % 100) + ((yr % 100) /  4) +
      (isleap(yr) ? 6 : 0) + 1) % 7;
}

#define delim(p)  ((p) == '\0' || isspace((unsigned char)(p)))

static char* SPVM_strptime(const char *buf, const char *fmt, struct tm *tm);

static const unsigned char* conv_num(const unsigned char *buf, int *dest, unsigned int llim, unsigned int ulim);

static const unsigned char *find_string(const unsigned char *bp, int *tgt, const char * const *n1, const char * const *n2, int c);

// http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/time/strptime.c?rev=HEAD
static char * SPVM_strptime(const char *buf, const char *fmt, struct tm *tm)
{
  unsigned char c;
  const unsigned char *bp, *ep, *zname;
  int alt_format, i, split_year = 0, neg = 0, state = 0, day_offset = -1, week_offset = 0, offs, mandatory;
  const char *new_fmt;

  bp = (const unsigned char *)buf;

  while (bp != NULL && (c = *fmt++) != '\0') {
    /* Clear `alternate' modifier prior to new conversion. */
    alt_format = 0;
    i = 0;

    /* Eat up white-space. */
    if (isspace(c)) {
      while (isspace(*bp))
        bp++;
      continue;
    }

    if (c != '%')
      goto literal;


again:    switch (c = *fmt++) {
    case '%': /* "%%" is converted to "%". */
literal:
      if (c != *bp++)
        return NULL;
      LEGAL_ALT(0);
      continue;

    case 'd': /* The day of month. */
      bp = conv_num(bp, &tm->tm_mday, 1, 31);
      LEGAL_ALT(ALT_O);
      state |= S_MDAY;
      continue;

    case 'H':
      bp = conv_num(bp, &tm->tm_hour, 0, 23);
      LEGAL_ALT(ALT_O);
      state |= S_HOUR;
      continue;
    case 'M': /* The minute. */
      bp = conv_num(bp, &tm->tm_min, 0, 59);
      LEGAL_ALT(ALT_O);
      continue;

    case 'm': /* The month. */
      i = 1;
      bp = conv_num(bp, &i, 1, 12);
      tm->tm_mon = i - 1;
      LEGAL_ALT(ALT_O);
      state |= S_MON;
      continue;

    case 'S': /* The seconds. */
      bp = conv_num(bp, &tm->tm_sec, 0, 61);
      LEGAL_ALT(ALT_O);
      continue;

    case 'Y': /* The year. */
      i = TM_YEAR_BASE; /* just for data sanity... */
      bp = conv_num(bp, &i, 0, 9999);
      tm->tm_year = i - TM_YEAR_BASE;
      LEGAL_ALT(ALT_E);
      state |= S_YEAR;
      continue;
    default:  /* Unknown/unsupported conversion. */
      return NULL;
    }
  }

  if (!HAVE_YDAY(state) && HAVE_YEAR(state)) {
    if (HAVE_MON(state) && HAVE_MDAY(state)) {
      /* calculate day of year (ordinal date) */
      tm->tm_yday =  start_of_month[isleap_sum(tm->tm_year,
          TM_YEAR_BASE)][tm->tm_mon] + (tm->tm_mday - 1);
      state |= S_YDAY;
    } else if (day_offset != -1) {
      /*
       * Set the date to the first Sunday (or Monday)
       * of the specified week of the year.
       */
      if (!HAVE_WDAY(state)) {
        tm->tm_wday = day_offset;
        state |= S_WDAY;
      }
      tm->tm_yday = (7 -
          first_wday_of(tm->tm_year + TM_YEAR_BASE) +
          day_offset) % 7 + (week_offset - 1) * 7 +
          tm->tm_wday  - day_offset;
      state |= S_YDAY;
    }
  }

  if (HAVE_YDAY(state) && HAVE_YEAR(state)) {
    int isleap;

    if (!HAVE_MON(state)) {
      /* calculate month of day of year */
      i = 0;
      isleap = isleap_sum(tm->tm_year, TM_YEAR_BASE);
      while (tm->tm_yday >= start_of_month[isleap][i])
        i++;
      if (i > 12) {
        i = 1;
        tm->tm_yday -= start_of_month[isleap][12];
        tm->tm_year++;
      }
      tm->tm_mon = i - 1;
      state |= S_MON;
    }

    if (!HAVE_MDAY(state)) {
      /* calculate day of month */
      isleap = isleap_sum(tm->tm_year, TM_YEAR_BASE);
      tm->tm_mday = tm->tm_yday -
          start_of_month[isleap][tm->tm_mon] + 1;
      state |= S_MDAY;
    }

    if (!HAVE_WDAY(state)) {
      /* calculate day of week */
      i = 0;
      week_offset = first_wday_of(tm->tm_year);
      while (i++ <= tm->tm_yday) {
        if (week_offset++ >= 6)
          week_offset = 0;
      }
      tm->tm_wday = week_offset;
      state |= S_WDAY;
    }
  }

  return (char *)bp;
}

static const unsigned char *
conv_num(const unsigned char *buf, int *dest, unsigned int llim, unsigned int ulim)
{
  unsigned int result = 0;
  unsigned char ch;

  /* The limit also determines the number of valid digits. */
  unsigned int rulim = ulim;

  ch = *buf;
  if (ch < '0' || ch > '9')
    return NULL;

  do {
    result *= 10;
    result += ch - '0';
    rulim /= 10;
    ch = *++buf;
  } while ((result * 10 <= ulim) && rulim && ch >= '0' && ch <= '9');

  if (result < llim || result > ulim)
    return NULL;

  *dest = result;
  return buf;
}

static const unsigned char *find_string(const unsigned char *bp, int *tgt, const char * const *n1, const char * const *n2, int c)
{
  int i;
  size_t len;

  /* check full name - then abbreviated ones */
  for (; n1 != NULL; n1 = n2, n2 = NULL) {
    for (i = 0; i < c; i++, n1++) {
      len = strlen(*n1);
      if (strncmp(*n1, (const char *)bp, len) == 0) {
        *tgt = i;
        return bp + len;
      }
    }
  }

  /* Nothing matched */
  return NULL;
}
int32_t SPNATIVE__SPVM__Time__strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  void* obj_str = stack[0].oval;
  if (!obj_str) { return env->die(env, "String must be defined", MFILE, __LINE__); }
  const char* str = env->get_chars(env, obj_str);
  
  void* obj_format = stack[1].oval;
  if (!obj_format) { return env->die(env, "Format must be defined", MFILE, __LINE__); }
  const char* format = env->get_chars(env, obj_format);

  struct tm resultp = {0};
  
  const char* end_ptr = SPVM_strptime(str, format, &resultp);
  
  if (end_ptr && *end_ptr != '\0') {
    return env->die(env, "Format parsing failed \"%s\"", end_ptr, MFILE, __LINE__);
  }
  else if (!end_ptr) {
    return env->die(env, "Format parsing failed", MFILE, __LINE__);
  }

  void* obj_time_info = env->new_object_by_name(env, "SPVM::Time::Info", &e, MFILE, __LINE__);
  if (e) { return e; }

  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Time__strftime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_format = stack[0].oval;
  if (!obj_format) { return env->die(env, "Format must be defined", MFILE, __LINE__); }
  const char* format = env->get_chars(env, obj_format);
  
  void* obj_time_info = stack[1].oval;
  if (!obj_time_info) { return env->die(env, "SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "sec", &resultp.tm_sec, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "min", &resultp.tm_min, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "hour", &resultp.tm_hour, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mday", &resultp.tm_mday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mon", &resultp.tm_mon, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "year", &resultp.tm_year, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "wday", &resultp.tm_wday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "yday", &resultp.tm_yday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "isdst", &resultp.tm_isdst, MFILE, __LINE__);
  
  char str[256] = {0};
  int32_t count = strftime(str, 256, format, &resultp);
  
  if (count == 0) {
    return env->die(env, "strftime fail", MFILE, __LINE__);
  }

  void* obj_str = env->new_string(env, str, strlen(str));
  
  stack[0].oval = obj_str;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Time__timelocal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { return env->die(env, "SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "sec", &resultp.tm_sec, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "min", &resultp.tm_min, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "hour", &resultp.tm_hour, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mday", &resultp.tm_mday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "mon", &resultp.tm_mon, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "year", &resultp.tm_year, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "wday", &resultp.tm_wday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "yday", &resultp.tm_yday, MFILE, __LINE__);
  SPVM_GET_FIELD_INT(env, obj_time_info, "SPVM::Time::Info", "isdst", &resultp.tm_isdst, MFILE, __LINE__);
  
  int64_t ltime = (int64_t)mktime(&resultp);
  
  stack[0].lval = ltime;
  
  return 0;
}
