// singlton1.cpp : �������̨Ӧ�ó������ڵ㡣
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

