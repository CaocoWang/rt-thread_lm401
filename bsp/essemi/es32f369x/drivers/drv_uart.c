/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version   
 * 2021-04-20     liuhy         the second version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "es_conf_info_uart.h"

#ifdef RT_USING_SERIAL

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
    IRQn_Type irq;
};

#ifdef BSP_USING_UART0
/* UART0 device driver structure */
struct es32_uart uart0 =
{
    {UART0},
    UART0_IRQn
};

struct rt_serial_device serial0;

void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart0.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart0.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    {UART1},
    UART1_IRQn
};

struct rt_serial_device serial1;

void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart1.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart1.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    {UART2},
    UART2_IRQn
};

struct rt_serial_device serial2;

void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart2.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart2.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    {UART3},
    UART3_IRQn
};

struct rt_serial_device serial3;

void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart3.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart3.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
/* UART4 device driver structure */
struct es32_uart uart4 =
{
    {UART4},
    UART4_IRQn
};

struct rt_serial_device serial4;

void UART4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart4.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart4.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
/* UART5 device driver structure */
struct es32_uart uart5 =
{
    {UART5},
    UART5_IRQn
};

struct rt_serial_device serial5;

void UART5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart5.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart5.huart, UART_IF_RFTH);
        rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

static rt_err_t es32f3x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    gpio_init_t gpio_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.odos = GPIO_PUSH_PULL;
    gpio_initstructure.pupd = GPIO_PUSH_UP;
    gpio_initstructure.podrv = GPIO_OUT_DRIVE_6;
    gpio_initstructure.nodrv = GPIO_OUT_DRIVE_6;
    gpio_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_initstructure.type = GPIO_TYPE_TTL;

#ifdef BSP_USING_UART0
    if(uart == (&uart0))
    {
#if  defined(ES_UART0_TX_GPIO_FUNC)&&defined(ES_UART0_TX_GPIO_PORT)&&defined(ES_UART0_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART0_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_TX_GPIO_PORT, ES_UART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART0_RX_GPIO_FUNC)&&defined(ES_UART0_RX_GPIO_PORT)&&defined(ES_UART0_RX_GPIO_PIN)        
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART0_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_RX_GPIO_PORT, ES_UART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
        ald_cmu_perh_clock_config(CMU_PERH_UART0, ENABLE);
    }
    
#endif /* uart0 gpio init */
                                 
#ifdef BSP_USING_UART1
    if(uart == (&uart1))
    {
#if  defined(ES_UART1_TX_GPIO_FUNC)&&defined(ES_UART1_TX_GPIO_PORT)&&defined(ES_UART1_TX_GPIO_PIN)  
        gpio_initstructure.func = ES_UART1_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_TX_GPIO_PORT, ES_UART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART1_RX_GPIO_FUNC)&&defined(ES_UART1_RX_GPIO_PORT)&&defined(ES_UART1_RX_GPIO_PIN) 
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART1_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_RX_GPIO_PORT, ES_UART1_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART1, ENABLE);
    }
#endif /* uart1 gpio init */
                               
#ifdef BSP_USING_UART2
    if(uart == (&uart2))
    {
#if  defined(ES_UART2_TX_GPIO_FUNC)&&defined(ES_UART2_TX_GPIO_PORT)&&defined(ES_UART2_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART2_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_TX_GPIO_PORT, ES_UART2_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART2_RX_GPIO_FUNC)&&defined(ES_UART2_RX_GPIO_PORT)&&defined(ES_UART2_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART2_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_RX_GPIO_PORT, ES_UART2_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART2, ENABLE);
    }
#endif /* uart2 gpio init */
                                 
#ifdef BSP_USING_UART3
    if(uart == (&uart3))
    {
#if  defined(ES_UART3_TX_GPIO_FUNC)&&defined(ES_UART3_TX_GPIO_PORT)&&defined(ES_UART3_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART3_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_TX_GPIO_PORT, ES_UART3_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART3_RX_GPIO_FUNC)&&defined(ES_UART3_RX_GPIO_PORT)&&defined(ES_UART3_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART3_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_RX_GPIO_PORT, ES_UART3_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART3, ENABLE);   
    }
#endif /* uart3 gpio init */
                                  
