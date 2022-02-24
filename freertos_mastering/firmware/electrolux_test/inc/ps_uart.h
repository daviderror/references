/**
 *  \file   : ps_uart.c
 *  \header : ps_uart.h
 *  \brief  : a processor system (Zynq7000) uart driver.
 *  \author : Shimko Artyom
 *  \details:
 *     Allows to send/receive data by a processor system uart module.
 *     First of all, ps_uart_handle creation is needed. Secondly, the handler has to be initialized.
 *     The stop_bits, parity_type, data_bits, channel_mode, baud_rate, do_unblocking_mode, id fields
 *     are initialized by the one. For normal transfer of data the channel_mode has to be "normal".
 *     The id field is both number of an uart and a register base address.
 *     Next step is transmitting/receiving data from/to another uart. To send/receive data frames as a block
 *     mode the do_unblocking_mode is set to "false" value. To transfer the data frames as an unblocking mode
 *     the do_unblocking_mode is set to "true" value and in this type of work of driver there is a requirement to
 *     determine the void (*callback)(void *) field by a user callback function.
 *     Unblock writing and reading start just from setting of interrupt settings. After that in the
 *     user callback functions interact with transmitting/receiving processes via the set_data_word() and
 *     the get_data_word() functions.
 *
 *  \13.02.2022: created
 */

#ifndef INC_UART_H
#define INC_UART_H

#include <stdint.h>
#include <stdbool.h>

#include "xparameters.h" // a platform parameter header

#if XPAR_XUARTPS_NUM_INSTANCES > 0

