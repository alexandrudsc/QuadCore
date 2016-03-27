#include <pic16f917.h>
#include "i2c.h"
#include "adc.h"
/* handler for all interrupts. 
 * 
 */
interrupt void ISR()
{
    if (SSPIF) {
        i2c_interrupt();
    }
     
    if (ADIF) {
        
    }
}
