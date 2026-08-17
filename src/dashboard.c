#include "can_utils.h"


int main()
{
    int can_socket;

    struct can_frame frame;


    can_socket = open_can_socket("homecan");


    printf("==============================\n");
    printf("   SMART GREENHOUSE DASHBOARD\n");
    printf("==============================\n");


    while(1)
    {

        frame = receive_can_message(can_socket);



        // Temperature display
        if(frame.can_id == 0x100)
        {
            printf("\nTemperature: %d C\n",
                   frame.data[0]);
        }



        // Humidity display
        else if(frame.can_id == 0x101)
        {
            printf("Humidity: %d %%\n",
                   frame.data[0]);
        }



        // Actuator status
        else if(frame.can_id == 0x300)
        {
            int status = frame.data[0];


            if(status & 0x01)
                printf("Fan: ON\n");
            else
                printf("Fan: OFF\n");



            if(status & 0x02)
                printf("Water Pump: ON\n");
            else
                printf("Water Pump: OFF\n");
        }



        // Fault messages
        else if(frame.can_id == 0x400)
        {

            if(frame.data[0] == 0x01)
            {
                printf("FAULT: Sensor ECU Timeout\n");
            }


            else if(frame.data[0] == 0x02)
            {
                printf("FAULT: Invalid Temperature\n");
            }


            else if(frame.data[0] == 0x03)
            {
                printf("FAULT: Invalid Humidity\n");
            }

        }

    }


    close(can_socket);

    return 0;
}
