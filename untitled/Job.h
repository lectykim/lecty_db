//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_JOB_H
#define UNTITLED_JOB_H

#include <functional>
#include <memory>
using CallBackType = std::function<void()>;

class Job {
public:
    explicit Job(CallBackType && callback) : _callback(std::move(callback)){

    }
    template<typename T,typename Ret, typename...Args>
    Job(std::shared_ptr<T> owner,Ret(T::*memFunc)(Args...),Args&&...args)
    {
        _callback = [owner,memFunc,args...]()
        {
            (owner.get()->*memFunc)(args...);
        };
    }

    void Execute()
    {
        _callback();
    }

private:
    CallBackType _callback;
};


#endif //UNTITLED_JOB_H
