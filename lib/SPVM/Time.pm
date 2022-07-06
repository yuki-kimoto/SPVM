package SPVM::Time;

1;

=head1 Name

SPVM::Time - Time Manipulation

=head1 Usage
  
  use Time;
  
  # Get the current epoch time
  my $epoch = Time->time;
  
  # Convert a epoch time to the Time::Info object that is local time
  my $time_info_local = Time->localtime($epoch);
  
  # Convert a epoch time to the Time::Info object that is UTC
  my $time_info_utc = Time->gmtime($epoch);
  
=head1 Description

C<Time> is a module to manipulate time.

=head1 Class Methods

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

=head1 See Also

See L<Time::Local|SPVM::Time::Local> about C<timelocal> and C<timegm> methods.
