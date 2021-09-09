#include "spvm_native.h"
#include<stdio.h>
#include<gsl/gsl_statistics.h>

#define LEN 6

int32_t SPNATIVE__MyGSL__stat(SPVM_ENV* env, SPVM_VALUE* stack) {
  double data[LEN] = {10.5, 18.2, 10.3, 15.4, 16.2, 18.3};

  double max = gsl_stats_max( data, 1, LEN );
  double min = gsl_stats_min( data, 1, LEN );
  double mean = gsl_stats_mean( data, 1, LEN );
  double sd = gsl_stats_sd( data, 1, LEN );

  printf( "max: \t%f \n", max );
  printf( "min: \t%f \n", min );
  printf( "mean: \t%f \n", mean);
  printf( "sd: \t%f \n", sd );

  return 0;
}
