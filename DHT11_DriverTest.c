/* ========================================================================== */
/*                                                                            */
/*   DHT11_DriverTest.c                                                       */
/*   (c) 2012 Author  Brian Pundyke                                           */
/*                                                                            */
/*   Description                                                              */
/*   Example code using adaFruit DHT11/12 sensor library for Pi               */                       
/*   compile with g++ common_dht_read.cpp pi_2_mmio.cpp pi_2_dht_read.cpp DHT11_DriverTest.c -o dht11Test
/*                                                                            */
/*                                                                            */
/* ========================================================================== */

#include "pi_2_dht_read.h"
#include <stdio.h>
#include <time.h>

#define DHT11_SENSOR_PIN 4
#define SENSOR_READ_FREQUENCY 3000  // DHT11 cannot be read more frequently than every 2 secs

unsigned long start_time_millis;
float humidity_Reading = 0.0;
float temp_Reading = 0.0;
int _result = 0;

unsigned long current_time_millis (void)
{
    struct timespec tSpec;
    
    //posix 
    clock_gettime(CLOCK_MONOTONIC, &tSpec);
    unsigned long milliseconds = tSpec.tv_sec*1000 + tSpec.tv_nsec/1000000; // caculate milliseconds
    return milliseconds;
}

int main(void)
  {
   start_time_millis = current_time_millis ();
    while (1)  {
        unsigned long time_now_millis = current_time_millis();
        if (time_now_millis > (start_time_millis + SENSOR_READ_FREQUENCY)) {
          _result = pi_2_dht_read(DHT11, DHT11_SENSOR_PIN, &humidity_Reading, &temp_Reading);
      
          if (_result == DHT_SUCCESS) {
              printf("H = %2.1f    T = %2.1f\n", humidity_Reading, temp_Reading);
          } else {
              printf("Error = %d \n", _result);           
      }
    start_time_millis = current_time_millis();
    }
  }
return(0);
}
