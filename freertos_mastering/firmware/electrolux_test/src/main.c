#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "ps_uart.h"

#define DATA_ARR_SIZE 128U

#define RX_TX_FIFO_OFFSET   12U
#define RX_DATA_REG_0       (uint32_t *) (XPAR_PS7_UART_0_BASEADDR + RX_TX_FIFO_OFFSET)
#define RX_DATA_REG_1       (uint32_t *) (XPAR_PS7_UART_1_BASEADDR + RX_TX_FIFO_OFFSET)

static QueueHandle_t rx_queue = NULL, tx_queue = NULL;
static TaskHandle_t rx_task = NULL, tx_task = NULL;
static SemaphoreHandle_t semphr_0 = NULL, semphr_1 = NULL;

static ps_uart_handle rx_hnd = {}, tx_hnd = {};

static char data_arr_0[DATA_ARR_SIZE] = {},
            data_arr_1[DATA_ARR_SIZE] = {};

void rx_intr_callback (void *p_prm);
void tx_intr_callback (void *p_prm);

static void rx_task_callback(void *p_prm);
static void tx_task_callback(void *p_prm);

int main(void)
{
    const size_t queue_size = 10;

    status rx_status = error;

    rx_hnd.baud_rate = 9600U;
    rx_hnd.callback = rx_intr_callback;
    rx_hnd.channel_mode = normal;
    rx_hnd.data_bits = data_8;
    rx_hnd.do_unblocking_mode = true;
    rx_hnd.id = ps_usart_id_0;
    rx_hnd.parity_type = none_parity;
    rx_hnd.stop_bits = stop_1;

    tx_hnd.baud_rate = 115200U;
    tx_hnd.callback = tx_intr_callback;
    tx_hnd.channel_mode = normal;
    tx_hnd.data_bits = data_8;
    tx_hnd.do_unblocking_mode = true;
    tx_hnd.id = ps_usart_id_1;
    tx_hnd.parity_type = none_parity;
    tx_hnd.stop_bits = stop_1;

    if (ok != (rx_status = ps_uart_init(&rx_hnd))) {
        return error;
    }

    if (ok != (rx_status = ps_uart_init(&tx_hnd))) {
        return error;
    }

    if (NULL == (rx_queue = xQueueCreate(queue_size, sizeof(char)))) {
        return error;
    }

    if (NULL == (tx_queue = xQueueCreate(queue_size, sizeof(char)))) {
        return error;
    }

    configASSERT(rx_queue);
    configASSERT(tx_queue);

    if (NULL == (semphr_0 = xSemaphoreCreateMutex())) {
        return error;
    }

    if (NULL == (semphr_1 = xSemaphoreCreateMutex())) {
        return error;
    }

    xTaskCreate(rx_task_callback,(const char *) "rx",
                configMINIMAL_STACK_SIZE,
                NULL,tskIDLE_PRIORITY,&rx_task);

    xTaskCreate(tx_task_callback,(const char *) "tx",
                configMINIMAL_STACK_SIZE,
                NULL,tskIDLE_PRIORITY,&tx_task);

    vTaskStartScheduler();

    while (true) {
        asm("NOP");
    }

//    vTaskDelete(rx_task);
//    vTaskDelete(tx_task);

    return ok;
}

void rx_intr_callback (void *p_prm)
{
    xQueueSend(rx_queue, RX_DATA_REG_0, 0UL);
}

void tx_intr_callback (void *p_prm)
{
    xQueueReceive(tx_queue,    RX_DATA_REG_1, portMAX_DELAY);
}

static void rx_task_callback(void *p_prm)
{
    bool ch_buf_flag = false;
    ps_uart_read(&rx_hnd, NULL, 0);

    const TickType_t semph_wait_tick = 10;

    while (true) {
        for (size_t i = 0; i < DATA_ARR_SIZE; i++) {
            if (true == ch_buf_flag) {
                xSemaphoreTake(semphr_0, semph_wait_tick);
                xQueueReceive(rx_queue, data_arr_0, portMAX_DELAY);
                xSemaphoreGive(semphr_0);
            }
            else {
                xSemaphoreTake(semphr_1, semph_wait_tick);
                xQueueReceive(rx_queue, data_arr_1, portMAX_DELAY);
                xSemaphoreGive(semphr_1);
            }
        }

        ch_buf_flag ^= ch_buf_flag;
    }
}

static void tx_task_callback(void *p_prm)
{
    bool ch_buf_flag = false;
    ps_uart_write(&rx_hnd, NULL, 0);

    const TickType_t semph_wait_tick = 10;

    while (true) {
        for (size_t i = 0; i < DATA_ARR_SIZE; i++) {
            if (true == ch_buf_flag) {
                xSemaphoreTake(semphr_0, semph_wait_tick);
                xQueueSend(tx_queue, data_arr_0, 0UL);
                xSemaphoreGive(semphr_0);
            }
            else {
                xSemaphoreTake(semphr_1, semph_wait_tick);
                xQueueSend(tx_queue, data_arr_1, 0UL);
                xSemaphoreGive(semphr_1);
            }
        }

        ch_buf_flag ^= ch_buf_flag;
    }
}