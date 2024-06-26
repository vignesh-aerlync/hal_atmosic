/**
 ******************************************************************************
 *
 * @file pmu_cfg.h
 *
 * @brief Power Management Unit driver configuration
 *
 * Copyright (C) Atmosic 2024
 *
 ******************************************************************************
 */

#pragma once

/**
 * @defgroup PMU PMU
 * @ingroup DRIVERS
 * @brief Power Management driver configuration
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_BATT_TYPE
#define BATT_TYPE CONFIG_BATT_TYPE
#endif
#ifndef BATT_TYPE
#define BATT_TYPE BATT_TYPE_NON_RECHARGEABLE
#endif

#ifdef CONFIG_BATT_LEVEL
#define BATT_LEVEL CONFIG_BATT_LEVEL
#endif
#ifndef BATT_LEVEL
#define BATT_LEVEL BATT_LEVEL_GT_1P8V
#endif

#ifndef VDDPA_SRC
#define VDDPA_SRC VDDPA_SRC_VDDIOP
#endif

#ifdef __cplusplus
}
#endif

/// @} PMU
