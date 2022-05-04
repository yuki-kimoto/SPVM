use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Builder;

use Test::More;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

sub compile_not_ok {
  my ($class_name, $error_message_re) = @_;
  
  my (undef, $file, $line) = caller;
  
    my $builder = SPVM::Builder->new;
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
    print_error_messages($builder);
}

sub print_error_messages {
  my ($builder) = @_;
  
  my $error_messages = $builder->get_error_messages;
  
  for my $error_message (@$error_messages) {
    print STDERR "[CompileError]$error_message\n";
  }
}

# SPVM compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/compile_error.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}

# SPVM dist compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/compile_error_dist.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}


# Class
{
  compile_not_ok('TestCase::CompileError::Class::NotClosed');
  compile_not_ok('TestCase::CompileError::Class::ClassNameDifferntFromModuleName');
  compile_not_ok('TestCase::CompileError::Class::classPartNameStartWithLowerCase');
  compile_not_ok('foo');
  compile_not_ok('4foo');
}

# Pakcage name must start SPVM::
{
  compile_not_ok('ClassNameCompileError');
}

# use
{
  compile_not_ok('TestCase::CompileError::Use::ImportMethodNotFound');
  compile_not_ok('TestCase::CompileError::Use::AliasStartsLowerCase');
  compile_not_ok('TestCase::CompileError::Use::AliasDuplication');
}

# Logical operator
{
  compile_not_ok('TestCase::CompileError::LogicalOperator::AndNotExpression');
  compile_not_ok('TestCase::CompileError::LogicalOperator::OrNotExpression');
  compile_not_ok('TestCase::CompileError::LogicalOperator::NotNotExpression');
}

# oarray
{
  compile_not_ok('TestCase::CompileError::OArray::AssignNumeric');
  compile_not_ok('TestCase::CompileError::OArray::AssignNumericArray');
}

# Literal
{
  # Caharater
  {
    compile_not_ok('TestCase::CompileError::Literal::Character::InvalidCharacterLiteralEmpty');
    compile_not_ok('TestCase::CompileError::Literal::Character::InvalidCharacterLiteral');
    compile_not_ok('TestCase::CompileError::Literal::Character::NotEnd');
    compile_not_ok('TestCase::CompileError::Literal::Character::InvalidHexAscii1');
    compile_not_ok('TestCase::CompileError::Literal::Character::InvalidHexAscii2');
  }
  # Integer
  compile_not_ok('TestCase::CompileError::Literal::Integer::IntOutOfRange');
}

# Lexcarl Variable
{
  compile_not_ok('TestCase::CompileError::LexVar::LexVarNameStartDigit');
  compile_not_ok('TestCase::CompileError::LexVar::LexVarNameInvalidColon');
  compile_not_ok('TestCase::CompileError::LexVar::LexVarNameEndColon2');
  compile_not_ok('TestCase::CompileError::LexVar::LexVarNameContainsUnderScoreTwice');
  compile_not_ok('TestCase::CompileError::LexVar::LexVarNameColon2Twice');
}

# Class Variable
{
  compile_not_ok('TestCase::CompileError::ClassVar::Private');
  compile_not_ok('TestCase::CompileError::ClassVar::OurClassVarNameStartDigit');
  compile_not_ok('TestCase::CompileError::ClassVar::OurClassVarNameInvalidColon');
  compile_not_ok('TestCase::CompileError::ClassVar::OurClassVarNameEndColon2');
  compile_not_ok('TestCase::CompileError::ClassVar::OurClassVarNameContainsUnderScoreTwice');
  compile_not_ok('TestCase::CompileError::ClassVar::OurClassVarNameColon2Twice');
}

# Method
{
  compile_not_ok('TestCase::CompileError::Method::Begin');
  compile_not_ok('TestCase::CompileError::Method::MethodNameStartDigit');
  compile_not_ok('TestCase::CompileError::Method::MethodNameContainsUnderScoreTwice');
  compile_not_ok('TestCase::CompileError::Method::TooManyArguments', qr/Too many arguments/i);
  compile_not_ok('TestCase::CompileError::Method::TooManyArgumentsMulnum'. qr/Too many arguments/i);
}

# Field
{
  compile_not_ok('TestCase::CompileError::Field::Private');
  compile_not_ok('TestCase::CompileError::Field::HasFieldNameContainsUnderScoreTwice');
  compile_not_ok('TestCase::CompileError::Field::HasFieldNameStartDigit');
}


# Enum
{
  compile_not_ok('TestCase::CompileError::Enum::PrivateAccess');
}

# Call sub
{
  {
    
    compile_not_ok('TestCase::CompileError::Switch::NoLastBreak');
    
    
  }
}

# Value
{
  compile_not_ok('TestCase::CompileError::Value::FieldsZero');
  compile_not_ok('TestCase::CompileError::Value::Fields17');
}

# Call method
{
  compile_not_ok('TestCase::CompileError::CallMethod::NotFound');
  compile_not_ok('TestCase::CompileError::CallMethod::ClassNotFound');
}

# Assign
{
  compile_not_ok('TestCase::CompileError::Assign::StringToBytArray');
  compile_not_ok('TestCase::CompileError::Assign::DifferentObject');
  compile_not_ok('TestCase::CompileError::Assign::ConstToNoConst');
  compile_not_ok('TestCase::CompileError::Assign::NotNumericToNumeric');
  compile_not_ok('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte');
  compile_not_ok('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort');
  compile_not_ok('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte');
  compile_not_ok('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt');
  compile_not_ok('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort');
  compile_not_ok('TestCase::CompileError::Assign::UnboxingDifferentType');
  compile_not_ok('TestCase::CompileError::Assign::BoxingDifferentType');
}

