/*
 * type.h
 *
 *  Created on: Jul 2, 2023
 *      Author: hassa
 */

#ifndef INC_PERIPHERALS_TYPE_H_
#define INC_PERIPHERALS_TYPE_H_
#include <stdint.h>
/*
 * ******************************************************************************
 *                        Timer Data Type                                *
 * ******************************************************************************
 */
typedef uint32_t tick_t;
typedef uint32_t micros_t;
typedef uint32_t millis_t;
typedef uint32_t seconds_t;




/*
 * ******************************************************************************
 *                                User State                                    *
 * ******************************************************************************
 * Status code that may be returned by shell commands and protocol
 * implementations.
 * @note Any change to these status codes and the corresponding
 * message strings is strictly forbidden. New codes can be added,
 * however, but make sure that any message string tables are updated
 * at the same time.
 */
enum status_code {
    STATUS_OK = 0, //!< Success
    ERR_IO_ERROR = -1, //!< I/O error
    ERR_FLUSHED = -2, //!< Request flushed from queue
    ERR_TIMEOUT = -3, //!< Operation timed out
    ERR_BAD_DATA = -4, //!< Data integrity check failed
    ERR_PROTOCOL = -5, //!< Protocol error
    ERR_UNSUPPORTED_DEV = -6, //!< Unsupported device
    ERR_NO_MEMORY = -7, //!< Insufficient memory
    ERR_INVALID_ARG = -8, //!< Invalid argument
    ERR_BAD_ADDRESS = -9, //!< Bad address
    ERR_BUSY = -10, //!< Resource is busy
    ERR_BAD_FORMAT = -11, //!< Data format not recognized
    ERR_NO_TIMER = -12, //!< No timer available
    ERR_TIMER_ALREADY_RUNNING = -13, //!< Timer already running
    ERR_TIMER_NOT_RUNNING = -14, //!< Timer not running

    /**
     * @brief Operation in progress
     *
     * This status code is for driver-internal use when an operation
     * is currently being performed.
     * @note Drivers should never return this status code to any
     * callers. It is strictly for internal use.
     */
    OPERATION_IN_PROGRESS = -128,
};






#endif /* INC_PERIPHERALS_TYPE_H_ */
