#include "Layer.hpp"

namespace Atakama
{

Layer::Layer(const std::string& name)
: m_Name(name)
{

}

void Layer::OnAttach()
{

}
void Layer::OnDetach()
{

}

void Layer::OnUpdate(float ts)
{

}
void Layer::OnUpdateUI(float ts)
{

}

LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::Add(Layer* layer)
{
    layer->OnAttach();
    m_Layers.emplace_back(layer);
}

void LayerStack::Remove(Layer* layer)
{
    auto it = std::find(begin(), end(), layer);
    if (it != m_Layers.end())
    {
        layer->OnDetach();
        m_Layers.erase(it);
        delete layer;
    }
}

std::vector<Layer*>::iterator LayerStack::begin()
{
    return m_Layers.begin();
}
std::vector<Layer*>::iterator LayerStack::end()
{
    return m_Layers.end();
}
std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
{
    return m_Layers.rbegin();
}
std::vector<Layer*>::reverse_iterator LayerStack::rend()
{
    return m_Layers.rend();
}

std::vector<Layer*>::const_iterator LayerStack::begin() const
{
    return m_Layers.begin();
}

std::vector<Layer*>::const_iterator LayerStack::end() const
{
    return m_Layers.end();
}

std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const
{
    return m_Layers.rbegin();
}

std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const
{
    return m_Layers.rend();
}


}
