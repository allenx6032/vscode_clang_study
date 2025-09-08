#ifndef SYZ_MESSAGE_QUEUE_H
#define SYZ_MESSAGE_QUEUE_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>

namespace handler {

class Message;
class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();

    void enqueueMessage(std::shared_ptr<Message> msg);
    std::shared_ptr<Message> next();

    int size() const;
    bool isEmpty() const;

    void quit();
    // void quitSafety();

private:
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    std::list<std::shared_ptr<Message>> queue_;
    bool is_destroyed_;
};

}

#endif // SYZ_MESSAGE_QUEUE_H