#ifdef BSP_USING_UART4
    if(uart == (&uart4))
    {
#if  defined(ES_UART4_TX_GPIO_FUNC)&&defined(ES_UART4_TX_GPIO_PORT)&&defined(ES_UART4_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART4_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_TX_GPIO_PORT, ES_UART4_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART4_RX_GPIO_FUNC)&&defined(ES_UART4_RX_GPIO_PORT)&&defined(ES_UART4_RX_GPIO_PIN)  
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART4_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_RX_GPIO_PORT, ES_UART4_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART4, ENABLE); 
    }
#endif /* uart4 gpio init */
                                 
#ifdef BSP_USING_UART5
    if(uart == (&uart5))
    {
#if  defined(ES_UART5_TX_GPIO_FUNC)&&defined(ES_UART5_TX_GPIO_PORT)&&defined(ES_UART5_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART5_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_TX_GPIO_PORT, ES_UART5_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART5_RX_GPIO_FUNC)&&defined(ES_UART5_RX_GPIO_PORT)&&defined(ES_UART5_RX_GPIO_PIN)  
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART5_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_RX_GPIO_PORT, ES_UART5_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART5, ENABLE);
    }
#endif /* uart5 gpio init */

    ald_uart_tx_fifo_config(&uart->huart, UART_TXFIFO_EMPTY);
    ald_uart_rx_fifo_config(&uart->huart, UART_RXFIFO_1BYTE);

    uart->huart.init.mode        = UART_MODE_UART;
    uart->huart.init.baud        = cfg->baud_rate;
    uart->huart.init.word_length = (uart_word_length_t)(8 - cfg->data_bits);
    uart->huart.init.parity = (uart_parity_t)(cfg->parity == PARITY_EVEN ? UART_PARITY_EVEN : cfg->parity);
    uart->huart.init.fctl        = UART_HW_FLOW_CTL_DISABLE; 
    uart->huart.init.stop_bits        = UART_STOP_BITS_1;
    ald_uart_init(&uart->huart);

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        UART_MSB_FIRST_ENABLE(&uart->huart);
    }
    else
    {
        UART_MSB_FIRST_DISABLE(&uart->huart);
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        UART_DATA_INV_ENABLE(&uart->huart);
    }
    else
    {
        UART_DATA_INV_DISABLE(&uart->huart);
    }

    return RT_EOK;
}

static rt_err_t es32f3x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct es32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, DISABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, ENABLE);
        break;
    }

    return RT_EOK;
}

static int es32f3x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    while (ald_uart_get_status(&uart->huart, UART_STATUS_TFEMPTY) == RESET)
        ;
    WRITE_REG(uart->huart.perh->TXBUF, c);

    return 1;
}

static int es32f3x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (ald_uart_get_status(&uart->huart, UART_STATUS_RFTH))
    {
        ch = (uint8_t)(uart->huart.perh->RXBUF & 0xFF);
    }

    return ch;
}

static const struct rt_uart_ops es32f3x_uart_ops =
{
    es32f3x_configure,
    es32f3x_control,
    es32f3x_putc,
    es32f3x_getc,
};

int rt_hw_uart_init(void)
{
    struct es32_uart *uart;

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es32f3x_uart_ops;
    serial0.config = (struct serial_configure)ES_UART0_CONFIG;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, ES_DEVICE_NAME_UART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f3x_uart_ops;
    serial1.config = (struct serial_configure)ES_UART1_CONFIG;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, ES_DEVICE_NAME_UART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es32f3x_uart_ops;
    serial2.config = (struct serial_configure)ES_UART2_CONFIG;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, ES_DEVICE_NAME_UART2,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es32f3x_uart_ops;
    serial3.config = (struct serial_configure)ES_UART3_CONFIG;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, ES_DEVICE_NAME_UART3,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    uart = &uart4;
    serial4.ops = &es32f3x_uart_ops;
    serial4.config = (struct serial_configure)ES_UART4_CONFIG;

    /* register UART4 device */
    rt_hw_serial_register(&serial4, ES_DEVICE_NAME_UART4,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    uart = &uart5;
    serial5.ops = &es32f3x_uart_ops;
    serial5.config = (struct serial_configure)ES_UART5_CONFIG;

    /* register UART5 device */
    rt_hw_serial_register(&serial5, ES_DEVICE_NAME_UART5,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART5 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
