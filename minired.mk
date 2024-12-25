################################################################################
#
# minired package
#
################################################################################

MINIRED_VERSION = 1.0
MINIRED_SITE = ./package/minired
MINIRED_SITE_METHOD = local# Other methods like git,wget,scp,file etc. are also available.
MINIRED_DEPENDENCIES = host-pkgconf dbus bluez5_utils
MINIRED_INSTALL_STAGING = YES

$(eval $(meson-package))
