#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <math.h>

int main() {
    stdio_init_all();
    printf("add-03\n");

    adc_init ();

    adc_gpio_init(26);
    adc_select_input(0);

    while (1) {
        uint16_t RawValue = adc_read();
        const float R1 = 10000.0;
        const float Beta = 3950.0;
        const float TempInicial = 298.0;
        const float Vref = 3.3 ;
        float VR2 = (RawValue * Vref) / 4095;
        float R2 = R1 / ( Vref / VR2 - 1 );
        
        float temperatura = Beta / (log(R2 / R1) + (Beta / TempInicial));
        printf ("Raw Value: 0x%03x , R2: %.2f Ω, VR2: %.2f V, Temperatura: %.2f °C\n", RawValue, R2, VR2, temperatura - 273);
        sleep_ms (500);
    
    }
}
