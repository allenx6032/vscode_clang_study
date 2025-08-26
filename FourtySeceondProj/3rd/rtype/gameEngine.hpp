/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "AssetManager.hpp"
#include "registry.hpp"
#include "LuaManager.hpp"
#include "network.hpp"
#include "TimeManager.hpp"
#include "JsonManager.hpp"
#include "GraphicLib.hpp"

class GameEngine : public Registry, public TimeManager, public Network, public LuaManager, public JsonManager, public AssetManager {
    public :
        GameEngine() = default;
        ~GameEngine() = default;

    // INFO: Network encapsulation
    public:
        // TODO

    // INFO: ECS encapsulation (Registry) (Overload)
    public:
        /**
         * @brief Add a system to the registry
         *
         * @tparam Components The components that the system will use
         * @param f The function that will be called when the system is run
         * @note The function must take a GameEngine & as first parameter and the components as following parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename Function>
        std::function<void()> ecsAddSystem(Function &&f)
        {
            // convert function to lambda
            _systems.push_back([f](GameEngine &r) {
                f(r, r.ecsGetComponents<Components>()...);
            });

            // iterator to the element we just added so we can remove it later if needed
            auto var = _systems.end() - 1;

            return [this, var](){
                _systems.erase(var);
            };
        };

        /**
         * @brief Add a system to the registry
         *
         * @tparam Components The components that the system will use
         * @param f The function that will be called when the system is run
         * @note The function must take a GameEngine & as first parameter and the components as following parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename Function>
        std::function<void()> ecsAddSystem(Function const &f)
        {
            // convert function to lambda
            _systems.push_back([f](GameEngine &r) {
                f(r, r.ecsGetComponents<Components>()...);
            });

            // iterator to the element we just added so we can remove it later if needed
            auto var = _systems.end() - 1;

            return [this, var](){
                _systems.erase(var);
            };
        };

        /**
         * @brief Add a system to the registry
         *
         * @tparam Components The components that the system will use
         * @param f The function that will be called when the system is run
         * @param p The extra parameters that will be passed to the function
         * @note The function must take a GameEngine & as first parameter and the components as following parameters and the extra parameters as last parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename... ExtraParams, typename Function>
        std::function<void()> ecsAddSystem(Function &&f, ExtraParams &&...p)
        {
            // convert function to lambda
            _systems.push_back([f, &p...](GameEngine &r) {
                f(r, r.ecsGetComponents<Components>()..., std::forward<ExtraParams>(p)...);
            });

            // iterator to the element we just added so we can remove it later if needed
            auto var = _systems.end() - 1;

            return [this, var](){
                _systems.erase(var);
            };
        };

        // /**
        //  * @brief Add a system to the registry
        //  *
        //  * @tparam Components The components that the system will use
        //  * @param f The function that will be called when the system is run
        //  * @param p The extra parameters that will be passed to the function
        //  * @note The function must take a GameEngine & as first parameter and the components as following parameters and the extra parameters as last parameters
        //  *
        //  * @return A function to remove the system from the registry
        //  */
        // template <class... Components, typename... ExtraParams, typename Function>
        // std::function<void()> ecsAddSystem(Function const &f, ExtraParams &&...p)
        // {
        //     // convert function to lambda
        //     _systems.push_back([f, &p...](GameEngine &r) {
        //         f(r, r.ecsGetComponents<Components>()..., std::forward<ExtraParams>(p)...);
        //     });

        //     // iterator to the element we just added so we can remove it later if needed
        //     auto var = _systems.end() - 1;

        //     return [this, var](){
        //         _systems.erase(var);
        //     };
        // };

        /**
         * @brief Delete all systems from the registry
         */
        void ecsClearSystems()
        {
            _systems.clear();
        };

        /**
         * @brief Run all the systems
         *
         * @note The systems are run in the order they were added
         */
        void ecsRunSystems()
        {
            for (auto const &system : _systems)
                system(*this);
            auto end = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(end - _start).count();
            _start = std::chrono::high_resolution_clock::now();
        };

        /**
         * @brief Run a single system
         *
         * @tparam Components The components that the system will use
         * @param f The system to run
         * @note The function must take a GameEngine & as first parameter and the components as following parameters
         */
        template <class... Components, typename Function>
        void ecsRunSingleSystem(Function &&f) {
            f(*this, ecsGetComponents<Components>()...);
        };

        /**
         * @brief Run a single system
         *
         * @tparam Components The components that the system will use
         * @param f The system to run
         * @param p The extra parameters that will be passed to the function
         * @note The function must take a GameEngine & as first parameter and the components as following parameters and the extra parameters as last parameters
         */
        template <class... Components, typename... ExtraParams, typename Function>
        void ecsRunSingleSystem(Function &&f, ExtraParams &&...p) {
            f(*this, ecsGetComponents<Components>()..., std::forward<ExtraParams>(p)...);
        };

    // INFO: Public Variables
    public:
        // delta time
        float deltaTime = 0.0f;

    private:
        std::vector<std::function<void(GameEngine &)>> _systems;
        std::chrono::time_point<std::chrono::high_resolution_clock> _start = std::chrono::high_resolution_clock::now();
};

#include "systems.hpp"

void test();
