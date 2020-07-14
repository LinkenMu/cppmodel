#pragma once
template<class T>
class SharedPtr
{
public:
	SharedPtr(T& t) {
		object_ = new T(t);
		used_ = new(int);
		(*used_) = 1;
	};//construct
	SharedPtr() {
		object_ = nullptr;
		used_ = nullptr;
	};

	SharedPtr(SharedPtr<T>&& t) {
		delete object_;
		object_ = t.object_;
		used_ = t.used_;

	};//move
	SharedPtr(SharedPtr<T>& t) {
		if (object_ == t.object_)
		{
			return;
		}
		object_ = t.object_;
		used_ = t.used_;
		(*used_)++;
	};//copy

	~SharedPtr() {
		if (*used_ > 0) {
			(*used_)--;
		}

		if (*used_ == 0) {
			delete object_;
			delete used_;
		}
	};

	SharedPtr& operator =(const SharedPtr& t)
	{
		if (object_ == t.object_) {
			return *this;
		}
		if (object_) {
			(*used_)--;
			if (*used_ == 0) {
				delete object_;
				delete used_;
			}
		}

		object_ = t.object_;
		used_ = t.used_;
		(*used_)++;
		return *this;
	}

	SharedPtr& operator =(const SharedPtr&& t)
	{
		if (object_ != nullptr)
		{
			delete object_;
		}
		if (used_)
		{
			delete used_;
		}

		object_ = t.object_;
		used_ = t.used_;
		return *this;
	}

	SharedPtr& operator* ()
	{
		assert(object_ == nullptr);
		return *object;
	}

	SharedPtr* operator->()
	{
		assert(object_ == nullptr);
		return object_;
	}

	int GetRefCount() {
		return *used_;
	}
private:
	T *object_;
	int* used_;
};

