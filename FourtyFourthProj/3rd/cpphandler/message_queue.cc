#include "message_queue.h"

namespace handler {

MessageQueue::MessageQueue()
    : is_destroyed_(false) {
        
}

MessageQueue::~MessageQueue() {
        
}

void MessageQueue::enqueueMessage(std::shared_ptr<Message> msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.emplace_back(msg);
    cond_.notify_one();
}

std::shared_ptr<Message> MessageQueue::next() {
    if (is_destroyed_) {
        return nullptr;
    }

    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] { return is_destroyed_ || !queue_.empty(); });

    if (is_destroyed_) {
        return nullptr;
    }

    std::shared_ptr<Message> msg =  queue_.front();
    queue_.pop_front();
    return msg;
}

int MessageQueue::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

bool MessageQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

void MessageQueue::quit() {
    if (is_destroyed_) {
        return;
    }

    cond_.notify_all();
    if (queue_.empty()) {
        return;
    }

    
    std::lock_guard<std::mutex> lock(mutex_);   
    queue_.clear();
    cond_.notify_all();
}

// void MessageQueue::quitSafety() {
//     if (is_destroyed_) {
//         return;
//     }

//     cond_.notify_all();
//     if (queue_.empty()) {
//         return;
//     }

    
//     std::lock_guard<std::mutex> lock(mutex_);   
//     auto it = queue_.begin();

// }

}