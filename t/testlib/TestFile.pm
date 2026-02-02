package TestFile;

use strict;
use warnings;
use File::Basename 'basename';
use File::Path 'mkpath';

# Copy test_files to test_files_tmp
sub copy_test_files_tmp {

  my $test_files_dir = 't/test_files';
  my $test_files_tmp_dir = 't/test_files/.tmp';
  
  mkpath $test_files_tmp_dir;
  
  my @test_files = glob "$test_files_dir/*";
  
  for my $file (@test_files) {
    my $file_base = basename $file;
    my $file_tmp = "$test_files_tmp_dir/$file_base";
    
    open my $in_fh, '<', $file
      or die "Can't open file $file: $!";
    
    my $content = do { local $/; <$in_fh> };
    
    open my $out_fh, '>', $file_tmp
      or die "Can't open file $file: $!";
    
    binmode $out_fh;
    
    print $out_fh $content;
  }
}

sub slurp_binmode {
  my ($output_file) = @_;
  
  open my $fh, '<', $output_file
    or die "Can't open file $output_file:$!";
  
  binmode $fh;
  
  my $output = do { local $/; <$fh> };
  
  return $output;
}

sub generate_class_method_call_script {
  my ($script_file, $class_name, $method_name) = @_;
  
  # Prepend "SPVM::" to the class name to create a valid Perl-side SPVM class name
  my $spvm_class_name = "SPVM::$class_name";
  
  my $content = <<"EOS";
use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use SPVM '$class_name';

use TestFile;

# Call the SPVM method using the full Perl-side name
$spvm_class_name->$method_name;
EOS

  open my $script_fh, '>', $script_file
    or die "Can't open file $script_file: $!";
  
  print $script_fh $content;
  close $script_fh;
}

1;
