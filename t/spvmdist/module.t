use strict;
use warnings;

use Test::More;

use SPVM::Dist;

# Exception
{
  {
    my $dist = SPVM::Dist->new(
      class_name => '',
    );
    
    eval { $dist->generate_dist };
    like($@, qr/The class name must be specified/);
  }

  {
    my $dist = SPVM::Dist->new(
      class_name => 'Foo-Bar',
    );
    
    eval { $dist->generate_dist };
    like($@, qr/The class name can't contain \"-\"/);
  }
}

done_testing;
