BEGIN { $ENV{SPVM_CC_OPTIMIZE} = '-O0 -g3'; }

use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;
use Config;
use File::Find;
use File::Path 'mkpath';
use File::Basename 'dirname';
use File::Copy 'copy';
use Config;
use FindBin;

# Choose classes that is shared for performance
use SPVM 'TestCase';
use SPVM 'TestCase::Minimal';
use SPVM 'TestCase::Simple';

=pod ALL

use SPVM 'MinimalMethod';
use SPVM 'MyMath';
use SPVM 'TestCase';
use SPVM 'TestCase::Accessor';
use SPVM 'TestCase::Alias';
use SPVM 'TestCase::Allow';
use SPVM 'TestCase::Allow::PrivateData';
use SPVM 'TestCase::Comment::LF';
use SPVM 'TestCase::DefaultLoadedClasses';
use SPVM 'TestCase::Definition::InitBlock';
use SPVM 'TestCase::Definition::InitBlock::Data';
use SPVM 'TestCase::Destroy';
use SPVM 'TestCase::Destroy::Data::Basic';
use SPVM 'TestCase::Destroy::Data::ExceptionNotOverride';
use SPVM 'TestCase::Destroy::Data::InheritanceChild';
use SPVM 'TestCase::Destroy::Data::InheritanceParent';
use SPVM 'TestCase::Empty';
use SPVM 'TestCase::Enum';
use SPVM 'TestCase::Enum::Data1';
use SPVM 'TestCase::Examples';
use SPVM 'TestCase::Exception';
use SPVM 'TestCase::ExchangeAPI';
use SPVM 'TestCase::FatCamma';
use SPVM 'TestCase::GenericType';
use SPVM 'TestCase::Inheritance';
use SPVM 'TestCase::InlineExpansion';
use SPVM 'TestCase::Interface';
use SPVM 'TestCase::Interface::AnyObjectReturn';
use SPVM 'TestCase::Interface::Args1';
use SPVM 'TestCase::Interface::NoRequiredMethod';
use SPVM 'TestCase::Interface::OptionalArgument';
use SPVM 'TestCase::Interface::Point';
use SPVM 'TestCase::Interface::Type';
use SPVM 'TestCase::InterfaceNoRequiredMethodTest';
use SPVM 'TestCase::Issues::Issue515';
use SPVM 'TestCase::Issues::Issue515::Regex';
use SPVM 'TestCase::Issues::Issue515::Regex::Match';
use SPVM 'TestCase::Issues::Issue515::Regex::Replacer';
use SPVM 'TestCase::Issues::Issue567';
use SPVM 'TestCase::Issues::Issue645';
use SPVM 'TestCase::Issues::Issue649';
use SPVM 'TestCase::Issues::Issue715';
use SPVM 'TestCase::Issues::Issue816';
use SPVM 'TestCase::Issues::Issue507::MyClass1';
use SPVM 'TestCase::Issues::Issue507::MyClass2';
use SPVM 'TestCase::LINEN';
use SPVM 'TestCase::LINERN';
use SPVM 'TestCase::LINER';
use SPVM 'TestCase::LineDirective';
use SPVM 'TestCase::List';
use SPVM 'TestCase::LocalVar';
use SPVM 'TestCase::Matrix4_16b';
use SPVM 'TestCase::Matrix4_16d';
use SPVM 'TestCase::Matrix4_16f';
use SPVM 'TestCase::Matrix4_16i';
use SPVM 'TestCase::Matrix4_16l';
use SPVM 'TestCase::Matrix4_16s';
use SPVM 'TestCase::Minimal';
use SPVM 'TestCase::Module::Array';
use SPVM 'TestCase::Module::Bool';
use SPVM 'TestCase::Module::Byte';
use SPVM 'TestCase::Module::ByteList';
use SPVM 'TestCase::Module::CallerInfo';
use SPVM 'TestCase::Module::Cloner';
use SPVM 'TestCase::Module::CommandInfo';
use SPVM 'TestCase::Module::Comparator';
use SPVM 'TestCase::Module::Complex_2d';
use SPVM 'TestCase::Module::Complex_2f';
use SPVM 'TestCase::Module::Double';
use SPVM 'TestCase::Module::DoubleList';
use SPVM 'TestCase::Module::EqualityChecker';
use SPVM 'TestCase::Module::Error';
use SPVM 'TestCase::Module::Float';
use SPVM 'TestCase::Module::FloatList';
use SPVM 'TestCase::Module::Fn';
use SPVM 'TestCase::Module::Format';
use SPVM 'TestCase::Module::Hash';
use SPVM 'TestCase::Module::Immutable::ByteList';
use SPVM 'TestCase::Module::Immutable::DoubleList';
use SPVM 'TestCase::Module::Immutable::FloatList';
use SPVM 'TestCase::Module::Immutable::IntList';
use SPVM 'TestCase::Module::Immutable::LongList';
use SPVM 'TestCase::Module::Immutable::ShortList';
use SPVM 'TestCase::Module::Immutable::StringList';
use SPVM 'TestCase::Module::Int';
use SPVM 'TestCase::Module::IntList';
use SPVM 'TestCase::Module::List';
use SPVM 'TestCase::Module::Long';
use SPVM 'TestCase::Module::LongList';
use SPVM 'TestCase::Module::Native::Argument';
use SPVM 'TestCase::Module::Native::BasicType';
use SPVM 'TestCase::Module::Native::Compiler';
use SPVM 'TestCase::Module::Native::MethodCall';
use SPVM 'TestCase::Module::Native::Runtime';
use SPVM 'TestCase::Module::Packer';
use SPVM 'TestCase::Module::Point';
use SPVM 'TestCase::Module::Point3D';
use SPVM 'TestCase::Module::QList';
use SPVM 'TestCase::Module::Scope::Guard';
use SPVM 'TestCase::Module::Short';
use SPVM 'TestCase::Module::ShortList';
use SPVM 'TestCase::Module::Sort';
use SPVM 'TestCase::Module::StringBuffer';
use SPVM 'TestCase::Module::StringList';
use SPVM 'TestCase::Module::Sync::Mutex';
use SPVM 'TestCase::Mulnum';
use SPVM 'TestCase::MulnumArray';
use SPVM 'TestCase::NativeAPI';
use SPVM 'TestCase::NativeAPICpp';
use SPVM 'TestCase::NativeAPILinkInfo';
use SPVM 'TestCase::NativeAPISrc';
use SPVM 'TestCase::OnlyField';
use SPVM 'TestCase::Operator::Add';
use SPVM 'TestCase::Operator::Address';
use SPVM 'TestCase::Operator::AnonMethod';
use SPVM 'TestCase::Operator::AnonMethod::AnonMethod';
use SPVM 'TestCase::Operator::AnonMethod::ImplementAnonMethod1';
use SPVM 'TestCase::Operator::AnonMethod::ImplementAnonMethod2';
use SPVM 'TestCase::Operator::ArrayAccess';
use SPVM 'TestCase::Operator::ArrayBigSize';
use SPVM 'TestCase::Operator::ArrayInit';
use SPVM 'TestCase::Operator::ArrayLength';
use SPVM 'TestCase::Operator::ArrayMiddleSize';
use SPVM 'TestCase::Operator::Assign';
use SPVM 'TestCase::Operator::BitOperator';
use SPVM 'TestCase::Operator::BreakPoint';
use SPVM 'TestCase::Operator::Caller';
use SPVM 'TestCase::Operator::ClassVar';
use SPVM 'TestCase::Operator::ComparisonOperator';
use SPVM 'TestCase::Operator::CompileTypeName';
use SPVM 'TestCase::Operator::Concat';
use SPVM 'TestCase::Operator::ConditionEvaluation';
use SPVM 'TestCase::Operator::Constant';
use SPVM 'TestCase::Operator::Copy';
use SPVM 'TestCase::Operator::CopyFields';
use SPVM 'TestCase::Operator::Data::Weaken';
use SPVM 'TestCase::Operator::DefinedOr';
use SPVM 'TestCase::Operator::Delete';
use SPVM 'TestCase::Operator::Divide';
use SPVM 'TestCase::Operator::Dump';
use SPVM 'TestCase::Operator::DumpTest1';
use SPVM 'TestCase::Operator::DynamicLength';
use SPVM 'TestCase::Operator::Exists';
use SPVM 'TestCase::Operator::FILE';
use SPVM 'TestCase::Operator::FieldAccess';
use SPVM 'TestCase::Operator::Increment';
use SPVM 'TestCase::Operator::IsCompileType';
use SPVM 'TestCase::Operator::IsType';
use SPVM 'TestCase::Operator::Isa';
use SPVM 'TestCase::Operator::LogicalOperator';
use SPVM 'TestCase::Operator::MethodCall';
use SPVM 'TestCase::Operator::Modulo';
use SPVM 'TestCase::Operator::Move';
use SPVM 'TestCase::Operator::Multiply';
use SPVM 'TestCase::Operator::New';
use SPVM 'TestCase::Operator::New::Array';
use SPVM 'TestCase::Operator::NumericOperator';
use SPVM 'TestCase::Operator::PACKAGE';
use SPVM 'TestCase::Operator::Print';
use SPVM 'TestCase::Operator::Ref';
use SPVM 'TestCase::Operator::Say';
use SPVM 'TestCase::Operator::Seqop';
use SPVM 'TestCase::Operator::SpecialAssign';
use SPVM 'TestCase::Operator::Stdio';
use SPVM 'TestCase::Operator::String';
use SPVM 'TestCase::Operator::Subtract';
use SPVM 'TestCase::Operator::TernaryOperator';
use SPVM 'TestCase::Operator::TypeCast';
use SPVM 'TestCase::Operator::TypeDefaultValue';
use SPVM 'TestCase::Operator::TypeName';
use SPVM 'TestCase::Operator::UnaryMinus';
use SPVM 'TestCase::Operator::UnaryPlus';
use SPVM 'TestCase::Operator::Unsigned';
use SPVM 'TestCase::Operator::Warn';
use SPVM 'TestCase::Operator::Weaken';
use SPVM 'TestCase::PointForTest';
use SPVM 'TestCase::Point_3b';
use SPVM 'TestCase::Point_3d';
use SPVM 'TestCase::Point_3f';
use SPVM 'TestCase::Point_3i';
use SPVM 'TestCase::Point_3l';
use SPVM 'TestCase::Point_3s';
use SPVM 'TestCase::Pointer';
use SPVM 'TestCase::PointerChild';
use SPVM 'TestCase::PointerEmpty';
use SPVM 'TestCase::Precedence';
use SPVM 'TestCase::PrecompileClassAttribute';
use SPVM 'TestCase::Private';
use SPVM 'TestCase::Resource::Mylib1';
use SPVM 'TestCase::Resource::Mylib2';
use SPVM 'TestCase::Scope';
use SPVM 'TestCase::Simple';
use SPVM 'TestCase::SimpleChild';
use SPVM 'TestCase::SimpleChildOfChild';
use SPVM 'TestCase::Statement::For';
use SPVM 'TestCase::Statement::If';
use SPVM 'TestCase::Statement::IfRequire';
use SPVM 'TestCase::Statement::Return';
use SPVM 'TestCase::Statement::Switch';
use SPVM 'TestCase::Statement::Unless';
use SPVM 'TestCase::Statement::UseInMethod';
use SPVM 'TestCase::Statement::While';
use SPVM 'TestCase::SymbolName_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_';
use SPVM 'TestCase::ThreadSafe';
use SPVM 'TestCase::UseResource';
use SPVM 'TestCase::UseResource::Basic';
use SPVM 'TestCase::UseResource::Mylib1';
use SPVM 'TestCase::UseResource::Mylib2';
use SPVM 'TestCase::Util::Node';
use SPVM 'TestCase::Util::Thread';
use SPVM 'TestCase::Util::Thread::ID';
use SPVM 'TestCase::Util::Thread::ThisThread';

=cut

copy_dlls_from_build_dir_to_lib($ENV{SPVM_BUILD_DIR});

sub copy_dlls_from_build_dir_to_lib {
  my ($build_dir) = @_;
  
  # (Comment: Use absolute path to ensure regex matches correctly)
  my $work_lib_dir = File::Spec->rel2abs("$build_dir/work/lib");
  return unless -d $work_lib_dir;

  my $script_lib_dir = "$FindBin::Bin/lib";
  my $dlext = $Config{dlext};

  find(sub {
    if (/\.$dlext$/) {
      my $src_file = File::Spec->rel2abs($File::Find::name);
      
      # (Comment: More robust way to get relative path)
      my $rel_path = $src_file;
      $rel_path =~ s|^\Q$work_lib_dir\E[/\\ ]*||; # (Comment: Support both / and \)
      
      my $dest_file = "$script_lib_dir/$rel_path";
      
      # (Comment: Create destination directory before copy)
      my $dest_dir = dirname($dest_file);
      unless (-d $dest_dir) {
        mkpath($dest_dir) or die "Can't mkpath $dest_dir: $!";
      }
      
      copy($src_file, $dest_file) or die "Can't copy $src_file to $dest_file: $!";
    }
  }, $work_lib_dir);
}

