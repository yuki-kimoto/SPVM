use strict;
use warnings;

use Test::More;

use SPVM::Dist;

# Exception
{
  {
    my $dist = SPVM::Dist->new(
      basic_type_name => '',
    );
    
    eval { $dist->generate_dist };
    like($@, qr/The basic type name must be specified/);
  }

  {
    my $dist = SPVM::Dist->new(
      basic_type_name => 'Foo-Bar',
    );
    
    eval { $dist->generate_dist };
    like($@, qr/The basic type name cannnot contain \"-\"/);
  }
}

done_testing;
