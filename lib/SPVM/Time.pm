package SPVM::Time;

1;

=head1 NAME

SPVM::Time - Time Manipulation

=head1 SYNOPSYS
  
  use Time;
  
  # Get the current epoch time
  my $epoch = Time->time;
  
  # Convert a epoch time to the Time::Info object that is local time
  my $time_info_local = Time->localtime($epoch);
  
  # Convert a epoch time to the Time::Info object that is UTC
  my $time_info_utc = Time->gmtime($epoch);
  
  # Convert a Time::Info object that is local time to the epoch time
  my $epoch = Time->timelocal($time_info_local);
  
  # Convert a Time::Info object that is UTC to the epoch time
  my $epoch = Time->timegm($time_info_utc);

=head1 DESCRIPTION

C<Time> is a module to manipulate time.

=head1 CLASS METHODS

=head2 time

  static method time : long ()

Get the current epoch time. 

This method is the same as C<time> function of C<Linux>.

  my $epoch = Time->time;

=head2 localtime

  static method localtime : Time::Info ($time : long)

Convert an epoch time to the L<Time::Info|SPVM::Time::Info> object that is local time.

This method is the same as C<localtime> function of C<Linux>.

  my $time_info = Time->localtime($epoch);

=head2 gmtime

  static method gmtime : Time::Info ($time : long)

Convert an epoch time to the L<Time::Info|SPVM::Time::Info> object that is C<UTC>.

This method is the same as C<gmtime> function of C<Linux>.

  my $time_info = Time->gmtime($epoch);

=head2 timelocal

  static method timelocal : long ($time_info : Time::Info)

Convert a L<Time::Info|SPVM::Time::Info> object that is local time to the epoch time.

This method is the same as C<timelocal> function of C<Linux>.

  my $epoch = Time::Local->timelocal($time_info);

=head2 timegm

  static method timegm : long ($time_info : Time::Info)

Convert a L<Time::Info|SPVM::Time::Info> object that is C<UTC> to the epoch time.

This method is the same as C<timegm> function of C<Linux>.

  my $epoch = Time::Local->timegm($time_info);
