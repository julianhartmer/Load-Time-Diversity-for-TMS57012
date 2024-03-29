/** @file adc.c 
*   @brief ADC Driver Source File
*   @date 15.Mar.2012
*   @version 03.01.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "adc.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void adcInit(void)
*   @brief Initializes ADC Driver
*
*   This function initializes the ADC driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void adcInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */



    /** @b Initialize @b ADC1: */

    /** - Reset ADC module */
    adcREG1->RSTCR = 1U;
    adcREG1->RSTCR = 0U;

    /** - Enable 12-BIT ADC  */
    adcREG1->OPMODECR |= 0x80000000U;

    /** - Setup prescaler */
    adcREG1->CLOCKCR = 7U;
 
    /** - Setup memory boundaries */
    adcREG1->BNDCR  =(8U << 16U)|(8U + 8U);
    adcREG1->BNDEND = 2U;
 
    /** - Setup event group conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[0U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup event group hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G0SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup event group sample window */
    adcREG1->G0SAMP = 0U;

    /** - Setup event group sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G0SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Setup group 1 conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[1U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 1 hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G1SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup group 1 sample window */
    adcREG1->G1SAMP = 0U;

    /** - Setup group 1 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G1SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Setup group 2 conversion mode
     *     - Setup data format
     *     - Enable/Disable channel id in conversion result
     *     - Enable/Disable continuous conversion
     */
    adcREG1->GxMODECR[2U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 2 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG1->G2SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup group 2 sample window */
    adcREG1->G2SAMP = 0U;

    /** - Setup group 2 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G2SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Enable ADC module */
    adcREG1->OPMODECR |= 0x80140001U;

    /** - Wait for buffer inialisation complete */
    while ((adcREG1->BUFINIT) != 0) { /* Wait */ } 
    
    /** - Setup parity */
    adcREG1->PARCR = 0x00000005U;



/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void adcStartConversion(adcBASE_t *adc, uint32_t group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function starts a convesion of the ADC hardware group.
*
*/

/** - s_adcSelect is used as constant table for channel selection */
static const uint32_t s_adcSelect[2U][3U] =
{
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
   
};

/** - s_adcSelect is used as constant table for channel selection */
static const uint32_t s_adcFiFoSize[2U][3U] =
{
    16U,
    16U,
    16U,

};

/* USER CODE BEGIN (6) */
/* USER CODE END */

void adcStartConversion(adcBASE_t *adc, uint32_t group)
{
    uint32_t index = adc == adcREG1 ? 0U : 1U;

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Setup FiFo size */
    adc->GxINTCR[group] = s_adcFiFoSize[index][group];

    /** - Start Conversion */
    adc->GxSEL[group] = s_adcSelect[index][group];

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void adcStopConversion(adcBASE_t *adc, uint32_t group)
*   @brief Stops an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function stops a convesion of the ADC hardware group.
*
*/

/* USER CODE BEGIN (10) */
/* USER CODE END */

void adcStopConversion(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    /** - Stop Conversion */
    adc->GxSEL[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */


/** @fn void adcResetFiFo(adcBASE_t *adc, uint32_t group)
*   @brief Resets FiFo read and write pointer.
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function resets the FiFo read and write pointrs.
*
*/

/* USER CODE BEGIN (14) */
/* USER CODE END */

void adcResetFiFo(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    /** - Reset FiFo */
    adc->GxFIFORESETCR[group] = 1U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           the conversion should be stopped before calling this function. 
    */

/* USER CODE BEGIN (16) */
/* USER CODE END */
}

/* USER CODE BEGIN (17) */
/* USER CODE END */


/** @fn uint32_t adcGetData(adcBASE_t *adc, uint32_t group, adcData_t *data)
*   @brief Gets converted a ADC values
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[out] data Pointer to store ADC converted data
*   @return The function will return the number of converted values copied into data buffer:
*
*   This function writes a ADC message into a ADC message box.
*
*/


/* USER CODE BEGIN (18) */
/* USER CODE END */

uint32_t adcGetData(adcBASE_t *adc, uint32_t group, adcData_t *data)
{
    uint32_t       i;
    uint32_t  buf;
    uint32_t  mode;    
    uint32_t  index = adc == adcREG1 ? 0U : 1U;
    uint32_t       count = adc->GxINTCR[group] >= 256U ? s_adcFiFoSize[index][group] : s_adcFiFoSize[index][group] - (uint32_t)(adc->GxINTCR[group] & 0xFF);
    adcData_t *ptr = data; 

/* USER CODE BEGIN (19) */
/* USER CODE END */

    mode = ((adc->GxMODECR[group]) & 0x00000300U);

    if(mode == ADC_12_BIT)
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0; i < count; i++)
        {
          buf        = adc->GxBUF[group].BUF0;
          ptr->value = (uint16_t)(buf & 0xFFFU);
          ptr->id    = (uint32_t)((buf >> 16U) & 0x1FU);
          ptr++;
        }
      }
      else
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0; i < count; i++)
        {
          buf        = adc->GxBUF[group].BUF0;
          ptr->value = (uint16_t)(buf & 0x3FFU);
          ptr->id    = (uint32_t)((buf >> 10U) & 0x1FU);
          ptr++;
        }
      }


    adc->GxINTFLG[group] = 9U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           The user is responsible to initialize the message box.
    */

/* USER CODE BEGIN (20) */
/* USER CODE END */

    return count;
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32_t adcIsFifoFull(adcBASE_t *adc, uint32_t group)
*   @brief Checks if FiFo buffer is full
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When FiFo buffer is not full   
*           - 1: When FiFo buffer is full   
*           - 3: When FiFo buffer overflow occured    
*
*   This function checks FiFo buffer status.
*
*/


/* USER CODE BEGIN (22) */
/* USER CODE END */

uint32_t adcIsFifoFull(adcBASE_t *adc, uint32_t group)
{
    uint32_t flags;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    /** - Read FiFo flags */
    flags = adc->GxINTFLG[group] & 3U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (24) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (25) */
/* USER CODE END */


/** @fn uint32_t adcIsConversionComplete(adcBASE_t *adc, uint32_t group)
*   @brief Checks if Conversion is complete
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer

*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When is not finished   
*           - 8: When conversion is complete   
*
*   This function checks if conversion is complete.
*
*/


/* USER CODE BEGIN (26) */
/* USER CODE END */

uint32_t adcIsConversionComplete(adcBASE_t *adc, uint32_t group)
{
    uint32_t flags;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    /** - Read conversion flags */
    flags = adc->GxINTFLG[group] & 8U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (29) */
/* USER CODE END */

/** @fn void adcCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   This function computes offset error using Calibration mode
*
*/
void adcCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */
    
	uint32_t conv_val[5]={0,0,0,0,0},loop_index=0;
	uint32_t offset_error=0;
	uint32_t backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00;
	adc->GxSEL[1]=0x00;
	adc->GxSEL[2]=0x00;

	for(loop_index=0;loop_index<4;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0;
	
		switch(loop_index)
		{
			case 0 : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0;
						break;

			case 1 :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100;
						break;

			case 2 : 	/* Test 1 : Bride En = 1 , HiLo =0 */
						adc->CALCR=0x0200;
						break;
		
			case 3 : 	/* Test 1 : Bride En = 1 , HiLo =1 */
						adc->CALCR=0x0300;
						break;
		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000;

		/* Wait for calibration conversion to complete */
		while((adc->CALCR & 0x00010000)==0x00010000);

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0;

	/* Compute the Offset error correction value */
	conv_val[4]=conv_val[0]+ conv_val[1] + conv_val[2] + conv_val[3];

	conv_val[4]=(conv_val[4]/4);

	offset_error=conv_val[4]-0x7FF;

	/*Write the offset error to the Calibration register */
	/* Load 2;s complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFF;
	offset_error=offset_error+1;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
 /**   @note The function adcInit has to be called before using this function. */

/* USER CODE BEGIN (31) */
/* USER CODE END */
}


/** @fn void adcMidPointCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Mid Point Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   This function computes offset error using Mid Point Calibration mode
*
*/

/* USER CODE BEGIN (32) */
/* USER CODE END */

uint32_t adcMidPointCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */
    
	uint32_t conv_val[3]={0,0,0},loop_index=0;
	uint32_t offset_error=0;
	uint32_t backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00;
	adc->GxSEL[1]=0x00;
	adc->GxSEL[2]=0x00;

	for(loop_index=0;loop_index<2;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0;
	
		switch(loop_index)
		{
			case 0 : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0;
						break;

			case 1 :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100;
						break;

		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000;

		/* Wait for calibration conversion to complete */
		while((adc->CALCR & 0x00010000)==0x00010000);

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0;

	/* Compute the Offset error correction value */
	conv_val[2]=(conv_val[0])+ (conv_val[1]);

	conv_val[2]=(conv_val[2]/2);

	offset_error=conv_val[2]-0x7FF;

	/* Write the offset error to the Calibration register           */
	/* Load 2's complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFF;
	offset_error=offset_error+1;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
	return(offset_error);

 /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/* USER CODE BEGIN (35) */
/* USER CODE END */

/** @fn void adcEnableNotification(adcBASE_t *adc, uint32_t group)
*   @brief Enable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will enable the notification of a conversion.
*   In single conversion mode for conversion complete and
*   in continuous conversion mode when the FiFo buffer is full.
*
*/

/* USER CODE BEGIN (36) */
/* USER CODE END */

void adcEnableNotification(adcBASE_t *adc, uint32_t group)
{
    uint32_t notif = adc->GxMODECR[group] & 2U ? 1U : 8U;

/* USER CODE BEGIN (37) */
/* USER CODE END */

    adc->GxINTENA[group] = notif;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           This function should be called before the conversion is started
    */

/* USER CODE BEGIN (38) */
/* USER CODE END */
}

/* USER CODE BEGIN (39) */
/* USER CODE END */


/** @fn void adcDisableNotification(adcBASE_t *adc, uint32_t group)
*   @brief Disable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will disable the notification of a conversion.
*/

/* USER CODE BEGIN (40) */
/* USER CODE END */

void adcDisableNotification(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (41) */
/* USER CODE END */

    adc->GxINTENA[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (42) */
/* USER CODE END */
}

/* USER CODE BEGIN (43) */
/* USER CODE END */


/* USER CODE BEGIN (50) */
/* USER CODE END */
