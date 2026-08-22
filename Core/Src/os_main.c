#include "ahura.h"
#include "usbd_hid.h"
#include "usb_device.h"

#define HID_BUF_SIZE    4

void os_main(void)
{
    const int8_t x = 50;
    const int8_t y = 50;
    uint8_t hid_buffer[][HID_BUF_SIZE] = {
        { 0, 0, y, 0 },
        { 0, 0, -y, 0 },
        { 0, x, 0, 0 },
        { 0, -x, 0, 0 },
        { 0, 0, -y, 0 },
        { 0, 0, y, 0 },
        { 0, -x, 0, 0 },
        { 0, x, 0, 0 }
    };
    uint8_t i = 0;

    while (1)
    {
        os_delay_ms(500);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        // format: [7..3]  [2..0]       [7..0]         [7..0]        [7..0]
        //         Empty  Buttons   X-axis(signed) Y axis(signed) Wheel(signed)
        USBD_HID_SendReport(&hUsbDeviceFS,
                            &hid_buffer[++i % (sizeof(hid_buffer) / HID_BUF_SIZE)][0],
                            HID_BUF_SIZE);
    }
}
