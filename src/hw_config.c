/**
 ******************************************************************************
 * @file    hw_config.c
 * @author  Spark Application Team
 * @version V1.0.0
 * @date    13-March-2013
 * @brief   Hardware Configuration & Setup
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_TypeDef* DIO_PORT[Dn] = {D0_GPIO_PORT, D1_GPIO_PORT, D2_GPIO_PORT, D3_GPIO_PORT,
								D4_GPIO_PORT, D5_GPIO_PORT, D6_GPIO_PORT, D7_GPIO_PORT};
const uint16_t DIO_PIN[Dn] = {D0_PIN, D1_PIN, D2_PIN, D3_PIN,
								D4_PIN, D5_PIN, D6_PIN, D7_PIN};
const uint32_t DIO_CLK[Dn] = {D0_GPIO_CLK, D1_GPIO_CLK, D2_GPIO_CLK, D3_GPIO_CLK,
								D4_GPIO_CLK, D5_GPIO_CLK, D6_GPIO_CLK, D7_GPIO_CLK};

GPIO_TypeDef* LED_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT};
const uint16_t LED_PIN[LEDn] = {LED1_PIN, LED2_PIN};
const uint32_t LED_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {BUTTON1_GPIO_PORT, BUTTON2_GPIO_PORT};
const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON1_PIN, BUTTON2_PIN};
const uint32_t BUTTON_CLK[BUTTONn] = {BUTTON1_GPIO_CLK, BUTTON2_GPIO_CLK};
GPIOMode_TypeDef BUTTON_GPIO_MODE[BUTTONn] = {BUTTON1_GPIO_MODE, BUTTON2_GPIO_MODE};
__IO uint8_t BUTTON_DEBOUNCED[BUTTONn] = {0x00, 0x00};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {BUTTON1_EXTI_LINE, BUTTON2_EXTI_LINE};
const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {BUTTON1_EXTI_PORT_SOURCE, BUTTON2_EXTI_PORT_SOURCE};
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {BUTTON1_EXTI_PIN_SOURCE, BUTTON2_EXTI_PIN_SOURCE};
const uint16_t BUTTON_IRQn[BUTTONn] = {BUTTON1_EXTI_IRQn, BUTTON2_EXTI_IRQn};
EXTITrigger_TypeDef BUTTON_EXTI_TRIGGER[BUTTONn] = {BUTTON1_EXTI_TRIGGER, BUTTON2_EXTI_TRIGGER};

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Configures Main system clocks & power.
 * @param  None
 * @retval None
 */
void Set_System(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 file (startup_stm32f10x_xx.S) before to branch to application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32f10x.c file
	 */

	/* NVIC configuration */
	NVIC_Configuration();

	/* Configure DIOs */
	int Dx;
	for(Dx = 0; Dx < Dn; ++Dx)
	{
		DIO_Init(Dx);
	}

	/* Configure the LEDs and set the default states */
	int LEDx;
	for(LEDx = 0; LEDx < LEDn; ++LEDx)
	{
	    LED_Init(LEDx);
	    LED_Off(LEDx);
	}

    /* Configure the Button */
    BUTTON_Init(BUTTON1, BUTTON_MODE_EXTI);

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		/* Capture error */
		while (1)
		{
		}
	}
}

/*******************************************************************************
 * Function Name  : NVIC_Configuration
 * Description    : Configures Vector Table base location.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void NVIC_Configuration(void)
{
	/* Set the Vector Table base location at 0x0000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
}

/**
  * @brief  Configures Dx GPIO.
  * @param  Dx: Specifies the Dx to be configured.
  * @retval None
  */
