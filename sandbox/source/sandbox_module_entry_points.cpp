#include "sandbox_module_entry_points.h"

#include <glm/gtc/matrix_transform.hpp>

#include <silk/engine/engine.h>
#include <silk/engine/graphics/vertex_buffer.h>
#include <silk/engine/input/keyboard_device.h>

namespace silk::sandbox
{
    void SandboxModuleEntryPoints::Install(Engine& engine)
    {
        engine.GetDebugToolbox().RegisterTool(&m_SandboxDebugTool);

        m_InputService = &engine.GetInputService();

        m_KeyboardDevice.Init(engine.GetMainWindow());
        m_InputService->RegisterDevice(m_KeyboardDevice);

        m_LeftAction.ConfigureButton();
        m_LeftAction.AddSettings(m_KeyboardDevice.GetDeviceId(), (InputId)KeyboardInputId::KeyLeft);

        m_RightAction.ConfigureButton();
        m_RightAction.AddSettings(m_KeyboardDevice.GetDeviceId(), (InputId)KeyboardInputId::KeyRight);

        m_ResetAction.ConfigureButton(ButtonInputActionEvent::Tap);
        m_ResetAction.AddSettings(m_KeyboardDevice.GetDeviceId(), (InputId)KeyboardInputId::KeySpace);

        InputActionWatcher& inputActionWatcher{ m_InputService->GetInputActionWatcher() };
        inputActionWatcher.RegisterInputAction(m_LeftAction);
        inputActionWatcher.RegisterInputAction(m_RightAction);
        inputActionWatcher.RegisterInputAction(m_ResetAction);

        m_OnResetSlot.SetBoundFunction([this](const InputActionState& state) { OnReset(state); });
        inputActionWatcher.GetInputActionState(m_ResetAction)->GetButtonEventSignal().Connect(m_OnResetSlot);


        m_Camera.SetPriority(1);
        m_Camera.EnableScreenClear({});
        m_Camera.ConfigurePerspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        m_Camera.LookAt(
            glm::vec3(4, 3, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );

        m_DrawSlot.SetBoundFunction([this](GraphicsContext& context, const Camera& camera) { OnDraw(context, camera); });
        m_Camera.GetDrawSignal().Connect(m_DrawSlot);
        
        m_UICamera.SetPriority(1);
        m_UICamera.ConfigureOrthographic(0.0f, 800.0f, 0.0f, 600.0f);

        m_DrawUISlot.SetBoundFunction([this](GraphicsContext& context, const Camera& camera) { OnDrawUI(context, camera); });
        m_UICamera.GetDrawSignal().Connect(m_DrawUISlot);

        GraphicsContext& graphicsContext{ engine.GetGraphicsContext() };
        graphicsContext.EnableDepthTest(DepthTestFunction::Less);
        graphicsContext.RegisterCamera(m_Camera);
        graphicsContext.RegisterCamera(m_UICamera);

        const char* vertexSource
        {
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
            "layout(location = 1) in vec3 vertexColor;\n"
            "layout(location = 2) in vec2 vertexUV;\n"
            "\n"
            "uniform mat4 MVP;\n"
            "\n"
            "out vec3 o_vertexColor;\n"
            "out vec2 UV;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);\n"
            "    o_vertexColor = vertexColor;\n"
            "    UV = vertexUV;\n"
            "}\n"
        };

        const char* fragmentSource
        {
            "#version 330 core\n"
            "\n"
            "in vec3 o_vertexColor;\n"
            "in vec2 UV;\n"
            "out vec3 color;\n"
            "\n"
            "uniform sampler2D myTextureSampler;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    color = o_vertexColor * texture(myTextureSampler, UV).rgb;\n"
            "}\n"
        };

        m_Shader.Create(vertexSource, fragmentSource);

        static const float vertexData[] = {
           -1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
            1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 0.0f,

           -1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
            1.0f,  1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 0.0f,
           -1.0f,  1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
        };

        static const VertexDataType vertexDataTypes[]
        {
            VertexDataType::Float3, VertexDataType::Float3, VertexDataType::Float2
        };

        m_Mesh.Create();
        m_Mesh.Bind();
        m_Mesh.AddVertexBuffer(vertexData, sizeof(vertexData), vertexDataTypes, 3);
        m_Mesh.Unbind();

        static const unsigned char texData[]
        {
            255, 0, 0,   255,    0,   255, 0,   255,
            0,   0, 255, 255,    255, 255, 255, 255,
        };

        m_Texture.Create(2, 2, texData);
    }

    void SandboxModuleEntryPoints::Uninstall(Engine& engine)
    {
        InputActionWatcher& inputActionWatcher{ m_InputService->GetInputActionWatcher() };

        inputActionWatcher.GetInputActionState(m_ResetAction)->GetButtonEventSignal().Disconnect(m_OnResetSlot);

        inputActionWatcher.UnregisterInputAction(m_LeftAction);
        inputActionWatcher.UnregisterInputAction(m_RightAction);
        inputActionWatcher.UnregisterInputAction(m_ResetAction);

        engine.GetInputService().UnregisterDevice(m_KeyboardDevice);
        m_KeyboardDevice.Shutdown(engine.GetMainWindow());

        m_Texture.Destroy();
        m_Mesh.Destroy();
        m_Shader.Destroy();

        m_Camera.GetDrawSignal().Disconnect(m_DrawSlot);
        engine.GetGraphicsContext().UnregisterCamera(m_Camera);

        engine.GetDebugToolbox().UnregisterTool(&m_SandboxDebugTool);
    }

    void SandboxModuleEntryPoints::OnDraw(GraphicsContext& context, const Camera& camera)
    {
        if (m_InputService->GetInputActionWatcher().GetButtonState(m_LeftAction))
        {
            m_Value -= 0.1f;
        }
        if (m_InputService->GetInputActionWatcher().GetButtonState(m_RightAction))
        {
            m_Value += 0.1f;
        }

        glm::mat4 Model = glm::mat4(1.0f);
        Model = glm::rotate(Model, m_Value, glm::vec3{ 0.0f, 1.0f, 0.0f });

        glm::mat4 mvp = camera.GetProjectionMatrix() * camera .GetViewMatrix() * Model;

        m_Shader.Bind();
        m_Shader.SetUniform("MVP", mvp);
        m_Texture.Bind();
        context.DrawMesh(m_Mesh);
        m_Texture.Unbind();
        m_Shader.Unbind();
    }

    void SandboxModuleEntryPoints::OnDrawUI(GraphicsContext& context, const Camera& camera)
    {
        glm::mat4 Model = glm::mat4(1.0f);
        Model = glm::translate(Model, glm::vec3{ 100.0f, 100.0f, 0.0f });
        Model = glm::scale(Model, glm::vec3{ 100.0f });

        glm::mat4 mvp = camera.GetProjectionMatrix() * camera .GetViewMatrix() * Model;

        m_Shader.Bind();
        m_Shader.SetUniform("MVP", mvp);
        m_Texture.Bind();
        context.DrawMesh(m_Mesh);
        m_Texture.Unbind();
        m_Shader.Unbind();
    }

    void SandboxModuleEntryPoints::OnReset(const InputActionState&)
    {
        m_Value = 0.0f;
    }
}
