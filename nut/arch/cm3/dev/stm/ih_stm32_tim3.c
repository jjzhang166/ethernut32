/*
 * Copyright (C) 2010 by Ulrich Prinz (uprinz2@netscape.net)
 * Copyright (C) 2010 by Rittal GmbH & Co. KG. All rights reserved.
 *
 * All rights reserved.
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
 */

/*
 * \verbatim
 * $Id$
 * \endverbatim
 */

#include <arch/cm3.h>
#include <dev/irqreg.h>

#include <arch/cm3/stm/stm32xxxx.h>

#ifndef NUT_IRQPRI_TIM3
#define NUT_IRQPRI_TIM3  4
#endif

#define THIS_SIG    sig_TIM3
#define THIS_IRQn   TIM3_IRQn
#define THIS_IRQPRI NUT_IRQPRI_TIM3
#define THIS_ENTRY  TIM3Entry

static int TimInterruptCtl(int cmd, void *param);

IRQ_HANDLER THIS_SIG = {
#ifdef NUT_PERFMON
    0,                  /* Interrupt counter, ir_count. */
#endif
    NULL,               /* Passed argument, ir_arg. */
    NULL,               /* Handler subroutine, ir_handler. */
    TimInterruptCtl       /* Interrupt control, ir_ctl. */
};

/*!
 * \brief TIM3 interrupt entry.
 */
static void THIS_ENTRY(void *arg)
{
#ifdef NUT_PERFMON
    THIS_SIG.ir_count++;
#endif
    if (THIS_SIG.ir_handler) {
        (THIS_SIG.ir_handler) (THIS_SIG.ir_arg);
    }
}

#include "ih_stm32_tim.c"
