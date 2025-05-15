#pragma once

#include <algorithm>
#include <vector>

#include <silk/core/slot.h>

namespace silk
{
    template <typename T>
    class Signal;

    template <typename ... TArgs>
    class Signal<void(TArgs...)>
    {
    public:
        using SlotType = Slot<void(TArgs...)>;

        void Connect(SlotType& slot)
        {
            m_ConnectedSlots.push_back(&slot);
        }

        void Disconnect(SlotType& slot)
        {
            auto foundIt = std::remove(m_ConnectedSlots.begin(), m_ConnectedSlots.end(), &slot);
            if (foundIt != m_ConnectedSlots.end())
            {
                m_ConnectedSlots.erase(foundIt);
            }
        }

        void Raise(TArgs... args)
        {
            for (auto* slot : m_ConnectedSlots)
            {
                if (slot->m_BoundFunction)
                {
                    slot->m_BoundFunction(std::forward(args)...);
                }
            }
        }

        void Clear()
        {
            m_ConnectedSlots.clear();
        }

    private:
        std::vector<SlotType*> m_ConnectedSlots;
    };
}
