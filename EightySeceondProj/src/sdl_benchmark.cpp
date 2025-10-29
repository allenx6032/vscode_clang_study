#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
// #include <cmath>
#include <random>

#define _USE_MATH_DEFINES
#include <math.h>
//#include <cmath>
// #include <algorithm>
#ifndef M_PI
#define M_PI       3.14159265358979323846
#define F_PI       3.14159265358979323846f
#define M_PI_2     1.57079632679489661923
#define F_PI_2     1.57079632679489661923f  // Float precision
#define M_PI_4     0.785398163397448309616
#define F_PI_4     0.785398163397448309616f
#define M_1_PI     0.318309886183790671538
#define F_1_PI     0.318309886183790671538f
#define M_2_PI     0.636619772367581343076
#define F_2_PI     0.636619772367581343076f
#define M_2_SQRTPI 1.12837916709551257390
#define F_2_SQRTPI 1.12837916709551257390f
#define M_SQRT2    1.41421356237309504880
#define F_SQRT2    1.41421356237309504880f
#define M_SQRT1_2  0.707106781186547524401
#define F_SQRT1_2  0.707106781186547524401f
#endif

class SDL2Benchmark {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool running;
    int width, height;
    
    // 基准测试相关变量
    std::vector<double> frameTimes;
    std::chrono::high_resolution_clock::time_point startTime;
    int frameCount;
    double currentFPS;
    
    // 测试对象
    struct TestObject {
        float x, y;
        float vx, vy;
        float radius;
        SDL_Color color;
    };
    std::vector<TestObject> objects;

public:
    SDL2Benchmark(int w = 800, int h = 600) 
        : width(w), height(h), running(false), frameCount(0), currentFPS(0.0) {
    }

    ~SDL2Benchmark() {
        cleanup();
    }

    bool initialize() {
        // 初始化SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL初始化失败: " << SDL_GetError() << std::endl;
            return false;
        }

        // 创建窗口
        window = SDL_CreateWindow("SDL2 Benchmark", 
                                 SDL_WINDOWPOS_CENTERED, 
                                 SDL_WINDOWPOS_CENTERED,
                                 width, height, 
                                 SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "窗口创建失败: " << SDL_GetError() << std::endl;
            return false;
        }

        // 创建渲染器
        renderer = SDL_CreateRenderer(window, -1, 
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            std::cerr << "渲染器创建失败: " << SDL_GetError() << std::endl;
            return false;
        }

        // 初始化TTF
        if (TTF_Init() < 0) {
            std::cerr << "TTF初始化失败: " << SDL_GetError() << std::endl;
            return false;
        }

