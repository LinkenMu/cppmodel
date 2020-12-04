#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

template <class T>
class ThreadFifo {
public:
    void PutIn(shared_ptr<T> p){
        unique_lock<mutex> lock(mutex_);
        my_queue_.push(p);  
        cv.notify_one();
    };
    
    shared_ptr<T> GetOut(){
        unique_lock<mutex> lock(mutex_);
        cv.wait(lock, [this]()->bool{return !my_queue_.empty();});
        auto out = my_queue_.front(); 
        my_queue_.pop();
        return out;
    };
private:
    queue<shared_ptr<T>> my_queue_;
    mutex mutex_;
    condition_variable cv;
};