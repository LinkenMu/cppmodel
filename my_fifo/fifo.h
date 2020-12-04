#include <queue>
#include <memory>
using namespace std;

template <class T>
class Fifo {
public:
    void PutIn(shared_ptr<T> p){
      my_queue_.push(p);  
    };
    
    shared_ptr<T> GetOut(){
        auto out = my_queue_.front(); 
        my_queue_.pop();
        return out;
    };
private:
    queue<shared_ptr<T>> my_queue_;
};