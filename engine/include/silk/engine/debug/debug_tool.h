#pragma once

namespace silk
{
    class DebugTool
    {
    protected:
        virtual void OnRegister() {};
        virtual void OnUnregister() {};

        virtual void Display() {};

        friend class DebugToolbox;
    };
}