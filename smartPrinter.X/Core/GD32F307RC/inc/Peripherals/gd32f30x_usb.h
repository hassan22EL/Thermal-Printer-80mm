/*
 * gd32f30x_usb.h
 *
 *  Created on: Jul 4, 2023
 *      Author: hassa
 */

#ifndef INC_PERIPHERALS_GD32F30X_USB_H_
#define INC_PERIPHERALS_GD32F30X_USB_H_

#include <gd32f30x.h>


/*!
 \brief      configure USB clock
 \param[in]  none
 \param[out] none
 \retval     none
 */
void usb_rcu_config ( void) ;
/*!
 \brief      configure USB interrupt
 \param[in]  none
 \param[out] none
 \retval     none
 */
void usb_intr_config ( void) ;



#endif /* INC_PERIPHERALS_GD32F30X_USB_H_ */
