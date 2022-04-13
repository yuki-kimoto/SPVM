package SPVM::Time;

1;

=head1 NAME

SPVM::Time - Time manipulation

=head1 SYNOPSYS
  
  use Time;
  
  # Get Current Epoch time
  my $time = Time->time;
  
  # Get Local time information
  my $time_info = Time->localtime(Time->time);
  
  # Get GMT time information
  my $time_info = Time->gmtime(Time->time);
  
  # Convert Time::Info to which is local time zone to calender time as same as time method format.
  my $time = Time->timelocal($time_info);
  
  # Convert Time::Info which is the standard Greenwich time zone to calender time as same as time method format.
  my $time = Time->timegm($time_info);

=head1 DESCRIPTION

Time manipulation.

=head1 CLASS METHODS

=head2 time

  static method time : long ();

Returns the number of non-leap seconds since whatever time the system considers
to be the epoch, suitable for feeding to "gmtime" and "localtime".
On most systems the epoch is 00:00:00 UTC, January 1, 1970;

Example:

  my $time = Time->time;

=head2 localtime

  static method localtime : Time::Info ($time : long)

Converts a time as returned by the time method to a L<Time::Info|SPVM::Time::Info> object
with the time analyzed for the local time zone.

Example:

  my $time_info = Time->localtime(Time->time);

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

  my $time_info = Time->localtime(Time->time)

See also the "timelocal" method. (for converting seconds,
minutes, hours, and such back to the integer value returned by
time()).

=head2 gmtime

  static method gmtime : Time::Info ($time : long)

Works just like "localtime" but the returned values are localized
for the standard Greenwich time zone.

See also the "timegm" method. (for converting seconds,
minutes, hours, and such back to the integer value returned by
time()).

=head2 timelocal

  static method timelocal : long ($time_info : Time::Info)

timelocal method convert L<Time::Info|SPVM::Time::Info> which is local time zone to calender time as same as time method format.

wday and yday is ignored.

  my $time = Time->timelocal($time_info);

=head2 timegm

  static method timegm : long ($time_info : Time::Info)

timegm method convert L<Time::Info|SPVM::Time::Info> which is the standard Greenwich time zone to calender time as same as time method format.

wday and yday is ignored.

  my $time = Time->timegm($time_info);

