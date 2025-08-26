/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Vector3.hpp"
#include "Time.hpp"
#include <sfml/SFML_Audio.hpp>

namespace gameEngine {
    class Sound {
        public:
            enum Status {
                Stopped,
                Paused,
                Playing
            };

        public:
            Sound() :
                _sound()
            {
            };
            Sound(const Sound &sound) :
                _sound(sound._sound)
            {
            };
            Sound(const sf::SoundBuffer &buffer) :
                _sound(buffer)
            {
            };
            Sound(const std::string &path) :
                _sound()
            {
                _buffer.loadFromFile(path);
                _sound.setBuffer(_buffer);
            };

            void play() { _sound.play(); };
            void pause() { _sound.pause(); };
            void stop() { _sound.stop(); };
            void setBuffer(const sf::SoundBuffer &buffer) {
                _buffer = buffer;
                _sound.setBuffer(buffer);
            };
            const sf::SoundBuffer *getBuffer() const { return _sound.getBuffer(); };
            void setLoop(bool loop) { _sound.setLoop(loop); };
            bool getLoop() const { return _sound.getLoop(); };
            void setPlayingOffset(const Time &timeOffset) { _sound.setPlayingOffset(timeOffset); };
            Time getPlayingOffset() const { return _sound.getPlayingOffset(); };
            Sound::Status getStatus() const {
                sf::Sound::Status status = _sound.getStatus();
                return static_cast<Sound::Status>(status);
            };
            void resetBuffer() { _sound.resetBuffer(); };
            void setPitch(float pitch) { _sound.setPitch(pitch); };
            void setVolume(float volume) { _sound.setVolume(volume); };
            void setPosition(float x, float y, float z) { _sound.setPosition(x, y, z); };
            void setPosition(const Vector3f &position) { _sound.setPosition(position); };
            void setRelativeToListener(bool relative) { _sound.setRelativeToListener(relative); };
            void setMinDistance(float distance) { _sound.setMinDistance(distance); };
            void setAttenuation(float attenuation) { _sound.setAttenuation(attenuation); };
            float getPitch() const { return _sound.getPitch(); };
            float getVolume() const { return _sound.getVolume(); };
            Vector3f getPosition() const { return _sound.getPosition(); };
            bool isRelativeToListener() const { return _sound.isRelativeToListener(); };
            float getMinDistance() const { return _sound.getMinDistance(); };
            float getAttenuation() const { return _sound.getAttenuation(); };

        public:
            Sound(const sf::Sound &sound) :
                _sound(sound)
            {
            };

            operator sf::Sound() const { return _sound; };

        private:
            sf::Sound _sound;
            sf::SoundBuffer _buffer;
    };
}
