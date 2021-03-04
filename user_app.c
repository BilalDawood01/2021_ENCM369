/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"
#define _XTAL_FREQ 64000000

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    T0CON0 = 0x90;
    T0CON1 = 0x54;  
} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
//    static u16 u16Counter = 0;
//    if(u16Counter == 500)
//    {
//        RA0 ^= 0x01; //
//        u16Counter = 0;
//    }
//    u16Counter++;
    
    static u16 u16TimerCounter = 0;             
    static u16 u16LedState[] = {0x2A}; //the value to be bitmasked                    
       
    u16 u16LataState = 0x80&LATA;//clears all LEDs to be written in               
    
    if(u16TimerCounter==250)
    {   u16LedState[0] ^= 0x3F;//all 1s becomes zero, zeros become 1
        LATA = u16LataState|u16LedState[0];//updates temp lata variable with new 
                                          //LED sequence

        u16TimerCounter=0;
    }
 
    u16TimerCounter++;
    
    
} /* end UserAppRun */

void TimeXus(u16 u16Microseconds){
    T0CON0 &= 0x7F; //turns off
    
    u16 u16OverFlow = 0xFFFF - u16Microseconds; //to make sure reset is done properly 
    
    u8 u8LowInput = u16OverFlow & 0xFF;
    u8 u8HighInput = (u16OverFlow>>8)& 0xFF;
    
    TMR0L = u8LowInput; //stores 8 lower bits of our counter
    TMR0H = u8HighInput; //stores 8 MSB of counter
    
    PIR3 = PIR3&0x7F;//sets flag low, resets warning to let the timer know the counter is done
    
    T0CON0 = T0CON0 | 0X80;//turns the timer back on
}


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
