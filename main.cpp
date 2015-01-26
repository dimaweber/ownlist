#include <iostream>

template<class T>
class OwnList
{
    template<class C>
    struct Item
    {
        C value;
        Item<C>* next;
        Item<C>()
        {
            next = nullptr;
        }
        Item<C>(const C& c )
            :Item<C>()
        {
            value = c;
        }
        Item<C>(const C& c, Item<C>* n)
            :Item<C>()
        {
            value = c;
            next = n;
        }
    };

    Item<T>* head;
    Item<T>* tail;
    int count;

public:
    OwnList();
    ~OwnList();

    void insertFirst(const T& v); // O(1)
    void insertLast(const T &v); // O(1)

    void removeFirst(); // O(1)
    void removeLast(); // O(n)

    bool isEmpty() const; // O(1)

    void reverse(); // O(n)

    void display (bool newline = false) const; // O(n)

    int size() const; // O(1)

    // for tests purpose
    bool compareArray(T* array, int arrayLen);
};

template <class T>
OwnList<T>::OwnList()
    :head(nullptr), tail(nullptr), count(0)
{
}

template <class T>
OwnList<T>::~OwnList()
{
    while(!isEmpty())
        removeFirst();
}

template<class T>
void OwnList<T>::insertFirst(const T& v)
{
    Item<T>* p = new Item<T>(v);
    p->next = head;
    head = p;
    if (tail == nullptr)
        tail = p;
    count++;
}

template<class T>
void OwnList<T>::insertLast(const T& v)
{
    Item<T>* p = new Item<T>(v);
    tail->next = p;
    tail = p;
    if (head == nullptr)
        head = p;
    count++;
}

template <class T>
void OwnList<T>::removeFirst()
{
    if (isEmpty())
        return;

    Item<T>* p = head;
    head = p->next;
    delete p;
    count--;
}

template<class T>
void OwnList<T>::removeLast()
{
    if (isEmpty())
        return;

    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Item<T>* p = head;
        while (p->next != tail)
            p = p->next;
        p->next = nullptr;
        delete tail;
        tail = p;
    }
    count--;
}

template<class T>
bool OwnList<T>::isEmpty() const
{
    return head == nullptr;
}

template<class T>
void OwnList<T>::reverse()
{
    Item<T>* cur = head;
    Item<T>* prev = nullptr;
    Item<T>* next = nullptr;

    while (cur != nullptr)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    cur = tail;
    tail = head;
    head = cur;
}

template<class T>
void OwnList<T>::display(bool newline) const
{
    std::cout << "[";
    for (Item<T>* p = head; p != nullptr; p=p->next)
        std::cout << p->value << ' ';
    std::cout << "]";
    if (newline)
        std::cout << "\n";
}

template<class T>
int OwnList<T>::size() const
{
    return count;
}

template<class T>
bool OwnList<T>::compareArray(T *array, int arrayLen)
{
    if (arrayLen != size())
        return false;
    int i=0;

    for(auto p = head; p!=nullptr; p=p->next, i++)
    {
       if (p->value != array[i])
           return false;
    }
    return true;
}

template <class T>
void testFunction(OwnList<T> list)
{
    {
        T checkArray[] = {};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray) / sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }

    list.insertFirst(5);
    {
        T checkArray[] = {5};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray)/ sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }

    list.insertLast(10);
    {
        T checkArray[] = {5, 10};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray)/ sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }


    list.insertFirst(3);
    {
        T checkArray[] = {3, 5, 10};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray)/ sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }


    list.insertLast(15);
    {
        T checkArray[] = {3, 5, 10, 15};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray)/ sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }

    std::cout << "before revert: ";
    list.display(true);

    list.reverse();

    std::cout << "after revert";
    list.display(true);


    {
        T checkArray[] = {15, 10, 5, 3};
        std::cout << "create empty list: ";
        if ( !list.compareArray(checkArray, sizeof(checkArray)/ sizeof(T)) )
            std::cerr << "fail\n";
        else
            std::cout << "ok\n";
    }

    std::cout << "remove first: ";
    list.removeFirst();
    list.display(true);

    std::cout << "remove last: ";
    list.removeLast();
    list.display(true);

    std::cout << "remove last: ";
    list.removeLast();
    list.display(true);

    std::cout << "remove last: ";
    list.removeLast();
    list.display(true);

    std::cout << "list is empty: ";
    if (list.isEmpty())
        std::cout << "ok\n";
    else
        std::cout << "fail\n";
}

int main(int argc, char* argv[])
{
    std::cout << "Int test:\n";
    OwnList<int> l1;
    testFunction(l1);

    std::cout << "Float test:\n";
    OwnList<float> l2;
    testFunction(l2);
}
