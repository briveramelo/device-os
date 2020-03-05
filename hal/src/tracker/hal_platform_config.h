#pragma once

#include "hal_platform_nrf52840_config.h"
#include "platforms.h"

#define HAL_PLATFORM_NCP (1)
#define HAL_PLATFORM_NCP_AT (1)
#define HAL_PLATFORM_CELLULAR (1)
#define HAL_PLATFORM_SETUP_BUTTON_UX (1)

#define HAL_PLATFORM_PMIC_BQ24195 (1)
#define HAL_PLATFORM_PMIC_BQ24195_I2C (HAL_I2C_INTERFACE2)
#define HAL_PLATFORM_ETHERNET_FEATHERWING_SPI_CLOCKDIV 4
#define HAL_PLATFORM_FUELGAUGE_MAX17043 (1)
#define HAL_PLATFORM_FUELGAUGE_MAX17043_I2C (HAL_I2C_INTERFACE2)
#define HAL_PLATFORM_HW_FORM_FACTOR_SOM (1)
#define HAL_PLATFORM_POWER_MANAGEMENT (1)
#define HAL_PLATFORM_POWER_MANAGEMENT_OPTIONAL (0)
#define HAL_PLATFORM_PMIC_BQ24195_FAULT_COUNT_THRESHOLD (4)
#define HAL_PLATFORM_RADIO_ANTENNA_EXTERNAL (1)

#define HAL_PLATFORM_IO_EXPANDER (1)
#define HAL_PLATFORM_IO_EXPANDER_SPI (HAL_SPI_INTERFACE2)

#define PRODUCT_SERIES "boron"
