# Copyright (c) 2023-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    atm_otp
    pseq
    reg
)

zephyr_link_libraries(
    ${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/pseq/pseq_core.po
)

if (CONFIG_ADC OR CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG OR CONFIG_PM)
    assert(CONFIG_ARM_FIRMWARE_USES_SECURE_ENTRY_FUNCS "Must provide NSC functions")
    zephyr_include_directories(
	hw_cfg
	pmu
    )
    zephyr_sources(
	hw_cfg/hw_cfg.c
	pmu/pmu.c
    )
    zephyr_link_libraries(
	${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/hw_cfg/hw_cfg_core.po
	${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/pmu/pmu_core.po
    )
endif ()

if (CONFIG_BT OR CONFIG_ENTROPY_ATM_TRNG)
    add_subdirectory(ble)

    zephyr_include_directories(
	rf
    )
    zephyr_sources(
	rf/rf.c
    )
    zephyr_link_libraries(
	${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/rf/rf_core.po
    )
endif ()

if (CONFIG_TRUSTED_EXECUTION_SECURE)
    # CONFIG_BOOTLOADER_MCUBOOT is never set by MCUBoot application and is
    # set by SPE only when building with MCUboot support. sec_hw_cfg will only
    # be compiled by MCUboot or SPE (when not chain-loaded by MCUboot)
    if (NOT CONFIG_BOOTLOADER_MCUBOOT)
	zephyr_include_directories(
	    sec_hw_cfg
	)
	zephyr_sources(
	    atm_otp/atm_otp.c
	    sec_hw_cfg/sec_hw_cfg.c
	)
	zephyr_link_libraries(
	    ${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/sec_hw_cfg/sec_hw_cfg_core.po
	)
    endif ()
endif ()

if (NOT CONFIG_NO_BROWNOUT)
    zephyr_include_directories(
	brwnout
    )
    zephyr_sources(
	brwnout/brwnout.c
    )
    zephyr_link_libraries(
	${LINKERFLAGPREFIX},${CMAKE_CURRENT_SOURCE_DIR}/brwnout/brwnout_core.po
    )
endif()
