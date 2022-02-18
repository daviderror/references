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

#include "xscugic.h" // a platform interrupt header

#include "ps_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------upper half---------------------------------------------//

static inline status init_driver_(ps_uart_handle *p_handle, bool do_init);
static inline status check_params_(ps_uart_handle *p_handle);

//---------------------------------------------lower half---------------------------------------------//

static inline void set_stop_bits_(ps_uart_regs *p_reg_base, ps_uart_stop_bits stop_bits, bool do_setting);
static inline void set_parity_type_(ps_uart_regs *p_reg_base, ps_uart_parity_type parity_type, bool do_setting);
static inline void set_data_bits_(ps_uart_regs *p_reg_base, ps_uart_data_bits data_bits, bool do_setting);
static inline void set_channel_mode_(ps_uart_regs *p_reg_base, ps_uart_channel_mode channel_mode, bool do_setting);
static inline void set_baud_rate_(ps_uart_regs *p_reg_base, uint32_t baud_rate, bool do_setting);
static inline void set_tx_enable_(ps_uart_regs *p_reg_base, bool do_setting);
static inline void set_rx_enable_(ps_uart_regs *p_reg_base, bool do_setting);
static inline void set_reset_(ps_uart_regs *p_reg_base, ps_uart_path_reset path_reset, bool *reset_done);
static inline void set_interrupt_(ps_uart_regs *p_uart_regs, uint32_t interrupt_mask); //uint32_t??
static inline void set_rx_fifo_level_(ps_uart_regs *p_reg_base, uint8_t rx_fifo_level, bool do_setting);
static inline void set_tx_fifo_level_(ps_uart_regs *p_reg_base, uint8_t tx_fifo_level, bool do_setting);

//---------------------------------------------upper half---------------------------------------------//

char get_data_word(ps_uart_regs *regs) {
    const uint32_t rx_mask = 0x2;

    while(rx_mask == (regs->channel & rx_mask));
    return regs->tx_rx_fifo;
}

void set_data_word(ps_uart_regs *regs, char data) {
    const uint32_t tx_mask = 0x8;

    while(tx_mask == (regs->channel & tx_mask));
    regs->tx_rx_fifo = data;
}

void read_un_block_mode_data(ps_uart_regs *p_uart_regs)
{
    const uint32_t interrupt_mask = 0x2FF;
    set_interrupt_(p_uart_regs, interrupt_mask);
}

void read_block_mode_data(ps_uart_regs *p_uart_regs, char *p_data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        p_data[i] = get_data_word(p_uart_regs);
    }
}

void write_un_block_mode_data(ps_uart_regs *p_uart_regs)
{
    const uint32_t interrupt_mask = 0x1FF;
    set_interrupt_(p_uart_regs, interrupt_mask);
}

void write_block_mode_data(ps_uart_regs *p_uart_regs, char *p_data, size_t size)
{
    set_tx_enable_(p_uart_regs, true);

    for(size_t i = 0; i < size; i++) {
        set_data_word(p_uart_regs , p_data[i]);
    }
}

status ps_uart_init(ps_uart_handle *p_handle)
{
    if (NULL == p_handle) {
        return prm_error;
    }

    return init_driver_(p_handle, true);
}

status ps_uart_release(ps_uart_handle *p_handle)
{
    if (true != p_handle->init) {
         return un_init;
    }

    return init_driver_(p_handle, false);
}

status ps_uart_read(ps_uart_handle *p_handle, char *p_data, size_t size)
{
    if (NULL == p_handle) {
        return prm_error;
    }

    if (false != p_handle->init) {
        return un_init;
    }

    if ((false == p_handle->do_unblocking_mode) && ((NULL == p_data) || (0 == size))) {
        return prm_error;
    }

    p_handle->ready = false;

    if (true == p_handle->do_unblocking_mode) {
        read_un_block_mode_data((ps_uart_regs *) p_handle->id);
    }
    else {
        read_block_mode_data((ps_uart_regs *) p_handle->id, p_data, size);
        p_handle->ready = true;
    }

    return ok;
}

status ps_uart_write(ps_uart_handle *p_handle, char *p_data, size_t size)
{
    if (NULL == p_handle) {
        return prm_error;
    }

    if (false != p_handle->init) {
        return un_init;
    }

    if ((false == p_handle->do_unblocking_mode) && ((NULL == p_data) || (0 == size))) {
        return prm_error;
    }

    p_handle->ready = false;

    if (true == p_handle->do_unblocking_mode) {
        write_un_block_mode_data((ps_uart_regs *) p_handle->id);
    }
    else {
        write_block_mode_data((ps_uart_regs *) p_handle->id, p_data, size);
        p_handle->ready = true;
    }

    return ok;
}

