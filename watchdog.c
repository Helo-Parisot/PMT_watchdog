
#include "watchdog.h"
#include "pmu_tools.h"
#include <malloc.h>
#include <signal.h>
#include <time.h>
#include <errno.h>



struct Watchdog_t
{
	timer_t timerid; /* TODO: POSIX timer *//**< POSIX Timer*/
	uint32_t myDelay; /**< configured delay */
	WatchdogCallback myCallback; /**< function to be called at delay expiration */
};

/**
 * Calls the watchdog callback when the delay of the timer expires
 *
 * @param handlerParam must be the watchdog reference
 */
static void mainHandler (/* TODO: set the right type */ union sigval handlerParam)
{
	Watchdog *theWatchdog = handlerParam.sival_ptr; /* TODO: get the timer's reference */;

	theWatchdog->myCallback (theWatchdog);
}

Watchdog *Watchdog_construct (uint32_t thisDelay, WatchdogCallback callback)
{
	Watchdog *result;
	int error_code;
	struct sigevent sev;
	timer_t timerid;

	// allocates and initializes the watchdog's attributes
	result = (Watchdog *)malloc (sizeof(Watchdog));
	STOP_ON_ERROR (result == NULL);
	result->myDelay = thisDelay;
	result->myCallback = callback;

	// creates the POSIX timer

	union sigval sig_value;
	sig_value.sival_ptr=result;

	sev.sigev_notify=SIGEV_THREAD;
	sev.sigev_signo= 0;
	sev.sigev_value= sig_value;
	sev.sigev_notify_function=&mainHandler;
	sev.sigev_notify_attributes=0;

	error_code = timer_create(CLOCK_THREAD_CPUTIME_ID, &sev, &timerid);
	STOP_ON_ERROR(error_code < 0);

	return result;
}

void Watchdog_start (Watchdog *this)
{
	int error_code;

	// starts the POSIX timer
	struct timespec new_value_1;
		new_value_1.tv_sec = 0;        		// Seconds
		new_value_1.tv_nsec = 0;            //Nanoseconds

		struct timespec new_value_2;
		new_value_2.tv_sec = this->myDelay;    //Seconds
		new_value_2.tv_nsec = 0;               //Nanoseconds

		struct itimerspec new_ivalue;
		new_ivalue.it_interval = new_value_1;  //Timer interval
		new_ivalue.it_value = new_value_2;     //Initial expiration
		errno = 0;
		error_code = timer_settime(this->timerid,0,&new_ivalue,NULL);
		STOP_ON_ERROR(error_code < 0);
}

void Watchdog_cancel (Watchdog *this)
{
	int error_code;

	// disarms the POSIX timer
	struct timespec new_value_1;
		new_value_1.tv_sec = 0;        		// Seconds
		new_value_1.tv_nsec = 0;            //Nanoseconds

		struct timespec new_value_2;
		new_value_2.tv_sec = 0; 			//Seconds
		new_value_2.tv_nsec = 0;            //Nanoseconds

		struct itimerspec new_ivalue;
		new_ivalue.it_interval = new_value_1;  //Timer interval
		new_ivalue.it_value = new_value_2;     //Initial expiration

		error_code = timer_settime(this->timerid,0,&new_ivalue,NULL);
		STOP_ON_ERROR(error_code < 0);
}

void Watchdog_destroy (Watchdog *this)
{
	int error_code;

	// disarms and deletes the POSIX timer
	error_code = timer_delete(this->timerid);
	STOP_ON_ERROR(error_code < 0);
	// then we can free memory
	free (this);
}
