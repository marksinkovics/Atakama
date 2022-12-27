#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include "Events/Event.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <vector>

#define EVENT_SUBSCRIBE()

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
        Callback(const std::string id): m_Id(id) {}
        virtual ~Callback() = default;
        virtual std::string& GetId() { return m_Id; }
        virtual bool Invoke(Event& event) { return false; };
    protected:
        std::string m_Id;
    };

    template<typename T>
    class CallbackImpl: public Callback
    {
    public:
        CallbackImpl(const CallbackFunc<T> &callback): Callback(callback.target_type().name()), m_Callback(callback) {}
        ~CallbackImpl() = default;
        CallbackFunc<T>& GetCallback() { return m_Callback; }

        bool Invoke(Event& event) override {
            return m_Callback(static_cast<T&>(event));
        }
    private:
        CallbackFunc<T> m_Callback;
    };

    std::map<EventType, std::vector<Scope<Callback>>> m_Observers;
public:
    template<typename T>
    void subscribe(const CallbackFunc<T> &slot)
    {
        EventType type = T::GetStaticType();
        m_Observers[type].push_back(CreateScope<CallbackImpl<T>>(slot));
    }
        
    template<typename T>
    void unsubscribe(const CallbackFunc<T> &slot)
    {
        EventType type = T::GetStaticType();
        m_Observers[type].erase(std::remove_if(std::begin(m_Observers[type]), std::end(m_Observers[type]), [&slot](Scope<Callback>& ptr) {
            return ptr->GetId() == slot.target_type().name();
        }), std::end(m_Observers[type]));
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
