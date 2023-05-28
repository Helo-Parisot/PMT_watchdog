#ifndef CALCUL_PI_H_
#define CALCUL_PI_H_

#include <stdint.h>

/**
 * Starts a thread that will compute pi
 *
 * @param iterationCount number of computation iterations
 */
extern void startComputePi(uint32_t iterationCount);

/**
 * Tells the thread to stop computation
 */
extern void abortComputePi(void);

/**
 * Waits the thread's termination
 */
extern void waitEndOfComputeThread (void);

#endif /* CALCUL_PI_H_ */
