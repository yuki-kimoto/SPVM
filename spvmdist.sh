#!/bin/sh

      # Create SPVM module
      export SPVM_MODULE_NAME=$1
      export SPVM_MODULE_NAME_DIR=$(echo $SPVM_MODULE_NAME | perl -p -e 's/::/-/g')
      h2xs -X "SPVM::$SPVM_MODULE_NAME"
      spvmgenlib -f --module-dir "SPVM-$SPVM_MODULE_NAME_DIR/lib/SPVM" --native-language c $SPVM_MODULE_NAME
      
      # Add the content of make to Makefile.PL
      perl -e '
      use strict;
      use warnings;
      
      my $class_name = shift;
      print <<EOS
sub MY::postamble {
  
  use SPVM::Builder::Util::API;
  
  my \$make_rule = "";
  
  # Native compile make rule
  \$make_rule .= SPVM::Builder::Util::API::create_make_rule_native("$class_name");

  # Native compile make rule
  \$make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile("$class_name");
  
  return \$make_rule;
}
EOS
' $SPVM_MODULE_NAME >> "SPVM-$SPVM_MODULE_NAME_DIR/Makefile.PL"

