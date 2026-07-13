/*
* CasioUhrLeander.c
*
* Created: 13.07.2026 08:24:56
* Author : e4Ineich
*/

#include "ucBoardDriver.h"


int main(void)
{
    initBoard  (1);
    lcdLight  (255);
    
    //Variabeln
    uint8_t timeSecounds = 0;
    uint32_t systemTime_ms = 0;
    uint32_t timeSecoundsReset = 0;
    uint8_t timeMinutes = 0;
    uint8_t timeHours = 0;
    uint8_t vierUndZwanzigStundenMode = 0;
    
    uint8_t tasterModeNeu = 0;
    uint8_t tasterModeAlt = 0;
    uint8_t tasterModeFlanke = 0;
    

    while (1)
    {
        systemTime_ms = getSystemTimeMs  ();
        
        
        if ((systemTime_ms - timeSecoundsReset) >= 10)
        {
            timeSecounds = timeSecounds + 60;
            timeSecoundsReset = systemTime_ms;
        }
        
        tasterModeNeu = buttonReadPL  (1);
        
        tasterModeFlanke = tasterModeNeu && !tasterModeAlt;
        tasterModeAlt = tasterModeNeu;
        
        if (tasterModeFlanke)
        {
            vierUndZwanzigStundenMode = !vierUndZwanzigStundenMode;
            tasterModeFlanke = 0;
        }
        
        
        //---------------------------------------------------
        
        if (vierUndZwanzigStundenMode)
        {
            if (timeSecounds >= 60)
            {
                timeMinutes = timeMinutes + 1;
                timeSecounds = 0;
            }
            
            if (timeMinutes >= 60)
            {
                timeHours = timeHours + 1;
                timeSecounds = 0;
                timeMinutes = 0;
                
            }
            
            if (timeHours >= 24)
            {
                timeSecounds = 0;
                timeMinutes = 0;
                timeHours = 0;
            }
        }
        else
        {
            if (timeSecounds >= 60)
            {
                timeMinutes = timeMinutes + 1;
                timeSecounds = 0;
            }
            
            if (timeMinutes >= 60)
            {
                timeHours = timeHours + 1;
                timeSecounds = 0;
                timeMinutes = 0;
                
            }
            
            if (timeHours >= 12)
            {
                timeSecounds = 0;
                timeMinutes = 0;
                timeHours = 0;
            }
        }
        
        lcdWriteText  (1,0, "%02u : %02u : %02u", timeHours, timeMinutes, timeSecounds);
        
    }
}