status ps_uart_reset(ps_uart_handle *p_handle, ps_uart_path_reset path_reset, bool *reset_done)
{
    if ((NULL == p_handle) || (NULL == reset_done)) {
        return prm_error;
    }

    if ((path_reset < tx) || (path_reset > both)) {
        return prm_error;
    }

    if (false != p_handle->init) {
        return un_init;
    }

    set_reset_((ps_uart_regs* ) p_handle->id, path_reset, reset_done);

    return ok;
}

static inline status init_driver_(ps_uart_handle *p_handle, bool do_init)
{
    const uint32_t rx_fifo_level = 10,
                   tx_fifo_level = 10,
                   intr_priority = 1;

    ps_uart_regs *p_ps_uart_regs = NULL;

    status check_params_status = error;

    p_handle->ready = false;
    p_handle->init = false;

    if (0 != (check_params_status = check_params_(p_handle))) {
        return check_params_status;
    }

    p_ps_uart_regs = (ps_uart_regs* )p_handle->id;

    set_tx_enable_(p_ps_uart_regs, false);
    set_rx_enable_(p_ps_uart_regs, false);

    set_stop_bits_   (p_ps_uart_regs, p_handle->stop_bits, do_init);
    set_parity_type_ (p_ps_uart_regs, p_handle->parity_type, do_init);
    set_data_bits_   (p_ps_uart_regs, p_handle->data_bits, do_init);
    set_channel_mode_(p_ps_uart_regs, p_handle->channel_mode, do_init);
    set_baud_rate_   (p_ps_uart_regs, p_handle->baud_rate, do_init);

    set_rx_fifo_level_(p_ps_uart_regs, rx_fifo_level, do_init);
    set_tx_fifo_level_(p_ps_uart_regs, tx_fifo_level, do_init);

    if (true == do_init) {
        p_handle->ready = true;
        p_handle->init = true;

    //    XScuGic_Connect(intr_priority,(Xil_ExceptionHandler) p_handle->callback); // a platform function
    }

    return ok;
}

static inline status check_params_(ps_uart_handle *p_handle)
{
    if ((p_handle->channel_mode < normal) ||
        (p_handle->channel_mode > remote_loopback)) {
        return prm_error;
    }

    if ((data_6 != p_handle->data_bits) &&
        (data_7 != p_handle->data_bits) &&
        (data_8 != p_handle->data_bits)) {
        return prm_error;
    }

    if ((ps_usart_id_0 != p_handle->id) &&
        (ps_usart_id_1 != p_handle->id)) {
        return prm_error;
    }

    if ((p_handle->parity_type < even) ||
        (p_handle->parity_type > none_parity)) {
        return prm_error;
    }

    if ((p_handle->stop_bits < stop_1) ||
        (p_handle->stop_bits > stop_2)) {
        return prm_error;
    }

    return ok;
}

//---------------------------------------------lower half---------------------------------------------//

static inline void set_stop_bits_(ps_uart_regs *p_reg_base, ps_uart_stop_bits stop_bits, bool do_setting) {

    p_reg_base->mode &= ~((true << PS_UART_STOP_NUM_BIT_0_OFFSET) | (true << PS_UART_STOP_NUM_BIT_1_OFFSET));

    if (true == do_setting) {
        p_reg_base->mode |= (stop_bits << PS_UART_STOP_NUM_BIT_0_OFFSET);
    }
    else {
        p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_STOP_NUM_BIT_MASK);
    }
}

static inline void set_parity_type_(ps_uart_regs *p_reg_base, ps_uart_parity_type parity_type, bool do_setting) {
    p_reg_base->mode &= ~((true << PS_UART_PAR_TYP_BIT_0_OFFSET) | (true << PS_UART_PAR_TYP_BIT_1_OFFSET));

    if (true == do_setting) {
        p_reg_base->mode |= (parity_type << PS_UART_PAR_TYP_BIT_0_OFFSET);
    }
    else {
        p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_PAR_TYP_BIT_MASK);
    }
}

static inline void set_data_bits_(ps_uart_regs *p_reg_base, ps_uart_data_bits data_bits, bool do_setting) {
    p_reg_base->mode &= ~((true << PS_UART_DATA_NUM_BIT_0_OFFSET) | (true << PS_UART_DATA_NUM_BIT_1_OFFSET));

    if (true == do_setting) {
        p_reg_base->mode |= (data_bits << PS_UART_DATA_NUM_BIT_0_OFFSET);
    }
    else {
        p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_DATA_NUM_BIT_MASK);
    }
}

static inline void set_channel_mode_(ps_uart_regs *p_reg_base, ps_uart_channel_mode channel_mode, bool do_setting) {
    p_reg_base->mode &= ~((true << PS_UART_CHNL_MD_BIT_0_OFFSET) | (true << PS_UART_CHNL_MD_BIT_1_OFFSET));

    if (true == do_setting) {
        p_reg_base->mode |= (channel_mode << PS_UART_CHNL_MD_BIT_0_OFFSET);
    }
    else {
        p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_CHNL_MD_BIT_MASK);
    }
}

