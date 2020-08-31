#include "spvm_native.h"

#include <stdio.h>
#include <opencv2/opencv.hpp>


extern "C" {

using namespace cv;

int32_t SPNATIVE__MyOpenCVResize__resize(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* sv_file = stack[0].oval;
  const char* file = env->get_elems_byte(sv_file);
  
  Mat image;
  image = imread( file, 1 );

  if ( !image.data )
  {
      printf("No image data \n");
      return -1;
  }
  namedWindow("Display Image", WINDOW_AUTOSIZE );
  imshow("Display Image", image);

  waitKey(0);
  
  return SPVM_SUCCESS;
}

}
