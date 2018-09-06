package SPVM::Builder::C::Native;

# SPVM::Builder::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use base 'SPVM::Builder::C';

use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

use SPVM::Builder;
use SPVM::Builder::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'native';
  
  return $self;
}

sub build_shared_lib_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $work_dir = "spvm_build/work";
  mkpath $work_dir;

  my $output_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared library
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}


1;