        // 加载字体
        font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
        if (!font) {
            // 尝试其他常见字体路径
            font = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 24);
            if (!font) {
                std::cerr << "字体加载失败，将无法显示文本" << std::endl;
            }
        }

        // 初始化测试对象
        initializeTestObjects(1000); // 创建1000个测试对象

        running = true;
        startTime = std::chrono::high_resolution_clock::now();
        
        return true;
    }

    void initializeTestObjects(int count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> posX(0, width);
        std::uniform_real_distribution<float> posY(0, height);
        std::uniform_real_distribution<float> velocity(-2.0f, 2.0f);
        std::uniform_real_distribution<float> radius(5.0f, 20.0f);
        std::uniform_int_distribution<int> colorComp(50, 255);

        objects.clear();
        for (int i = 0; i < count; ++i) {
            TestObject obj;
            obj.x = posX(gen);
            obj.y = posY(gen);
            obj.vx = velocity(gen);
            obj.vy = velocity(gen);
            obj.radius = radius(gen);
            obj.color = {
                static_cast<Uint8>(colorComp(gen)),
                static_cast<Uint8>(colorComp(gen)),
                static_cast<Uint8>(colorComp(gen)),
                255
            };
            objects.push_back(obj);
        }
    }

    void run() {
        while (running) {
            handleEvents();
            update();
            render();
            
            // 更新帧率统计
            updateFrameStats();
        }
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    } else if (event.key.keysym.sym == SDLK_SPACE) {
                        // 空格键重新生成测试对象
                        initializeTestObjects(objects.size());
                    } else if (event.key.keysym.sym == SDLK_UP) {
                        // 上箭头增加对象数量
                        initializeTestObjects(objects.size() + 100);
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        // 下箭头减少对象数量
                        if (objects.size() > 100) {
                            initializeTestObjects(objects.size() - 100);
                        }
                    }
                    break;
            }
        }
    }

    void update() {
        // 更新测试对象位置
        for (auto& obj : objects) {
            obj.x += obj.vx;
            obj.y += obj.vy;

            // 边界碰撞检测
            if (obj.x - obj.radius < 0 || obj.x + obj.radius > width) {
                obj.vx = -obj.vx;
                obj.x = std::max(obj.radius, std::min(obj.x, width - obj.radius));
            }
            if (obj.y - obj.radius < 0 || obj.y + obj.radius > height) {
                obj.vy = -obj.vy;
                obj.y = std::max(obj.radius, std::min(obj.y, height - obj.radius));
            }
        }
    }

    void render() {
        // 清除屏幕
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 渲染测试对象
        for (const auto& obj : objects) {
            SDL_SetRenderDrawColor(renderer, obj.color.r, obj.color.g, obj.color.b, obj.color.a);
            drawCircle(obj.x, obj.y, obj.radius);
        }

        // 渲染性能信息
        renderPerformanceInfo();

        // 更新屏幕
        SDL_RenderPresent(renderer);
    }

    void drawCircle(float x, float y, float radius) {
        // 简单的圆形绘制（使用多边形近似）
        const int segments = 20;
        std::vector<SDL_Point> points(segments + 1);
        
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * M_PI * i / segments;
            points[i].x = static_cast<int>(x + radius * cos(angle));
            points[i].y = static_cast<int>(y + radius * sin(angle));
        }
        
        SDL_RenderDrawLines(renderer, points.data(), points.size());
    }

    void renderPerformanceInfo() {
        if (!font) return;

        std::string info = "FPS: " + std::to_string(static_cast<int>(currentFPS)) + 
                          " | Objects: " + std::to_string(objects.size()) +
                          " | Frame Time: " + std::to_string(1000.0 / currentFPS).substr(0, 5) + "ms";

        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, info.c_str(), white);
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                SDL_Rect destRect = {10, 10, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &destRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }

    void updateFrameStats() {
        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

        if (elapsed >= 1000) { // 每秒更新一次FPS
            currentFPS = frameCount * 1000.0 / elapsed;
            frameCount = 0;
            startTime = currentTime;

            // 输出性能信息到控制台
            std::cout << "FPS: " << static_cast<int>(currentFPS) 
                      << " | Objects: " << objects.size()
                      << " | Frame Time: " << (1000.0 / currentFPS) << "ms" << std::endl;
        }
    }

    void runBenchmarkTest(int durationSeconds = 10) {
        std::cout << "开始基准测试，持续时间: " << durationSeconds << "秒" << std::endl;
        std::cout << "测试对象数量: " << objects.size() << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<double> fpsSamples;

        while (running) {
            handleEvents();
            update();
            render();
            updateFrameStats();

            auto current = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - start).count();

            if (elapsed >= durationSeconds) {
                break;
            }

            // 收集FPS样本
            fpsSamples.push_back(currentFPS);
        }

        // 计算统计信息
        if (!fpsSamples.empty()) {
            double avgFPS = 0;
            double minFPS = fpsSamples[0];
            double maxFPS = fpsSamples[0];

            for (double fps : fpsSamples) {
                avgFPS += fps;
                if (fps < minFPS) minFPS = fps;
                if (fps > maxFPS) maxFPS = fps;
            }
            avgFPS /= fpsSamples.size();

            std::cout << "\n=== 基准测试结果 ===" << std::endl;
            std::cout << "平均FPS: " << avgFPS << std::endl;
            std::cout << "最低FPS: " << minFPS << std::endl;
            std::cout << "最高FPS: " << maxFPS << std::endl;
            std::cout << "帧时间: " << (1000.0 / avgFPS) << "ms" << std::endl;
            std::cout << "测试对象数量: " << objects.size() << std::endl;
        }
    }

    void cleanup() {
        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        TTF_Quit();
        SDL_Quit();
    }
};


void checkEnvironmentVariables() {
    std::cout << "=== Checking SDL Environment Variables ===" << std::endl;
    
    // 检查标准环境变量
    const char* sdl_dynamic_api = std::getenv("SDL_DYNAMIC_API");
    const char* sdl_library_path = std::getenv("SDL_LIBRARY_PATH");
    const char* sdl_path = std::getenv("SDL_PATH");
    
    std::cout << "SDL_DYNAMIC_API: " << (sdl_dynamic_api ? sdl_dynamic_api : "NULL") << std::endl;
    std::cout << "SDL_LIBRARY_PATH: " << (sdl_library_path ? sdl_library_path : "NULL") << std::endl;
    std::cout << "SDL_PATH: " << (sdl_path ? sdl_path : "NULL") << std::endl;
    
    // 设置环境变量（如果需要）
    if (!sdl_dynamic_api) {
        std::cout << "Setting SDL_DYNAMIC_API environment variable..." << std::endl;
#ifdef _WIN32
        _putenv("SDL_DYNAMIC_API=libSDL2.dll");
#elif __APPLE__
        _putenv("SDL_DYNAMIC_API=libSDL2.dylib");
#else
        setenv("SDL_DYNAMIC_API", "libSDL2.so", 1);
#endif
    }
}

int main(int argc, char* argv[]) {
    
    // 或者使用编译器特定的方式
    #ifdef _MSC_VER
	// 设置栈大小为 8MB
    SetThreadStackGuarantee(&(ULONG){ 8 * 1024 * 1024 });
    #pragma comment(linker, "/STACK:8388608")
    #endif
	
    printf("Starting SDL benchmark...\n");
    
    checkEnvironmentVariables();

    SDL2Benchmark benchmark(1200, 800);
    
    if (!benchmark.initialize()) {
        std::cerr << "初始化失败!" << std::endl;
        return -1;
    }

    // 运行交互式基准测试
    // benchmark.run();

    // 或者运行固定时长的基准测试
    benchmark.runBenchmarkTest(10);

    return 0;
}