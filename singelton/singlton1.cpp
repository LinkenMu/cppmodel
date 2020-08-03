// singlton1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "singlten.h"
using namespace std;
class A {
public:
	void Print() { cout << "a "<< (this) << endl; };
	friend class Singleton<A>;
private:
	A() {};

};
int main()
{
	Singleton<A>::GetInctance()->Print();
	Singleton<A>::GetInctance()->Print();

    return 0;
}

