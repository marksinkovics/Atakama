#ifndef ATAKAMA_LAYER_HPP
#define ATAKAMA_LAYER_HPP

namespace Atakama
{

class Layer
{
public:
    Layer(const std::string& name = "Layer");

    virtual void OnAttach();
    virtual void OnDetach();

    virtual void OnUpdate(float ts);
    virtual void OnUpdateUI(float ts);
protected:
    std::string m_Name;
};

class LayerStack
{
public:
    LayerStack() = default;
    ~LayerStack();

    void Add(Layer* layer);
    void Remove(Layer* layer);

    std::vector<Layer*>::iterator begin();
    std::vector<Layer*>::iterator end();
    std::vector<Layer*>::reverse_iterator rbegin();
    std::vector<Layer*>::reverse_iterator rend();

    std::vector<Layer*>::const_iterator begin() const;
    std::vector<Layer*>::const_iterator end()    const;
    std::vector<Layer*>::const_reverse_iterator rbegin() const;
    std::vector<Layer*>::const_reverse_iterator rend() const;
private:
    std::vector<Layer*> m_Layers;
};


}


#endif
