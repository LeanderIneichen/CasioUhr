/*
* CasioUhrLeander.c
*
* Created: 13.07.2026 08:24:56
* Author : e4Ineich
*/

#include "ucBoardDriver.h"
#pragma GCC optimize 0


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
    uint8_t hoursAnzeige = 0;
    
    uint8_t tasterModeNeu = 0;
    uint8_t tasterModeAlt = 0;
    uint8_t tasterModeFlanke = 0;
    
    uint8_t stundenMode = 0;
    
    uint8_t tag = 1;
    
    
    //Arays
    const char * ZeitMode[] = 
    {
       /*0*/ "AM ",
       /*1*/ "PM ",
       /*2*/ "24h",
    };
    

    while (1)
    {
        systemTime_ms = getSystemTimeMs  ();
        
        
        if ((systemTime_ms - timeSecoundsReset) >= 1)
        {
            timeSecounds = timeSecounds + 1;
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
        

        if (!vierUndZwanzigStundenMode)   
        {
            stundenMode = 2;              
        }
        else                              
        {
            if (timeHours < 12)
            stundenMode = 0;          
            else
            stundenMode = 1;          
        }
        
        //---------------------------------------------------
        

            
            if (timeSecounds == 60)
            {
                timeMinutes = timeMinutes + 1;
                timeSecounds = 0;
            }
            
            if (timeMinutes == 60)
            {
                timeHours = timeHours + 1;
                timeSecounds = 0;
                timeMinutes = 0;
                
            }
            
            if (timeHours == 24)
            {
                timeSecounds = 0;
                timeMinutes = 0;
                timeHours = 0;
            }
            
            //-------------------------------------------------------------
            
            if (((hoursAnzeige == 23) && (timeMinutes == 59) && (timeSecounds == 59)) || ((hoursAnzeige == 11) && (timeMinutes == 59) && (timeSecounds == 59) && (stundenMode == 1)))
            {
              tag = tag + 1;
            }
        
        if (tag > 31)
        {
            tag = 1; 
        }
        
        
        
        hoursAnzeige = vierUndZwanzigStundenMode ? (timeHours % 12 ) : timeHours;
             
        lcdWriteText  (0,0, "%s", ZeitMode[stundenMode]);
        lcdWriteText  (1,0, "%02u : %02u : %02u",hoursAnzeige , timeMinutes, timeSecounds);
        lcdWriteText  (0,5, "%02u",tag);
        
    }
}

