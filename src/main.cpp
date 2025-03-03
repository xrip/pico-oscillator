#include <pico.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/clocks.h>
#include <hardware/gpio.h>

#define CLOCK_SELECT_PIN 0
#define CLOCK_PIN 1

#define CLOCK_FREQUENCY_1 (26'842'600)
#define CLOCK_FREQUENCY_2 (28'636'360)

static void clock_init(uint pin, const uint32_t frequency) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    const uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config pwm = pwm_get_default_config();
    pwm_config_set_clkdiv(&pwm, clock_get_hz(clk_sys) / (4.0 * frequency));
    pwm_config_set_wrap(&pwm, 3); // MAX PWM value
    pwm_init(slice_num, &pwm, true);
    pwm_set_gpio_level(pin, 2);
}

int main() {
    gpio_init(CLOCK_SELECT_PIN);
    gpio_set_dir(CLOCK_SELECT_PIN, GPIO_IN);

    clock_init(CLOCK_PIN, CLOCK_FREQUENCY_1);

    uint8_t current_clock = 0, last_clock = 0;

    while (true) {
        current_clock = gpio_get(CLOCK_SELECT_PIN);

        if (current_clock != last_clock) {
            clock_init(CLOCK_PIN, 1 == current_clock ? CLOCK_FREQUENCY_2 : CLOCK_FREQUENCY_1);
            last_clock = current_clock;
        }

        busy_wait_us(10);
    }

}
