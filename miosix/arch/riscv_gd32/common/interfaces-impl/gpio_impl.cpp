/***************************************************************************
 *   Copyright (C) 2012 by Terraneo Federico                               *
 *   Copyright (C) 2019 by Cremonese Filippo, Picca Niccolò                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include "gpio_impl.h"

namespace miosix {

void GpioBase::modeImpl(unsigned int p, unsigned char n, Mode::Mode_ m)
{
    if(n >= 8)
    {
        GPIO_CTL1(p) &= ~(0xf << (4 * (n - 8)));
        GPIO_CTL1(p) |= (m & 0xf) << (4 * (n - 8));
    } else {
        GPIO_CTL0(p) &= ~(0xf << (4 * n));
        GPIO_CTL0(p) |= (m & 0xf) << (4 * n);
    }

    // if the GPIO_OCTL bit is set, actually set it
    if(m & 0x10) GPIO_OCTL(p) |= 1 << n;
    else         GPIO_OCTL(p) &= ~(1 << n);
}

// Not needed in this architecture
void GpioBase::afImpl(unsigned int p, unsigned char n, unsigned char af) {}

} //namespace miosix
