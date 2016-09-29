#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"
#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
#define SAMPLE_TIME 1
int loop=25;
int main(int argc, char const *argv[])
{
	struct timespec start = {0, 0};
	struct timespec end = {0, 0};

	if (argc < 2) return -1;

	int N = atoi(argv[1]);
	int i;
	double clock_time[loop];

	// Baseline
	for(i = 0; i < loop;i++) {
		clock_gettime(CLOCK_ID, &start);
		compute_pi_baseline(N);
		clock_gettime(CLOCK_ID, &end);
		clock_time[i] = (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
        }
	printf("%lf,", compute_ci(clock_time));
	printf("%lf,", compute_error(compute_pi_baseline(N)));

	// OpenMP with 2 threads
	for(i = 0; i < loop;i++) {
		clock_gettime(CLOCK_ID, &start);
		compute_pi_openmp(N, 2);
		clock_gettime(CLOCK_ID, &end);
		clock_time[i] = (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
	}
	printf("%lf,", compute_ci(clock_time));
	printf("%lf,", compute_error(compute_pi_openmp(N, 2)));

        // OpenMP with 4 threads
	for(i = 0; i < SAMPLE_TIME;i++) {
		clock_gettime(CLOCK_ID, &start);
		compute_pi_openmp(N, 4);
		clock_gettime(CLOCK_ID, &end);
		clock_time[i] = (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
	}
	printf("%lf,", compute_ci(clock_time));
	printf("%lf,", compute_error(compute_pi_openmp(N, 4)));

	// AVX SIMD
	for(i = 0; i < SAMPLE_TIME;i++) {
		clock_gettime(CLOCK_ID, &start);
		compute_pi_avx(N);
		clock_gettime(CLOCK_ID, &end);
		clock_time[i] = (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
	}
	printf("%lf,", compute_ci(clock_time));
	printf("%lf,", compute_error(compute_pi_avx(N)));

    // AVX SIMD + Loop unrolling
	for(i = 0; i < SAMPLE_TIME;i++) {
		clock_gettime(CLOCK_ID, &start);
		compute_pi_avx_unroll(N);
		clock_gettime(CLOCK_ID, &end);
		clock_time[i] = (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
	}
	printf("%lf,", compute_ci(clock_time));
	printf("%lf\n", compute_error(compute_pi_avx_unroll(N)));
    return 0;
}

double compute_ci(double time[]) {
    double mean = 0;
    double sd = 0;
    double lowerbound=0;
    double upperbound;
    double cTime[loop];
    double result = 0;
    int cTimeSize = 0;
    int i;
    for(i = 0; i < loop; i++) {
        mean += time[i];
    }
    mean = mean / loop;
    for(i = 0; i < loop; i++) {
        sd += (time[i] - mean) * (time[i] - mean);
    }
    sd = sqrt(sd/loop);
    lowerbound = mean - 2 * sd;
    upperbound = mean + 2 * sd;
    for(i = 0; i < loop; i++) {
        if(time[i]>= lowerbound && time[i] <= upperbound) {
            cTime[cTimeSize] = time[i];
            cTimeSize++;
        }
    }
    for(i = 0; i < cTimeSize; i++) {
        result += cTime[i];
    }
    result = result / cTimeSize;
    return result;
}

double compute_error(double Pi){
    Pi=fabs(Pi-M_PI)/M_PI;
    return Pi;
}
