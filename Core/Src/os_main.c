/**
 * @file os_main_template.c
 * @brief Template for the application's default task body.
 *
 * NOT part of the kernel build (like os_cb_template.c): copy this file into the application source
 * tree as os_main.c, add it to the APPLICATION build, and write the application's own code inside
 * os_main(). Its prototype is already in ahura.h.
 *
 * The "_cb" suffix used elsewhere is reserved for callbacks the kernel queries for platform
 * behaviour; os_main() is different in kind - it is where the application's code runs - even
 * though it is supplied the same way.
 *
 * The task itself is created by os_init(), unconditionally except in self-test builds, and sized
 * by OS_CONFIG_MAIN_TASK_STACK_SIZE / OS_CONFIG_MAIN_TASK_PRIORITY. Nothing to call from main().
 *
 * @copyright (c) 2026 Ahura Project Contributors
 *            SPDX-License-Identifier: MIT
 *            See LICENSE.md in the project root for the full license text.
 */

/*
 * ***********************************************************************************************************
 * Includes
 * ***********************************************************************************************************
*/

#include "ahura.h"
#include "usbd_hid.h"
#include "usb_device.h"

#define HID_BUF_SIZE    4

/*
 * ***********************************************************************************************************
 * Public function implementations
 * ***********************************************************************************************************
*/

/******************************************************************************************************/
/**
 * @brief Default application task body: runs once os_start() hands control to task context.
 *        Replace the body with the application's own code.
 *
 * @return None.
 */
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
