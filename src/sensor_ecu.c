#include "can_utils.h"
#include <time.h>


int main()
{
    int can_socket;

    unsigned char data[1];


    can_socket = open_can_socket("homecan");


    printf("Sensor ECU Started\n");


    srand(time(NULL));


    while(1)
    {
        int temperature;
        int humidity;


        temperature = 20 + rand()%21; 
        humidity = 30 + rand()%51;


        // Temperature message 0x100
        data[0] = temperature;

        send_can_message(
            can_socket,
            0x100,
            data,
            1
        );


        // Humidity message 0x101
        data[0] = humidity;

        send_can_message(
            can_socket,
            0x101,
            data,
            1
        );


        // Heartbeat message 0x102
        data[0] = 0xAA;

        send_can_message(
            can_socket,
            0x102,
            data,
            1
        );


        printf("--------------------\n");
        printf("Temperature: %d C\n", temperature);
        printf("Humidity: %d %%\n", humidity);
        printf("Heartbeat Sent\n");


        sleep(2);
    }


    close(can_socket);

    return 0;
}
