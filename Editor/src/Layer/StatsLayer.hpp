#ifndef ATAKAMA_STATS_LAYER_HPP
#define ATAKAMA_STATS_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{

class EditorApplication;

class StatsLayer: public Layer
{
public:
    StatsLayer();
    ~StatsLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdateUI(float ts) override;
private:
    EditorApplication* m_Application;
    EditorUIConfig& m_UIConfig;
};

}

#endif
