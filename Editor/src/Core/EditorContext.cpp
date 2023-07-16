#include "EditorContext.hpp"

namespace Atakama::Editor
{

RuntimeEditorContext g_RuntimeEditorContext;

void RuntimeEditorContext::Init()
{
	WindowConfigs[WindowId::Demo] = { "Demo", "Demo", false};
	WindowConfigs[WindowId::Document] = { "Document - Sandbox", "Document" };
	WindowConfigs[WindowId::ProjectSettings] = {"Project Settings", "ProjectSettings" };
	WindowConfigs[WindowId::Stats] = { "Stats", "Stats" };
	WindowConfigs[WindowId::Viewport] = { "Viewport", "Viewport" };
	WindowConfigs[WindowId::DepthView] = { "Depth", "DepthView", false};
	WindowConfigs[WindowId::SceneView] = { "Scene", "SceneView" };
	WindowConfigs[WindowId::ObjectProperties] = { "Object Properties", "ObjectProperties" };
}

void RuntimeEditorContext::Shutdown()
{
}

WindowConfig& GetWindowConfig(WindowId windowId)
{
	return g_RuntimeEditorContext.WindowConfigs[windowId];
}

std::string GetImGuiWindowId(WindowId windowId)
{
	return g_RuntimeEditorContext.WindowConfigs[windowId].GetImGuiWindowId();
}

EditorUIConfig& GetUIConfig()
{
	return g_RuntimeEditorContext.UIConfig;
}

}
