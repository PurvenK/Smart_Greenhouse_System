#include "can_utils.h"


int main()
{
    int can_socket;

    struct can_frame frame;

    unsigned char data[1];


    can_socket = open_can_socket("homecan");


    printf("Controller ECU Started\n");


    while(1)
    {

        frame = receive_can_message(can_socket);



        // Temperature received
        if(frame.can_id == 0x100)
        {
            int temperature = frame.data[0];


            printf("Temperature received: %d C\n",
                   temperature);



            if(temperature > 30)
            {
                data[0] = 1;

                printf("Fan Command: ON\n");
            }
            else
            {
                data[0] = 0;

                printf("Fan Command: OFF\n");
            }


            send_can_message(
                can_socket,
                0x200,
                data,
                1
            );
        }



        // Humidity received
        else if(frame.can_id == 0x101)
        {
            int humidity = frame.data[0];


            printf("Humidity received: %d %%\n",
                   humidity);



            if(humidity < 40)
            {
                data[0] = 1;

                printf("Pump Command: ON\n");
            }
            else
            {
                data[0] = 0;

                printf("Pump Command: OFF\n");
            }


            send_can_message(
                can_socket,
                0x201,
                data,
                1
            );
        }

    }


    close(can_socket);

    return 0;
}
