package SPVM::Util;

use strict;
use warnings;
use Carp 'croak';

sub get_sub_names {
  my $module = shift;
  
  my $module_file = $module;
  $module_file =~ s/:/\//g;
  $module_file = "lib/$module_file.spvm";
  
  open my $module_fh, '<', $module_file
    or croak "Can't open $module_file: $!";
  
  my $sub_names = [];
  
  my $src = do { local $/; <$module_fh> };

  $DB::single = 1;
  
  # \s*\:\s*([^\{]+?);
  while ($src =~ /sub\s+([^\s]+)\s*\((?:[^\)]*?)\)\s*\:\s*([^\{]+);/g) {
    my $sub_name = $1;
    my $descripter_type = $2;
    if ($descripter_type =~ /\bnative\b/) {
      push @$sub_names, $sub_name;
    }
  }
  
  return $sub_names;
}

1;
