/**
 *******************************************************************************
 *
 * @file spi_multi.c
 *
 * @brief SPI multi transaction driver
 *
 * Copyright (C) Atmosic 2022
 *
 *******************************************************************************
 */

#include "arch.h"
#include "spi_multi.h"
#include "atm_utils_math.h"

void spi_multi_transaction(spi_dev_t const *spi, uint32_t tx_size,
    uint8_t const *tx_buffer, uint32_t rx_size, uint8_t *rx_buffer,
    uint8_t flags)
{
    // Assert both size are buffer are zero or both are non-zero
    ASSERT_INFO(!((!!tx_size) ^ (!!tx_buffer)), tx_size, tx_buffer);
    ASSERT_INFO(!((!!rx_size) ^ (!!rx_buffer)), rx_size, rx_buffer);
    // Assert if both tx and rx zero
    ASSERT_INFO(!((tx_size == 0) && (rx_size == 0)), tx_size, rx_size);

    bool csn_stays_low = true;
    bool tx_csn_stays_low = true;
    bool rx_csn_stays_low = true;
    int8_t tx_num_data_bytes = -1;
    int8_t rx_num_data_bytes = -1;
    uint32_t tx_current_data_byte = 0;
    uint32_t rx_current_data_byte = 0;
    uint8_t tx_opcode = 0;
    bool write_flag = false;
    uint32_t lower = 0;
    uint32_t upper = 0;
    while ((tx_size) || (rx_size)) {
	if (tx_size > 8) {
	    tx_num_data_bytes = 8;
	    // Upto 9 bytes of data can be transmitted in one transaction
	    tx_size = tx_size - 9;
	} else if (tx_size > 0) {
	    tx_num_data_bytes = tx_size - 1;
	    tx_size = 0;
	    if (flags & SPI_MULTI_FLAG_CS_DISABLE) {
		tx_csn_stays_low = false;
	    }
	} else {
	    tx_num_data_bytes = -1;
	    tx_csn_stays_low = false;
	}
	if (rx_size > 8) {
	    rx_num_data_bytes = 8;
	    // Upto 9 bytes of data can be received in one transaction
	    rx_size = rx_size - 9;
	} else if (rx_size > 0) {
	    rx_num_data_bytes = rx_size - 1;
	    rx_size = 0;
	    if (flags & SPI_MULTI_FLAG_CS_DISABLE) {
		rx_csn_stays_low = false;
	    }
	} else {
	    rx_num_data_bytes = -1;
	    rx_csn_stays_low = false;
	}
	csn_stays_low = tx_csn_stays_low | rx_csn_stays_low;
	for (uint8_t local_count = 0; local_count <= tx_num_data_bytes;
	    local_count++) {
	    if (!local_count) {
		tx_opcode = tx_buffer[tx_current_data_byte++];
		write_flag = true;
	    } else if (local_count <= 4) {
		lower |= (tx_buffer[tx_current_data_byte++]
		    << ((local_count - 1) * 8));
	    } else {
		upper |= (tx_buffer[tx_current_data_byte++]
		    << ((local_count - 5) * 8));
	    }
	}
	uint32_t transaction =
	    SPI_TRANSACTION_SETUP__DUMMY_CYCLES__WRITE(spi->dummy_cycles) |
	    SPI_TRANSACTION_SETUP__CSN_STAYS_LOW__WRITE(csn_stays_low);
	if (write_flag) {
	    transaction |= SPI_TRANSACTION_SETUP__OPCODE__WRITE(tx_opcode);
	    tx_opcode = 0;
	    write_flag = false;
	}
	transaction |=
	    SPI_TRANSACTION_SETUP__CLKDIV__WRITE(spi->clkdiv) |
	    SPI_TRANSACTION_SETUP__RWB__MASK |
	    SPI_TRANSACTION_SETUP__NUM_DATA_BYTES__WRITE(
		ATM_MAX(tx_num_data_bytes, rx_num_data_bytes));
	spi->base->DATA_BYTES_LOWER = lower;
	spi->base->DATA_BYTES_UPPER = upper;
	lower = 0;
	upper = 0;
	spi->base->TRANSACTION_SETUP = transaction;
	spi->base->TRANSACTION_SETUP |= SPI_TRANSACTION_SETUP__START__MASK;
	// Wait for transaction to complete
	while (spi->base->TRANSACTION_STATUS &
	    SPI_TRANSACTION_STATUS__RUNNING__MASK) {
	    YIELD();
	}
	for (uint8_t local_count = 0; local_count <= rx_num_data_bytes;
	    local_count++) {
	    if (!local_count) {
		rx_buffer[rx_current_data_byte] =
		    ((spi->base->TRANSACTION_STATUS) >> 8) & 0xFF;
	    } else if (local_count <= 4) {
		rx_buffer[rx_current_data_byte] =
		    (spi->base->DATA_BYTES_LOWER >> (8 * (local_count - 1))) &
		    0xFF;
	    } else {
		rx_buffer[rx_current_data_byte] =
		    (spi->base->DATA_BYTES_UPPER >> (8 * (local_count - 5))) &
		    0xFF;
	    }
	    rx_current_data_byte++;
	}
    }
}
