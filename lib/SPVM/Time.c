#define _XOPEN_SOURCE

#include "spvm_native.h"

#include <time.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static const char* MFILE = "SPVM/Time.c";

int32_t SPNATIVE__SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  time_t time = (time_t)stack[0].lval;
  struct tm resultp;

#ifdef _WIN32
  localtime_s(&resultp, &time);
#else
  localtime_r(&time, &resultp);
#endif

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  time_t time = (time_t)stack[0].lval;
  struct tm resultp;

#ifdef _WIN32
  gmtime_s(&resultp, &time);
#else
  gmtime_r(&time, &resultp);
#endif

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
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
# define isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif

/*
 * We do not implement alternate representations. However, we always
 * check whether a given modifier is allowed for a certain conversion.
 */
#define ALT_E			0x01
#define ALT_O			0x02
#define LEGAL_ALT(x)		{ if (alt_format & ~(x)) return NULL; }

#define S_YEAR			(1 << 0)
#define S_MON			(1 << 1)
#define S_YDAY			(1 << 2)
#define S_MDAY			(1 << 3)
#define S_WDAY			(1 << 4)
#define S_HOUR			(1 << 5)

#define HAVE_MDAY(s)		(s & S_MDAY)
#define HAVE_MON(s)		(s & S_MON)
#define HAVE_WDAY(s)		(s & S_WDAY)
#define HAVE_YDAY(s)		(s & S_YDAY)
#define HAVE_YEAR(s)		(s & S_YEAR)
#define HAVE_HOUR(s)		(s & S_HOUR)

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

#define delim(p)	((p) == '\0' || isspace((unsigned char)(p)))

static char* SPVM_strptime(const char *buf, const char *fmt, struct tm *tm);

static const unsigned char* conv_num(const unsigned char *buf, int *dest, unsigned int llim, unsigned int ulim);

static const unsigned char *find_string(const unsigned char *bp, int *tgt, const char * const *n1, const char * const *n2, int c);

