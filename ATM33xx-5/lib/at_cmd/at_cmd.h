/**
 *******************************************************************************
 *
 * @file at_cmd.h
 *
 * @brief Atmosic AT Command Core
 *
 * Copyright (C) Atmosic 2021-2024
 *
 *******************************************************************************
 */
#pragma once

/**
 *******************************************************************************
 * @defgroup ATM_BTFM_ATCORE AT command core
 * @ingroup ATM_BTFM_PROC
 * @brief ATM bluetooth framework AT command core
 *
 * This module contains the necessary procedure of AT command core.
 *
 * @{
 *******************************************************************************
 */

#include <stdbool.h>
#include "at_cmd_pasr.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The length of AT command response
#ifndef AT_CMD_RESP_LEN
#define AT_CMD_RESP_LEN 256
#endif // AT_CMD_RESP_LEN

/// Invalid channel number
#define AT_CMD_INVALID_CH 0xFF

/// The transfer layer support number
#ifndef AT_CMD_XFER_MAX_NUM
#define AT_CMD_XFER_MAX_NUM 3
#endif // AT_CMD_XFER_MAX_NUM

/// Command type
typedef enum {
    /// Test command. "AT+<x>=?"
    at_cmd_type_test,
    /// Read command. "AT+<x>?"
    at_cmd_type_query,
    /// Exec command. "AT+<x>="
    at_cmd_type_exec
} at_cmd_type_t;

/// AT command error code
typedef enum {
    /// No error
    AT_CMD_ERR_NO_ERROR,
    /// Command not support
    AT_CMD_ERR_NOT_SUPPORT,
    /// Wrong argument count
    AT_CMD_ERR_WRONG_ARGU_CNT,
    /// Wrong argument range
    AT_CMD_ERR_WRONG_ARGU_RANGE,
    /// Wrong argument type
    AT_CMD_ERR_WRONG_ARGU_TYPE,
    /// Wrong argument type or range
    AT_CMD_ERR_WRONG_ARGU_TYPE_OR_RANGE,
    /// Wrong argument content
    AT_CMD_ERR_WRONG_ARGU_CONTENT,
    /// Wrong execute type
    AT_CMD_ERR_WRONG_EXECUTE_TYPE,
    /// Specific error
    AT_CMD_ERR_SPECIFIC_ERR = 0x80
} at_cmd_err_t;

/// AT command channel
typedef uint8_t at_cmd_ch_t;

/// AT command parameter for handler
typedef struct {
    /// AT command type
    at_cmd_type_t type;
    /// Error code
    at_cmd_err_t err;
    /// Argument count
    uint16_t argc;
    /// Argument content
    at_pasr_tlv_t **args;
    /// AT command data residue
    bool data_residue;
    /// Transport channel
    at_cmd_ch_t ch;
    /// Application error code
    uint16_t app_err;
    /// Command string
    char const *str;
} at_cmd_param_t;

/// The AT command handler
typedef void (*at_cmd_hdlr_t)(at_cmd_param_t *param);

/// AT command definition
typedef struct {
    /// Command string. Ex: BCSC for AT+BCSC=
    char const *str;
    /// AT command parameter format
    char const *fmt;
    /// Expect paramter numbers
    uint16_t const param_num;
    /// AT command handler
    at_cmd_hdlr_t hdlr;
    /// Test response string. If no, left NULL.
    char const *test_str;
} at_cmd_t;

typedef enum {
    /// AT command response (prefix)
    at_prefix = 1,
    /// AT command response (data)
    at_data = (1 << 1),
    /// AT command response (postfix)
    at_postfix = (1 << 2),
    /// AT command response (prefix + data + postfix)
    at_all = at_prefix | at_data | at_postfix
} at_cmd_resp_flag_t;

/// The AT command response handler
typedef void (*at_cmd_resp_hdlr_t)(at_cmd_ch_t ch, void const *resp,
    uint16_t len);

/**
 *******************************************************************************
 * @brief The transport layer handler
 * @param[in] ch The channel got from @ref at_cmd_alloc
 * @param[in, out] data Data string
 * @param[in, out] len The length of data string
 *******************************************************************************
 */
typedef char const *(*at_cmd_xfer_hdlr_t)(at_cmd_ch_t ch, void const *data,
    uint16_t *len);

/// Built-in transport for UART
#define AT_CMD_DFT_XFER_UART ((at_cmd_xfer_hdlr_t)0x1)

