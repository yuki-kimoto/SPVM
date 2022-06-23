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

use FindBin;
use lib "$FindBin::Bin/default/lib";

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

# Call method
{
  compile_not_ok_file('TestCase::CompileError::CallMethod::NotFound', qr/The "TestCase::CompileError::CallMethod::NotFound->NOT_FOUND_METHOD" method is not defined/);
  compile_not_ok_file('TestCase::CompileError::CallMethod::ClassNotFound', qr/The "NotFoundClass" class is not yet loaded/);
  {
    my $source = 'class Tmp { static method main : int () { my $num = 1; $num->foo; }  }';
    compile_not_ok($source, qr/The invocant type of the "foo" method must be a class type or a interface type/);
  }
}

# Assign
{
  compile_not_ok_file('TestCase::CompileError::Assign::StringToBytArray');
  compile_not_ok_file('TestCase::CompileError::Assign::DifferentObject');
  compile_not_ok_file('TestCase::CompileError::Assign::ConstToNoConst');
  compile_not_ok_file('TestCase::CompileError::Assign::NotNumericToNumeric');
  compile_not_ok_file('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte');
  compile_not_ok_file('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort');
  compile_not_ok_file('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte');
  compile_not_ok_file('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt');
  compile_not_ok_file('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort');
  compile_not_ok_file('TestCase::CompileError::Assign::UnboxingDifferentType');
  compile_not_ok_file('TestCase::CompileError::Assign::BoxingDifferentType');
}

# Remainder
{
  compile_not_ok_file('TestCase::CompileError::Remainder::RightIsNotIntegral');
  compile_not_ok_file('TestCase::CompileError::Remainder::LeftIsNotIntegral');
}


# isa
{
  compile_not_ok_file('TestCase::CompileError::Isa::LeftIsNotObject');
}

# Convert
{
  compile_not_ok_file('TestCase::CompileError::Convert::ConvertFromByteArrayToString');
  compile_not_ok_file('TestCase::CompileError::Convert::ConvertFromStringToByteArray');
  compile_not_ok_file('TestCase::CompileError::Convert::ConvertToRef');
  compile_not_ok_file('TestCase::CompileError::Convert::ConvertFromRef');
  compile_not_ok_file('TestCase::CompileError::Convert::ConvertFromMultiNumericType');
}

# Concat
{
  compile_not_ok_file('TestCase::CompileError::Concat::RightIsNotString');
  compile_not_ok_file('TestCase::CompileError::Concat::LeftIsNotString');
}

# Divide - Compile Error
{
  compile_not_ok_file('TestCase::CompileError::Divide::LeftIsNotNumeric');
  compile_not_ok_file('TestCase::CompileError::Divide::RightIsNotNumeric');
  compile_not_ok_file('TestCase::CompileError::Divide::DivuiLeftIsNotInt');
  compile_not_ok_file('TestCase::CompileError::Divide::DivuiRightIsNotInt');
  compile_not_ok_file('TestCase::CompileError::Divide::DivulLeftIsNotLong');
  compile_not_ok_file('TestCase::CompileError::Divide::DivulRightIsNotLong');
}


# Remainder - Compile Error
{
  compile_not_ok_file('TestCase::CompileError::Remainder::LeftIsNotIntegral', qr/left.+%.+integral/);
  compile_not_ok_file('TestCase::CompileError::Remainder::RightIsNotIntegral', qr/right.+%.+integral/);
  compile_not_ok_file('TestCase::CompileError::Remainder::RemuiLeftIsNotInt', qr/left.+remui.+int/);
  compile_not_ok_file('TestCase::CompileError::Remainder::RemuiRightIsNotInt', qr/right.+remui.+int/);
  compile_not_ok_file('TestCase::CompileError::Remainder::RemulLeftIsNotLong', qr/left.+remul.+long/);
  compile_not_ok_file('TestCase::CompileError::Remainder::RemulRightIsNotLong', qr/right.+remul.+long/);
}

# Weaken
{
  compile_not_ok_file('TestCase::CompileError::Weaken::IsweakFieldNotObjectType', qr/isweak.*object/);
  compile_not_ok_file('TestCase::CompileError::Weaken::UnweakenFieldNotObjectType', qr/unweaken.*object/);
  compile_not_ok_file('TestCase::CompileError::Weaken::WeakenFieldNotObjectType', qr/weaken.*object/);
}

# Subtraction Operator
{
  # The beginning of the number is an integer literal
  {
    {
      my $source = 'class Tmp { static method main : void () { my $num = 0; $num-2; } }';
      compile_not_ok($source, qr/Unexpected token "-2"/);
    }
  }
}

# Comparison operator
{
  compile_not_ok_file('TestCase::CompileError::ComparisonOperator::GtNotNumeric');
  compile_not_ok_file('TestCase::CompileError::ComparisonOperator::GeNotNumeric');
  compile_not_ok_file('TestCase::CompileError::ComparisonOperator::LtNotNumeric');
  compile_not_ok_file('TestCase::CompileError::ComparisonOperator::LeNotNumeric');
}

# Add
{
  compile_not_ok_file('TestCase::CompileError::Add::LeftIsNotNumeric');
  compile_not_ok_file('TestCase::CompileError::Add::RightIsNotNumeric');
}

# Multiply
{
  compile_not_ok_file('TestCase::CompileError::Multiply::LeftIsNotNumeric');
  compile_not_ok_file('TestCase::CompileError::Multiply::RightIsNotNumeric');
}

# Subtract
{
  compile_not_ok_file('TestCase::CompileError::Subtract::LeftIsNotNumeric');
  compile_not_ok_file('TestCase::CompileError::Subtract::RightIsNotNumeric');
}


# Unary minus
{
  compile_not_ok_file('TestCase::CompileError::UnaryMinus::NotNumeric');
}

# Unary plus
{
  compile_not_ok_file('TestCase::CompileError::UnaryPlus::NotNumeric');
}

# New operator - new
{
  compile_not_ok_file('TestCase::CompileError::New::Private');
}

done_testing;
