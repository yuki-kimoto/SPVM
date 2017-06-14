package SPVM;

use 5.008007;
use strict;
use warnings;

use SPVM::Compiler;

my $compiler;

BEGIN {
  $compiler = SPVM::Compiler->new;
  
  # Add moduel include path
  push @{$compiler->include_paths}, @INC;
}

our $VERSION = '0.01';

sub import {
  my ($class, $package_name) = @_;
  
  # Add package infomations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];

    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @{$compiler->package_infos}, $package_info;
  }
}

sub get_compiler {
  return $compiler;
}

require XSLoader;
XSLoader::load('SPVM', $VERSION);

# Preloaded methods go here.

1;
__END__
# Below is stub documentation for your module. You'd better edit it!

=head1 NAME

SPVM - Perl extension for blah blah blah

=head1 SYNOPSIS

  use SPVM;
  blah blah blah

=head1 DESCRIPTION

Stub documentation for SPVM, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHOR

A. U. Thor, E<lt>kimoto@sakura.ne.jpE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017 by A. U. Thor

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.16.3 or,
at your option, any later version of Perl 5 you may have available.


=cut
