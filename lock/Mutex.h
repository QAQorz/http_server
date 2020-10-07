#ifndef _SERVER_LOCK_H
#define _SERVER_LOCK_H

#include <pthread.h>

namespace server {

class MutexLock {
public:
    MutexLock(): holder_(0){
        pthread_mutex_init(&mutex_, nullptr);
    }
    ~MutexLock(){
        pthread_mutex_destroy(&mutex_);
    }

    void set_holder(int tid);
    void reset_holder();
    void lock();
    void unlock();
    bool isLock();
private:
    pthread_mutex_t mutex_;
    pthread_t holder_;
};

}

#endif