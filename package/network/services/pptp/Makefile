#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pptp
PKG_VERSION:=1.7.1
PKG_RELEASE:=5

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=@SF/pptpclient
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/services/
PKG_MD5SUM:=b47735ba5d6d37dfdbccb85afc044ede
DL_DIR:=$(TOPDIR)/dl

include $(INCLUDE_DIR)/package.mk

define Package/pptp
  SECTION:=net
  CATEGORY:=Network
  TITLE:=PPTP client
  MAINTAINER:=Jo-Philipp Wich <xm@subsignal.org>
  URL:=http://pptpclient.sourceforge.net/
  DEPENDS:=+ppp +resolveip
endef

define Package/pptp/description
 This package contains a PPTP (Point-to-Point Tunneling Protocol) client.
endef

define Package/pptp/conffiles
/etc/ppp/options.pptp
endef

MAKE_FLAGS += OPTIMIZE="$(TARGET_CFLAGS)"

define Package/pptp/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pptp $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/ppp
	$(INSTALL_DATA) ./files/options.pptp $(1)/etc/ppp/
	$(INSTALL_DIR) $(1)/lib/netifd/proto/
	$(INSTALL_BIN) ./files/pptp.sh $(1)/lib/netifd/proto/
endef

$(eval $(call BuildPackage,pptp))
