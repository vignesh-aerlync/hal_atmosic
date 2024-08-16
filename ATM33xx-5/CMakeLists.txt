# Copyright (c) 2022-2024 Atmosic
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
    include
    include/arm
    include/armgcc
    include/reg
)

add_subdirectory(lib)
add_subdirectory(drivers)

zephyr_linker_sources(NOINIT noinit.ld)
zephyr_linker_sources(RAMFUNC_SECTION ramfunc-section.ld)
