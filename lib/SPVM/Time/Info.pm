package SPVM::Time::Info;

1;

=head1 Name

SPVM::Time::Info - Time information

=head1 Usage
  
  use Time::Info;
  
  # Time information
  my $time_info = Time::Info->new;
  
  # Set and get second
  my $sec = $time_info->tm_sec;
  $time_info->set_tm_sec(12);
  
  # Set and get minutes
  my $min = $time_info->tm_min;
  $time_info->set_tm_min(34);
  
  # Set and get hour
  my $hour = $time_info->tm_hour;
  $time_info->set_tm_hour(12);

  # Set and get day of month
  my $mday = $time_info->tm_mday;
  $time_info->set_tm_mday(4);

  # Set and get month
  my $mon = $time_info->tm_mon;
  $time_info->set_tm_mon(3);

  # Set and get year
  my $year = $time_info->tm_year;
  $time_info->set_tm_year(1);

  # Set and get week day
  my $wday = $time_info->tm_wday;
  $time_info->set_tm_wday(12);

  # Set and get day of year
  my $yday = $time_info->tm_yday;
  $time_info->set_tm_yday(234);

  # Set and get the specified time occurs during Daylight Saving Time
  my $isdst = $time_info->tm_isdst;
  $time_info->set_tm_isdst(1);

=head1 Description

C<Time::Info> is the time information that date structure is C<struct tm> of C<C language>.

=head1 Class Methods

=head2 new

  static method new : Time::Info ()

Create a new L<Time::Info|SPVM::Time::Info> object.

  my $time_info = Time::Info->new;

=head1 Instance Methods

=head2 sec

  method sec : int ()

Get second. This is same as getting C<tm_sec> of C<struct tm>.

  my $sec = $time_info->tm_sec;

=head2 set_tm_sec

  method set_tm_sec : void ($sec : int)

Set second. This is same as setting C<tm_sec> of C<struct tm>.

  $time_info->set_tm_sec(12);

=head2 min
  
  method min : int ()

Get minutes. This is same as getting C<tm_min> of C<struct tm>.

  my $min = $time_info->tm_min;

=head2 set_tm_min

  method set_tm_min : void ($min : int)

Set minutes. This is same as setting C<tm_min> of C<struct tm>.

  $time_info->set_tm_min(34);

=head2 hour

  method hour : int ()

Get hour. This is same as getting C<tm_hour> of C<struct tm>.

  my $hour = $time_info->tm_hour;

=head2 set_tm_hour

  method set_tm_hour : void ($hour : int)

Set hour. This is same as setting C<tm_hour> of C<struct tm>.

  $time_info->set_tm_hour(12);

=head2 mday

  method mday : int ()

Get day of month. This is same as getting C<tm_mday> of C<struct tm>.

  my $mday = $time_info->tm_mday;

=head2 set_tm_mday

  method set_tm_mday : void ($mday : int)

Set day of month. This is same as setting C<tm_mday> of C<struct tm>.

  $time_info->set_tm_mday(4);

=head2 mon

  method mon : int ()

Get month. This is same as getting C<tm_mon> of C<struct tm>.

  my $mon = $time_info->tm_mon;

=head2 set_tm_mon

  method set_tm_mon : void ($mon : int)

Set month. This is same as setting C<tm_mon> of C<struct tm>.

  $time_info->set_tm_mon(3);

=head2 year

  method year : int ()

Get year. This is same as getting C<tm_year> of C<struct tm>.

  my $year = $time_info->tm_year;

=head2 set_tm_year

  method set_tm_year : void ($year : int)

Set year. This is same as setting C<tm_year> of C<struct tm>.

  $time_info->set_tm_year(1);

=head2 wday

  method wday : int ()

Get weekday. This is same as getting C<tm_wday> of C<struct tm>.

  my $wday = $time_info->tm_wday;

=head2 set_tm_wday

  method set_tm_wday : void ($wday : int)

Set weekday. This is same as setting C<tm_wday> of C<struct tm>.

  $time_info->set_tm_wday(12);

=head2 yday

  method yday : int ()

Get day of year. This is same as getting C<tm_yday> of C<struct tm>.

  my $yday = $time_info->tm_yday;

=head2 set_tm_yday

  method set_tm_wday : void ($wday : int)

Set day of year. This is same as setting C<tm_yday> of C<struct tm>.

  $time_info->set_tm_yday(234);

=head2 isdst

  method isdst : int ()

Get the flag whether the time is daylight saving time. This is same as getting C<tm_yday> of C<struct tm>.

  my $isdst = $time_info->tm_isdst;

=head2 set_tm_isdst

  method set_tm_isdst : void ($isdst : int)

Set the flag whether the time is daylight saving time.  This is same as getting C<tm_isdst> of C<struct tm>.

  $time_info->set_tm_isdst(1);
