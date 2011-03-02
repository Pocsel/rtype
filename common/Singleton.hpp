#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <cassert>

namespace Gmgp
{

    /// Classe commune pour déclarer des Singleton
    template <typename T>
        class Singleton
        {
            private:
                static T* _instance;

                explicit Singleton(Singleton const&)
                {
                }

                Singleton& operator =(Singleton const&)
                {
                    return *this;
                }

            protected:
                explicit Singleton()
                {
                    assert(Singleton<T>::_instance == 0);
                }

                ~Singleton()
                {
                }

            public:
                /// Récupère l'instance du Singleton
                static T* GetInstance(void)
                {
                    if (Singleton<T>::_instance == 0)
                        Singleton<T>::_instance = new T;
                    return Singleton<T>::_instance;
                }

                /// Supprime l'instance du Singleton
                static void DelInstance(void)
                {
                    if (Singleton<T>::_instance != 0)
                        delete Singleton<T>::_instance;
                    Singleton<T>::_instance = 0;
                }
        };

    template<typename T> T* Singleton<T>::_instance = 0;

}

#endif

