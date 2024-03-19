//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_LOCKQUEUE_H
#define UNTITLED_LOCKQUEUE_H
#include <vector>
#include <mutex>
#include <queue>
template<typename T>
class LockQueue {


public:
    void Push(T item){
        std::lock_guard<std::mutex> guard(m);
        _items.push(item);
    }
    T Pop()
    {
        std::lock_guard<std::mutex> guard(m);
        if(_items.empty())
            return T();
        T ret = _items.front();
        _items.pop();
        return ret;
    }
    void PopAll(std::vector<T>& items)
    {
        std::lock_guard<std::mutex> guard(m);
        while(true){
            if(_items.empty())
                return;
            else
            {
                T item = _items.front();
                _items.pop();
                items.push_back(item);
            }
        }
    }

    size_t Size(){return _items.size();}

    void Claer()
    {
        std::lock_guard<std::mutex> guard(m);
        _items = std::queue<T>();
    }

private:
    std::mutex m;
    std::queue<T> _items;
};


#endif //UNTITLED_LOCKQUEUE_H
