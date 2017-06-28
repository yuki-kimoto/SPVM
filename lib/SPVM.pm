package SPVM;

use 5.008007;
use strict;
use warnings;

use SPVM::Data;

use Carp 'croak';

our $VERSION = '0.0204';

our $SPVM;
our @PACKAGE_INFOS;
our @INCLUDE_PATHS;
our @SUB_SYMTABLE;
our $ENV;

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
  $spvm->build_type_symtable;
  
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
    
    my $sub;
    $sub .= "sub SPVM::$abs_name {\n";
    $sub .= "  SPVM::call_sub(\$spvm, \"$abs_name\", \@_);\n";
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

SPVM - Fast calculation, GC, static typing, VM with perlish syntax

B<SPVM is under developing! I will change implementation and specification without warnings.>

=head1 SYNOPSIS
  
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyModule2';
  
  my $total = SPVM::MyModule2::foo(SPVM::int(3), SPVM::int(5));
  print $total->value . "\n";
  
Module file

  # lib/SPVM/MyModule1.spvm
  package MyModule1 {
    has x : int;
    has y : int;
    
    sub sum ($a : int, $b : int) : int {
      
      my $total = $a + $b;
      
      return $total;
    }
  }
  
  # lib/SPVM/MyModule2.spvm
  use MyModule1;
  package MyModule2 {
    
    sub foo ($a : int, $b : int) : int {
      
      my $total = ($a * $b) + MyModule1::sum(2, 4);
      
      return $total;
    }
  }

If you want to know more syntax, see C<solo/SPVM/Test.spvm>.

If you want to know SPVM language, see C<solo/README.md>

=head1 DESCRIPTION

Do you need B<faster Perl>? SPVM provides fast calculation to Perl.

=over 4

=item *

B<Fast calculation> - The Perl's biggest weak point is the calculation performance. SPVM provides fast calculations.

=item *

B<GC> - You don't need to care about freeing memory

=item *

B<Static typing> - Static typing for performance

=item *

B<VM> - Byte codes are generated so that you can run them on SPVM language

=item *

B<Perlish syntax> - SPVM syntax is very similar to Perl

=item *

B<Perl module> - SPVM function can be called from Perl itself (Not yet implemented).

=back;

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CONTRIBUTERS

=over 4

=item *

[akinomyoga](https://github.com/akinomyoga) (Koichi Murase)

=item *

[NAGAYASU Shinya](https://github.com/nagayasu-shinya)

=item *

[Reini Urban](https://github.com/rurban)

=item *

[chromatic](https://github.com/chromatic)

=item *

[Kazutake Hiramatsu](https://github.com/kazhiramatsu)

=back

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017 by Yuki Kimoto

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.16.3 or,
at your option, any later version of Perl 5 you may have available.

=cut
