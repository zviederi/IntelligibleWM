#pragma once

#ifdef QT_NO_DEBUG
#define VERIFY(x) (x)
#else //QT_NO_DEBUG
#define VERIFY(x) Q_ASSERT(x)
#endif //QT_NO_DEBUG

#include <algorithm>
#include <functional>

namespace IWM {

    template <typename ArgumentType, typename ResultType>
    struct unary_function
    {
        using argument_type = ArgumentType;
        using result_type = ResultType;
    };
    
    namespace stdutils
    {
        template<typename T>
        inline void destroy(T *&v)
        {
            delete v;
            v = NULL;
        }

        template<typename T>
        struct RemoveIfFound : public unary_function<T, bool>
        {
            RemoveIfFound(T whatSearch) : _whatSearch(whatSearch) {}

            bool operator()(T item) const {
                if (item == _whatSearch) {
                    destroy(item);
                    return true;
                }
                return false;
            }

            T _whatSearch;
        };

        template <typename T>
        struct default_delete : public unary_function <T, void>
        {
            inline void operator ()(T *ptr) const
            {
                  destroy(ptr);
            }
        };

        template <typename T>
        struct default_delete<T*> : public unary_function<T*, void>
        {
            inline void operator ()(T *ptr) const
            {
                  destroy(ptr);
            }
        };

        template<typename T, unsigned int N>
        struct default_delete<T[N]>
                :public unary_function<const T[N], void>
        {
            inline void operator ()(const T ptr) const
            {
                delete [] ptr;
            }
        };

    };
    
}