//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_JOBQUEUE_H
#define UNTITLED_JOBQUEUE_H
#include "Job.h"
#include "LockQueue.h"
#include <atomic>
class JobQueue :public std::enable_shared_from_this<JobQueue>{
public:
    void DoAsync(CallBackType&& callback)
    {
        Push(std::make_shared<Job>(std::move(callback)));
    }

    template<typename T,typename Ret, typename... Args>
    void DoAsync(Ret(T::*memFunc)(Args...),Args...args)
    {
        std::shared_ptr<T> owner = static_cast<T*>(shared_from_this());
        Push(std::make_shared<Job>(owner,memFunc,std::forward<Args>(args)...));
    }

    void ClearJobs(){_jobs.Claer();}

public:
     void Push(std::shared_ptr<Job> jobRef);
     void Execute();

protected:
    LockQueue<std::shared_ptr<Job>> _jobs;
    std::atomic<int32_t> _jobCount=0;
};


#endif //UNTITLED_JOBQUEUE_H
