#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include "Events/Event.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <vector>


namespace OGLSample
{

class EventDispatcher
{
private:
    
    template<typename T>
    using CallbackFunc = std::function<bool(T&)>;
    
    class Callback
    {
    public:
        virtual ~Callback() = default;
        virtual bool Invoke(Event& event) { return false; };
    };

    template<typename T>
    class CallbackImpl: public Callback
    {
    public:
        CallbackImpl(const CallbackFunc<T> &callback): Callback(), m_Callback(callback) {}
        ~CallbackImpl() = default;

        bool Invoke(Event& event) override {
            return m_Callback(static_cast<T&>(event));
        }
    private:
        CallbackFunc<T> m_Callback;
    };

    std::map<EventType, std::vector<Scope<Callback>>> m_Observers;
public:
    template<typename T>
    void subscribe(EventType type, const CallbackFunc<T> &slot)
    {
        m_Observers[type].push_back(CreateScope<CallbackImpl<T>>(slot));
    }

    void post(Event &event)
    {
        auto type = event.GetType();
        if (m_Observers.find(type) == m_Observers.end())
        {
            return;
        }

        for (auto &&observer : m_Observers.at(type))
        {
            if (!event.Handled)
            {
                if (observer) {
                    event.Handled |= observer->Invoke(event);
                }
            }
        }
    }
};

}

#endif
