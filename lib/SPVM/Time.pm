package SPVM::Time;

use SPVM 'SPVM::Time';

1;

=head1 NAME

SPVM::Time - Time manipulation

=head1 SYNOPSYS
  
  use SPVM::Time;
  
  # Epoch time
  my $time = SPVM::Time->time;
  
  # Local time information
  my $time_info = SPVM::Time->localtime(SPVM::Time->time);
  
  # GM time information
  my $time_info = SPVM::Time->gmtime(SPVM::Time->time);
  
  # Convert L<SPVM::Time::Info> which is local time zone to calender time as same as time method format.
  my $time = SPVM::Time->timelocal($time_info);
  
  # Convert L<SPVM::Time::Info> which is the standard Greenwich time zone to calender time as same as time method format.
  my $time = SPVM::Time->timegm($time_info);
  
  # Parse string and convert it to a L<SPVM::Time::Info> object.
  my $time_info = SPVM::Time->strptime("2019-12-15 10:24:55", "%Y-%m-%d %H:%M:%S")
  
  # Convert SPVM::Time::Info to string by specific format.
  my $datetime_str = SPVM::Time->strftime("%Y-%m-%d %H:%M:%S", $time_info)

=head1 DESCRIPTION

Time manipulation.

=head1 CLASS METHODS

=head2 time

  sub time : long ();

Returns the number of non-leap seconds since whatever time the system considers
to be the epoch, suitable for feeding to "gmtime" and "localtime".
On most systems the epoch is 00:00:00 UTC, January 1, 1970;

Example:

  my $time = SPVM::Time->time;

=head2 localtime

  sub localtime : SPVM::Time::Info ($time : long)

Converts a time as returned by the time method to a L<SPVM::Time::Info> object
with the time analyzed for the local time zone.

Example:

  my $time_info = SPVM::Time->localtime(SPVM::Time->time);

"mday" is the day of the month and "mon" the month in the range
0..11, with 0 indicating January and 11 indicating December.

"year" contains the number of years since 1900. To get a 4-digit
year write:

    my $year = $time_info->year + 1900;

"wday" is the day of the week, with 0 indicating Sunday and 3
indicating Wednesday. "yday" is the day of the year, in the range
0..364 (or 0..365 in leap years.)

"isdst" is true if the specified time occurs during Daylight Saving
Time, false otherwise.

If you get current time information, pass return value of "time" method.

  my $time_info = SPVM::Time->localtime(SPVM::Time->time)

See also the "timelocal" method. (for converting seconds,
minutes, hours, and such back to the integer value returned by
time()).

=head2 gmtime

  sub gmtime : SPVM::Time::Info ($time : long)

Works just like "localtime" but the returned values are localized
for the standard Greenwich time zone.

See also the "timegm" method. (for converting seconds,
minutes, hours, and such back to the integer value returned by
time()).

=head2 timelocal

  sub timelocal : long ($time_info : SPVM::Time::Info)

timelocal method convert L<SPVM::Time::Info> which is local time zone to calender time as same as time method format.

wday and yday is ignored.

  my $time = SPVM::Time->timelocal($time_info);

=head2 timegm

  sub timegm : long ($time_info : SPVM::Time::Info)

timegm method convert L<SPVM::Time::Info> which is the standard Greenwich time zone to calender time as same as time method format.

wday and yday is ignored.

  my $time = SPVM::Time->timegm($time_info);

=head2 strftime

  sub strftime : string ($format : string, $time_info : SPVM::Time::Info)

Convert SPVM::Time::Info to string by specific format.

  my $datetime_str = SPVM::Time->strftime("%Y-%m-%d %H:%M:%S", $time_info)

Supported Format:

  %Y is replaced by the year with century as a decimal number.
  %m is replaced by the month as a decimal number (01-12).
  %d is replaced by the day of the month as a decimal number (01-31).
  %H is replaced by the hour (24-hour clock) as a decimal number (00-23).
  %M is replaced by the minute as a decimal number (00-59).
  %S is replaced by the second as a decimal number (00-60).

=head2 strptime

  sub strptime : SPVM::Time::Info ($str : string, $format : string)

Parse string and convert it to a L<SPVM::Time::Info> object.

  my $time_info = SPVM::Time->strptime("2019-12-15 10:24:55", "%Y-%m-%d %H:%M:%S")

See strftime method about supported format.
