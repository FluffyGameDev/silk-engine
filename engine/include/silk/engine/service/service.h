#pragma once

namespace silk
{
    class Engine;

    class Service
    {
    public:
        virtual void Init(Engine&) {}
        virtual void Shutdown(Engine&) {}
    };
}
