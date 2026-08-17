#ifndef CAN_UTILS_H
#define CAN_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>


// Open SocketCAN interface
int open_can_socket(char *interface)
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;


    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(s < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }


    strcpy(ifr.ifr_name, interface);

    ioctl(s, SIOCGIFINDEX, &ifr);


    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;


    if(bind(s,
            (struct sockaddr *)&addr,
            sizeof(addr)) < 0)
    {
        perror("CAN bind failed");
        exit(1);
    }


    return s;
}


// Send CAN message
void send_can_message(int socket,
                      int id,
                      unsigned char *data,
                      int length)
{
    struct can_frame frame;


    frame.can_id = id;
    frame.can_dlc = length;


    for(int i=0;i<length;i++)
    {
        frame.data[i] = data[i];
    }


    if(write(socket,
             &frame,
             sizeof(frame)) != sizeof(frame))
    {
        perror("CAN send failed");
    }
}


// Receive CAN message
struct can_frame receive_can_message(int socket)
{
    struct can_frame frame;


    read(socket,
         &frame,
         sizeof(frame));


    return frame;
}


#endif
