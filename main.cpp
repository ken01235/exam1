#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bottom1(D8);
DigitalIn bottom2(D9);
DigitalIn bottom3(D10);
AnalogOut aout(PA_5);
AnalogIn ain(A0);

int num = 0;
uint16_t output[240] = {0};
uLCD_4DGL uLCD(D1, D0, D2);

void print_num(int);
void generate_output(void);
void sample(void);

int main()
{
    int bt1 = 0, bt2 = 0, bt3 = 0;

    EventQueue queue(2 * EVENTS_EVENT_SIZE);
    Thread t1;
    Thread t2;

    uLCD.background_color(BLACK);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(3);
    uLCD.text_height(3);
    uLCD.locate(0, 2);
    uLCD.printf(" 1/8 ");
    while(1) {
        if (!bt1 && bottom1) {
            num = (num + 1) % 4;
            uLCD.locate(0, 2);
            uLCD.color(GREEN);
            print_num(num);
            bt1 = bottom1;
        } else if (bt1 && !bottom1) {
            bt1 = bottom1;
        }

        if (!bt2 && bottom2) {
            num = (num + 3) % 4;
            uLCD.locate(0, 2);
            uLCD.color(GREEN);
            print_num(num);
            bt2 = bottom2;
        } else if (bt2 && !bottom2) {
            bt2 = bottom2;
        }

        if (!bt3 && bottom3) {
            uLCD.locate(0, 2);
            uLCD.color(RED);
            print_num(num);
            uLCD.color(GREEN);
            bt3 = bottom3;
            break;
        } else if (bt3 && !bottom3) {
            bt3 = bottom3;
        }
    }
    if (num ==  3) {
        for (int i = 0; i < 80; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 80);
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 80] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 160] = (65535 * 3 / 3.3 * (240 - i - 160) / 80);
        }
    } else if (num == 2) {
        for (int i = 0; i < 40; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 40);
        }
        for (int i = 0; i < 160; ++i) {
            output[i + 40] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 40; ++i) {
            output[i + 200] = (65535 * 3 / 3.3 * (240 - i - 200) / 40);
        }
    } else if (num == 1) {
        for (int i = 0; i < 20; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 20);
        }
        for (int i = 0; i < 200; ++i) {
            output[i + 20] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 20; ++i) {
            output[i + 220] = (65535 * 3 / 3.3 * (240 - i - 220) / 20);
        }
    } else if (num == 0) {
        for (int i = 0; i < 10; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 10);
        }
        for (int i = 0; i < 220; ++i) {
            output[i + 10] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 10; ++i) {
            output[i + 230] = (65535 * 3 / 3.3 * (240 - i - 230) / 10);
        }
    }
    // queue.call(generate_output);
    // queue.dispatch();
    if (num ==  3) {
        for (int i = 0; i < 80; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 80);
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 80] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 160] = (65535 * 3 / 3.3 * (240 - i - 160) / 80);
        }
    } else if (num == 2) {
        for (int i = 0; i < 40; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 40);
        }
        for (int i = 0; i < 160; ++i) {
            output[i + 40] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 40; ++i) {
            output[i + 200] = (65535 * 3 / 3.3 * (240 - i - 200) / 40);
        }
    } else if (num == 1) {
        for (int i = 0; i < 20; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 20);
        }
        for (int i = 0; i < 200; ++i) {
            output[i + 20] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 20; ++i) {
            output[i + 220] = (65535 * 3 / 3.3 * (240 - i - 220) / 20);
        }
    } else if (num == 0) {
        for (int i = 0; i < 10; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 10);
        }
        for (int i = 0; i < 220; ++i) {
            output[i + 10] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 10; ++i) {
            output[i + 230] = (65535 * 3 / 3.3 * (240 - i - 230) / 10);
        }
    }
    int i = 0;
    int j = 0;
    float answer[500] = {0};
    while (1) {
        aout.write_u16(output[i]);
        i = (i + 1) % 240;
        if (j < 500) {
            answer[j] = ain;
            j++;
        } else if (j == 500) {
            for (int k = 0; k < 500; ++k) {
                printf("%f\n", answer[k]);
            }
            j++;
        }
        ThisThread::sleep_for(1ms);
    }
}

void print_num(int num) {
    switch (num) {
    case 0:
        uLCD.printf(" 1/8 ");
        break;
    case 1:
        uLCD.printf(" 1/4 ");
        break;
    case 2:
        uLCD.printf(" 1/2 ");
        break;
    case 3:
        uLCD.printf("  1  ");
        break;
    default:
        break;
    }
}

void generate_output() {
    if (num ==  3) {
        for (int i = 0; i < 80; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 80);
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 80] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 80; ++i) {
            output[i + 160] = (65535 * 3 / 3.3 * (240 - i - 160) / 80);
        }
    } else if (num == 2) {
        for (int i = 0; i < 40; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 40);
        }
        for (int i = 0; i < 160; ++i) {
            output[i + 40] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 40; ++i) {
            output[i + 200] = (65535 * 3 / 3.3 * (240 - i - 200) / 40);
        }
    } else if (num == 1) {
        for (int i = 0; i < 20; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 20);
        }
        for (int i = 0; i < 200; ++i) {
            output[i + 20] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 20; ++i) {
            output[i + 220] = (65535 * 3 / 3.3 * (240 - i - 220) / 20);
        }
    } else if (num == 0) {
        for (int i = 0; i < 10; ++i) {
            output[i] = (65535 * 3 / 3.3 * i / 10);
        }
        for (int i = 0; i < 220; ++i) {
            output[i + 10] = 65535 * 3 / 3.3;
        }
        for (int i = 0; i < 10; ++i) {
            output[i + 230] = (65535 * 3 / 3.3 * (240 - i - 230) / 10);
        }
    }
}

void sample() {
    float answer[500] = {0};
    for (int i = 0; i < 500; ++i) {
        answer[i] = ain;
    }
    for (int i = 0; i < 500; ++i) {
        printf("%f\n", answer[i]);
    }
}

