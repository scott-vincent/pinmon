#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

void initPin(int pin)
{
    char command[256];

    sprintf(command, "raspi-gpio set %d pu", pin);
    system(command);

    pinMode(pin, INPUT);
}

int main()
{
    char pinNames[256] = "\0";
    char pinName[256];
    char pinStates[256] = "\0";
    char lastStates[256] = "\0";

    wiringPiSetupGpio();

    const int NumPins = 26;
    int pin[NumPins] = {
        2,3,4,17,27,22,10,9,11,5,6,13,19,26,
        14,15,18,23,24,25,8,7,12,16,20,21
    };

    for (int i = 0; i < NumPins; i++) {
        initPin(pin[i]);

        sprintf(pinName, " %02d", pin[i]);
        strcat(pinNames, pinName);
    }

    while (true) {
        pinStates[0] = '\0';

        for (int i = 0; i < NumPins; i++) {
            if (digitalRead(pin[i]) == 0) {
                strcat(pinStates, "  0");
            }
            else {
                strcat(pinStates, "  1");
            }
        }

        if (strcmp(pinStates, lastStates) != 0) {
            // Clear the screen
            printf("\033[H\033[2J");

            printf("BCM GPIO Pin States\n\n");
            printf("%s\n%s\n\n", pinNames, pinStates);

            strcpy(lastStates, pinStates);
        }

        delay(1);
    }
}
