#pragma once
#include "System.h"
#include "Transform.h"
#include "RelativeTransform.h"
#include "LimitTransform.h"

class TransformSystem : public System
{
public:
    void run(World &world) override;

private:
    void update_relative_tr(int index, RelativeTransform *rtr,World &world);
    void update_limit_tr(LimitTransform *ltr,World &world);
};
