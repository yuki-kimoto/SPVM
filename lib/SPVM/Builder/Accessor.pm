package SPVM::Builder::Accessor;

# SPVM::Builder::Accessor is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;

use Exporter 'import';
our @EXPORT_OK = qw(has);

sub has {
  my ($fields) = @_;
  
  # Get caller package name
  my $caller = caller;

  for my $field (@$fields) {
    # Generate accessor with method chaining
    my $code = <<"EOS";
package $caller;
sub $field {
  my \$self = shift;
  if (\@_) {
    \$self->{$field} = shift;
    return \$self;
  }
  return \$self->{$field};
}
EOS

    eval $code;
    
    # Report error immediately
    if ($@) {
      die "Error generating accessor '$field' for class '$caller': $@";
    }
  }
}

