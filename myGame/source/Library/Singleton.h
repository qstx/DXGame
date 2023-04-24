#pragma once
#include <mutex>

namespace Library
{

    template <typename T>
    class Singleton
    {
    public:
        template <typename... Args>
        static T* GetInstance(Args &&...args);
        //template <typename... Args>
        //virtual T* CreateInstance(Args &&...args)=0;
        static std::mutex lock;
        Singleton(Singleton& other) = delete;
        void operator=(const Singleton& other) = delete;
    protected:
        Singleton() = default;
        virtual ~Singleton();
    private:
        static T* instance;
    };
    template <typename T>
    T* Singleton<T>::instance(nullptr);

    template <typename T>
    std::mutex Singleton<T>::lock;

    template <typename T>
    template<typename ...Args>
    T* Singleton<T>::GetInstance(Args &&...args)
    {
        if (!instance)
        {
            std::lock_guard<std::mutex> locker(lock);
            if (!instance)
            {
                instance = new T(std::forward<Args>(args)...);
            }
        }
        //static T _pinstance(std::forward<Args>(args)...);
        return instance;
    }

    template <typename T>
    Singleton<T>::~Singleton()
    {
        delete instance;
    }

    template <typename T, typename ...Args>
    T* GetInstance(Args &&...args)
    {
        return Singleton<T>::GetInstance(std::forward<Args>(args)...);
    }
}