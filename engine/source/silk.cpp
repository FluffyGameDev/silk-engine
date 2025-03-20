#include <silk/engine/engine.h>
#include <silk/engine/engine_config.h>

int main()
{
    silk::EngineConfig engineConfig{ 30 };
    silk::RunEngine(engineConfig);
}
