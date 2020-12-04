/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
using namespace std;
// #include "fifo.h"
#include "threads_fifo.h"
int main ()
{
    ThreadFifo<int> f1;
    
    thread th([&f1](){
        cout<<"thread wait------"<<endl;
        auto a1 = f1.GetOut();
        printf("a1 0x%x \n", *a1);
    });
    
    this_thread::sleep_for(chrono::seconds(2));
    shared_ptr<int> a(new int(0x44));
    f1.PutIn(a);
    cout<<"------------"<<endl;
    th.join();
    cout<<"+------------"<<endl;
  return 0;
}

// int main ()
// {
//     Fifo<int> f1;
    
//     shared_ptr<int> a(new int(0x44));
//     shared_ptr<int> b(new int(0x55));
//     f1.PutIn(a);
//     f1.PutIn(b);
//     cout<<"------------"<<endl;
    
//     auto a1 = f1.GetOut();
//     auto b1 = f1.GetOut();
//     printf("%x %x\n", *a1, *b1);
//   return 0;
// }