# Remainder
{
  compile_not_ok('TestCase::CompileError::Remainder::RightIsNotIntegral');
  compile_not_ok('TestCase::CompileError::Remainder::LeftIsNotIntegral');
}

# String
{
  compile_not_ok('TestCase::CompileError::String::CharacterAssign');
  compile_not_ok('TestCase::CompileError::String::AssignNonMutableToMutable');
}

# Comparison operator
{
  compile_not_ok('TestCase::CompileError::ComparisonOperator::GtNotNumeric');
  compile_not_ok('TestCase::CompileError::ComparisonOperator::GeNotNumeric');
  compile_not_ok('TestCase::CompileError::ComparisonOperator::LtNotNumeric');
  compile_not_ok('TestCase::CompileError::ComparisonOperator::LeNotNumeric');
}

# Bool
{
  compile_not_ok('TestCase::CompileError::Bool::NotNumericObject');
}

# isa
{
  compile_not_ok('TestCase::CompileError::Isa::LeftIsNotObject');
}

{
  compile_not_ok('TestCase::CompileError::InvalidType');
}

{
  compile_not_ok('TestCase::CompileError::TypeCantBeDetectedUndef');
}

{
  compile_not_ok('TestCase::CompileError::TypeCantBeDetectedUndefDefault');
}

{
  compile_not_ok('TestCase::CompileError::New::Private');
}

# Convert
{
  compile_not_ok('TestCase::CompileError::Convert::ConvertFromByteArrayToString');
  compile_not_ok('TestCase::CompileError::Convert::ConvertFromStringToByteArray');
  compile_not_ok('TestCase::CompileError::Convert::ConvertToRef');
  compile_not_ok('TestCase::CompileError::Convert::ConvertFromRef');
  compile_not_ok('TestCase::CompileError::Convert::ConvertFromValueType');
}

# Concat
{
  compile_not_ok('TestCase::CompileError::Concat::RightIsNotString');
  compile_not_ok('TestCase::CompileError::Concat::LeftIsNotString');
}

# Type
{
  compile_not_ok('TestCase::CompileError::Type::MutableNoStringCaseStringArray');
  compile_not_ok('TestCase::CompileError::Type::MutableNoStringCaseInt');
  compile_not_ok('TestCase::CompileError::Type::MultiDimensionalAnyObject', qr/Multi dimensional array of any object/i);
}

# Divide - Compile Error
{
  compile_not_ok('TestCase::CompileError::Divide::LeftIsNotNumeric');
  compile_not_ok('TestCase::CompileError::Divide::RightIsNotNumeric');
  compile_not_ok('TestCase::CompileError::Divide::DivuiLeftIsNotInt');
  compile_not_ok('TestCase::CompileError::Divide::DivuiRightIsNotInt');
  compile_not_ok('TestCase::CompileError::Divide::DivulLeftIsNotLong');
  compile_not_ok('TestCase::CompileError::Divide::DivulRightIsNotLong');
}


# Remainder - Compile Error
{
  compile_not_ok('TestCase::CompileError::Remainder::LeftIsNotIntegral', qr/left.+%.+integral/);
  compile_not_ok('TestCase::CompileError::Remainder::RightIsNotIntegral', qr/right.+%.+integral/);
  compile_not_ok('TestCase::CompileError::Remainder::RemuiLeftIsNotInt', qr/left.+remui.+int/);
  compile_not_ok('TestCase::CompileError::Remainder::RemuiRightIsNotInt', qr/right.+remui.+int/);
  compile_not_ok('TestCase::CompileError::Remainder::RemulLeftIsNotLong', qr/left.+remul.+long/);
  compile_not_ok('TestCase::CompileError::Remainder::RemulRightIsNotLong', qr/right.+remul.+long/);
}

# Interface
{
  compile_not_ok('TestCase::CompileError::Interface::HaveBlock', qr/interface.+block/i);
  compile_not_ok('TestCase::CompileError::Interface::NativeMethod', qr/interface.+native/i);
  compile_not_ok('TestCase::CompileError::Interface::StaticMethod', qr/interface.+instance/i);
  compile_not_ok('TestCase::CompileError::Interface::ArrayElementCantAssign', qr/List to Stringable/i);
  compile_not_ok('TestCase::CompileError::Interface::NotHaveInterfaceMethod', qr/TestCase::CompileError::Interface::NotHaveInterfaceMethod.+to_string.*string\(self\).+interface.+Stringable/i);
}

# Syntax
{
  compile_not_ok('TestCase::CompileError::Syntax::LineNumber', qr/our.*\b8:3\b/i);
}

# Type comment
{
  compile_not_ok('TestCase::CompileError::TypeComment::NotExistType', qr/NotExists::XXXX/);
}

# Weaken
{
  compile_not_ok('TestCase::CompileError::Weaken::IsweakFieldNotObjectType', qr/isweak.*object/);
  compile_not_ok('TestCase::CompileError::Weaken::UnweakenFieldNotObjectType', qr/unweaken.*object/);
  compile_not_ok('TestCase::CompileError::Weaken::WeakenFieldNotObjectType', qr/weaken.*object/);
}

done_testing;
