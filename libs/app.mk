#
# This file is generated by ModusToolbox during the 'make getlibs' operation
# Any edits to this file will be lost the next time the library manager is run or
# the next time 'make getlibs' is run.
#
modlibs library-manager qspi-configurator config device-configurator capsense-configurator capsense-tuner seglcd-configurator bsp-assistant config_usbdev usbdev-configurator smartio-configurator config_ezpd ez-pd-configurator :
	make -C ece353-mtb-team28-submit-app $@

config_bt bt-configurator config_lin lin-configurator :
	$(error $@ configurator cannot be executed at the application level. Run this command from the desired project directory.)

.PHONY: modlibs library-manager qspi-configurator config device-configurator capsense-configurator capsense-tuner seglcd-configurator bsp-assistant config_bt bt-configurator config_usbdev usbdev-configurator smartio-configurator config_ezpd ez-pd-configurator config_lin lin-configurator
