package SPVM::Time::Info;

1;

=head1 NAME

SPVM::Time::Info - Time::Info in SPVM | Time information

=head1 SYNOPSYS
  
  use Time::Info;
  
  # Time information
  my $time_info = Time::Info->new;
  
  # Set and get second
  my $sec = $time_info->sec;
  $time_info->set_sec(12);
  
  # Set and get minutes
  my $min = $time_info->min;
  $time_info->set_min(34);
  
  # Set and get hour
  my $hour = $time_info->hour;
  $time_info->set_hour(12);

  # Set and get day of month
  my $mday = $time_info->mday;
  $time_info->set_mday(4);

  # Set and get month
  my $mon = $time_info->mon;
  $time_info->set_mon(3);

  # Set and get year
  my $year = $time_info->year;
  $time_info->set_year(1);

  # Set and get week day
  my $wday = $time_info->wday;
  $time_info->set_wday(12);

  # Set and get day of year
  my $yday = $time_info->yday;
  $time_info->set_yday(234);

  # Set and get the specified time occurs during Daylight Saving Time
  my $isdst = $time_info->isdst;
  $time_info->set_isdst(1);

=head1 DESCRIPTION

Time information

=head1 STATIC METHODS

=head2 new

  sub new : Time::Info ()

Create a new L<Time::Info|SPVM::Time::Info> object.

  my $time_info = Time::Info->new;

=head1 INSTANCE METHODS

=head2 sec

  sub sec : int ($self : self)

Get second.

  my $sec = $time_info->sec;

=head2 set_sec

  sub set_sec : void ($self : self, $sec : int)

Set second.

  $time_info->set_sec(12);

=head2 min
  
  sub min : int ($self : self)

Get minutes.

  my $min = $time_info->min;

=head2 set_min

  sub set_min : void ($self : self, $min : int)

Set minutes.

  $time_info->set_min(34);

=head2 hour

  sub min : int ($self : self)

Get hour.

  my $hour = $time_info->hour;

=head2 set_hour

  sub set_min : void ($self : self, $min : int)

Set hour.

  $time_info->set_hour(12);

=head2 mday

  sub mday : int ($self : self)

Get day of month.

  my $mday = $time_info->mday;

=head2 set_mday

  sub set_mday : void ($self : self, $mday : int)

Set day of month.

  $time_info->set_mday(4);

=head2 mon

  sub mon : int ($self : self)

Get month.

  my $mon = $time_info->mon;

=head2 set_mon

  sub set_mon : void ($self : self, $mon : int)

Set month.

  $time_info->set_mon(3);

=head2 year

  sub year : int ($self : self)

Get year.

  my $year = $time_info->year;

=head2 set_year

  sub set_year : void ($self : self, $year : int)

Set year.

  $time_info->set_year(1);

=head2 wday

  sub wday : int ($self : self)

Get weekday.

  my $wday = $time_info->wday;

=head2 set_wday

  sub set_wday : void ($self : self, $wday : int)

Set weekday.

  $time_info->set_wday(12);

=head2 yday

  sub wday : int ($self : self)

Get day of year.

  my $yday = $time_info->yday;

=head2 set_yday

  sub set_wday : void ($self : self, $wday : int)

Set day of year.

  $time_info->set_yday(234);

=head2 isdst

  sub isdst : int ($self : self)

Set the value if the specified time occurs during Daylight Saving Time

  my $isdst = $time_info->isdst;

=head2 set_isdst

  sub set_isdst : void ($self : self, $isdst : int)

Get the value if the specified time occurs during Daylight Saving Time.

  $time_info->set_isdst(1);
