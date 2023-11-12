/*
 * usbd_conf.h
 *
 *  Created on: Jul 9, 2023
 *      Author: hassa
 */

#ifndef DEVICE_CLASS_PRINTER_INCLUDE_USBD_CONF_H_
#define DEVICE_CLASS_PRINTER_INCLUDE_USBD_CONF_H_

#include <usb_conf.h>

/* USB configure exported defines */
#define USBD_CFG_MAX_NUM                    1U
#define USBD_ITF_MAX_NUM                    2U

#define CUSTOM_HID_INTERFACE                0x00U
#define CDC_COM_INTERFACE                   0x01U

#define USB_STR_DESC_MAX_SIZE               255U

/* endpoint used by the custom HID device */
#define CUSTOMHID_IN_EP                     EP_IN(1U)
#define CUSTOMHID_OUT_EP                    EP_OUT(1U)

/* endpoint used by the USB printer device */
#define PRINTER_IN_EP                       EP_IN(2U)
#define PRINTER_OUT_EP                      EP_OUT(2U)

#define USB_STRING_COUNT                    4U

#define CUSTOMHID_OUT_PACKET                2U
#define CUSTOMHID_IN_PACKET                 2U

#define PRINTER_IN_PACKET                   64U
#define PRINTER_OUT_PACKET                  64U

#endif /* DEVICE_CLASS_PRINTER_INCLUDE_USBD_CONF_H_ */
