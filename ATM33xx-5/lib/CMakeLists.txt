# Copyright (c) 2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

if (CONFIG_APP_BATT)
    zephyr_include_directories(
	app_batt
    )

    zephyr_sources(
	app_batt/app_batt.c
    )
endif ()

add_subdirectory(atm_mcuboot_ext)
