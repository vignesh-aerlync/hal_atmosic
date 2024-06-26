# Copyright (c) 2022-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    include
    include/arm
    include/armgcc
    include/reg
)

if (CONFIG_ATM_ENABLE_NSC_EXAMPLE)
    zephyr_include_directories(
	examples/spe/src/cust_sec_func
    )
endif()

add_subdirectory(lib)
add_subdirectory(drivers)

zephyr_linker_sources(NOINIT noinit.ld)
zephyr_linker_sources(RAMFUNC_SECTION ramfunc-section.ld)
