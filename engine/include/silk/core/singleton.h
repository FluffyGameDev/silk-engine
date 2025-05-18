#pragma once

#include <typeinfo>

#include <silk/core/assert.h>

namespace silk
{
    template <typename TSingleton>
    class Singleton
    {
    public:
        static TSingleton* Get() { return s_Instance; }

    protected:
        void RegisterInstance(TSingleton* instance)
        {
            SILK_ASSERT(s_Instance == nullptr, "Trying to register a singleton of type %s more than once.", typeid(TSingleton).name());
            s_Instance = instance;
        }

        void UnregisterInstance(TSingleton* instance)
        {
            SILK_ASSERT(s_Instance == nullptr, "Trying to unregister a singleton of type %s that isn't the instance.", typeid(TSingleton).name());
            s_Instance = instance;
        }

    private:
        static inline TSingleton* s_Instance{};
    };
}
