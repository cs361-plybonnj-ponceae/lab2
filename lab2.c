/*
 * CS 361: Lab02
 *
 * Name: Nic Plybon & Adrien Ponce
 * This code complies with the JMU Honor Code
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct msg {
  char magic[8];
  uint32_t id;
  char now[200];
  char data[36];
};

int main (int argc, char **argv) {

    mqd_t mq_desc;
    struct mq_attr attributes;
    char * buffer;
    ssize_t n;
    struct msg msg;


    if (argc != 2) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    //Open the queue, creating if necessary
    if ((mq_desc = mq_open(argv[1], O_RDONLY, NULL)) < 0) {
        printf("Error opening message queue %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    // Get attributes for the queue
    mq_getattr(mq_desc, &attributes);
    printf("Queue <%s>\n", argv[1]);
    printf("\tFlags:\t\t\t<%ld>\n", attributes.mq_flags);
    printf("\tMax messages:\t\t<%ld>\n", attributes.mq_maxmsg);
    printf("\tMax size:\t\t<%ld>\n", attributes.mq_msgsize);
    printf("\tCurrent messages:\t<%ld>\n\n\n", attributes.mq_curmsgs);

    // Allocate space for buffer
    buffer = malloc(attributes.mq_msgsize + 1);
    if (buffer == NULL) {
        return 1;
    }

    // Receive the message 
    n = mq_receive(mq_desc, buffer, attributes.mq_msgsize, NULL);
    if (n < 0) {
        printf("Error receiving message from %s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    buffer[n] = '\0';

    for (int i = 0; i < 8; i++) {
        msg.magic[i] = buffer[i];
    }

 
    char * magic = "cs361lab";
    if (strncmp(msg.magic, magic, 8) == 0) {
        printf("Received message (<%ld> bytes):\n", n);
        printf("\tMagic:\t<%s>\n", msg.magic);
        printf("\tID:\t<>\n");
        printf("\tTime:\t<");
         for (int i = 11; i < 211; i++) {
            printf("%c", buffer[i]);
        }
        printf(">\n");
        printf("\tData:\t<");
        for (int i = 211; i < 248; i++) {
            printf("%c", buffer[i]);
        }
        printf(">\n");


    } else {
        printf("Received message (<%ld> bytes):\n", n);
        printf("\tInvalid message\n");
    }



    




   

    free(buffer);
    return 0;
}