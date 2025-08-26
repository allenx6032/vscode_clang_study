#pragma once
#include "common.hpp"

namespace net
{

    template<typename T>
    class Queue
    {
        public:
            Queue() = default;
            Queue(const Queue<T>&) = delete;
            virtual ~Queue() {clear(); };

        public:

            const T& front()
            {
                std::scoped_lock lock(muxQueue);
                return deQueue.front();
            }

            const T& back()
            {
                std::scoped_lock lock(muxQueue);
                return deQueue.back();
            }

            T popFront()
            {
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deQueue.front());
                deQueue.pop_front();
                return t;
            }

            T popBack()
            {
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deQueue.back());
                deQueue.pop_back();
                return t;
            }

            void pushBack(const T& item)
            {
                std::scoped_lock lock(muxQueue);
                deQueue.emplace_back(std::move(item));

            }

            void pushFront(const T& item)
            {
                std::scoped_lock lock(muxQueue);
                deQueue.emplace_front(std::move(item));
            }

            bool empty()
            {
                std::scoped_lock lock(muxQueue);
                return deQueue.empty();
            }

            size_t count()
            {
                std::scoped_lock lock(muxQueue);
                return deQueue.size();
            }

            void clear()
            {
                std::scoped_lock lock(muxQueue);
                deQueue.clear();
            }

        protected:
            std::mutex muxQueue;
            std::deque<T> deQueue;
            std::condition_variable cvQueue;
            std::mutex muxBlock;
    };

}
