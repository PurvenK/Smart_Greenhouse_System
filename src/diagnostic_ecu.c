#include "can_utils.h"
#include <time.h>


int main()
{
    int can_socket;

    struct can_frame frame;

    unsigned char data[1];

    time_t last_heartbeat;


    can_socket = open_can_socket("homecan");


    printf("Diagnostic ECU Started\n");


    last_heartbeat = time(NULL);



    while(1)
    {

        // Wait for CAN message
        frame = receive_can_message(can_socket);



        // Heartbeat received
        if(frame.can_id == 0x102)
        {
            last_heartbeat = time(NULL);

            printf("Sensor ECU Alive\n");
        }



        // Temperature check
        else if(frame.can_id == 0x100)
        {
            int temperature = frame.data[0];


            if(temperature > 100)
            {
                printf("FAULT: Invalid Temperature\n");


                data[0] = 0x02;


                send_can_message(
                    can_socket,
                    0x400,
                    data,
                    1
                );
            }
        }



        // Humidity check
        else if(frame.can_id == 0x101)
        {
            int humidity = frame.data[0];


            if(humidity > 100)
            {
                printf("FAULT: Invalid Humidity\n");


                data[0] = 0x03;


                send_can_message(
                    can_socket,
                    0x400,
                    data,
                    1
                );
            }
        }



        // Timeout check
        if(difftime(time(NULL),
                    last_heartbeat) > 5)
        {
            printf("FAULT: Sensor ECU Timeout\n");


            data[0] = 0x01;


            send_can_message(
                can_socket,
                0x400,
                data,
                1
            );


            last_heartbeat = time(NULL);
        }

    }


    close(can_socket);

    return 0;
}
