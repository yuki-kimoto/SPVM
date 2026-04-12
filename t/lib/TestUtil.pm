package TestUtil;

use parent 'Exporter';

use strict;
use warnings;
use File::Temp();
use Test::More;
use Carp 'confess';
use File::Path 'mkpath';
use File::Basename 'dirname';
use SPVM::Builder;
use FindBin;

our @EXPORT_OK = qw(compile_ok_file compile_ok compile_not_ok_file compile_not_ok);

sub compile_not_ok {
  my ($sources, $error_message_re) = @_;
  
  if (defined $error_message_re) {
    unless (ref $error_message_re) {
      my $quotemeta = quotemeta $error_message_re;
      $error_message_re = qr/$quotemeta/;
    }
  }
  
  unless (ref $sources eq 'ARRAY') {
    $sources = [$sources];
  }
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $tmp_include_dir = File::Temp->newdir;
    
  my $first_basic_type_name;
  for my $source (@$sources) {
    my $basic_type_name;
    if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
      $basic_type_name = $1;
    }
    unless (defined $basic_type_name) {
      die "Can't find basic type name in the source";
    }
    
    unless (defined $first_basic_type_name) {
      $first_basic_type_name = $basic_type_name;
    }
    
    my $class_file = "$tmp_include_dir/$basic_type_name.spvm";
    $class_file =~ s|::|/|g;
    
    mkpath dirname $class_file;
    open my $class_fh, '>', $class_file
      or confess("Can't open file \"$class_file\":$!");
    
    binmode $class_fh;
    
    print $class_fh $source;
    close $class_fh;
  }
  
  compile_not_ok_file($first_basic_type_name, $error_message_re, {include_dir => "$tmp_include_dir", file => $file, line => $line});
}

sub compile_not_ok_file {
  my ($basic_type_name, $error_message_re, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $include_dir = $options->{include_dir};
  
  my (undef, $caller_file, $caller_line) = caller;
  
  my $file;
  if (defined $options->{file}) {
    $file = $options->{file};
  }
  else {
    $file = $caller_file;
  }

  my $line;
  if (defined $options->{line}) {
    $line = $options->{line};
  }
  else {
    $line = $caller_line;
  }
  
  my $builder = SPVM::Builder->new;
  if (defined $include_dir) {
    unshift @{$builder->include_dirs}, $include_dir;
  }
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  
  for my $include_dir (@{$builder->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  eval { $compiler->compile($basic_type_name); };
  my $success = $@ ? 0 : 1;
  ok(!$success);
  my $error_messages = $compiler->get_error_messages;
  my $first_error_message = $error_messages->[0];
  my $message_ok;
  if ($error_message_re) {
    $message_ok = like($first_error_message, $error_message_re);
  }
  
  if ($success || ($error_message_re && !$message_ok)) {
    warn "  at $file line $line\n";
  }
}

sub compile_ok {
  my ($sources) = @_;
  
  unless (ref $sources eq 'ARRAY') {
    $sources = [$sources];
  }
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $tmp_include_dir = File::Temp->newdir;
    
  my $first_basic_type_name;
  for my $source (@$sources) {
    my $basic_type_name;
    if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
      $basic_type_name = $1;
    }
    unless (defined $basic_type_name) {
      die "Can't find basic type name in the source";
    }
    
    unless (defined $first_basic_type_name) {
      $first_basic_type_name = $basic_type_name;
    }
    
    my $class_file = "$tmp_include_dir/$basic_type_name.spvm";
    $class_file =~ s|::|/|g;
    
    mkpath dirname $class_file;
    open my $class_fh, '>', $class_file
      or confess("Can't open file \"$class_file\":$!");
    
    binmode $class_fh;
    
    print $class_fh $source;
    close $class_fh;
  }
  
  compile_ok_file($first_basic_type_name, {include_dir => "$tmp_include_dir", file => $file, line => $line});
}

sub compile_ok_file {
  my ($basic_type_name, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $include_dir = $options->{include_dir};
  
  my (undef, $caller_file, $caller_line) = caller;
  
  my $file;
  if (defined $options->{file}) {
    $file = $options->{file};
  }
  else {
    $file = $caller_file;
  }

  my $line;
  if (defined $options->{line}) {
    $line = $options->{line};
  }
  else {
    $line = $caller_line;
  }
  
  my $builder = SPVM::Builder->new;
  if (defined $include_dir) {
    unshift @{$builder->include_dirs}, $include_dir;
  }
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  
  for my $include_dir (@{$builder->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  eval { $compiler->compile($basic_type_name); };
  
  my $success = $@ ? 0 : 1;
  
  ok($success);
  
  if (!$success) {
    warn "  at $file line $line\n";
    
    my $error_messages = $compiler->get_error_messages;
    my $first_error_message = $error_messages->[0];
    warn "[Compile Error]$first_error_message";
  }
}

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
  
  # Generate method call string only if $method_name is defined
  my $method_call = "";
  if (defined $method_name) {
    $method_call = "$spvm_class_name->$method_name;";
  }
  
  my $content = <<"EOS";
use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;

use SPVM '$class_name';

use TestUtil;

# Call the SPVM method if a method name is provided
$method_call
EOS

  open my $script_fh, '>', $script_file
    or die "Can't open file $script_file: $!";
  
  print $script_fh $content;
  close $script_fh;
}

sub is_in_precompile_test {
  return $FindBin::Bin =~ m|t/03_precompile\b| ? 1 : 0;
}

sub to_os_specific_path {
  my ($path) = @_;
  
  my $cmd = File::Spec->catfile(split("/", $path));
  
  return $cmd;
}


1;
