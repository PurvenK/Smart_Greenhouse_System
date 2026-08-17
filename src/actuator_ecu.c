#include "can_utils.h"


int main()
{
    int can_socket;

    struct can_frame frame;

    unsigned char data[1];


    int fan_status = 0;
    int pump_status = 0;


    can_socket = open_can_socket("homecan");


    printf("Actuator ECU Started\n");


    while(1)
    {

        frame = receive_can_message(can_socket);



        // Fan command
        if(frame.can_id == 0x200)
        {
            fan_status = frame.data[0];


            if(fan_status)
                printf("Fan: ON\n");
            else
                printf("Fan: OFF\n");

        }



        // Water pump command
        else if(frame.can_id == 0x201)
        {
            pump_status = frame.data[0];


            if(pump_status)
                printf("Water Pump: ON\n");
            else
                printf("Water Pump: OFF\n");

        }



        // Send actuator status
        data[0] = fan_status | (pump_status << 1);


        send_can_message(
            can_socket,
            0x300,
            data,
            1
        );

    }


    close(can_socket);

    return 0;
}
