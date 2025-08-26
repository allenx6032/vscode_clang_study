/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "sparseArray.hpp"
#include "entity.hpp"
#include "exception.hpp"
#include <any>
#include <functional>
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

class Registry {
    public:
        Registry()
        {
        };
        ~Registry()
        {
        };


        // INFO: component list
        /**
         * @brief Register a component in the registry
         *
         * @tparam Component The component to register
         * @return sparseArray<Component>& The array of the component that has been registered
        **/
        template <class Component>
        SparseArray<Component> &ecsRegisterComponent()
        {
            std::type_index type(typeid(Component));
            _components_arrays[type] = std::any(SparseArray<Component>());
            SparseArray<Component> &array = std::any_cast<SparseArray<Component> &>(_components_arrays.at(type));
            _destroy_component_callbacks.push_back([](Registry &r, Entity const &e) {
                if (r.ecsGetComponents<Component>().has(e))
                    r.ecsRemoveComponent<Component>(e);
            });
            return array;
        };

        /**
         * @brief Get a reference to the array of a component
         *
         * @tparam Component The component to get the array of
         * @return sparseArray<Component>& The array of the component
         * @throw gameEngine::invalid_component If the component is not registered
        **/
        template <class Component>
        SparseArray<Component> &ecsGetComponents()
        {
            std::type_index type(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end())
                throw gameEngine::ecs::InvalidComponent();
            try {
                SparseArray<Component> &array = std::any_cast<SparseArray<Component> &>(_components_arrays.at(type));
                return array;
            } catch (std::bad_any_cast const &e) {
                throw gameEngine::ecs::InvalidComponent();
            }
        };

        /**
         * @brief Get a const reference to the array of a component
         *
         * @tparam Component The component to get the array of
         * @return sparseArray<Component> const & The array of the component
         * @throw gameEngine::invalid_component If the component is not registered
        **/
        template <class Component>
        SparseArray<Component> const &ecsGetComponents() const
        {
            std::type_index type(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end())
                throw gameEngine::ecs::InvalidComponent();
            try {
                SparseArray<Component> const &array = std::any_cast<SparseArray<Component> const &>(_components_arrays.at(type));
                return array;
            } catch (std::bad_any_cast const &e) {
                throw gameEngine::ecs::InvalidComponent();
            }
        };

        // INFO: entity list
        /**
         * @brief Create an entity
         *
         * @return Entity The entity that has been created
         * @note The entity is created with an index that is the next available index
        **/
        Entity ecsSpawnEntity()
        {
            if (_free_entity.empty()) {
                _entity_size++;
                return Entity(_entity_size);
            }
            size_t index = _free_entity.back();
            _free_entity.pop_back();
            return Entity(index);
        };

        /**
         * @brief Get an entity from an index
         *
         * @param index The index of the entity
         * @return Entity The entity that has been created with the given index
         * @throw gameEngine::invalid_argument If the index is not valid
        **/
        Entity ecsEntityFromIndex(std::size_t index)
        {
            if (index > _entity_size || index <= 0 ||
                std::find(_free_entity.begin(), _free_entity.end(), index) != _free_entity.end())
                throw gameEngine::ecs::InvalidArgument("The index is not valid");
            return Entity(index);
        };

        /**
         * @brief Destroy an entity
         *
         * @param entity The entity to destroy
         * @throw gameEngine::invalid_argument If the entity is not valid
        **/
        void ecsKillEntity(Entity const &entity)
        {
            if (entity > _entity_size || entity <= 0 ||
                std::find(_free_entity.begin(), _free_entity.end(), entity) != _free_entity.end())
                throw gameEngine::ecs::InvalidArgument("The entity is not valid");
            // std::cout << "Killing entity " << entity << std::endl;
            // destroy components of the entity
            for (auto const &callback : _destroy_component_callbacks)
                callback(*this, entity);
            _free_entity.push_back((size_t)entity);
        };

        /**
         * @brief Kill all the Entities in the registry (use to reset the registry)
         */
        void ecsKillAllEntities()
        {
            for (size_t i = 0; i <= _entity_size; i++) {
                try {
                    ecsKillEntity(Entity(i));
                } catch (gameEngine::ecs::InvalidArgument const &e) {
                    continue;
                }
            }
            _entity_size = 0;
            _free_entity.clear();
        };

