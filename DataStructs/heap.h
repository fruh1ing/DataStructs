#include <assert.h>
template<typename T>
class MaximumHeap
{
public:
	MaximumHeap(size_t size);
	~MaximumHeap();
	size_t parent(size_t i);
	size_t left(size_t i);
	size_t right(size_t i);

	void max_heapify(size_t i);
	void build_max_heap();
	void sort();
private:
	void exchange(size_t i, size_t j);
	size_t size_;
	T* arr;
};

template<typename T>
void MaximumHeap<T>::exchange(size_t i, size_t j)
{
	assert(i <= size_);
	assert(i <= size_);
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template<typename T>
void MaximumHeap<T>::sort()
{
	size_t lenght = size_;
	for (int i = size_; i > 1; --i)
	{
		exchange(i, 1);
		size_--;
		max_heapify(1);
	}
	size_ = lenght;
}

template<typename T>
void MaximumHeap<T>::build_max_heap()
{
	int n = size_ / 2;
	while (n > 0)
	{
		max_heapify(n);
		--n;
	}
}

template<typename T>
void MaximumHeap<T>::max_heapify(size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest;
	if (l < size_ && arr[l] > arr[i])
		largest = l;
	else
		largest = i;
	if (r<size_ && arr[r]>arr[i])
		largest = r;
	if (largest != i)
	{
		T temp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = temp;
		max_heapify(largest);
	}

}

template<typename T>
size_t MaximumHeap<T>::right(size_t i)
{
	assert(2 * i + 1 <= size_);
	return 2 * i + 1;
}

template<typename T>
size_t MaximumHeap<T>::left(size_t i)
{
	assert(2 * i <= size_);
	return 2 * i;
}

template<typename T>
size_t MaximumHeap<T>::parent(size_t i)
{
	assert(a <= size_);
	return i / 2;
}

template<typename T>
MaximumHeap<T>::MaximumHeap(size_t size) :size_(size)
{
	arr = new T[size + 1];
}

template<typename T>
MaximumHeap<T>::~MaximumHeap()
{
	delete[] arr;
}
