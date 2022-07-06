/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G12 V2.04.06.02 [08 Nov 2021]
* Device(s)    : R5F10277
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 26-05-2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#include <stdio.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define LED_POWER (P2_bit.no1) // 1 POWER
#define LED_LOW (P0_bit.no0)   // 2 LOW
#define LED_MED (P0_bit.no1)   // 3 MED
#define LED_HIGH (P0_bit.no2)  // 4 HIGH
#define LED_TUB (P0_bit.no3)   // 5 TUB
#define LED_FLAT (P6_bit.no0)  // 6 FLAT
#define LED_SMF (P6_bit.no1)   // 7 SMF
#define LED_LOCAL (P2_bit.no0) // 8 LOCAL
//#define ECO (P4_bit.no0)       // ECO/UPS
//#define BUZZ (P1_bit.no0)



//////////////////////////////////////
#define NO_OF_BATTERIES 4
#define NO_OF_CURRENT 3
#define SELECTION_HYS_COUNT 10

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

uint16_t battery[NO_OF_BATTERIES][NO_OF_CURRENT] = {

    /*   H         M       L              */ /*U_R = 0*/

    {691, 851, 1023}, /*Tubular*/

    {506, 623, 750}, /*Flat*/

    {303, 374, 450}, /*VRLA/SMF*/

    {166, 204, 246} /*Local*/

};


 uint16_t test[6]= {299, 239, 1019,510,379,167};

// ECO = 1;
void delay()
{
    uint32_t i = 100000;
    while (i--)
        WDTE = 0xACU; /* restart watchdog timer */
}


const uint16_t adcValue = 1;
uint8_t tBatt, tCurr;
uint16_t i;
uint16_t j;
uint16_t out;


void led_test(uint16_t x){
  WDTE = 0xACU; /* restart watchdog timer */


                  if (x>=battery[0][0] - SELECTION_HYS_COUNT && x<=battery[0][0]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 1;
                     LED_FLAT = 0;
                     LED_SMF = 0;
                     LED_LOCAL = 0;
                    //    P0_bit.no2 = 1;
                      LED_HIGH = 1;
                    
                     LED_MED = 0;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[1][0] - SELECTION_HYS_COUNT && x<=battery[1][0]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 1;
                     LED_SMF = 0;
                     LED_LOCAL = 0;

                     LED_HIGH = 1;
                     LED_MED = 0;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[2][0] - SELECTION_HYS_COUNT && x<=battery[2][0]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 0;
                     LED_SMF = 1;
                     LED_LOCAL = 0;

                     LED_HIGH = 1;
                     LED_MED = 0;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[3][0] - SELECTION_HYS_COUNT && x<=battery[3][0]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 0;
                     LED_SMF = 0;
                     LED_LOCAL = 1;

                     LED_HIGH = 1;
                     LED_MED = 0;
                     LED_LOW = 0;
                 }

                 else if (x>=battery[0][1] - SELECTION_HYS_COUNT && x<=battery[0][1]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 1;
                     LED_FLAT = 0;
                     LED_SMF = 0;
                     LED_LOCAL = 0;

                     LED_HIGH = 0;
                     LED_MED = 1;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[1][1] - SELECTION_HYS_COUNT && x<=battery[1][1]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 1;
                     LED_SMF = 0;
                     LED_LOCAL = 0;

                     LED_HIGH = 0;
                     LED_MED = 1;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[2][1] - SELECTION_HYS_COUNT && x<=battery[2][1]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 0;
                     LED_SMF = 1;
                     LED_LOCAL = 0;

                     LED_HIGH = 0;
                     LED_MED = 1;
                     LED_LOW = 0;
                 }
                 else if (x>=battery[3][1] - SELECTION_HYS_COUNT && x<=battery[3][1]+SELECTION_HYS_COUNT)
                 {
                     LED_TUB = 0;
                     LED_FLAT = 0;
                     LED_SMF = 0;
                     LED_LOCAL = 1;

                     LED_HIGH = 0;
                     LED_MED = 1;
                     LED_LOW = 0;
                 }

                     else if (x>=battery[0][2] - SELECTION_HYS_COUNT && x<=battery[0][2]+SELECTION_HYS_COUNT)
                     {
                         LED_TUB = 1;
                         LED_FLAT = 0;
                         LED_SMF = 0;
                         LED_LOCAL = 0;

                         LED_HIGH = 0;
                         LED_MED = 0;
                         LED_LOW = 1;
                     }
                     else if (x>=battery[1][2] - SELECTION_HYS_COUNT && x<=battery[1][2]+SELECTION_HYS_COUNT)
                     {
                         LED_TUB = 0;
                         LED_FLAT = 1;
                         LED_SMF = 0;
                         LED_LOCAL = 0;

                         LED_HIGH = 0;
                         LED_MED = 0;
                         LED_LOW = 1;
                     }
                     else if (x>=battery[2][2] - SELECTION_HYS_COUNT && x<=battery[2][2]+SELECTION_HYS_COUNT)
                     {
                         LED_TUB = 0;
                         LED_FLAT = 0;
                         LED_SMF = 1;
                         LED_LOCAL = 0;

                         LED_HIGH = 0;
                         LED_MED = 0;
                         LED_LOW = 1;
                     }
                     else if (x>=battery[3][2] - SELECTION_HYS_COUNT && x<=battery[3][2]+SELECTION_HYS_COUNT)
                     {
                         LED_TUB = 0;
                         LED_FLAT = 0;
                         LED_SMF = 0;
                         LED_LOCAL = 1;

                         LED_HIGH = 0;
                         LED_MED = 0;
                         LED_LOW = 1;
                     }
                 
             
             else
             {
                 LED_TUB = 0;
                 LED_FLAT = 0;
                 LED_SMF = 0;
                 LED_LOCAL = 0;

                 LED_HIGH = 0;
                 LED_MED = 0;
                 LED_LOW = 0;
             }

}
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
	R_ADC_Set_OperationOn();
    while (1U)
    {
        WDTE = 0xACU; /* restart watchdog timer */
        
        out = R_ADC_Get_Conversion(_11_AD_INPUT_CHANNEL_17);
        led_test(out);

	//if(out==1)
        //printf("out is: %b",out);

        /*--------------------
        for(i=0;i<6;i++){
          led_test(test[i]);
          delay();
        }
        ---------------------*/
    } 
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
