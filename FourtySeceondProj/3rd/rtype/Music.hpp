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
    class Music {
        public:
            enum Status {
                Stopped,
                Paused,
                Playing
            };

        public:
            Music() :
                _music()
            {
            };
            Music(const std::string &path) :
                _music()
            {
                _music.openFromFile(path);
            };

            bool openFromFile(const std::string &filename) { return _music.openFromFile(filename); };
            bool openFromMemory(const void *data, std::size_t sizeInBytes) { return _music.openFromMemory(data, sizeInBytes); };
            bool openFromStream(sf::InputStream &stream) { return _music.openFromStream(stream); };
            Time getDuration() const {
                sf::Time time = _music.getDuration();
                return Time(time);
            };

            void play() { _music.play(); };
            void pause() { _music.pause(); };
            void stop() { _music.stop(); };
            unsigned int getChannelCount() const { return _music.getChannelCount(); };
            unsigned int getSampleRate() const { return _music.getSampleRate(); };
            Music::Status getStatus() const {
                sf::SoundSource::Status status = _music.getStatus();
                return static_cast<Music::Status>(status);
            };
            void setPlayingOffset(const Time &timeOffset) { _music.setPlayingOffset(timeOffset); };
            Time getPlayingOffset() const {
                sf::Time time = _music.getPlayingOffset();
                return Time(time);
            };

            void setLoop(bool loop) { _music.setLoop(loop); };
            bool getLoop() const { return _music.getLoop(); };
            void setPitch(float pitch) { _music.setPitch(pitch); };
            void setVolume(float volume) { _music.setVolume(volume); };
            void setPosition(float x, float y, float z) { _music.setPosition(x, y, z); };
            void setPosition(const Vector3f &position) { _music.setPosition(position); };
            void setRelativeToListener(bool relative) { _music.setRelativeToListener(relative); };
            void setMinDistance(float distance) { _music.setMinDistance(distance); };
            void setAttenuation(float attenuation) { _music.setAttenuation(attenuation); };

            float getPitch() { return _music.getPitch(); };
            float getVolume() { return _music.getVolume(); };
            Vector3f getPosition() { return _music.getPosition(); };
            bool isRelativeToListener() { return _music.isRelativeToListener(); };
            float getMinDistance() { return _music.getMinDistance(); };
            float getAttenuation() { return _music.getAttenuation(); };

        private:
            sf::Music _music;
    };
}