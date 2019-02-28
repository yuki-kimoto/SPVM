# Create module which use all test modules

use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';
use File::Find;

# remove and edit and copy lib file for JIT
my $test_default_dir = 't/default/lib';

my @module_names;

find(
  {
    wanted => sub {
      my $file = $File::Find::name;
      
      if (-f $file) {
        
        my $top_dir_re = quotemeta $test_default_dir;
        
        my $module_name = $file;
        
        return unless $module_name =~ /\.spvm$/;
        
        $module_name =~ s/^$top_dir_re[\/\\]//;
        
        $module_name =~ s/[\/\\]/::/g;
        
        $module_name =~ s/\.spvm$//;
        
        return if $module_name =~ /CompileError/;
        
        push @module_names, $module_name;
      }
    },
    no_chdir => 1,
  },
  $test_default_dir
);

my $all_module_file = 't/default/lib/UseAllTestCase.spvm';

open my $fh, '>', $all_module_file
  or die "Can't write $all_module_file: $!";

my $src = "package UseAllTestCase {\n";

for my $module_name (@module_names) {
  $src .= "  use $module_name;\n";
}

$src .= "}\n";

print $fh $src;
