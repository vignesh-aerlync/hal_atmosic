# Copyright (c) 2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

if (CONFIG_ATM_VENDOR)
    zephyr_include_directories(
	atm_hci_uart
    )
    zephyr_sources(
	atm_hci_uart/atm_hci_uart.c
    )
endif ()
