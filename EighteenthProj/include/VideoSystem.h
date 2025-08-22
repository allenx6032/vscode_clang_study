#pragma once
#include "System.h"
#include "Video.h"

class VideoSystem : public System
{
public:
    void run(World &world) override;

private:
    void update_video(Video *video); // 视频
};
