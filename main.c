/*
 * main.c
 *
 *  Created on: 12/07/2022 (dd/mm/yyyy)
 *      Author: Helo_P
 */
#include "watchdog.h"
#include "math.h"
#include "compute_pi.h"

static uint32_t iterationCount = 3999999999;

int main (void){
	Watchdog * this = Watchdog_construct((uint32_t)2,(WatchdogCallback)abortComputePi);
	Watchdog_start(this);
	startComputePi(iterationCount);
	waitEndOfComputeThread();
	abortComputePi();
	Watchdog_destroy(this);

	return 0;
}
