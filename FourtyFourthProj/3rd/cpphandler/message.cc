#include "message.h"

namespace handler {

Message::Message() : what(-1)
  , arg1(-1)
  , arg2(-1)
  , arg3(-1)
  , arg4(-1)
  , arg5(-1)
  , arg6(-1)
  , arg7(-1)
  , flag1(false)
  , obj1(nullptr)
  , obj2(nullptr)
  , obj3(nullptr)
  , obj4(nullptr)
  , target() {

}


Message::~Message() {
    std::cout << "~Message" << std::endl;
}

}