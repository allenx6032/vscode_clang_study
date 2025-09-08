#ifndef SYZ_LOPPER_H
#define SYZ_LOPPER_H

#include <mutex>
#include <memory>

class MessageQueue;
class Looper {
public:
    static

private:
    void loop();

    bool exiting_;
    bool exited_;
    bool exit_safely_;
    bool looping_;
    pthread_mutex_t variable_mutex_;
    std::unique_ptr<MessageQueue> message_queue_;
};

#endif // SYZ_LOPPER_H