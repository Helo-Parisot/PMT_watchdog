#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include "pmu_tools.h"

#define IS_ODD(n) ((n) & 1)
static double ComputedPiValue;
static bool StopCompute;
static pthread_t ComputeThread;
static uint32_t IterationCount;

/**
 * main function of computation thread
 */
static void *computePi(void *unused)
{
	uint32_t Rank;

	ComputedPiValue = 0.0;
	Rank = 0;

	do
	{
		if (IS_ODD(Rank))
			ComputedPiValue -= 4.0 / (2.0 * Rank + 1.0);
		else
			ComputedPiValue += 4.0 / (2.0 * Rank + 1.0);

		Rank++;
		// displays pi values sometimes, computation has to be fast
		if ((Rank % (1000 * 1000)) == 0)
		{
			printf("PI[@%u] : %f\n", Rank, ComputedPiValue);
		}
	} while (!StopCompute && (Rank < IterationCount));

	return NULL;
}

void startComputePi(uint32_t iterationCount)
{
	int returnCode;

	StopCompute = false;
	IterationCount = iterationCount;
	returnCode = pthread_create(&ComputeThread, NULL, &computePi, NULL);
	STOP_ON_ERROR(returnCode != 0);
}

void abortComputePi(void)
{
	StopCompute = true;
}

void waitEndOfComputeThread(void)
{
	int returnCode;

	returnCode = pthread_join(ComputeThread, NULL);
	STOP_ON_ERROR(returnCode != 0);

	printf("Final PI value is : %f\n", ComputedPiValue);
}
