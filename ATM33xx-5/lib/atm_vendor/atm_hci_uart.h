/**
 *******************************************************************************
 *
 * @file atm_hci_uart.h
 *
 * @brief Header File - ATM HCI data from uart to another device/CPU
 * using and handle vendor command with hci_raw module for zephyr only
 *
 * Copyright (C) Atmosic 2024
 *
 *******************************************************************************
 */

#pragma once

#include "compiler.h" // __NORETURN inline functions

#ifdef CONFIG_BT_HCI_RAW_CMD_EXT
#include "atm_vendor_internal.h"
#endif

/**
 * @defgroup ATM_BTFM_HCI_UART ATM HCI uart
 * @ingroup ATM_BTFM_PROC
 * @brief ATM HCI uart
 *
 * This module contains the necessary API to int uart and hci data handler.
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable and initial uart device handler
 */
void atm_uart_init(void);

/**
 * @brief Enable and initial hci raw data handler
 */
void atm_hci_init(void);

#ifdef CONFIG_BT_HCI_RAW_CMD_EXT
/**
 * @brief ATM vendor command handler register
 * @param[in] hdrs ATM vendor command handlers.
 * @param[in] size Array size of ATM vendor command handlers.
 */
__NONNULL_ALL
void atm_vendor_handler_register(struct vendor_handler const *hdrs,
    size_t size);
#endif

#ifdef __cplusplus
}
#endif

///@}
