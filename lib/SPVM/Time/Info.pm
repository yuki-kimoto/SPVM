package SPVM::Time::Info;

1;

=head1 Name

SPVM::Time::Info - struct tm in C language

=head1 Usage
  
  use Time::Info;
  
  my $tm = Time::Info->new;
  
  my $sec = $tm->tm_sec;
  $tm->set_tm_sec(12);
  
  my $min = $tm->tm_min;
  $tm->set_tm_min(34);
  
  my $hour = $tm->tm_hour;
  $tm->set_tm_hour(12);

  my $mday = $tm->tm_mday;
  $tm->set_tm_mday(4);

  my $mon = $tm->tm_mon;
  $tm->set_tm_mon(3);

  my $year = $tm->tm_year;
  $tm->set_tm_year(1);

  my $wday = $tm->tm_wday;
  $tm->set_tm_wday(12);

  my $yday = $tm->tm_yday;
  $tm->set_tm_yday(234);

  my $isdst = $tm->tm_isdst;
  $tm->set_tm_isdst(1);

=head1 Description

C<Time::Info> represents C<struct tm> of C<C language>.

See L<ctime(3) - Linux man page|https://linux.die.net/man/3/ctime> about C<struct tm> in Linux.

=head1 Class Methods

=head2 new

  static method new : Time::Info ()

Creates a new L<Time::Info|SPVM::Time::Info> object.

  my $tm = Time::Info->new;

=head1 Instance Methods

=head2 tm_sec

  method tm_sec : int ()

Gets C<tm_sec>.

  my $tm_sec = $tm->tm_sec;

=head2 set_tm_sec

  method set_tm_sec : void ($tm_sec : int)

Sets C<tm_sec>.

  $tm->set_tm_sec(12);

=head2 tm_min
  
  method tm_min : int ()

Gets C<tm_min>.

  my $tm_min = $tm->tm_min;

=head2 set_tm_min

  method set_tm_min : void ($tm_min : int)

Sets C<tm_min>.

  $tm->set_tm_min(34);

=head2 tm_hour

  method tm_hour : int ()

Gets C<tm_hour>.

  my $tm_hour = $tm->tm_hour;

=head2 set_tm_hour

  method set_tm_hour : void ($tm_hour : int)

Sets C<tm_hour>.

  $tm->set_tm_hour(12);

=head2 tm_mday

  method tm_mday : int ()

Gets C<tm_mday>.

  my $tm_mday = $tm->tm_mday;

=head2 set_tm_mday

  method set_tm_mday : void ($tm_mday : int)

Sets C<tm_mday>.

  $tm->set_tm_mday(4);

=head2 tm_mon

  method tm_mon : int ()

Gets C<tm_mon>.

  my $tm_mon = $tm->tm_mon;

=head2 set_tm_mon

  method set_tm_mon : void ($tm_mon : int)

Sets C<tm_mon>.

  $tm->set_tm_mon(3);

=head2 tm_year

  method tm_year : int ()

Gets C<tm_year>.

  my $tm_year = $tm->tm_year;

=head2 set_tm_year

  method set_tm_year : void ($tm_year : int)

Sets C<tm_year>.

  $tm->set_tm_year(1);

=head2 tm_wday

  method tm_wday : int ()

Gets C<tm_wday>.

  my $tm_wday = $tm->tm_wday;

=head2 set_tm_wday

  method set_tm_wday : void ($tm_wday : int)

Sets C<tm_wday>.

  $tm->set_tm_wday(12);

=head2 tm_yday

  method tm_yday : int ()

Gets C<tm_yday>.

  my $yday = $tm->tm_yday;

=head2 set_tm_yday

  method set_tm_yday : void ($tm_yday : int)

Sets C<tm_yday>.

  $tm->set_tm_yday(234);

=head2 tm_isdst

  method tm_isdst : int ()

Gets C<tm_isdst>.

  my $isdst = $tm->tm_isdst;

=head2 set_tm_isdst

  method set_tm_isdst : void ($tm_isdst : int)

Sets C<tm_isdst>.

  $tm->set_tm_isdst(1);

=head1 Thingking

The name of this module(C<Time::Info>) should have been C<Sys::Time::Tm> and this module should have belonged to L<Sys|SPVM::Sys> distribution.

But C<Time::Info> is already used by L<Time::Local|SPVM::Time::Local> and duplicate module management causes confusion, so C<Sys::Time::Tm> is not created.
