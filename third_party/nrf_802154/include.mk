TARGET_NRF_802154_PATH = $(NRF_802154_MODULE_PATH)

INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/fem
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/hal
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/mac_features
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/platform/clock
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/platform/temperature
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/platform/timer
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/raal
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/raal/softdevice
INCLUDE_DIRS += $(TARGET_NRF_802154_PATH)/nrf_802154/src/timer_scheduler

CFLAGS += -DENABLE_FEM=1
CFLAGS += -DNRF_802154_PROJECT_CONFIG=\"openthread-platform-config.h\"
CFLAGS += -DRAAL_SOFTDEVICE=1