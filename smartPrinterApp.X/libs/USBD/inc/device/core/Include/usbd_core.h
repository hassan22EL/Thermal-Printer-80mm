

#ifndef __USBD_CORE_H
#define __USBD_CORE_H

#include "drv_usb_core.h"
#include "drv_usb_dev.h"

typedef enum
{
    USBD_OK = 0U,                           /*!< status OK */
    USBD_BUSY,                              /*!< status busy */
    USBD_FAIL,                              /*!< status fail */
} usbd_status;

enum _usbd_status
{
    USBD_DEFAULT    = 1U,                    /*!< default status */
    USBD_ADDRESSED  = 2U,                    /*!< address send status */
    USBD_CONFIGURED = 3U,                    /*!< configured status */
    USBD_SUSPENDED  = 4U                     /*!< suspended status */
};

/* static inline function definitions */

/*!
    \brief      set USB device address
    \param[in]  udev: pointer to USB core instance
    \param[in]  addr: device address to set
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_addr_set (usb_core_driver *udev, uint8_t addr)
{
    usb_devaddr_set(udev, addr);
}

/*!
    \brief      get the received data length
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation cur_status
*/
__STATIC_INLINE uint16_t usbd_rxcount_get (usb_core_driver *udev, uint8_t ep_num)
{
    return (uint16_t)udev->dev.transc_out[ep_num].xfer_count;
}

/* function declarations */
/* initializes the USB device-mode stack and load the class driver */
void usbd_init (usb_core_driver *udev, usb_core_enum core, usb_desc *desc, usb_class_core *class_core);
/* endpoint initialization */
uint32_t usbd_ep_setup (usb_core_driver *udev, const usb_desc_ep *ep_desc);
/* configure the endpoint when it is disabled */
uint32_t usbd_ep_clear (usb_core_driver *udev, uint8_t ep_addr);
/* endpoint prepare to receive data */
uint32_t usbd_ep_recev (usb_core_driver *udev, uint8_t ep_addr, uint8_t *pbuf, uint32_t len);
/* endpoint prepare to transmit data */
uint32_t usbd_ep_send (usb_core_driver *udev, uint8_t ep_addr, uint8_t *pbuf, uint32_t len);
/* set an endpoint to STALL status */
uint32_t usbd_ep_stall (usb_core_driver *udev, uint8_t ep_addr);
/* clear endpoint STALLed status */
uint32_t usbd_ep_stall_clear (usb_core_driver *udev, uint8_t ep_addr);
/* flush the endpoint FIFOs */
uint32_t usbd_fifo_flush (usb_core_driver *udev, uint8_t ep_addr);
/* device connect */
void usbd_connect (usb_core_driver *udev);
/* device disconnect */
void usbd_disconnect (usb_core_driver *udev);

#endif /* __USBD_CORE_H */
