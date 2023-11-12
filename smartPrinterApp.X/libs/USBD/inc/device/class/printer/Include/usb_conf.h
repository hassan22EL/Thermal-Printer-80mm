/*
 * usb_conf.h
 *
 *  Created on: Jul 9, 2023
 *      Author: hassa
 */

#ifndef DEVICE_CLASS_PRINTER_INCLUDE_USB_CONF_H_
#define DEVICE_CLASS_PRINTER_INCLUDE_USB_CONF_H_
#include <stdlib.h>
#include <gd32f30x.h>

#define  USE_USB_FS

/* USB Core and PHY interface configuration */

/****************** USB FS PHY CONFIGURATION *******************************
 *  The USB FS Core supports one on-chip Full Speed PHY.
 *  The USE_EMBEDDED_PHY symbol is defined in the project compiler preprocessor
 *  when FS core is used.
*******************************************************************************/

#ifdef USE_USB_FS
    #define USB_FS_CORE
#endif

/*******************************************************************************
 *                      FIFO Size Configuration in Device mode
 *
 *  (i) Receive data FIFO size = RAM for setup packets +
 *                   OUT endpoint control information +
 *                   data OUT packets + miscellaneous
 *      Space = ONE 32-bits words
 *      --> RAM for setup packets = 10 spaces
 *          (n is the nbr of CTRL EPs the device core supports)
 *      --> OUT EP CTRL info = 1 space
 *          (one space for status information written to the FIFO along with each
 *          received packet)
 *      --> Data OUT packets = (Largest Packet Size / 4) + 1 spaces
 *          (MINIMUM to receive packets)
 *      --> OR data OUT packets  = at least 2* (Largest Packet Size / 4) + 1 spaces
 *          (if high-bandwidth EP is enabled or multiple isochronous EPs)
 *      --> Miscellaneous = 1 space per OUT EP
 *          (one space for transfer complete status information also pushed to the
 *          FIFO with each endpoint's last packet)
 *
 *  (ii) MINIMUM RAM space required for each IN EP Tx FIFO = MAX packet size for
 *       that particular IN EP. More space allocated in the IN EP Tx FIFO results
 *       in a better performance on the USB and can hide latencies on the AHB.
 *
 *  (iii) TXn min size = 16 words. (n:Transmit FIFO index)
 *
 *  (iv) When a TxFIFO is not used, the Configuration should be as follows:
 *       case 1: n > m and Txn is not used (n,m:Transmit FIFO indexes)
 *       --> Txm can use the space allocated for Txn.
 *       case 2: n < m and Txn is not used (n,m:Transmit FIFO indexes)
 *       --> Txn should be configured with the minimum space of 16 words
 *
 *  (v) The FIFO is used optimally when used TxFIFOs are allocated in the top
 *      of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
*******************************************************************************/

/****************** USB OTG FS CONFIGURATION **********************************/
#ifdef USB_FS_CORE
    #define RX_FIFO_FS_SIZE                         128
    #define TX0_FIFO_FS_SIZE                        32
    #define TX1_FIFO_FS_SIZE                        32
    #define TX2_FIFO_FS_SIZE                        32
    #define TX3_FIFO_FS_SIZE                        32
#endif /* USB_FS_CORE */

#define USB_SOF_OUTPUT              1
#define USB_LOW_POWER               0

/****************** USB OTG MISC CONFIGURATION ********************************/
//#define VBUS_SENSING_ENABLED

/****************** USB OTG MODE CONFIGURATION ********************************/
//#define USE_HOST_MODE
#define USE_DEVICE_MODE
//#define USE_OTG_MODE

#ifndef USE_DEVICE_MODE
    #ifndef USE_HOST_MODE
        #error  "USE_DEVICE_MODE or USE_HOST_MODE should be defined!"
    #endif
#endif

#define __ALIGN_BEGIN
#define __ALIGN_END

/* __packed keyword used to decrease the data type alignment to 1-byte */
#if defined (__GNUC__)       /* GNU Compiler */
	#ifndef __packed
    	#define __packed __attribute__ ((__packed__))
	#endif
#elif defined (__TASKING__)    /* TASKING Compiler */
    #define __packed __unaligned
#endif /* __CC_ARM */


#ifdef USE_DEVICE_MODE

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
#endif



#endif /* DEVICE_CLASS_PRINTER_INCLUDE_USB_CONF_H_ */
