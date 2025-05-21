#pragma once

#include <silk/engine/service/service.h>

namespace silk::runtime
{
    class RuntimeService : public Service
    {
        void Init(Engine& engine) override;
        void Shutdown(Engine& engine) override;
    };
}
