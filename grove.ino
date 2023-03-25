#include <avdweb_AnalogReadFast.h>

int max_analog_dta = 300;
int min_analog_dta = 100;
int static_analog_dta = 0;

int getAnalog(int pin) {
    long sum = 0;
    for (int i = 0; i < 32; i++) {
        sum += analogReadFast(pin);
    }
    int dta = sum >> 5;
    max_analog_dta = max(dta, max_analog_dta);
    min_analog_dta = min(dta, min_analog_dta);
    return dta;
}

void setup() {
    Serial.begin(9600);
    long sum = 0;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j < 100; j++) {
            sum += getAnalog(A0);
            delayMicroseconds(100); // уменьшаем задержку
        }
    }
    static_analog_dta = sum / 1100;
}

int level = 5;
int level_buf = 5;

void loop() {
    int val = analogReadFast(A0); // быстрый аппаратный аналоговый ввод
    int level2;
    if (val > static_analog_dta) {
        level2 = 5 + map(val, static_analog_dta, max_analog_dta, 0, 5);
    } else {
        level2 = 5 - map(val, min_analog_dta, static_analog_dta, 0, 5);
    }
    if (level2 > level) {
        level++;
    } else if (level2 < level) {
        level--;
    }
    if (level != level_buf) {
        level_buf = level;
    }
    Serial.println(val);
    delayMicroseconds(100); // уменьшаем задержку
}
