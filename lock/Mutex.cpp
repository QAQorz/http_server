#include "Mutex.h"

#include "../threadpool/Thread.h"

namespace server {

void MutexLock::lock() {
    set_holder(Thread::gettid());
    pthread_mutex_lock(&mutex_);
}

void MutexLock::unlock() {
    pthread_mutex_unlock(&mutex_);
    reset_holder();
}

bool MutexLock::isLock() {
    return holder_ == 0;
}

void MutexLock::set_holder(int tid) {
    holder_ = tid;
}

void MutexLock::reset_holder() {
    holder_ = 0;
}

} // namespace server