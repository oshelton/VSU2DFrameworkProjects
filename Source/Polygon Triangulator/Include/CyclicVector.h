#ifndef CYCLICVECTOR_H_INCLUDED
#define CYCLICVECTOR_H_INCLUDED

#include <vector.h>

template <typename T> class CyclicVector
{
private:
    std::vector<T> source;

public:

    class iterator
    {
    private:
        CyclicVector<T>*  iterSource;
        unsigned int currentIndex;

    public:
        iterator(CyclicVector<T>*  vec) : currentIndex(0)
        {
            iterSource = vec;
        }

        iterator(CyclicVector<T>*  vec, const unsigned int& index) : currentIndex(index)
        {
            iterSource = vec;
        }

        T& operator * ()
        {
            while (currentIndex >= iterSource->size())
                currentIndex -= iterSource->size();

            return iterSource->at(currentIndex);
        }

        void operator ++ ()
        {
            while (currentIndex >= iterSource->size())
                currentIndex -= iterSource->size();

            if (++currentIndex >= iterSource->size())
                currentIndex = 0;
        }

        void operator += (const int& value)
        {
            currentIndex += value;

            while (currentIndex >= iterSource->size())
                currentIndex -= iterSource->size();

            while (currentIndex < 0)
                currentIndex += iterSource->size();
        }

        iterator operator + (const unsigned int& n)
        {
            int tmp = currentIndex + n;

            while (tmp >= iterSource->size())
                tmp -= iterSource->size();

            return iterator(iterSource, tmp);
        }

        void operator -- ()
        {
            while (currentIndex >= iterSource->size())
                currentIndex -= iterSource->size();

            if (--currentIndex < 0)
                currentIndex = iterSource->size() - 1;
        }

        void operator -= (const int& value)
        {
            currentIndex -= value;

            while (currentIndex >= iterSource->size())
                currentIndex -= iterSource->size();

            while (currentIndex < 0)
                currentIndex += iterSource->size();
        }

        iterator& operator - (const unsigned int& n)
        {
            int tmp = currentIndex - n;

            while (tmp < 0)
                tmp += iterSource->size();

            return iterator(iterSource, tmp);
        }

        const bool operator != (const CyclicVector<T>::iterator& toTest)
        {
            if (currentIndex != toTest.currentIndex || iterSource != toTest.iterSource)
                return true;
            else
                return false;
        }

        const bool operator == (const iterator& toTest)
        {
            if (getIndex() == toTest.getIndex() && iterSource == toTest.iterSource)
                return true;
            else
                return false;
        }

        const unsigned int getIndex()
        {
            return currentIndex;
        }
    };

     const std::vector<T>& getSource(){ return source;}

    T& at(unsigned int index)
    {
        while (index >= source.size())
            index -= source.size();

        return source[index];
    }

    T& operator [](unsigned int index)
    {
        return this->at(index);
    }

    T& front()
    {
        return source.front();
    }

    T& back()
    {
        return source.back();
    }

    iterator begin()
    {
        return iterator(this);
    }

    iterator end()
    {
        return iterator(this, source.size() - 1);
    }

    const size_t capacity()
    {
        return source.capacity();
    }

    void reserve(size_t size)
    {
        source.reserve(size);
    }

    void resize(size_t num)
    {
            source.resize(num);
    }

    const size_t size()
    {
        return source.size();
    }

    void clear()
    {
        source.clear();
    }

    const bool empty()
    {
        return source.empty();
    }

    iterator insert(const iterator& loc, const T& val)
    {
        source.insert(source.begin() + loc.getIndex(), val);
    }

    void erase(iterator loc)
    {
        source.erase(source.begin() + loc.getIndex());
    }

    T& pop_back()
    {
        T ret = source.back();
        source.pop_back();
        return ret;
    }

    void push_back(const T& val)
    {
        source.push_back(val);
    }
};

#endif // CYCLICVECTOR_H_INCLUDED
