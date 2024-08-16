# Copyright (c) 2023-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(atmwstk)
add_subdirectory(atm_aes)
add_subdirectory(atm_otp)
add_subdirectory(atm_sha2)
add_subdirectory(batt_model)
add_subdirectory(batt_model_coin)
add_subdirectory(batt_model_hsc_liion)
add_subdirectory(brwnout)
add_subdirectory(hw_cfg)
add_subdirectory(pmu)
add_subdirectory(pseq)
add_subdirectory(reset)
add_subdirectory(rf)
add_subdirectory(sec_hw_cfg)
add_subdirectory(sec_jrnl)
add_subdirectory(workarounds)

zephyr_include_directories(
    reg
)

if (CONFIG_ADC OR CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG OR CONFIG_PM)
    assert(CONFIG_ARM_FIRMWARE_USES_SECURE_ENTRY_FUNCS "Must provide NSC functions")
endif ()

if (CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG)
    add_subdirectory(ble)
endif ()