// http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/time/strptime.c?rev=HEAD
static char * SPVM_strptime(const char *buf, const char *fmt, struct tm *tm)
{
	unsigned char c;
	const unsigned char *bp, *ep, *zname;
	int alt_format, i, split_year = 0, neg = 0, state = 0,
	    day_offset = -1, week_offset = 0, offs, mandatory;
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


again:		switch (c = *fmt++) {
		case '%':	/* "%%" is converted to "%". */
literal:
			if (c != *bp++)
				return NULL;
			LEGAL_ALT(0);
			continue;

		/*
		 * "Alternative" modifiers. Just set the appropriate flag
		 * and start over again.
		 */
		case 'E':	/* "%E?" alternative conversion modifier. */
			LEGAL_ALT(0);
			alt_format |= ALT_E;
			goto again;

		case 'O':	/* "%O?" alternative conversion modifier. */
			LEGAL_ALT(0);
			alt_format |= ALT_O;
			goto again;

		case 'C':	/* The century number. */
			i = 20;
			bp = conv_num(bp, &i, 0, 99);

			i = i * 100 - TM_YEAR_BASE;
			if (split_year)
				i += tm->tm_year % 100;
			split_year = 1;
			tm->tm_year = i;
			LEGAL_ALT(ALT_E);
			state |= S_YEAR;
			continue;

		case 'd':	/* The day of month. */
		case 'e':
			bp = conv_num(bp, &tm->tm_mday, 1, 31);
			LEGAL_ALT(ALT_O);
			state |= S_MDAY;
			continue;

		case 'k':	/* The hour (24-hour clock representation). */
			LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'H':
			bp = conv_num(bp, &tm->tm_hour, 0, 23);
			LEGAL_ALT(ALT_O);
			state |= S_HOUR;
			continue;

		case 'l':	/* The hour (12-hour clock representation). */
			LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'I':
			bp = conv_num(bp, &tm->tm_hour, 1, 12);
			if (tm->tm_hour == 12)
				tm->tm_hour = 0;
			LEGAL_ALT(ALT_O);
			state |= S_HOUR;
			continue;

		case 'j':	/* The day of year. */
			i = 1;
			bp = conv_num(bp, &i, 1, 366);
			tm->tm_yday = i - 1;
			LEGAL_ALT(0);
			state |= S_YDAY;
			continue;

		case 'M':	/* The minute. */
			bp = conv_num(bp, &tm->tm_min, 0, 59);
			LEGAL_ALT(ALT_O);
			continue;

		case 'm':	/* The month. */
			i = 1;
			bp = conv_num(bp, &i, 1, 12);
			tm->tm_mon = i - 1;
			LEGAL_ALT(ALT_O);
			state |= S_MON;
			continue;

		case 'S':	/* The seconds. */
			bp = conv_num(bp, &tm->tm_sec, 0, 61);
			LEGAL_ALT(ALT_O);
			continue;

		case 'w':	/* The day of week, beginning on sunday. */
			bp = conv_num(bp, &tm->tm_wday, 0, 6);
			LEGAL_ALT(ALT_O);
			state |= S_WDAY;
			continue;

		case 'u':	/* The day of week, monday = 1. */
			bp = conv_num(bp, &i, 1, 7);
			tm->tm_wday = i % 7;
			LEGAL_ALT(ALT_O);
			state |= S_WDAY;
			continue;

		case 'g':	/* The year corresponding to the ISO week
				 * number but without the century.
				 */
			bp = conv_num(bp, &i, 0, 99);
			continue;

		case 'G':	/* The year corresponding to the ISO week
				 * number with century.
				 */
			do
				bp++;
			while (isdigit(*bp));
			continue;

		case 'V':	/* The ISO 8601:1988 week number as decimal */
			bp = conv_num(bp, &i, 0, 53);
			continue;

		case 'Y':	/* The year. */
			i = TM_YEAR_BASE;	/* just for data sanity... */
			bp = conv_num(bp, &i, 0, 9999);
			tm->tm_year = i - TM_YEAR_BASE;
			LEGAL_ALT(ALT_E);
			state |= S_YEAR;
			continue;

		case 'y':	/* The year within 100 years of the epoch. */
			/* LEGAL_ALT(ALT_E | ALT_O); */
			bp = conv_num(bp, &i, 0, 99);

			if (split_year)
				/* preserve century */
				i += (tm->tm_year / 100) * 100;
			else {
				split_year = 1;
				if (i <= 68)
					i = i + 2000 - TM_YEAR_BASE;
				else
					i = i + 1900 - TM_YEAR_BASE;
			}
			tm->tm_year = i;
			state |= S_YEAR;
			continue;

		case 'Z':
		case 'z':
			tzset();
			mandatory = c == 'z';
			/*
			 * We recognize all ISO 8601 formats:
			 * Z	= Zulu time/UTC
			 * [+-]hhmm
			 * [+-]hh:mm
			 * [+-]hh
			 * We recognize all RFC-822/RFC-2822 formats:
			 * UT|GMT
			 *          North American : UTC offsets
			 * E[DS]T = Eastern : -4 | -5
			 * C[DS]T = Central : -5 | -6
			 * M[DS]T = Mountain: -6 | -7
			 * P[DS]T = Pacific : -7 | -8
			 *          Nautical/Military
			 * [A-IL-M] = -1 ... -9 (J not used)
			 * [N-Y]  = +1 ... +12
			 * Note: J maybe used to denote non-nautical
			 *       local time
			 */
			if (mandatory)
				while (isspace(*bp))
					bp++;

			zname = bp;
			switch (*bp++) {
			case 'G':
				if (*bp++ != 'M')
					goto namedzone;
				/*FALLTHROUGH*/
			case 'U':
				if (*bp++ != 'T')
					goto namedzone;
				else if (!delim(*bp) && *bp++ != 'C')
					goto namedzone;
				/*FALLTHROUGH*/
			case 'Z':
				if (!delim(*bp))
					goto namedzone;
				tm->tm_isdst = 0;
#ifdef TM_GMTOFF
				tm->TM_GMTOFF = 0;
#endif
#ifdef TM_ZONE
				tm->TM_ZONE = utc;
#endif
				continue;
			case '+':
				neg = 0;
				break;
			case '-':
				neg = 1;
				break;
			default:
namedzone:
				bp = zname;

				/* Nautical / Military style */
				if (delim(bp[1]) &&
				    ((*bp >= 'A' && *bp <= 'I') ||
				     (*bp >= 'L' && *bp <= 'Y'))) {
#ifdef TM_GMTOFF
					/* Argh! No 'J'! */
					if (*bp >= 'A' && *bp <= 'I')
						tm->TM_GMTOFF =
						    (int)*bp - ('A' - 1);
					else if (*bp >= 'L' && *bp <= 'M')
						tm->TM_GMTOFF = (int)*bp - 'A';
					else if (*bp >= 'N' && *bp <= 'Y')
						tm->TM_GMTOFF = 'M' - (int)*bp;
					tm->TM_GMTOFF *= SECSPERHOUR;
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = NULL; /* XXX */
#endif
					bp++;
					continue;
				}
				/* 'J' is local time */
				if (delim(bp[1]) && *bp == 'J') {
#ifdef TM_GMTOFF
					tm->TM_GMTOFF = -timezone;
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = NULL; /* XXX */
#endif
					bp++;
					continue;
				}

				/*
				 * From our 3 letter hard-coded table
				 * XXX: Can be removed, handled by tzload()
				 */
				if (delim(bp[0]) || delim(bp[1]) ||
				    delim(bp[2]) || !delim(bp[3]))
					goto loadzone;
				ep = find_string(bp, &i, nast, NULL, 4);
				if (ep != NULL) {
#ifdef TM_GMTOFF
					tm->TM_GMTOFF = (-5 - i) * SECSPERHOUR;
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = nast[i];
#endif
					bp = ep;
					continue;
				}
				ep = find_string(bp, &i, nadt, NULL, 4);
				if (ep != NULL) {
					tm->tm_isdst = 1;
#ifdef TM_GMTOFF
					tm->TM_GMTOFF = (-4 - i) * SECSPERHOUR;
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = nadt[i];
#endif
					bp = ep;
					continue;
				}
				/*
				 * Our current timezone
				 */
				ep = find_string(bp, &i,
					       	 (const char * const *)tzname,
					       	  NULL, 2);
				if (ep != NULL) {
					tm->tm_isdst = i;
#ifdef TM_GMTOFF
					tm->TM_GMTOFF = -timezone;
#endif
#ifdef TM_ZONE
					tm->TM_ZONE = tzname[i];
#endif
					bp = ep;
					continue;
				}
loadzone:
				goto out;
			}
			offs = 0;
			for (i = 0; i < 4; ) {
				if (isdigit(*bp)) {
					offs = offs * 10 + (*bp++ - '0');
					i++;
					continue;
				}
				if (i == 2 && *bp == ':') {
					bp++;
					continue;
				}
				break;
			}
			if (isdigit(*bp))
				goto out;
			switch (i) {
			case 2:
				offs *= SECSPERHOUR;
				break;
			case 4:
				i = offs % 100;
				offs /= 100;
				if (i >= SECSPERMIN)
					goto out;
				/* Convert minutes into decimal */
				offs = offs * SECSPERHOUR + i * SECSPERMIN;
				break;
			default:
			out:
				if (mandatory)
					return NULL;
				bp = zname;
				continue;
			}
			/* ISO 8601 & RFC 3339 limit to 23:59 max */
			if (offs >= (HOURSPERDAY * SECSPERHOUR))
				goto out;
			if (neg)
				offs = -offs;
			tm->tm_isdst = 0;	/* XXX */
#ifdef TM_GMTOFF
			tm->TM_GMTOFF = offs;
#endif
#ifdef TM_ZONE
			tm->TM_ZONE = NULL;	/* XXX */
#endif
			continue;

		/*
		 * Miscellaneous conversions.
		 */
		case 'n':	/* Any kind of white-space. */
		case 't':
			while (isspace(*bp))
				bp++;
			LEGAL_ALT(0);
			continue;


		default:	/* Unknown/unsupported conversion. */
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
  
  void* obj_str = stack[0].oval;
  if (!obj_str) { SPVM_DIE("String must be defined", MFILE, __LINE__); }
  const char* str = (const char*)env->belems(env, obj_str);
  
  void* obj_format = stack[1].oval;
  if (!obj_format) { SPVM_DIE("Format must be defined", MFILE, __LINE__); }
  const char* format = (const char*)env->belems(env, obj_format);

  struct tm resultp = {0};
  
  const char* end_ptr = SPVM_strptime(str, format, &resultp);
  
  if (end_ptr && *end_ptr != '\0') {
    SPVM_DIE("Format parsing failed \"%s\"", end_ptr, MFILE, __LINE__);
  }
  else if (!end_ptr) {
    SPVM_DIE("Format parsing failed", MFILE, __LINE__);
  }

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__strftime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_format = stack[0].oval;
  if (!obj_format) { SPVM_DIE("Format must be defined", MFILE, __LINE__); }
  const char* format = (const char*)env->belems(env, obj_format);
  
  void* obj_time_info = stack[1].oval;
  if (!obj_time_info) { SPVM_DIE("SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_IFIELD(env, resultp.tm_sec, obj_time_info, "SPVM::Time::Info", "sec", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_min, obj_time_info, "SPVM::Time::Info", "min", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_hour, obj_time_info, "SPVM::Time::Info", "hour", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mday, obj_time_info, "SPVM::Time::Info", "mday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mon, obj_time_info, "SPVM::Time::Info", "mon", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_year, obj_time_info, "SPVM::Time::Info", "year", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_wday, obj_time_info, "SPVM::Time::Info", "wday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_yday, obj_time_info, "SPVM::Time::Info", "yday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_isdst, obj_time_info, "SPVM::Time::Info", "isdst", MFILE, __LINE__);
  
  char str[256] = {0};
  int32_t count = strftime(str, 256, format, &resultp);
  
  if (count == 0) {
    SPVM_DIE("strftime fail", MFILE, __LINE__);
  }

  void* obj_str = env->new_str_len(env, str, strlen(str));
  
  stack[0].oval = obj_str;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__mktime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { SPVM_DIE("SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_IFIELD(env, resultp.tm_sec, obj_time_info, "SPVM::Time::Info", "sec", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_min, obj_time_info, "SPVM::Time::Info", "min", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_hour, obj_time_info, "SPVM::Time::Info", "hour", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mday, obj_time_info, "SPVM::Time::Info", "mday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mon, obj_time_info, "SPVM::Time::Info", "mon", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_year, obj_time_info, "SPVM::Time::Info", "year", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_wday, obj_time_info, "SPVM::Time::Info", "wday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_yday, obj_time_info, "SPVM::Time::Info", "yday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_isdst, obj_time_info, "SPVM::Time::Info", "isdst", MFILE, __LINE__);
  
  int64_t ltime = (int64_t)mktime(&resultp);
  
  stack[0].lval = ltime;
  
  return SPVM_SUCCESS;
}
