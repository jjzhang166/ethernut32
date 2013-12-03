#ifndef __TIME_H
#define __TIME_H

/*
 * Copyright (C) 2001-2003 by egnite Software GmbH. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * For additional information see http://www.ethernut.de/
 *
 */

/*!
 * \file time.h
 * \brief Standard C time handling functions.
 */
#include <compiler.h>
#include <sys/types.h>

/*!
 * \addtogroup xgCrtTime
 * @{
 */


/*!
 * \brief Type definition for struct _tm
 */
typedef struct _tm tm;

/*!
 * \brief structure to store a date/time value.
 *
 * The structure tm stores a complete date and time combination. The granularity
 * is one second.
 *
 * \note The range of \b tm_mon is from 0 (January) to 11 (December).\n
 *       \b tm_year holds the year since 1900, for example value 103 means year 2003.
 */
struct _tm {
    int tm_sec;                 /*!< \brief seconds after the minute - [0,59] */
    int tm_min;                 /*!< \brief minutes after the hour - [0,59] */
    int tm_hour;                /*!< \brief hours since midnight - [0,23] */
    int tm_mday;                /*!< \brief day of the month - [1,31] */
    int tm_mon;                 /*!< \brief months since January - [0,11] */
    int tm_year;                /*!< \brief years since 1900 */
    int tm_wday;                /*!< \brief days since Sunday - [0,6] */
    int tm_yday;                /*!< \brief days since January 1 - [0,365] */
    int tm_isdst;               /*!< \brief daylight savings time flag */
};

/*!
 * \typedef long time_t
 * \brief Serial date/time. Holds number of seconds after January 1st, 1970.
 */

// time_t is defind on __APPLE__ and __CYGWIN, but not on __linux__ or on embedded systems
#if !defined(__APPLE__) && !defined(__CYGWIN__)
typedef long time_t;
#endif



time_t time(time_t * timer);
int gmtime_r(const time_t * timer, tm * theTime);
tm *gmtime(const time_t * timer);
int localtime_r(const time_t * timer, tm * theTime);
tm *localtime(const time_t * timer);

int stime(time_t * timer);
time_t mktime(tm * timeptr);
time_t _mkgmtime(tm * timeptr);

/*!
 * \brief Offset of the system time compared to epoc
 *
 * Used to calculate current time from the system run-time.
 */
extern struct timeval epo_offs;

/*!
 * \brief Used to control daylight conversions.
 *
 * Assign a nonzero value to enable daylight conversions. If enabled
 * the hour part of time values is adjusted if we are in daylight saving time.
 * Zero value to disable conversion.
 * Default is enabled.
 */
extern int _daylight;

/*!
 * \brief Defines your local timezone.
 *
 * Difference in seconds between universal coordinated time and local time.
 * This value is subtracted from the universal coordinated time to
 * calculate your local time. Default value is 5 * 60 * 60 = 18000,
 * which defines the time zone EST (GMT-5).
 *
 * \note Before using the time functions, set \b _timezone to your
 * local value.
 *
 */
extern long _timezone;

/*!
 * \brief Difference between standard and daylight savings time in seconds.
 *
 * This value is used to calculate the daylight savings time by subtracting this
 * value from the standard time. Unit is seconds.
 * Usually daylight savings time is one hour in advance to standard time, thus the default
 * value is -1 * 60 * 60 = -3600.
 */
extern long _dstbias;

/*@}*/
#endif
