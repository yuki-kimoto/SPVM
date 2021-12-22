use strict;
use warnings;

use Test::More 'no_plan';

use SPVM::Builder::Config;

use FindBin;

my $config = SPVM::Builder::Config->new;

# Parse Windows def file
{
  # libpng
  {
    my $def_file = "$FindBin::Bin/builder_config/libpng.def";
    my $export_functions = $config->parse_windows_def_file($def_file);
    my @expected = qw(
      png_access_version_number
      png_set_sig_bytes
      png_sig_cmp
    );
    is_deeply($export_functions, \@expected);
  }
  
  # zlib
  {
    my $def_file = "$FindBin::Bin/builder_config/zlib.def";
    my $export_functions = $config->parse_windows_def_file($def_file);
    my @expected = qw(
      zlibVersion
      deflate
      deflateSetDictionary
      deflateGetDictionary
    );
    is_deeply($export_functions, \@expected);
  }
}
