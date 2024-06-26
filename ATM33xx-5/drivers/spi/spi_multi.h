/**
 *******************************************************************************
 *
 * @file spi_multi.h
 *
 * @brief SPI multiple transaction driver
 *
 * Copyright (C) Atmosic 2022
 *
 *******************************************************************************
 */

#pragma once

/**
 * @defgroup SPI_MULTI SPI multiple read / write transaction
 * @ingroup DRIVERS
 * @brief User driver for SPI-connected devices
 * @{
 */

#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_MULTI_FLAG_CS_ENABLE (1 << 0)
#define SPI_MULTI_FLAG_CS_DISABLE (1 << 1)

/**
 * @brief Multi Byte transaction
 *
 * @param[in] spi Device structure.
 * @param[in] tx_size tx buffer size in bytes
 * @param[in] tx_buffer Data to write to SPI slave device.
 * @param[in] rx_size rx buffer size in bytes
 * @param[out] rx_buffer Data to be read from SPI slave device.
 * @param[in] flags Flags specifying SPI operations.
 */
void spi_multi_transaction(spi_dev_t const *spi, uint32_t tx_size,
    uint8_t const *tx_buffer, uint32_t rx_size, uint8_t *rx_buffer,
    uint8_t flags);

#ifdef __cplusplus
}
#endif

/// @}
