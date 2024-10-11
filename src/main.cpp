#include <stdio.h>
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "piodco/piodco.h"
#include "morse.h"

#define PLL_SYS_MHZ 300
#define RF_GPIO 10
PioDco DCO;
void Core1Entry();

void out_enable()
{
    PioDCOStart(&DCO);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
}

void out_disable()
{
    PioDCOStop(&DCO);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
}

int main()
{
    stdio_init_all();
    set_sys_clock_khz(PLL_SYS_MHZ * 1000, true);
	multicore_launch_core1(Core1Entry);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    while (1)
    {
        playMorse("FOX 1", 15);
        sleep_ms(2000);
    }
}

void Core1Entry()
{

    const uint32_t clkhz = PLL_SYS_MHZ * 1000000;

    /* Initialize DCO */
    PioDCOInit(&DCO, RF_GPIO, clkhz);

    /* Set initial freq. */
    PioDCOSetFreq(&DCO, 3510000, 0U);

    /* Run the main DCO algorithm. It spins forever. */
    PioDCOWorker2(&DCO);
}
