#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/KRATP1A
	NAME:=KR-ATP-1A
	PACKAGES:=kmod-usb-core kmod-usb2 kmod-ledtrig-usbdev
endef


define Profile/KRATP1A/Description
	Package set optimized for the KROKS KR-ATP-1A.
endef
$(eval $(call Profile,KRATP1A))

