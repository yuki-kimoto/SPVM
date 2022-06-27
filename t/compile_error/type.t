use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use File::Temp ();

use SPVM::Builder;

use Test::More;

my $file = 't/' . basename $0;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

sub compile_not_ok_file {
  my ($class_name, $error_message_re, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $module_dir = $options->{module_dir};
  
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
  if (defined $module_dir) {
    unshift @{$builder->module_dirs}, $module_dir;
  }
  
  my $success = $builder->compile_spvm($class_name, $file, $line);
  ok($success == 0);
  unless ($success == 0) {
    warn "  at $file line $line\n";
  }
  my $error_messages = $builder->get_error_messages;
  my $first_error_message = $error_messages->[0];
  if ($error_message_re) {
    like($first_error_message, $error_message_re);
  }
}

sub compile_not_ok {
  my ($source, $error_message_re) = @_;
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $class_name;
  if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
    $class_name = $1;
  }
  unless (defined $class_name) {
    die "Can't find class name in the source";
  }
  
  my $tmp_module_dir = File::Temp->newdir;
  
  my $module_file = "$tmp_module_dir/$class_name.spvm";
  $module_file =~ s|::|/|g;
  
  if (open my $module_fh, '>', $module_file) {
    print $module_fh $source;
    close $module_fh;
  }
  
  compile_not_ok_file($class_name, $error_message_re, {module_dir => "$tmp_module_dir", file => $file, line => $line});
}

sub print_error_messages {
  my ($builder) = @_;
  
  my $error_messages = $builder->get_error_messages;
  
  for my $error_message (@$error_messages) {
    print STDERR "[CompileError]$error_message\n";
  }
}

# Array of any object - object[]
{
  compile_not_ok_file('TestCase::CompileError::OArray::AssignNumeric');
  compile_not_ok_file('TestCase::CompileError::OArray::AssignNumericArray');
}

# String
{
  compile_not_ok_file('TestCase::CompileError::String::CharacterAssign');
  compile_not_ok_file('TestCase::CompileError::String::AssignNonMutableToMutable');
}

# Bool
{
  compile_not_ok_file('TestCase::CompileError::Bool::NotNumericObject');
}
{
  compile_not_ok_file('TestCase::CompileError::InvalidType');
}

{
  compile_not_ok_file('TestCase::CompileError::TypeCantBeDetectedUndef');
}

{
  compile_not_ok_file('TestCase::CompileError::TypeCantBeDetectedUndefDefault');
}

# Type
{
  compile_not_ok_file('TestCase::CompileError::Type::MutableNoStringCaseStringArray');
  compile_not_ok_file('TestCase::CompileError::Type::MutableNoStringCaseInt');
  compile_not_ok_file('TestCase::CompileError::Type::MultiDimensionalAnyObject', qr/Multi dimensional array of any object/i);
}

# Type comment
{
  compile_not_ok_file('TestCase::CompileError::TypeComment::NotExistType', qr/NotExists::XXXX/);
}


done_testing;
