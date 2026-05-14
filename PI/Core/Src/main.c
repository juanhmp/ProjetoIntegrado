/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7735\st7735.h"
#include <stdlib.h>
#include "st7735\fonts.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1_ON		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
#define LED1_OFF	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
#define LED2_ON		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
#define LED2_OFF	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
#define LED3_ON		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
#define LED3_OFF	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
#define LED4_ON		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
#define LED4_OFF	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
GPIO_PinState BOTAO1;
GPIO_PinState BOTAO2;
GPIO_PinState BOTAO3;
GPIO_PinState BOTAO4;
int inicio;
int senha[4];
int posicao = 0;
int i;
int campo[100];
int matricula_Aluno = 0;
int correta = 1;
int tentativas = 0;
int tentativa[4];
int sistemaIniciado = 0;
int digito;
int telaInicialMostrada = 0;
int botao1Travado = 0;
int configurandoAlunos = 0;
int qtdAlunos = 0;
int alunoBanheiro = 0 ;
int alunosPresentes = 0;
int alunos = 0;
char senha_i[5];
int area [100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void Senha(void);
void ApagarLeds(void);
void MostrarBinario(int numero);
void MostrarDigitacao(void);
void ConfirmarDigito(void);
void Alunos(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
ST7735_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  static int telaInicialMostrada = 0;
	  static int botao1Travado = 0;
	  static int configurandoAlunos = 0;
	  static int qtdAlunos = 0;
	  static int limiteBanheiro = 0;
	  static int alunoBanheiro = 0;
	  static int totalForamBanheiro = 0;
	  static int tentativas = 0;
	  static int aulaIniciada = 0;
	  static int confirmandoFim = 0;
	  static int alunosPresentes = 0;

	  GPIO_PinState BOTAO1 = HAL_GPIO_ReadPin(BOTAO1_GPIO_Port, BOTAO1_Pin);
	  GPIO_PinState BOTAO2 = HAL_GPIO_ReadPin(BOTAO2_GPIO_Port, BOTAO2_Pin);
	  GPIO_PinState BOTAO3 = HAL_GPIO_ReadPin(BOTAO3_GPIO_Port, BOTAO3_Pin);
	  GPIO_PinState BOTAO4 = HAL_GPIO_ReadPin(BOTAO4_GPIO_Port, BOTAO4_Pin);

	  if (configurandoAlunos == 1)
	  {
	      char texto[30];

	      sprintf(texto, "Alunos: %d   ", qtdAlunos);
	      ST7735_WriteString(10, 70, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	      if (BOTAO4 == 0)
	      {
	          qtdAlunos++;
	          if (qtdAlunos > 50)
	              qtdAlunos = 50;
	          HAL_Delay(200);
	      }

	      if (BOTAO2 == 0)
	      {
	          if (qtdAlunos > 0)
	              qtdAlunos--;
	          HAL_Delay(200);
	      }

	      if (BOTAO3 == 0)
	      {
	          ST7735_FillScreen(ST7735_BLACK);
	          ST7735_WriteString(10, 10, "Qtd salva", Font_7x10, ST7735_GREEN, ST7735_BLACK);

	          sprintf(texto, "Alunos: %d", qtdAlunos);
	          ST7735_WriteString(10, 30, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          HAL_Delay(1500);

	          configurandoAlunos = 0;
	          sistemaIniciado = 0;
	          telaInicialMostrada = 0;
	          posicao = 0;
	          digito = 0;
	          limiteBanheiro = 3;
	          inicio = 1;
	          aulaIniciada = 1;

	          ST7735_FillScreen(ST7735_BLACK);
	      }

	      continue;
	  }

	  if (inicio == 0)
	  {
	      if (telaInicialMostrada == 0)
	      {
	          ST7735_FillScreen(ST7735_BLACK);
	          ST7735_WriteString(10, 10, "Aperte BOTAO1 (PA9)", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	          ST7735_WriteString(10, 25, "para iniciar", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	          telaInicialMostrada = 1;
	      }

	      if (BOTAO1 == 0 && botao1Travado == 0 && sistemaIniciado == 0)
	      {
	          botao1Travado = 1;

	          Senha();
	          posicao = 0;
	          digito = 0;
	          sistemaIniciado = 1;
	          configurandoAlunos = 0;

	          ST7735_FillScreen(ST7735_BLACK);
	          ST7735_WriteString(10, 10, "Digite a senha", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	          ST7735_WriteString(10, 25, "PA11: Confirmar", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	          ST7735_WriteString(10, 40, "PA12: Aumentar", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	          ST7735_WriteString(10, 55, "PA10: Diminuir", Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          HAL_Delay(300);
	      }

	      if (BOTAO1 == 1)
	      {
	          botao1Travado = 0;
	      }

	      if (sistemaIniciado == 1 && configurandoAlunos == 0)
	      {
	          MostrarDigitacao();

	          if (BOTAO4 == 0)
	          {
	              digito++;
	              if (digito > 9)
	                  digito = 0;
	              HAL_Delay(200);
	          }

	          if (BOTAO3 == 0)
	          {
	              ConfirmarDigito();
	              HAL_Delay(200);
	          }

	          if (BOTAO2 == 0)
	          {
	              if (digito > 0)
	                  digito--;
	              HAL_Delay(200);
	          }

	          if (posicao == 4)
	          {
	              int correta = 1;
	              int i;

	              for (i = 0; i < 4; i++)
	              {
	                  if (tentativa[i] != senha[i])
	                  {
	                      correta = 0;
	                      break;
	                  }
	              }

	              if (correta)
	              {
	                  ST7735_FillScreen(ST7735_BLACK);
	                  ST7735_WriteString(10, 40, "Senha correta", Font_7x10, ST7735_GREEN, ST7735_BLACK);
	                  HAL_Delay(1000);

	                  configurandoAlunos = 1;
	                  sistemaIniciado = 0;
	                  posicao = 0;
	                  digito = 0;
	                  tentativas = 0;
	                  qtdAlunos = 0;

	                  ST7735_FillScreen(ST7735_BLACK);
	                  ST7735_WriteString(10, 10, "Qtd de alunos", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	                  ST7735_WriteString(10, 25, "PA12: Aumentar", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	                  ST7735_WriteString(10, 40, "PA10: Diminuir", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	                  ST7735_WriteString(10, 55, "PA11: Confirmar", Font_7x10, ST7735_WHITE, ST7735_BLACK);

	                  continue;
	              }
	              else
	              {
	                  tentativas++;

	                  ST7735_FillScreen(ST7735_BLACK);
	                  ST7735_WriteString(10, 40, "Senha incorreta", Font_7x10, ST7735_RED, ST7735_BLACK);
	                  HAL_Delay(2000);

	                  if (tentativas >= 3)
	                  {
	                      ST7735_FillScreen(ST7735_BLACK);
	                      ST7735_WriteString(10, 20, "3 erros", Font_7x10, ST7735_RED, ST7735_BLACK);
	                      ST7735_WriteString(10, 40, "Encerrando...", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	                      HAL_Delay(1500);

	                      tentativas = 0;
	                      posicao = 0;
	                      digito = 0;
	                      sistemaIniciado = 0;
	                      configurandoAlunos = 0;
	                      telaInicialMostrada = 0;

	                      ST7735_FillScreen(ST7735_BLACK);
	                      break;
	                  }

	                  posicao = 0;
	                  digito = 0;

	                  ST7735_FillScreen(ST7735_BLACK);
	                  ST7735_WriteString(10, 10, "Digite novamente", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	              }
	          }
	      }

	      continue;
	  }

	  if (aulaIniciada == 1)
	  {
	      char texto[40];

	      if (confirmandoFim == 0)
	      {
	          sprintf(texto, "No banheiro: %d   ", alunoBanheiro);
	          ST7735_WriteString(10, 10, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          sprintf(texto, "Limite banheiro: %d   ", limiteBanheiro);
	          ST7735_WriteString(10, 25, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          sprintf(texto, "Saidas: %d   ", totalForamBanheiro);
	          ST7735_WriteString(10, 40, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          sprintf(texto, "Alunos: %d/%d   ", alunosPresentes, qtdAlunos);
	          ST7735_WriteString(10, 55, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	          int larguraTotal = 100;
	          int alturaBarra = 8;
	          int xBarra = 10;
	          int yBarra = 70;
	          int larguraPreenchida = 0;

	          if (qtdAlunos > 0)
	          {
	              larguraPreenchida = (alunosPresentes * larguraTotal) / qtdAlunos;
	          }

	          if (larguraPreenchida > larguraTotal)
	          {
	              larguraPreenchida = larguraTotal;
	          }

	          ST7735_DrawLine(xBarra, yBarra, xBarra + larguraTotal, yBarra, ST7735_WHITE);
	          ST7735_DrawLine(xBarra, yBarra + alturaBarra, xBarra + larguraTotal, yBarra + alturaBarra, ST7735_WHITE);
	          ST7735_DrawLine(xBarra, yBarra, xBarra, yBarra + alturaBarra, ST7735_WHITE);
	          ST7735_DrawLine(xBarra + larguraTotal, yBarra, xBarra + larguraTotal, yBarra + alturaBarra, ST7735_WHITE);

	          for (int i = 0; i < larguraPreenchida; i++)
	          {
	              ST7735_DrawLine(xBarra + i, yBarra + 1, xBarra + i, yBarra + alturaBarra - 1, ST7735_GREEN);
	          }

	          if (BOTAO3 == 0)
	          {
	              confirmandoFim = 1;

	              ST7735_FillScreen(ST7735_BLACK);
	              ST7735_WriteString(10, 10, "Finalizar aula?", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	              ST7735_WriteString(10, 30, "Segure B3 e B1", Font_7x10, ST7735_GREEN, ST7735_BLACK);
	              ST7735_WriteString(10, 45, "B2/B4 cancela", Font_7x10, ST7735_RED, ST7735_BLACK);

	              HAL_Delay(300);
	          }

	          else if (BOTAO1 == 0)
	          {
	              if (alunosPresentes < qtdAlunos)
	              {
	                  Alunos();
	                  alunosPresentes++;
	              }

	              HAL_Delay(200);
	          }

	          else if (BOTAO4 == 0)
	          {
	              if (alunoBanheiro < limiteBanheiro)
	              {
	                  alunoBanheiro++;
	                  totalForamBanheiro++;
	              }

	              HAL_Delay(200);
	          }

	          else if (BOTAO2 == 0)
	          {
	              if (alunoBanheiro > 0)
	                  alunoBanheiro--;

	              HAL_Delay(200);
	          }
	      }
	      else
	      {
	          if (BOTAO1 == 0 && BOTAO3 == 0)
	          {
	              ST7735_FillScreen(ST7735_BLACK);

	              sprintf(texto, "Saidas: %d", totalForamBanheiro);
	              ST7735_WriteString(10, 20, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	              sprintf(texto, "Alunos: %d", alunosPresentes);
	              ST7735_WriteString(10, 40, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);

	              HAL_Delay(3000);

	              aulaIniciada = 0;
	              inicio = 0;
	              telaInicialMostrada = 0;
	              sistemaIniciado = 0;
	              posicao = 0;
	              digito = 0;
	              confirmandoFim = 0;

	              ST7735_FillScreen(ST7735_BLACK);
	              break;
	          }

	          else if (BOTAO2 == 0 || BOTAO4 == 0)
	          {
	              confirmandoFim = 0;
	              ST7735_FillScreen(ST7735_BLACK);
	              HAL_Delay(300);
	          }
	      }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin LED1_Pin LED2_Pin
                           LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BOTAO1_Pin BOTAO2_Pin BOTAO3_Pin BOTAO4_Pin */
  GPIO_InitStruct.Pin = BOTAO1_Pin|BOTAO2_Pin|BOTAO3_Pin|BOTAO4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Alunos(void){
	ST7735_FillScreen(ST7735_BLACK);
	char texto[30];
	   ST7735_WriteString(10, 40, "Escaneando face....", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	   HAL_Delay(1000);
	   ST7735_FillScreen(ST7735_BLACK);
	   campo[qtdAlunos] = matricula_Aluno;

	   sprintf(texto, "Matricula: %d  ", matricula_Aluno);
	   ST7735_WriteString(10, 40, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	   HAL_Delay(2000);
	   ST7735_FillScreen(ST7735_BLACK);
}
void Senha(void)
{
    srand(HAL_GetTick());
    for (int i = 0; i < 4; i++)
    {
        senha[i] = (rand() % 9)+ 1;
        MostrarBinario(senha[i]);


    }

}
void MostrarDigitacao(void)
{
    char texto[30];

    sprintf(texto, "Digito %d: %d  ", posicao + 1, digito);
    ST7735_WriteString(10, 70, texto, Font_7x10, ST7735_WHITE, ST7735_BLACK);
}
void ApagarLeds(void)
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}
void MostrarBinario(int numero)
{
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(10, 40, "Gerando senha...", Font_7x10, ST7735_WHITE, ST7735_BLACK);
	HAL_Delay (1000);
	ApagarLeds();
	if(numero & 1) LED1_ON;
	if(numero & 2) LED2_ON;
	if(numero & 4) LED3_ON;
	if(numero & 8) LED4_ON;
	HAL_Delay(2000);
	ApagarLeds();
	HAL_Delay(300);
}
void ConfirmarDigito(void)
{
    if (sistemaIniciado == 1 && posicao < 4)
    {
        tentativa[posicao] = digito;
        posicao++;

        digito = 0;

        HAL_Delay(250);
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
