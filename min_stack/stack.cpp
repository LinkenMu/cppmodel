// stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stack.h"

int main()
{
	int a[10] = {5,3,6,8,3,2,8,9,11,23};
	MinStack<int> stack1(a,10);
	stack1.PrintStack();

	MinStack<int> stack2(stack1);
	stack2.PrintStack();
	MinStack<int> stack3;
	
	stack3 = stack1;
	stack3.AddNode(44);
	stack3.PrintStack();


    return 0;
}

