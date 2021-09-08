use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::MyOpenCVResize';

# Initialize SPVM

my $image_in_file = "$FindBin::Bin/linux-pengin.png";

my $image_out_file = "$FindBin::Bin/linux-pengin-output.png";

SPVM::MyOpenCVResize->resize($image_in_file, $image_out_file);

=head1 OpenCV installation

=head2 Ubuntu 18 OpenCV installation

  sudo apt install -y libopencv-dev
