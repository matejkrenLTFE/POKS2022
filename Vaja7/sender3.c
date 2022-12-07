#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

int main() {
    mqd_t mq;
    char MESSAGE[MAX_SIZE] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\0";
    char MESSAGEB[MAX_SIZE] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\0";
    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    int i;
    for (i = 0; i < 15; i++) {
        if (i < 10) {
            mq_send(mq, MESSAGE, MAX_SIZE, 0); /* send the message */
            printf("%s\n", MESSAGE);
            MESSAGE[0]++;
        } else {
            mq_send(mq, MESSAGEB, MAX_SIZE, 1); /* send the message */
            printf("%s\n", MESSAGEB);
            MESSAGEB[0]++;
        }

        sleep(1);
    }
    mq_send(mq, MSG_STOP, MAX_SIZE, 0);
    mq_close(mq);
    return 0;
}
