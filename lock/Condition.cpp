#include "Condition.h"

namespace server {

void Condition::notify_one() {
    mutex_.lock();
    pthread_cond_signal(&cond_);
    mutex_.unlock();
}

void Condition::notify_all() {
    mutex_.lock();
    pthread_cond_broadcast(&cond_);
    mutex_.unlock();
}


} // namespace server