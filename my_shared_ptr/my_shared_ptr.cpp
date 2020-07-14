// my_shared_ptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shared_ptr.h"
#include <utility>
#include <iostream>
int main()
{
	int t1 = 0xaa;
	SharedPtr<int> s1(t1);
	std::cout << s1.GetRefCount() << std::endl;
	SharedPtr<int> s2(s1);
	std::cout << s1.GetRefCount() << std::endl;
	SharedPtr<int> s3(std::move(s1));
	std::cout << s1.GetRefCount() << std::endl;
	SharedPtr<int> s4;
	s4 = s1;
	std::cout << s1.GetRefCount() << std::endl;
	SharedPtr<int> s5;
	s5 = std::move(s1);
	std::cout << s1.GetRefCount() << std::endl;
	std::cout << s2.GetRefCount() << std::endl;
	std::cout << s3.GetRefCount() << std::endl;
	std::cout << s4.GetRefCount() << std::endl;
	std::cout << s5.GetRefCount() << std::endl;
	/*system("pause");*/
	return 0;
}

