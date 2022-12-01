#include "common.h"

int main() {
    mqd_t mq;
    char MESSAGE[MAX_SIZE] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\0";
    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);

    for (i = 0; i < 15; i++) {
        mq_send(mq, MESSAGE, MAX_SIZE, 0); /* send the message */
                                           // printf();
        // sleep();
    }
    mq_send(mq, MSG_STOP, MAX_SIZE, 0);
    mq_close(mq);
    return 0;
}
