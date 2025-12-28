#include <iostream>

using namespace std;

template<class T>
class Array 
{
private:
    T* arr; 
    unsigned int size;
    int count;
    int grow;

public:
    Array()
    {
        arr = nullptr;
        size = 0;
        count = 0;
        grow = 1;
    }

    Array(unsigned int size)
    {
        this->size = size;
        arr = new T[size]{};
    }

    ~Array() {
        if (arr != nullptr)
        {
            delete[] arr;
        }
    }

    bool IsEmpty() const
    {
        return count == 0;
    }

    int GetUpperBound() const
    {
        return count - 1;
    }

    void SetSize(int newSize, int grow = 1) {
        this->grow = (grow > 0) ? grow : 1;
        if (newSize == size) return;

        if (newSize == 0) {
            RemoveAll();
            return;
        }

        T* newArr = new T[newSize];
        int elementsToCopy = (newSize < count) ? newSize : count;

        for (int i = 0; i < elementsToCopy; ++i) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        size = newSize;
        if (count > size) count = size;
    }
    int getSize() const
    {
        return size;
    }
    
    void RemoveAll() 
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
        count = 0;
    }

    void Add(const T& value) 
    {
        if (count == size) 
        {
            SetSize(size + grow, grow);
        }
        arr[count++] = value;
    }

    void Append(const Array& other) 
    {
        for (int i = 0; i < other.count; ++i) 
        {
            Add(other.arr[i]);
        }
    }
    void InsertAt(int index, const T& value)
    {
        if (count == size) 
        {
            SetSize(size + grow, grow);
        }

        for (int i = count; i > index; --i) 
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        count++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= count) throw out_of_range("Invalid index");
        for (int i = index; i < count - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        count--;
    }

    void print() const 
    {
        for (unsigned int i = 0; i < size; i++) 
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array<int> arr1 (4);

    cout << "Initial size: " << arr1.getSize() << endl;
    arr1.print();
    arr1.Add(10);
    arr1.Add(40);
    arr1.Add(11);
    arr1.Add(7);
    arr1.print();
    arr1.InsertAt(1, 55);
    
    Array<int> arr2;
    arr2.Add(11);
    arr2.Add(100);
    arr1.Append(arr2);

    arr2.print();
    arr1.print();

    return 0;
}
