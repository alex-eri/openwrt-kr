#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/OOLITEKROKS
	NAME:=OOLITEKROKS
	PACKAGES:=kmod-usb-core kmod-usb2  kmod-ledtrig-usbdev
endef


define Profile/OOLITEKROKS/Description
	Package set optimized for the OOLITE KROKS.
endef
$(eval $(call Profile,OOLITEKROKS))

