#include "spvm_native.h"

#include <stdio.h>
#include <opencv2/opencv.hpp>

extern "C" {

static const char* FILE_NAME = "MyOpenCVResize.c";

int32_t SPVM__MyOpenCVResize__resize(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  using namespace cv;
  
  void* sv_in_file = stack[0].oval;
  const char* in_file = (const char*)env->get_elems_byte(env, sv_in_file);
  
  void* sv_out_file = stack[1].oval;
  const char* out_file = (const char*)env->get_elems_byte(env, sv_out_file);
  
  Mat image;
  image = imread( in_file, 1 );
  
  if (!image.data) {
    return env->die_v2(env, stack, "The imread function(opencv2/opencv.hpp) failed.", __func__, FILE_NAME, __LINE__);
  }
  
  resize(image, image, cv::Size(), 0.5, 0.5);
  
  imwrite(out_file, image);
  
  return 0;
}

}
