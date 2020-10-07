#ifndef _SERVER_CONDITION_H
#define _SERVER_CONDITION_H

#include "Mutex.h"

#include <pthread.h>

namespace server {

class Condition {
public:
    explicit Condition(MutexLock& mutex) : mutex_(mutex){
        pthread_cond_init(&cond_, nullptr);
    }
    ~Condition(){
        pthread_cond_destroy(&cond_);
    }

    void notify_one();
    void notify_all();
private:
    pthread_cond_t cond_;
    MutexLock& mutex_;
};

}

#endif