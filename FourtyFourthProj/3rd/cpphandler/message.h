#ifndef SYZ_MESSAGE_H
#define SYZ_MESSAGE_H

#include <iostream>
#include <memory>

namespace handler {

class Handler;
class Message {
public:
    Message();
    ~Message();
    int what;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    bool flag1;
    void *obj1;
    void *obj2;
    void *obj3;
    void *obj4;

private:
    std::weak_ptr<Handler> target;
};

}

#endif // SYZ_MESSAGE_H