/// The context of AT command allocate
typedef struct {
    /// Transport layer handler
    at_cmd_xfer_hdlr_t xfer;
    /// AT command response handler
    at_cmd_resp_hdlr_t resp;
} at_cmd_alloc_ctx_t;

/**
 *******************************************************************************
 * @brief The link time module registration
 * @param[in] cmd Command
 * @param[in] fmt Command parameter format
 *    b(#~@) int8_t. (#: minimal number, @: maximal number)
 *    B(#~@) uint8_t.
 *        B(1~2), unsigned 8 bit number from 1 to 2.
 *    w(#~@) int16_t
 *    W(#~@) uint16_t.
 *        W(~5), unsigned 16 bit number from 0 to 5.
 *    d(#~@) int32_t.
 *        d(-3~10), signed 32 bit number from -3 to 10.
 *        d(~1000), signed 32 bit number from -2147483647 to 1000"
 *    D(#~@) uint32_t.
 *        D(30~), unsigned 32 bit number from 30 to 4294967295
 *    A(#~@) byte array.
 *        A, byte array with any length
 *        A(3~), byte array with at least 3 bytes.
 *        A(2~5), byte array with length from 2 to 5 octets.
 *        A(6~6), byte array with 6 bytes exactly.
 *    S(#~@) UTF8 string.
 *        S, string with length 0 to 255 octets.
 *        S(3~), string with length from 3 to 255 octets.
 *        S(2~5), string with length from 2 to 5 octets.
 * @param[in] num Number of command parameters
 * @param[in] hdl Command handler
 * @param[in] test Test command output
 *******************************************************************************
 */
#define AT_COMMAND(cmd, fmt, num, hdl, test) \
    AT_COMMAND_VAR(p##hdl, cmd, fmt, num, hdl, test)

#define AT_COMMAND_VAR(var, cmd, fmt, num, hdl, test) \
    static const at_cmd_t __attribute__((section(".at_cmd." cmd), used)) \
    var = {cmd, fmt, num, hdl, test}
/**
 *******************************************************************************
 * @brief Allocate and configure AT command context
 * @param[in] ctx The context of AT command
 * @return Channel number if successful; otherwise return AT_CMD_INVALID_CH
 *******************************************************************************
 */
__NONNULL_ALL
at_cmd_ch_t at_cmd_alloc(at_cmd_alloc_ctx_t const *ctx);

/**
 *******************************************************************************
 * @brief AT command process
 * @param[in] ch The channel got from @ref at_cmd_alloc
 * @param[in] data Input string w/o command header (i.e. AT+)
 * @param[in] data_len The length of input string
 * @return true if successful
 *******************************************************************************
 */
__NONNULL(2)
bool at_cmd_proc(at_cmd_ch_t ch, void const *data, uint16_t data_len);

/**
 *******************************************************************************
 * @brief Send response array
 * @param[in] ch The channel got from @ref at_cmd_alloc
 * @param[in] flag @ref at_cmd_resp_flag_t
 * @param[in] len Length of dat.
 * @param[in] dat Array.
 *******************************************************************************
 */
__NONNULL(4)
void at_cmd_resp_array(at_cmd_ch_t ch, at_cmd_resp_flag_t flag, uint16_t len,
    uint8_t const *dat);

/**
 *******************************************************************************
 * @brief Generate response string
 * @param[in] ch The channel got from @ref at_cmd_alloc
 * @param[in] flag @ref at_cmd_resp_flag_t
 * @param[in] fmt Response string
 *******************************************************************************
 */
__attribute__((format (printf, 3, 4)))
void at_cmd_resp_concat(at_cmd_ch_t ch, at_cmd_resp_flag_t flag,
    char const *fmt, ...);

/**
 *******************************************************************************
 * @brief Apply response raw data
 * @param[in] ch The channel got from @ref at_cmd_alloc
 * @param[in] data Data
 * @param[in] len Data length
 *******************************************************************************
 */
__NONNULL(2)
void at_cmd_resp_raw(at_cmd_ch_t ch, void const *data, uint16_t len);

/**
 *******************************************************************************
 * @brief Retrieve number of AT commands available
 * @return How many AT commands available
 *******************************************************************************
 */
uint16_t at_cmd_count(void);

#ifdef __cplusplus
}
#endif

///@} ATM_BTFM_ATCORE

