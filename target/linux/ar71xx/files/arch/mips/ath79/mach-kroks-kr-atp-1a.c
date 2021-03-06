/*
 *  Oolite board support
 *
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/gpio.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-wmac.h"
#include "machtypes.h"
#include "dev-usb.h"


#define KROKS_KR_ATP_1A_GPIO_BTN_RESET	11
#define KROKS_KR_ATP_1A_GPIO_LED_LAN1	12
#define KROKS_KR_ATP_1A_GPIO_LED_LAN2	7
#define KROKS_KR_ATP_1A_GPIO_LED_USB	24

#define KROKS_KR_ATP_1A_KEYS_POLL_INTERVAL	20	/* msecs */
#define KROKS_KR_ATP_1A_KEYS_DEBOUNCE_INTERVAL (3 * KROKS_KR_ATP_1A_KEYS_POLL_INTERVAL)

static const char *kroks_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data kroks_flash_data = {
	.part_probes	= kroks_part_probes,
};

static struct gpio_led kroks_leds_gpio[] __initdata = {
	{
		.name		= "kroks:red:lan1",
		.gpio		= KROKS_KR_ATP_1A_GPIO_LED_LAN1,
		.active_low	= 0,
	},
  	{
		.name		= "kroks:red:lan2",
		.gpio		= KROKS_KR_ATP_1A_GPIO_LED_LAN2,
		.active_low	= 0,
	},
  	{
		.name		= "kroks:sw:usb",
		.gpio		= KROKS_KR_ATP_1A_GPIO_LED_USB,
		.active_low	= 1,
	},
  /*{
		.name		= "oolite:red:system",
		.gpio		= KROKS_KR_ATP_1A_GPIO_LED_SYSTEM,
		.active_low	= 1,
	},*/
};

static struct gpio_keys_button kroks_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = KROKS_KR_ATP_1A_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= KROKS_KR_ATP_1A_GPIO_BTN_RESET,
		.active_low	= 0,
	},
};

static void __init kroks_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(kroks_leds_gpio),
				 kroks_leds_gpio);

	ath79_register_gpio_keys_polled(-1, KROKS_KR_ATP_1A_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(kroks_gpio_keys),
					kroks_gpio_keys);

	ath79_register_usb();

	ath79_register_m25p80(&kroks_flash_data);
	ath79_init_mac(ath79_eth0_data.mac_addr, mac, 1);
	ath79_init_mac(ath79_eth1_data.mac_addr, mac, -1);

	ath79_register_mdio(0, 0x0);
	ath79_register_eth(1);
	//ath79_register_eth(0);

	ath79_register_wmac(ee, mac);
}

MIPS_MACHINE(ATH79_MACH_KROKS_KR_ATP_1A, "KROKS-KR-ATP-1A",
	     "KR-ATP-1A", kroks_setup);