static void set_baud_rate_(ps_uart_regs *p_reg_base, uint32_t baud_rate, bool do_setting) {
    p_reg_base->mode &= ~(true << PS_UART_CLK_SELECT_BIT_0_OFFSET);
    p_reg_base->baud_rate_divider = 0;

    if (true == do_setting) {
        if (PS_UART_BD_GN_REG_DSABLE_VALUE == baud_rate) {
            p_reg_base->baud_rate_generator = PS_UART_BD_GN_REG_DSABLE_VALUE;
            p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_CLK_SELECT_BIT_MASK);
            p_reg_base->baud_rate_divider = PS_UART_BD_RT_REG_RESET_VALUE;
        }
        else if (PS_UART_CLK_SELECT_DIV8_VALUE == baud_rate){
            p_reg_base->baud_rate_generator = PS_UART_BD_GN_REG_BPASS_VALUE;
            p_reg_base->mode |= (PS_UART_CLK_SELECT_DIV8_VALUE << PS_UART_CLK_SELECT_BIT_0_OFFSET);
            p_reg_base->baud_rate_divider = PS_UART_BD_RT_REG_RESET_VALUE;
        }
        else {
            p_reg_base->baud_rate_generator = PS_UART_BD_GN_REG_DEF_VALUE;
            p_reg_base->mode |= (PS_UART_CLK_SELECT_NONDIV8_VALUE << PS_UART_CLK_SELECT_BIT_0_OFFSET);
            p_reg_base->baud_rate_divider = (XPAR_XUARTPS_0_UART_CLK_FREQ_HZ  / (baud_rate * PS_UART_BD_GN_REG_DEF_VALUE)) - 1;
        }
    }
    else {
        p_reg_base->baud_rate_generator = PS_UART_BD_GN_REG_RESET_VALUE;
        p_reg_base->mode |= (PS_UART_MODE_REG_RESET_VALUE & PS_UART_CLK_SELECT_BIT_MASK);
        p_reg_base->baud_rate_divider = PS_UART_BD_RT_REG_RESET_VALUE;
    }
}

static inline void set_tx_enable_(ps_uart_regs *p_reg_base, bool do_setting) {
    if (true == do_setting) {
        p_reg_base->control |= (true << PS_UART_TX_ENABLE_BIT_OFFSET);
    }
    else {
        p_reg_base->control |= (true << PS_UART_TX_DISABLE_BIT_OFFSET);
    }
}

static inline void set_rx_enable_(ps_uart_regs *p_reg_base, bool do_setting) {
    if (true == do_setting) {
        p_reg_base->control |= (true << PS_UART_RX_ENABLE_BIT_OFFSET);
    }
    else {
        p_reg_base->control |= (true << PS_UART_RX_DISABLE_BIT_OFFSET);
    }
}

static inline void set_reset_(ps_uart_regs *p_reg_base, ps_uart_path_reset path_reset, bool *reset_done) {
    switch (path_reset) {
    case tx:
        p_reg_base->control |= (true << PS_UART_TX_RESET_BIT_OFFSET);
        *reset_done = !(p_reg_base->control & (true << PS_UART_TX_RESET_BIT_OFFSET));
    break;
    case rx:
        p_reg_base->control |= (true << PS_UART_RX_RESET_BIT_OFFSET);
        *reset_done = !(p_reg_base->control & (true << PS_UART_RX_RESET_BIT_OFFSET));
    break;
    case both:
        p_reg_base->control |= (true << PS_UART_TX_RESET_BIT_OFFSET) | (true << PS_UART_RX_RESET_BIT_OFFSET);
        *reset_done = !(p_reg_base->control & ((true << PS_UART_TX_RESET_BIT_OFFSET) | (TRUE << PS_UART_RX_RESET_BIT_OFFSET)));
    break;
    default:
        *reset_done = 0;
    break;
    }
}

static inline void set_interrupt_(ps_uart_regs *p_uart_regs, uint32_t interrupt_mask) {

    p_uart_regs->interrupt_enable = interrupt_mask;
}

static inline void set_rx_fifo_level_(ps_uart_regs *p_reg_base, uint8_t rx_fifo_level, bool do_setting)
{
    if (true == do_setting) {
        p_reg_base->rx_fifo_level = rx_fifo_level;
    }
    else {
        p_reg_base->rx_fifo_level = PS_UART_RX_FIFO_LVL_REG_RESET_VALUE;
    }
}

static inline void set_tx_fifo_level_(ps_uart_regs *p_reg_base, uint8_t tx_fifo_level, bool do_setting)
{
    if (true == do_setting) {
        p_reg_base->tx_fifo_level = tx_fifo_level;
    }
    else {
        p_reg_base->tx_fifo_level = PS_UART_TX_FIFO_LVL_REG_RESET_VALUE;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