#ifdef __cplusplus
extern "C" {
#endif

#define PS_UART_MODE_REG_RESET_VALUE     (uint32_t) 0x00000000

#define PS_UART_STOP_NUM_BIT_MASK        (uint32_t) 0x000000C0
#define PS_UART_STOP_NUM_BIT_0_OFFSET    (uint32_t) 0x00000006
#define PS_UART_STOP_NUM_BIT_1_OFFSET    (uint32_t) 0x00000007

#define PS_UART_PAR_TYP_BIT_MASK         (uint32_t) 0x00000018
#define PS_UART_PAR_TYP_BIT_0_OFFSET     (uint32_t) 0x00000003
#define PS_UART_PAR_TYP_BIT_1_OFFSET     (uint32_t) 0x00000004

#define PS_UART_DATA_NUM_BIT_MASK        (uint32_t) 0x00000006
#define PS_UART_DATA_NUM_BIT_0_OFFSET    (uint32_t) 0x00000001
#define PS_UART_DATA_NUM_BIT_1_OFFSET    (uint32_t) 0x00000001

#define PS_UART_CHNL_MD_BIT_MASK         (uint32_t) 0x00000300
#define PS_UART_CHNL_MD_BIT_0_OFFSET     (uint32_t) 0x00000008
#define PS_UART_CHNL_MD_BIT_1_OFFSET     (uint32_t) 0x00000009

#define PS_UART_CLK_SELECT_BIT_MASK      (uint32_t) 0x00000300
#define PS_UART_CLK_SELECT_BIT_0_OFFSET  (uint32_t) 0x00000008
#define PS_UART_CLK_SELECT_DIV8_VALUE    (uint32_t) 0x00000001
#define PS_UART_CLK_SELECT_NONDIV8_VALUE (uint32_t) 0x00000000

#define PS_UART_BD_GN_REG_RESET_VALUE    (uint32_t) 0x0000028B
#define PS_UART_BD_GN_REG_BPASS_VALUE    (uint32_t) 0x00000001
#define PS_UART_BD_GN_REG_DSABLE_VALUE   (uint32_t) 0x00000000
#define PS_UART_BD_GN_REG_DEF_VALUE      (uint32_t) 0x0000007C

#define PS_UART_BD_RT_REG_RESET_VALUE    (uint32_t) 0x0000000F

#define PS_UART_CONTROL_REG_RESET_VALUE  (uint32_t) 0x00000128
#define PS_UART_TX_DISABLE_BIT_OFFSET    (uint32_t) 0x00000005
#define PS_UART_TX_ENABLE_BIT_OFFSET     (uint32_t) 0x00000004
#define PS_UART_RX_DISABLE_BIT_OFFSET    (uint32_t) 0x00000003
#define PS_UART_RX_ENABLE_BIT_OFFSET     (uint32_t) 0x00000002
#define PS_UART_TX_RESET_BIT_OFFSET      (uint32_t) 0x00000001
#define PS_UART_RX_RESET_BIT_OFFSET      (uint32_t) 0x00000001

#define PS_UART_RX_FIFO_LVL_REG_RESET_VALUE (uint8_t) 0x20
#define PS_UART_TX_FIFO_LVL_REG_RESET_VALUE (uint8_t) 0x20

#define PS_UART_TX_FIFO_EMPTY_INTR_MSK_0  (uint32_t) 0x00000001
#define PS_UART_TX_FIFO_NRFULL_INTR_MSK_0 (uint32_t) 0x00000100
#define PS_UART_TX_FIFO_EMPTY_INTR_MSK_1  (uint32_t) 0x00000008
#define PS_UART_TX_FIFO_NRFULL_INTR_MSK_1 (uint32_t) 0x00000800

typedef struct {
    volatile uint32_t control;
    volatile uint32_t mode;
    volatile uint32_t interrupt_enable;
    volatile uint32_t interrupt_disable;
    volatile uint32_t interrupt_mask;
    volatile uint32_t interrupt_int;
    volatile uint32_t baud_rate_generator;
    volatile uint32_t rx_time_out;
    volatile uint32_t rx_fifo_level;
    volatile uint32_t modem_control;
    volatile uint32_t modem_int;
    volatile uint32_t channel;
    volatile uint32_t tx_rx_fifo;
    volatile uint32_t baud_rate_divider;
    volatile uint32_t flow_daley;
    volatile uint32_t tx_fifo_level;
} ps_uart_regs;

typedef enum {
    un_init = -2,
    error,
    ok,
    prm_error
} status;

typedef enum {
#ifdef XPAR_PS7_UART_0_DEVICE_ID
    ps_usart_id_0 = XPAR_PS7_UART_0_BASEADDR,
#endif
#ifdef XPAR_PS7_UART_1_DEVICE_ID
    ps_usart_id_1 = XPAR_PS7_UART_1_BASEADDR,
#endif
    none_id,
} ps_uart_id;

typedef enum {
    stop_1,
    stop_1d5,
    stop_2,
} ps_uart_stop_bits;

typedef enum {
    even,
    odd,
    space,
    mark,
    none_parity
} ps_uart_parity_type;

typedef enum {
    data_8,
    data_7 = 2,
    data_6
} ps_uart_data_bits;

typedef enum {
    normal,
    echo,
    local_loopback,
    remote_loopback
} ps_uart_channel_mode;

typedef enum {
    tx,
    rx,
    both
} ps_uart_path_reset;

typedef struct {
    ps_uart_stop_bits    stop_bits;
    ps_uart_parity_type  parity_type;
    ps_uart_data_bits    data_bits;
    ps_uart_channel_mode channel_mode;
    uint32_t             baud_rate;
    volatile bool        ready;
    bool                 do_unblocking_mode;
    volatile bool        init;
    uint32_t             id;
    void (*callback)(void *);
} ps_uart_handle;

char get_data_word(ps_uart_regs *regs);
void set_data_word(ps_uart_regs *regs, char data);
void read_block_mode_data(ps_uart_regs *p_uart_regs, char *p_data, size_t size);
void read_un_block_mode_data_(ps_uart_regs *p_uart_regs);
void write_un_block_mode_data(ps_uart_regs *p_uart_regs);
void write_block_mode_data(ps_uart_regs *p_uart_regs, char *p_data, size_t size);

status ps_uart_init(ps_uart_handle *p_handle);
status ps_uart_release(ps_uart_handle *p_handle);
status ps_uart_read(ps_uart_handle *p_handle, char *p_data, size_t size);
status ps_uart_write(ps_uart_handle *p_handle, char *p_data, size_t size);
int uart_reset(ps_uart_handle *p_handle, ps_uart_path_reset path_reset, bool *reset_done);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XPAR_XUARTPS_NUM_INSTANCES */
#endif /* INC_UART_H */