void DIO_Init(DIO_TypeDef Dx)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_Dx Clock */
    RCC_APB2PeriphClockCmd(DIO_CLK[Dx], ENABLE);

    /* Configure the GPIO_Dx pin */
    GPIO_InitStructure.GPIO_Pin = DIO_PIN[Dx];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(DIO_PORT[Dx], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected Dx On/Off.
  * @param  Dx: Specifies the Dx.
  * @param  State: Set On or Off.
  * @retval None
  */
DIO_Error_TypeDef DIO_SetState(DIO_TypeDef Dx, DIO_State_TypeDef State)
{
	if(Dx < 0 || Dx > Dn)
		return FAIL;
	else if(State == HIGH)
		DIO_PORT[Dx]->BSRR = DIO_PIN[Dx];
	else if(State == LOW)
		DIO_PORT[Dx]->BRR = DIO_PIN[Dx];

	return OK;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LED_Init(Led_TypeDef Led)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_APB2PeriphClockCmd(LED_CLK[Led], ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = LED_PIN[Led];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LED_PORT[Led], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LED_On(Led_TypeDef Led)
{
    LED_PORT[Led]->BSRR = LED_PIN[Led];
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LED_Off(Led_TypeDef Led)
{
    LED_PORT[Led]->BRR = LED_PIN[Led];
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LED_Toggle(Led_TypeDef Led)
{
    LED_PORT[Led]->ODR ^= LED_PIN[Led];
}

/**
  * @brief  Configures Button GPIO, EXTI Line and DEBOUNCE Timer.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON1: Button1
  *     @arg BUTTON2: Button2
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability
  * @retval None
  */
void BUTTON_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* Enable the BUTTON Clock */
    RCC_APB2PeriphClockCmd(BUTTON_CLK[Button] | RCC_APB2Periph_AFIO, ENABLE);

    /* Configure Button pin as input floating */
    GPIO_InitStructure.GPIO_Mode = BUTTON_GPIO_MODE[Button];
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
    GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

    if (Button_Mode == BUTTON_MODE_EXTI)
    {
        /* Enable TIM4 clock */
        RCC_APB1PeriphClockCmd(DEBOUNCE_TIMER_CLK, ENABLE);

        /* TIM Update Frequency = 72000000/7200/100 = 100Hz = 10ms */
        /* TIM_Prescaler: 7199 */
        /* TIM_Autoreload: 99 -> 100Hz = 10ms */
        uint16_t TIM_Prescaler = (SystemCoreClock / 10000) - 1;
        uint16_t TIM_Autoreload = (10000 / DEBOUNCE_FREQ) - 1;

        /* Time Base Configuration */
    	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    	TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler;
    	TIM_TimeBaseStructure.TIM_Period = TIM_Autoreload;
    	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    	TIM_TimeBaseInit(DEBOUNCE_TIMER, &TIM_TimeBaseStructure);

        /* TIM Configuration */
        //TIM_PrescalerConfig(DEBOUNCE_TIMER, TIM_Prescaler, TIM_PSCReloadMode_Update);
        //TIM_SetAutoreload(DEBOUNCE_TIMER, TIM_Autoreload);

        /* One Pulse Mode selection */
        TIM_SelectOnePulseMode(DEBOUNCE_TIMER, TIM_OPMode_Single);

        TIM_ClearITPendingBit(DEBOUNCE_TIMER, DEBOUNCE_TIMER_FLAG);

        /* TIM IT Enable */
        TIM_ITConfig(DEBOUNCE_TIMER, DEBOUNCE_TIMER_FLAG, ENABLE);

        /* Enable the TIM Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = DEBOUNCE_TIMER_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        NVIC_Init(&NVIC_InitStructure);

        /* Enable the Button EXTI Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        NVIC_Init(&NVIC_InitStructure);

        BUTTON_DEBOUNCED[Button] = 0x00;

        BUTTON_EXTI_Config(Button, ENABLE);
    }
}

void BUTTON_EXTI_Config(Button_TypeDef Button, FunctionalState NewState)
{
    EXTI_InitTypeDef EXTI_InitStructure;

	/* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

	/* Clear the EXTI line pending flag */
	EXTI_ClearFlag(BUTTON_EXTI_LINE[Button]);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = BUTTON_EXTI_TRIGGER[Button];
    EXTI_InitStructure.EXTI_LineCmd = NewState;
    EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Returns the selected Button non-filtered state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON1: Button1
  *     @arg BUTTON2: Button2
  * @retval Actual Button Pressed state.
  */
uint8_t BUTTON_GetState(Button_TypeDef Button)
{
    return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Returns the selected Button filtered state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON1: Button1
  *     @arg BUTTON2: Button2
  * @retval Button Debounced state.
  */
uint8_t BUTTON_GetDebouncedState(Button_TypeDef Button)
{
	if(BUTTON_DEBOUNCED[BUTTON1] != 0x00)
	{
		BUTTON_DEBOUNCED[BUTTON1] = 0x00;
		return 0x01;
	}
	return 0x00;
}

/**
 * @brief  Initialize the CC3000 - CS and ENABLE lines.
 * @param  None
 * @retval None
 */
void CC3000_WIFI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* CC3000_WIFI_CS_GPIO and CC3000_WIFI_EN_GPIO Peripheral clock enable */
	RCC_APB2PeriphClockCmd(CC3000_WIFI_CS_GPIO_CLK | CC3000_WIFI_EN_GPIO_CLK, ENABLE);

	/* Configure CC3000_WIFI pins: CS */
	GPIO_InitStructure.GPIO_Pin = CC3000_WIFI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(CC3000_WIFI_CS_GPIO_PORT, &GPIO_InitStructure);

	/* Deselect CC3000 */
	CC3000_CS_HIGH();

	/* Configure CC3000_WIFI pins: Enable */
	GPIO_InitStructure.GPIO_Pin = CC3000_WIFI_EN_PIN;
	GPIO_Init(CC3000_WIFI_EN_GPIO_PORT, &GPIO_InitStructure);

	/* Disable CC3000 */
	CC3000_Write_Enable_Pin(WLAN_DISABLE);
}

/**
 * @brief  Initialize and configure the SPI peripheral used by CC3000.
 * @param  None
 * @retval None
 */
void CC3000_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/* CC3000_SPI_SCK_GPIO, CC3000_SPI_MOSI_GPIO and CC3000_SPI_MISO_GPIO Peripheral clock enable */
	RCC_APB2PeriphClockCmd(CC3000_SPI_SCK_GPIO_CLK | CC3000_SPI_MOSI_GPIO_CLK | CC3000_SPI_MISO_GPIO_CLK, ENABLE);

	/* CC3000_SPI Peripheral clock enable */
	CC3000_SPI_CLK_CMD(CC3000_SPI_CLK, ENABLE);

	/* Configure CC3000_SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = CC3000_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(CC3000_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/* Configure CC3000_SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = CC3000_SPI_MOSI_PIN;
	GPIO_Init(CC3000_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* Configure CC3000_SPI pins: MISO */
	GPIO_InitStructure.GPIO_Pin = CC3000_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(CC3000_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	/* CC3000_SPI Config */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = CC3000_SPI_BAUDRATE_PRESCALER;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(CC3000_SPI, &SPI_InitStructure);
}

/**
 * @brief  Configure the DMA Peripheral used to handle CC3000 communication via SPI.
 * @param  None
 * @retval None
 */
void CC3000_DMA_Config(CC3000_DMADirection_TypeDef Direction, uint8_t* buffer, uint16_t NumData)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(CC3000_SPI_DMA_CLK, ENABLE);

	DMA_InitStructure.DMA_PeripheralBaseAddr = CC3000_SPI_DR_BASE;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) buffer;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	/* DMA used for Reception */
	if (Direction == CC3000_DMA_RX)
	{
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = NumData;
		DMA_DeInit(CC3000_SPI_RX_DMA_CHANNEL );
		DMA_Init(CC3000_SPI_RX_DMA_CHANNEL, &DMA_InitStructure);
	}
	/* DMA used for Transmission */
	else if (Direction == CC3000_DMA_TX)
	{
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize = NumData;
		DMA_DeInit(CC3000_SPI_TX_DMA_CHANNEL );
		DMA_Init(CC3000_SPI_TX_DMA_CHANNEL, &DMA_InitStructure);
	}
}

void CC3000_SPI_DMA_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure and enable SPI DMA TX Channel interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CC3000_SPI_TX_DMA_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	CC3000_SPI_Init();

	/* Configure DMA Peripheral but don't send data*/
	CC3000_DMA_Config(CC3000_DMA_RX, (uint8_t*) wlan_rx_buffer, 0);
	CC3000_DMA_Config(CC3000_DMA_TX, (uint8_t*) wlan_tx_buffer, 0);

	/* Enable SPI DMA TX Channel Transfer Complete Interrupt */
	DMA_ITConfig(CC3000_SPI_TX_DMA_CHANNEL, DMA_IT_TC, ENABLE);

	/* Enable SPI DMA request */
	SPI_I2S_DMACmd(CC3000_SPI, SPI_I2S_DMAReq_Rx, ENABLE);
	SPI_I2S_DMACmd(CC3000_SPI, SPI_I2S_DMAReq_Tx, ENABLE);

	/* Enable CC3000_SPI */
	SPI_Cmd(CC3000_SPI, ENABLE);

	/* Enable DMA RX Channel */
	DMA_Cmd(CC3000_SPI_RX_DMA_CHANNEL, ENABLE);
	/* Enable DMA TX Channel */
	DMA_Cmd(CC3000_SPI_TX_DMA_CHANNEL, ENABLE);
}

void CC3000_SPI_DMA_Channels(FunctionalState NewState)
{
	/* Enable/Disable DMA RX Channel */
	DMA_Cmd(CC3000_SPI_RX_DMA_CHANNEL, NewState);
	/* Enable/Disable DMA TX Channel */
	DMA_Cmd(CC3000_SPI_TX_DMA_CHANNEL, NewState);
}

/* CC3000 Hardware related callbacks passed to wlan_init */
long CC3000_Read_Interrupt_Pin(void)
{
	return GPIO_ReadInputDataBit(CC3000_WIFI_INT_GPIO_PORT, CC3000_WIFI_INT_PIN );
}

void CC3000_Interrupt_Enable(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* CC3000_WIFI_INT_GPIO and AFIO Peripheral clock enable */
	RCC_APB2PeriphClockCmd(CC3000_WIFI_INT_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

	/* Configure CC3000_WIFI pins: Interrupt */
	GPIO_InitStructure.GPIO_Pin = CC3000_WIFI_INT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(CC3000_WIFI_INT_GPIO_PORT, &GPIO_InitStructure);

	/* Select the CC3000_WIFI_INT GPIO pin used as EXTI Line */
	GPIO_EXTILineConfig(CC3000_WIFI_INT_EXTI_PORT_SOURCE, CC3000_WIFI_INT_EXTI_PIN_SOURCE );

	/* Clear the EXTI line pending flag */
	EXTI_ClearFlag(CC3000_WIFI_INT_EXTI_LINE );

	/* Configure and Enable CC3000_WIFI_INT EXTI line */
	EXTI_InitStructure.EXTI_Line = CC3000_WIFI_INT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set CC3000_WIFI_INT EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = CC3000_WIFI_INT_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void CC3000_Interrupt_Disable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Disable CC3000_WIFI_INT EXTI Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CC3000_WIFI_INT_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Disable CC3000_WIFI_INT EXTI line */
	EXTI_InitStructure.EXTI_Line = CC3000_WIFI_INT_EXTI_LINE;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void CC3000_Write_Enable_Pin(unsigned char val)
{
	/* Set WLAN Enable/Disable */
	if (val != WLAN_DISABLE)
	{
		GPIO_SetBits(CC3000_WIFI_EN_GPIO_PORT, CC3000_WIFI_EN_PIN );
	}
	else
	{
		GPIO_ResetBits(CC3000_WIFI_EN_GPIO_PORT, CC3000_WIFI_EN_PIN );
	}
}

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_SPI_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Disable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, DISABLE);

  /* DeInitializes the sFLASH_SPI */
  SPI_I2S_DeInit(sFLASH_SPI);

  /* sFLASH_SPI Peripheral clock disable */
  sFLASH_SPI_CLK_CMD(sFLASH_SPI_CLK, DISABLE);

  /* Configure sFLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_MEM_CS_PIN pin: sFLASH CS pin */
  GPIO_InitStructure.GPIO_Pin = sFLASH_MEM_CS_PIN;
  GPIO_Init(sFLASH_MEM_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_SPI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  /* sFLASH_MEM_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO
       and sFLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(sFLASH_MEM_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK |
                         sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

  /* sFLASH_SPI Periph clock enable */
  sFLASH_SPI_CLK_CMD(sFLASH_SPI_CLK, ENABLE);

  /* Configure sFLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sFLASH_MEM_CS_PIN pin: sFLASH CS pin */
  GPIO_InitStructure.GPIO_Pin = sFLASH_MEM_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(sFLASH_MEM_CS_GPIO_PORT, &GPIO_InitStructure);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = sFLASH_SPI_BAUDRATE_PRESCALER;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sFLASH_SPI, &SPI_InitStructure);

  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, ENABLE);
}

