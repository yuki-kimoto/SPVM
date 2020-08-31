use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyOpenCVResize';

# Initialize SPVM

my $image_file = "$FindBin::Bin/linux-pengin.png";

my $image_resize_file = "$FindBin::Bin/linux-pengin-resize.png";

MyOpenCVResize->resize($image_file);

=head1 Eigen installation

=head2 Ubuntu 18 OpenCV installation

  sudo apt install -y libopencv-dev
