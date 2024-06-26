# Copyright (c) 2022-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    atm_utils_c
    atm_utils_math
    atm_utils_reg
)

if (CONFIG_AT_CMD)
    zephyr_include_directories(
	at_cmd
    )

    zephyr_sources(
	at_cmd/at_cmd.c
	at_cmd/at_cmd_pasr.c
    )
endif ()

if (CONFIG_ATM_AES_HW OR CONFIG_ATM_SHA2_HW OR CONFIG_ATM_SHA2_HW_BOOTUTIL)
    zephyr_sources(
	atm_utils_reg/atm_utils_reg.c
    )
endif ()

if (CONFIG_ATM_ASM)
    add_subdirectory(atm_asm)
endif ()

if (CONFIG_ATM_UECC)
    zephyr_include_directories(
	${ZEPHYR_BASE}/../modules/crypto/micro-ecc
    )
endif ()

if (CONFIG_TRUSTED_EXECUTION_SECURE)
    zephyr_include_directories(
	sec_service
    )
    zephyr_sources(
	sec_service/sec_service.c
    )
endif ()

if (CONFIG_ATM_VENDOR)
    add_subdirectory(atm_vendor)
endif ()
