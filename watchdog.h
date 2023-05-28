
#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <stdint.h>

/**
 * The watchdog structure
 */
typedef struct Watchdog_t Watchdog;

/**
 * Function that will be called by the watchdog
 *
 * @param this the watchdog which have called this function
 */
typedef void (*WatchdogCallback)(Watchdog *this);

/**
 * Watchdog's constructor.
 *
 * @param delay expressed in microseconds
 * @param callback function to be called at expiration
 */
extern Watchdog *Watchdog_construct(uint32_t delay, WatchdogCallback callback);

/**
 * Arms the watchdog.
 *
 * @param this watchdog's instance
 */
extern void Watchdog_start(Watchdog *this);

/**
 * Disarms the watchdog.
 *
 * @param this watchdog's instance
 */
extern void Watchdog_cancel(Watchdog *this);

/**
 * watchdog's destructor
 *
 * @param this watchdog's instance
 */
extern void Watchdog_destroy(Watchdog *this);

#endif /* WATCHDOG_H_ */
