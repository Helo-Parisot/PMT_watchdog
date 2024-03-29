/*
 * pmu_tools.h
 *
 *  Created on: 13/07/2022 (dd/mm/yyyy)
 *      Author: Helo_P
 */

#ifndef PMU_TOOLS_H_
#define PMU_TOOLS_H_

#include <unistd.h>
#include <stdio.h>

/**
 * @def STOP_ON_ERROR
 *
 * @brief stops execution on error and outputs some useful
 * informations about the error.
 *
 * This macro is useful to evacuate error management for experimental
 * code (learning, feasibility, ...)
 *
 * @param error_condition should be true to mean there is an error, then
 * execution stops with error message, nothing is done if condition is false.
 *
 * @warning this macro should not be used in production code
 * nor in any code that can come to a production state as
 * this is a way to not manage errors. That's why you'll get
 * a preprocessor error if you define NDEBUG macro.
 */
#if !defined NDEBUG
#define STOP_ON_ERROR(error_condition) do { \
  if (error_condition) { \
    fprintf (stderr, "*** Error (%s) at %s:%d\nExiting\n", \
    #error_condition, __FILE__, __LINE__); \
    perror (""); \
    _exit (1); } \
  } while (0)
#else
#define STOP_ON_ERROR(error_condition) #error "STOP_ON_ERROR must not be used in release builds"
#endif

/**
 * @def trace
 *
 * Prints a debug trace message.
 *
 * This macro can be used as printf function, first argument is the
 * format string as subsequent arguments can be specified depending on
 * the format chose.
 *
 * Print out can be disable by defining NDEBUG macro.
 *
 * @param fmt format string, see #printf documentation
 */
#if !defined NDEBUG
#define trace(fmt, ...) do { \
	fprintf (stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, \
			__func__, ##__VA_ARGS__); \
	fflush (stderr); \
	} while (0)
#else
#define trace(fmt, ...)
#endif

/**
 * @def ARRAY_COUNT
 * Gives the size of an array regardless the size of each element
 *
 * @param array the array
 */
#define ARRAY_COUNT(array) ((sizeof (array))/sizeof(array[0]))

#endif /* PMU_TOOLS_H_ */
