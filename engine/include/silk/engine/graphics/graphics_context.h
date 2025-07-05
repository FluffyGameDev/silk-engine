#pragma once

namespace silk
{
    class Mesh;

    class GraphicsContext
    {
    public:
        void Init();
        void Shutdown();

        void StartFrame();
        void EndFrame();

        void DrawMesh(const Mesh& mesh) const;

    private:
    };
}
