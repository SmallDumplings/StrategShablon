#ifndef PATTERNT_H_INCLUDED
#define PATTERNT_H_INCLUDED
#include <vector>

using namespace std;

template<typename T>
class Iterator
{
protected:
    Iterator(){}
public:
    virtual ~Iterator(){}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrent() const = 0;
};

// Базовый интерфейс контейнера
template <typename T>
class Container {
public:
    virtual ~Container() {}
    virtual Iterator<T>* GetIterator() const = 0;
    virtual bool IsEmpty() const = 0;
};


const size_t MaxSize = 100;

template<typename T>
class StackIterator:public Iterator<T>
{
private:
    const T* StackContainer;
    size_t Pos;
    size_t Size;

public:
    StackIterator(const T *container, size_t size)
    : StackContainer(container), Pos(0), Size(size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return StackContainer[Pos]; }
};

template <typename T>
class StackClass : public Container<T>
{
private:
    T Items[MaxSize];
    size_t Top;

public:
    bool IsEmpty() const { return (Top == 0); }
    size_t Size() const { return Top; }
    void Push(T newObject) { Items[Top++] = newObject; }
    T Pop() { return Items[--Top]; }
    T* GetItems() { return Items; }
    T GetElementByIndex(size_t index) const { return Items[index]; }
    StackClass() : Top(0) {}

    Iterator<T>* GetIterator() const override {
        return new StackIterator<T>(Items, Top);
    }
};

template<typename T>
class VecIterator : public Iterator<T> {
private:
    const T *Veccontainer;
    size_t current;
    size_t Size;
public:
    VecIterator(const T *c, size_t size) : Veccontainer(c), current(0), Size(size) {}

    void First() override { current = 0; }
    void Next() override { ++current; }
    bool IsDone() const override { return (current >= Size); }
    T GetCurrent() const override { return Veccontainer[current]; }

};



template <typename T>
class VectorContainer : public Container<T>
{
private:
    vector<T> vectorContainer;

public:
    bool IsEmpty() const{
        return vectorContainer.empty();
    }
    T Top() const{
        return vectorContainer.back();
    }


    void Add(const T& vec) {
        vectorContainer.push_back(vec);
    }

    size_t Size() const {
        return vectorContainer.size();
    }
    const T* GetData() const { return vectorContainer.data(); }
    T IndexElement(size_t index) const
    {
        return vectorContainer[index];
    };

    Iterator<T>* GetIterator() const override {
        return new VecIterator<T>(vectorContainer.data(), vectorContainer.size());
    }

};




// Декоратор для итератора (пустой)

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

// Адаптер для контейнерных классов STL

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    const ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};


#endif // PATTERNT_H_INCLUDED
