#pragma once

#include <silk/core/slot.h>
#include <silk/engine/module/module_entry_points.h>

#include <silk/engine/graphics/camera.h>
#include <silk/engine/graphics/mesh.h>
#include <silk/engine/graphics/shader.h>
#include <silk/engine/graphics/texture.h>
#include <silk/engine/input/keyboard_device.h>
#include <silk/engine/input/mouse_device.h>
#include <silk/engine/input/actions/input_action.h>

#include "sandbox_debug_tool.h"

namespace silk
{
    class GraphicsContext;
    class InputActionState;
    class InputService;
}

namespace silk::sandbox
{
    class SandboxModuleEntryPoints : public ModuleEntryPoints
    {
    private:
        void Install(Engine& engine) override;
        void Uninstall(Engine& engine) override;

        void OnDraw(GraphicsContext& context, const Camera& camera);
        void OnDrawUI(GraphicsContext& context, const Camera& camera);

        void OnReset(const InputActionState& state);

        SandboxDebugTool m_SandboxDebugTool;
        Slot<void(GraphicsContext&, const Camera&)> m_DrawSlot;
        Slot<void(GraphicsContext&, const Camera&)> m_DrawUISlot;

        Camera m_Camera;
        Camera m_UICamera;
        Shader m_Shader;
        Mesh m_Mesh;
        Texture m_Texture;

        KeyboardDevice m_KeyboardDevice;
        MouseDevice m_MouseDevice;

        InputAction m_LeftAction;
        InputAction m_RightAction;
        InputAction m_ResetAction;
        InputAction m_MouseXAction;
        Slot<void(const InputActionState&)> m_OnResetSlot;

        InputService* m_InputService;
        float m_Value;
    };
}
