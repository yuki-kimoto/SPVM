use strict;
use warnings;

use FindBin;
use File::Find 'find';

use Test::More 'no_plan';

# Check that SPVM.xs, SPVM c source codes, and headers contain calloc only one in spvm_compiler_allocator.c
{
  my $builder_dir = "$FindBin::Bin/../lib/SPVM/Builder";
  my $xs_file = "$FindBin::Bin/../SPVM.xs";
  my @check_files = ($xs_file);
  find (
    sub {
      my $file = $File::Find::name;
      
      if (-f $file && $file =~ /(\.c|\.h)$/) {
        push @check_files, $file;
      }
    },
    $builder_dir
  );
  
  # Check if a xs file exist
  ok(grep { /\.xs$/ } @check_files);
  
  # Check if header files exist
  ok(grep { /\.h$/ } @check_files);
  
  # Check if c source files exist
  ok(grep { /\.c$/ } @check_files);
  
  my $alloc_counts = 0;
  my $calloc_counts_in_compiler_allocator_source;
  for my $check_file (@check_files) {
    open my $check_fh, '<', $check_file
      or die "Can't open file \"$check_file\": $!";
    
    my $check_content = do { local $/; <$check_fh> };
    my $re = qr/\b(calloc|alloc|malloc)\(/;
    my $match_count;
    if ($check_file =~ /spvm_compiler_allocator\.c$/) {
      $match_count = $check_content =~ /$re/g;
      $calloc_counts_in_compiler_allocator_source = 1;
    }
    else {
      $match_count = $check_content =~ /$re/g;
    }
    $alloc_counts += $match_count;
  }
  is($alloc_counts, 1);
  ok($calloc_counts_in_compiler_allocator_source);
}
