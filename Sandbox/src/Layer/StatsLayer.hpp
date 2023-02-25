#ifndef ATAKAMA_STATS_LAYER_HPP
#define ATAKAMA_STATS_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Application;

namespace Sandbox
{

class StatsLayer: public Layer
{
public:
    StatsLayer();
    ~StatsLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdateUI(float ts) override;
private:
    Application* m_Application;
};

}

}

#endif
