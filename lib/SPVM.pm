package SPVM;

use 5.008007;
use strict;
use warnings;

use Carp 'croak';

our $VERSION = '0.01';

my $SPVM;

sub get_spvm { $SPVM }

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{package_infos} = [];
  $self->{include_paths} = [];
  
  return bless $self, __PACKAGE__;
}

BEGIN {
  # SPVM
  my $spvm = SPVM->new;
  
  # Add moduel include path
  push @{$spvm->{include_paths}}, @INC;
  
  # Save SPVM
  $SPVM = $spvm;
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  # SPVM
  my $spvm = $SPVM;
  
  # Compile SPVM source code
  $spvm->compile;
  
  # Build resolved type symbol table
  $spvm->build_resolved_type_symtable;
  
  # Build subroutine symbole table
  $spvm->build_sub_symtable;
  
  # Build SPVM subroutine
  $spvm->build_spvm_subs;
  
  # Build run-time
  $spvm->build_runtime;
  
  # Free compiler
  $spvm->free_compiler;
}

sub import {
  my ($class, $package_name) = @_;
  
  # SPVM
  my $spvm = $SPVM;
  
  # Add package infomations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];

    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @{$spvm->{package_infos}}, $package_info;
  }
}

sub build_spvm_subs {
  my $spvm = $SPVM;
  
  my $sub_symtable = $spvm->{sub_symtable};
  
  for my $abs_name (keys %$sub_symtable) {
    
    my $sub_info = $sub_symtable->{$abs_name};
    my ($constant_pool_index, $arg_resolved_type_ids, $return_resolved_type_id) = @$sub_info;
    
    my $sub;
    $sub .= "sub SPVM::$abs_name {\n";
    $sub .= "  SPVM::call_sub(\$spvm, $constant_pool_index, \@_);\n";
    $sub .= "}";
    
    # Define SPVM subroutine
    eval $sub;
    
    if ($@) {
      croak "Can't define SVPM subroutine \"$abs_name\"\n$sub";
    }
  }
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
