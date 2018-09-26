#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "vol.h"

#define TABLE_SIZE (1<<16)
// Function to scale a sound sample using a volume_factor
// in the range of 0.00 to 1.00.
static inline int16_t scale_sample(int16_t sample, float volume_factor) {
	return (int16_t) (volume_factor * (float) sample);
}

int main() {

	int16_t* precomputed_table = malloc(TABLE_SIZE);
	if (!precomputed_table) {
		fprintf(stderr, "couldn't allocate precomputed table\n");
		return 1;
	}

	printf("TABLE_SIZE= %d\n", TABLE_SIZE);
	// Calculate precomputed values
	for(int i = 0; i < TABLE_SIZE; ++i) {
		precomputed_table[i] = scale_sample(i, 0.75);
	}

	// Allocate memory for large in and out arrays
	int16_t*	in;
	int16_t*	out;
	in = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	out = (int16_t*) calloc(SAMPLES, sizeof(int16_t));

	int		x;
	int		ttl;

	// Seed the pseudo-random number generator
	srand(-1);

	// Fill the array with random data
	for (x = 0; x < SAMPLES; x++) {
		in[x] = (rand()%65536)-32768;
	}

	// ######################################
	// This is the interesting part!
	// Scale the volume of all of the samples
	for (x = 0; x < SAMPLES; x++) {
		//int16_t current_sample = in[x];
		//printf("accessing table[%d]\n", current_sample + 32768);
		out[x] = 0; //precomputed_table[current_sample + 32768]; 
	}
	// ######################################

	// Sum up the data
	for (x = 0; x < SAMPLES; x++) {
		ttl = (ttl+out[x])%1000;
	}

	// Print the sum
	printf("Result: %d\n", ttl);

	return 0;

}

