/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int LED_PIN_R = 14; 
const int BTN_PIN_RED = 15;

const int FASE_1 = 10;
const int FASE_2 = 11;
const int FASE_3 = 12;
const int FASE_4 = 13;

void step() {
    gpio_put(FASE_1, 1);
    gpio_put(FASE_2, 0);
    gpio_put(FASE_3, 0);
    gpio_put(FASE_4, 0);
    sleep_ms(5);

    gpio_put(FASE_1, 0);
    gpio_put(FASE_2, 1);
    gpio_put(FASE_3, 0);
    gpio_put(FASE_4, 0);
    sleep_ms(5);

    gpio_put(FASE_1, 0);
    gpio_put(FASE_2, 0);
    gpio_put(FASE_3, 1);
    gpio_put(FASE_4, 0);
    sleep_ms(5);

    gpio_put(FASE_1, 0);
    gpio_put(FASE_2, 0);
    gpio_put(FASE_3, 0);
    gpio_put(FASE_4, 1);
    sleep_ms(5);
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_init(BTN_PIN_RED);

    gpio_init(FASE_1);
    gpio_init(FASE_2);
    gpio_init(FASE_3);
    gpio_init(FASE_4);

    gpio_set_dir(FASE_1, GPIO_OUT);
    gpio_set_dir(FASE_2, GPIO_OUT);
    gpio_set_dir(FASE_3, GPIO_OUT);
    gpio_set_dir(FASE_4, GPIO_OUT);



    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_set_dir(BTN_PIN_RED, GPIO_IN);


    gpio_pull_up(BTN_PIN_RED);
    while (true) {
        if (!gpio_get(BTN_PIN_RED)) {
            gpio_put(LED_PIN_R, 1);
            for (int i = 0; i < 512; i++) {
                step();
            }
            while (!gpio_get(BTN_PIN_RED)) {
            };
        } else {
            gpio_put(LED_PIN_R, 0);
        }
    }
}
