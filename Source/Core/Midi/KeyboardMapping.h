/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "Serializable.h"
#include "Note.h"

class KeyboardMapping final : public Serializable
{
public:

    KeyboardMapping();

    static constexpr auto maxMappedKeys = 1024;

    void map(Note::Key &key, int &channel) const noexcept
    {
        channel = this->index[key].channel;
        key = this->index[key].key;
    }

    // this method will not reset before loading a mapping,
    // because there can be a number of files for multiple channels,
    // so don't forget to reset() before calling this
    void loadScalaKbmFile(InputStream &fileContentStream,
        const String &fileNameWithoutExtension);

    void updateKey(int key, int8 targetKey, int8 targetChannel);

    SerializedData serialize() const override;
    void deserialize(const SerializedData &data) override;
    void reset() override;

private:

    struct KeyChannel final
    {
        KeyChannel() = default;
        KeyChannel(int8 key, int8 channel) :
            key(key), channel(channel) {}

        friend inline bool operator==(const KeyChannel &l, const KeyChannel &r)
        {
            return l.key == r.key && l.channel == r.channel;
        }

        friend inline bool operator!=(const KeyChannel &l, const KeyChannel &r)
        {
            return !(l == r);
        }

        inline KeyChannel getNextDefault() const noexcept
        {
            int k = this->key + 1;
            int8 c = this->channel;
            if (k >= Globals::twelveToneKeyboardSize)
            {
                k = 0;
                c++;
            }

            return { int8(k), c };
        }

        int8 key = 0;
        int8 channel = 0;
    };

    static KeyChannel getDefaultMappingFor(int key) noexcept;

    KeyChannel index[maxMappedKeys];

    JUCE_DECLARE_WEAK_REFERENCEABLE(KeyboardMapping)
};
