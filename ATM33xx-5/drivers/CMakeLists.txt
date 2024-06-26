# Copyright (c) 2023-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    atm_bp_clock
    dma
    flash
    rep_vec
    sec_cache
    sec_jrnl
    sec_reset
    spi
    timer
    trng
)

if (CONFIG_ATM_PLF_DEBUG)
    zephyr_compile_definitions(
	CFG_PLF_DEBUG
    )
    zephyr_sources(
	user_debug.c
    )
endif ()

if (CONFIG_ADC OR CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG OR CONFIG_PM)
    zephyr_include_directories(
	reset
	workarounds
    )
    zephyr_sources(
	reset/reset.c
	workarounds/workarounds.c
    )
endif ()

if ((CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG) AND CONFIG_USE_ATMWSTK)
    zephyr_include_directories(
	atmwstk
    )
    zephyr_sources(
	atmwstk/atmwstk.c
    )
endif ()

if (CONFIG_TRUSTED_EXECUTION_SECURE OR CONFIG_SOC_FLASH_ATM_RRAM)
    zephyr_include_directories(
	rram_rom_prot
    )
    zephyr_sources(
	rram_rom_prot/rram_rom_prot.c
    )
endif ()

if (CONFIG_TRUSTED_EXECUTION_SECURE)
    zephyr_sources(
	sec_cache/sec_cache.c
	sec_jrnl/sec_jrnl.c
    )

    if (NOT CONFIG_MCUBOOT)
	zephyr_include_directories(
	    at_tz_mpc
	    sec_dev_lockout
	)
	zephyr_sources(
	    at_tz_mpc/at_tz_mpc.c
	    sec_dev_lockout/sec_dev_lockout.c
	    sec_reset/sec_reset.c
	)
    endif ()
endif ()

if ((CONFIG_TRUSTED_EXECUTION_NONSECURE AND (CONFIG_SOC_FLASH_ATM OR CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG OR CONFIG_PM OR CONFIG_ADC)) OR (CONFIG_TRUSTED_EXECUTION_SECURE AND NOT CONFIG_BOOTLOADER_MCUBOOT))
    zephyr_sources(
	atm_bp_clock/atm_bp_clock.c
	spi/spi.c
    )
endif ()

if (CONFIG_ATM_AES_HW OR CONFIG_ATM_SHA2_HW OR CONFIG_ATM_UECC)
    zephyr_include_directories(
	../config
    )
    zephyr_link_libraries(mbedTLS)
endif ()

if (CONFIG_ATM_AES_HW)
    zephyr_include_directories(
	atm_aes
    )
    zephyr_sources(
	atm_aes/atm_aes.c
	atm_aes/aes_alt.c
    )
endif ()

if (CONFIG_ATM_SHA2_HW OR CONFIG_ATM_SHA2_HW_BOOTUTIL)
    zephyr_include_directories(
	atm_sha2
    )
    zephyr_sources(
	atm_sha2/atm_sha2.c
    )
endif ()
if (CONFIG_ATM_SHA2_HW)
    zephyr_sources(
	atm_sha2/sha256_alt.c
    )
endif ()

if (CONFIG_ATM_UECC)
    zephyr_include_directories(
	micro-ecc
    )
    zephyr_sources(
	micro-ecc/ecdsa_alt.c
    )
endif ()
