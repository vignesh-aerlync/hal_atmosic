/**
 *******************************************************************************
 *
 * @file power.h
 *
 * @brief Power mode api
 *
 * Copyright (C) Atmosic 2024
 *
 *******************************************************************************
 */

#pragma once

/**
 * @defgroup POWER POWER
 * @ingroup DRIVERS
 * @brief Power mode interface
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void atm_pseq_soc_off(uint32_t ticks);

#ifdef __cplusplus
}
#endif

/// @} POWER