        // INFO: Manage components of entities
        /**
         * @brief Add a component to an entity
         *
         * @tparam Component The component to add
         * @param to The entity to add the component to
         * @param c The component to add
         * @return typename sparseArray<Component>::reference_type A reference to the component that has been added
         * @throw gameEngine::invalid_component If the component is not registered
         * @throw gameEngine::invalid_argument If the entity is not valid or already has the component
        **/
        template <typename Component>
        typename SparseArray<Component>::reference_type ecsAddComponent(Entity const &to, Component &c)
        {
            std::type_index type(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end())
                throw gameEngine::ecs::InvalidComponent();
            if (ecsGetComponents<Component>().has(to))
                throw gameEngine::ecs::InvalidArgument("The entity already has the component");
            if (to > _entity_size || to <= 0 ||
                std::find(_free_entity.begin(), _free_entity.end(), to) != _free_entity.end())
                throw gameEngine::ecs::InvalidArgument("The entity is not valid");
            return ecsGetComponents<Component>().insertAt(to, c);
        };

        /**
         * @brief Add a component to an entity
         *
         * @tparam Component The component to add
         * @param to The entity to add the component to
         * @param c The component to add
         * @return typename sparseArray<Component>::reference_type A reference to the component that has been added
         * @throw gameEngine::invalid_component If the component is not registered
         * @throw gameEngine::invalid_argument If the entity is not valid
        **/
        template <typename Component, typename... Params>
        typename SparseArray<Component>::reference_type ecsEmplaceComponent(Entity const &to, Params &&...p)
        {
            std::type_index type(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end())
                throw gameEngine::ecs::InvalidComponent();
            if (to > _entity_size || to <= 0 ||
                std::find(_free_entity.begin(), _free_entity.end(), to) != _free_entity.end())
                throw gameEngine::ecs::InvalidArgument("The entity is not valid");
            return ecsGetComponents<Component>().emplaceAt(to, std::forward<Params>(p)...);
        };

        /**
         * @brief Remove a component from an entity
         *
         * @tparam Component The component to remove
         * @param from The entity to remove the component from
         * @throw gameEngine::invalid_component If the component is not registered
         * @note This function does not check if the entity has the component
         * @warning This function does not destroy the component
        **/
        template <typename Component>
        void ecsRemoveComponent(Entity const &from)
        {
            std::type_index type(typeid(Component));
            if (_components_arrays.find(type) == _components_arrays.end())
                throw gameEngine::ecs::InvalidComponent();
            if (!ecsGetComponents<Component>().has(from))
                return;
            ecsGetComponents<Component>().erase(from);
        };

        /**
         * @brief Add a system to the registry
         *
         * @tparam Components The components that the system will use
         * @param f The function that will be called when the system is run
         * @note The function must take a Registry & as first parameter and the components as following parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename Function>
        std::function<void()> ecsAddSystem(Function &&f)
        {
            // convert function to lambda
            _systems.push_back([f](Registry &r) {
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
         * @note The function must take a Registry & as first parameter and the components as following parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename Function>
        std::function<void()> ecsAddSystem(Function const &f)
        {
            // convert function to lambda
            _systems.push_back([f](Registry &r) {
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
         * @note The function must take a Registry & as first parameter and the components as following parameters and the extra parameters as last parameters
         *
         * @return A function to remove the system from the registry
         */
        template <class... Components, typename... ExtraParams, typename Function>
        std::function<void()> ecsAddSystem(Function &&f, ExtraParams &&...p)
        {
            // convert function to lambda
            _systems.push_back([f, &p...](Registry &r) {
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
        //  * @note The function must take a Registry & as first parameter and the components as following parameters and the extra parameters as last parameters
        //  *
        //  * @return A function to remove the system from the registry
        //  */
        // template <class... Components, typename... ExtraParams, typename Function>
        // std::function<void()> ecsAddSystem(Function const &f, ExtraParams &&...p)
        // {
        //     // convert function to lambda
        //     _systems.push_back([f, &p...](Registry &r) {
        //         f(r, r.ecsGetComponents<Components>()..., std::forward<ExtraParams>(p)...);
        //     });

        //     iterator to the element we just added so we can remove it later if needed
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
        };

        /**
         * @brief Run a single system
         *
         * @tparam Components The components that the system will use
         * @param f The system to run
         * @note The function must take a Registry & as first parameter and the components as following parameters
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
         * @note The function must take a Registry & as first parameter and the components as following parameters and the extra parameters as last parameters
         */
        template <class... Components, typename... ExtraParams, typename Function>
        void ecsRunSingleSystem(Function &&f, ExtraParams &&...p) {
            f(*this, ecsGetComponents<Components>()..., std::forward<ExtraParams>(p)...);
        };

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;

        size_t _entity_size = 0;
        std::vector<size_t> _free_entity;

        std::vector<std::function<void(Registry &)>> _systems;

        std::vector<std::function<void(Registry &, Entity const &)>> _destroy_component_callbacks;
};
