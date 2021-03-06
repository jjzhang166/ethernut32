/*
 * Copyright 2010 by egnite GmbH
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
 * \file arch/arm/board/morphoq1.c
 * \brief Morphoq 1 board initialization.
 *
 * \verbatim
 * $Id$
 * \endverbatim
 */

#include <toolchain.h>

#define PHY_STRAP_AD0       _BV(PB7_ERXER_A)
#define PHY_STRAP_AD1       _BV(PB17_ERXCK_A)
#define PHY_STRAP_AD2       _BV(PB14_ERX3_A)

#define PHY_STRAP_MODE0     _BV(PB5_ERX0_A)
#define PHY_STRAP_MODE1     _BV(PB6_ERX1_A)
#define PHY_STRAP_MODE2     _BV(PB16_ECOL_A)

#define PHY_STRAP_RMIISEL   _BV(PB13_ERX2_A)

#define PHY_STRAP   ( \
    PHY_STRAP_AD0 | PHY_STRAP_AD1 | PHY_STRAP_AD2 | \
    PHY_STRAP_MODE0 | PHY_STRAP_MODE1 | PHY_STRAP_MODE2 | \
    PHY_STRAP_RMIISEL )

/*!
 * \brief Delay loop.
 *
 * \param Number of loops to execute.
 */
static void MorphoqDelay(int n)
{
    int l;

    for (l = 0; l < n; l++) {
        _NOP();
    }
}

/*!
 * \brief Enable peripheral clocks.
 */
static void MorphoqClockInit(void)
{
    outr(PMC_PCER, _BV(PIOA_ID));
    outr(PMC_PCER, _BV(PIOB_ID));
    outr(PMC_PCER, _BV(EMAC_ID));
}

/*!
 * \brief Toggle external hardware reset line.
 */
static void MorphoqReset(void)
{
    unsigned int mr;

    /* Save initial configuration. */
    mr = inr(RSTC_MR) & ~RSTC_KEY_MSK;
    /* Set reset pulse length to 250us, disable user reset. */
    outr(RSTC_MR, RSTC_KEY | (2 << RSTC_ERSTL_LSB));
    /* Invoke external reset. */
    outr(RSTC_CR, RSTC_KEY | RSTC_EXTRST);
    /* If we have 10k/100n RC, we need to wait 25us (1200 cycles)
    ** for NRST becoming low. */
    MorphoqDelay(250);
    /* Wait until reset pin is released. */
    while ((inr(RSTC_SR) & RSTC_NRSTL) == 0);
    /* Due to the RC filter, the pin is rising very slowly. */
    MorphoqDelay(25000);
    /* Restore initial configuration. */
    outr(RSTC_MR, RSTC_KEY | mr);
}

/*!
 * \brief Initialize the PHY hardware.
 *
 * On startup all GPIO pull-ups on the SAM7X are enabled by default
 * and may fight against internal pull-downs of the LAN8710. Here
 * we switch off all pull-ups connected to LAN8710 strap pins and
 * issue an external reset.
 */
static void MorphoqPhyInit(void)
{
    /* The PHY needs 25ms for powering up. */
    MorphoqDelay(250000);
    /* Disable pull-ups. */
    outr(PIOB_PUDR, PHY_STRAP);
    outr(PIOB_ODR, PHY_STRAP);
    outr(PIOB_PER, PHY_STRAP);
    /* Toggle reset line. */
    MorphoqReset();
    /* Re-enable the pull-ups. */
    outr(PIOB_PUER, PHY_STRAP);
}

/*!
 * \brief Early Morphoq 1 hardware initialization.
 *
 * This routine is called during system initalization.
 */
void NutBoardInit(void)
{
    MorphoqClockInit();
    MorphoqPhyInit();
}
