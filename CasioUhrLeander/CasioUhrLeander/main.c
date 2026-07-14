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
    
    uint8_t wochenTagCounter = 0;
    
    uint8_t tag = 1;
    
    uint8_t tagCounter = 0;
    
    
    //Arays
    const char * ZeitMode[] = 
    {
       /*0*/ "AM ",
       /*1*/ "PM ",
       /*2*/ "24h",
    };
    
    const char * WochenTage[] =
    {
        /*0*/   "MO",
        /*1*/   "TU",
        /*2*/   "WE",
        /*3*/   "TH",
        /*4*/   "FR",
        /*5*/   "SA",
        /*6*/   "SO",
    };
    
    const char * WochenTagAnzahl[] =
    {
        /*0*/   "31",
        /*1*/   "28",
        /*2*/   "31",
        /*3*/   "30",
        /*4*/   "31",
        /*5*/   "30",
        /*6*/   "31",
        /*7*/   "31",
        /*8*/   "30",
        /*9*/   "31",
        /*10*/  "30",
        /*11*/  "31",
    };

    while (1)
    {
        systemTime_ms = getSystemTimeMs  ();
        
        
        if ((systemTime_ms - timeSecoundsReset) >= 1000)
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
              wochenTagCounter = wochenTagCounter + 1;
            }
        
        if (tag > WochenTagAnzahl[tagCounter])
        {
            tag = 1;
            tagCounter = tagCounter + 1; 
        }
        
        if (wochenTagCounter > 6)
        {
            wochenTagCounter = 0;
        }
        
        
        
        hoursAnzeige = vierUndZwanzigStundenMode ? (timeHours % 12 ) : timeHours;
             
        lcdWriteText  (0,0, "%s", ZeitMode[stundenMode]);
        lcdWriteText  (0,7, "%02u",tag);
        lcdWriteText  (0,4, "%s",WochenTage[wochenTagCounter]);
        lcdWriteText  (1,0, "%02u : %02u : %02u",hoursAnzeige , timeMinutes, timeSecounds);
        
    }
}

