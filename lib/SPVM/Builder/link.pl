use strict;
use warnings;
use ExtUtils::CBuilder;
use File::Copy ();
use File::Path 'mkpath';
use File::Basename 'basename', 'dirname';
use MIME::Base64 qw(decode_base64);
use Digest::SHA 'sha1_hex';
use File::Path 'mkpath';

# Get arguments
my @argv = split("\0", decode_base64($ARGV[0]));
my ($command_tmp_dir, $output_file, $module_name, $hint_cc, $output_type, $ld, $dl_func_list_file, $object_file_names_file, $ldflags_file) = @argv;

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout)
  or die "Can't open file '$log_stdout': $!";
open(STDERR, '>', $log_stderr)
  or die "Can't open file '$log_stderr': $!";

# Read dl_func_list
my $dl_func_list;
if (my $content = &slurp_binary($dl_func_list_file)) {
  $dl_func_list = [split(/\n/, $content)];
}

# Read object_file_names
my @object_file_names;
if (my $content = &slurp_binary($object_file_names_file)) {
  @object_file_names = split(/\n/, $content);
}

# Read ldflags
my @ldflags;
if (my $content = &slurp_binary($ldflags_file)) {
  @ldflags = split(/\n/, $content);
}

my $perllibs = '';
if ($^O eq 'MSWin32') {
  # [HACK]
  # On Windows, if perllibs is empty, ExtUtils::CBuilder::link may generate
  # an empty INPUT() section in the response file (linker argument file), 
  # which leads to a build failure.
  # To prevent this, we explicitly specify kernel32.lib (a core Windows library)
  if ($hint_cc =~ /cl(\.exe)?$/i) {
    # For MSVC (cl.exe)
    $perllibs = 'kernel32.lib';
  }
  else {
    # For others (e.g. MinGW/gcc)
    $perllibs = '-lkernel32';
  }
}

# Configure CBuilder
my $cbuilder_config = {
  cc => $hint_cc,
  ld => $ld,
  lddlflags => '',
  shrpenv => '',
  libpth => '',
  libperl => '',
  perllibs => $perllibs
};

my $cbuilder = ExtUtils::CBuilder->new(quiet => 1, config => $cbuilder_config);

# Create a dedicated object directory in the temporary directory
my $tmp_object_dir = "$command_tmp_dir/object";
mkpath($tmp_object_dir);

# Copy all object files with path hashing to avoid collisions
my @tmp_object_file_names;
for my $object_file_name (@object_file_names) {
  my $sha1 = Digest::SHA::sha1_hex($object_file_name);
  my $tmp_object_dir = "$tmp_object_dir/$sha1";
  mkpath($tmp_object_dir);
  
  my $tmp_object_file_name = "$tmp_object_dir/" . basename($object_file_name);
  File::Copy::copy($object_file_name, $tmp_object_file_name)
    or die "Can't copy '$object_file_name' to '$tmp_object_file_name': $!";
  push @tmp_object_file_names, $tmp_object_file_name;
}

# Determine link method and output option
my $link_method = ($output_type eq 'exe') ? 'link_executable' : 'link';
my $output_option = ($output_type eq 'exe') ? 'exe_file' : 'lib_file';

my $tmp_output_file = "$command_tmp_dir/link.output";

# Link to the .tmp file instead of the final file
$cbuilder->$link_method(
  $output_option => $tmp_output_file,
  objects => \@tmp_object_file_names,
  extra_linker_flags => "@ldflags",
  module_name => $module_name,
  dl_func_list => $dl_func_list,
);

mkpath dirname $output_file;

File::Copy::move($tmp_output_file, $output_file)
  or confess("Can't move '$tmp_output_file' to '$output_file': $!");
  
# Copied from SPVM::Builder::Util#slurp_binary
sub slurp_binary {
  my ($file) = @_;
  
  open my $fh, '<', $file
    or confess("Can't open file '$file':$!");
    
  my $content = do { local $/; <$fh> };
  
  return $content;
}
