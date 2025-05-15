#pragma once

#include <functional>
#include <utility>

namespace silk
{
    template <typename T>
    class Slot;

    template <typename T>
    class Signal;

    template <typename ... TArgs>
    class Slot<void(TArgs...)>
    {
    public:
        Slot()
            : m_BoundFunction{}
        {
        }

        Slot(std::function<void(TArgs...)>&& boundFunction)
            : m_BoundFunction{ std::move(boundFunction) }
        {
        }

        Slot(const Slot&) = delete;
        Slot(Slot&&) = delete;

        inline void SetBoundFunction(std::function<void(TArgs...)>&& boundFunction)
        {
            m_BoundFunction = std::move(boundFunction);
        }

    private:
        std::function<void(TArgs...)> m_BoundFunction;

        friend class Signal<void(TArgs...)>;
    };
}
