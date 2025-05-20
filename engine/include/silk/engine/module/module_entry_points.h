#pragma once

namespace silk
{
    class Engine;

    class ModuleEntryPoints
    {
    public:
        virtual void Install(Engine&) {}
        virtual void Uninstall(Engine&) {}
    };
}
