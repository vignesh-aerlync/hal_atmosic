# Copyright (c) 2022-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    atm_utils_math
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

if (CONFIG_ATM_UECC)
    zephyr_include_directories(
	${ZEPHYR_BASE}/../modules/crypto/micro-ecc
    )
endif ()

if (CONFIG_TRUSTED_EXECUTION_SECURE)
    zephyr_include_directories(
	sec_assert
	sec_service
    )
    zephyr_sources(
	sec_assert/sec_assert.c
	sec_service/sec_service.c
    )
endif ()

if (CONFIG_ATM_VENDOR)
    add_subdirectory(atm_vendor)
endif ()
