#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "PatternT.h"

using namespace std;

enum class ChocolateTaste : int
{
    Dark,
    White,
    Milky,
    Unknown
};

enum class ChocolateColorPack : int
{
    White,
    Blue,
    Purple,
    Unknown
};

// Функция для преобразования ChocolateTaste в строку
string TasteToString(ChocolateTaste taste) {
    switch(taste) {
        case ChocolateTaste::Dark: return "Dark";
        case ChocolateTaste::White: return "White";
        case ChocolateTaste::Milky: return "Milky";
        default: return "Unknown";
    }
}

// Функция для преобразования ChocolateColorPack в строку
string ColorToString(ChocolateColorPack color) {
    switch(color) {
        case ChocolateColorPack::White: return "White";
        case ChocolateColorPack::Blue: return "Blue";
        case ChocolateColorPack::Purple: return "Purple";
        default: return "Unknown";
    }
}


class Chocolate{
private:
    ChocolateTaste Taste;
    int price;
    double weight;
    ChocolateColorPack ColorPack;

protected:
    bool IsMelting;

public:
    Chocolate(ChocolateTaste taste, ChocolateColorPack colorPack, int price, double weight)
    : Taste(taste), ColorPack(colorPack), price(price), weight(weight), IsMelting(false){
        IsMelting = static_cast<bool>(rand()%2);
    }
    virtual ~Chocolate(){}

    string GetTaste() const { return TasteToString(Taste); }
    //ChocolateTaste GetTaste() const {return Taste; }

    string GetColorPack() const {return ColorToString(ColorPack); }

    ChocolateColorPack GetColorEnum() const { return ColorPack; }

    int GetPrice() const {return price;}

    bool IsMelt() const {return IsMelting;}

    virtual void eat()
    {
        if(IsMelt())
        {
            cout << "Eating melting chocolate ... " << endl;
        }
        else
        {
            cout << "Eating NOT melting fruit... " << endl;
        }
    };

    virtual void describe()
    {
       cout << "Chocolate taste: " << GetTaste() << ";  " <<
                             "Weight: " << weight << ";  " <<
                             "Price: " << price << ";  " <<
                             "Color pack: " << GetColorPack() << " MELTS: ";
    }

    virtual void melt () {cout << "Is melt?:" << IsMelting << endl;}
};






class Milka : public Chocolate
{
public:
    Milka();
    ~Milka();

    void eat()
    {
        //cout << "They ate it(" << endl;
        Chocolate::eat();
    };

    void describe() override
    {
        Chocolate::describe();
    }
    void melt() {
        cout << "Is melt?: " << IsMelting << endl;}
};

Milka::Milka() : Chocolate(ChocolateTaste::Dark, ChocolateColorPack::Purple, 70, 75.0)
{}

Milka::~Milka()
{}


class AlpenGold : public Chocolate
{
public:
    AlpenGold();
    ~AlpenGold();

    void eat(){
        //cout << "We left 1 piece :)" << endl;
        Chocolate::eat();
    };
    void describe() override
    {
        Chocolate::describe();
    }
    void melt() {
        IsMelting = true;
        cout << "Is melt?: " << IsMelting << endl;}
};

AlpenGold::AlpenGold() : Chocolate(ChocolateTaste::White, ChocolateColorPack::Blue, 50, 75.0)
{}

AlpenGold::~AlpenGold()
{}

class RitterSport : public Chocolate
{
public:
    RitterSport();
    ~RitterSport();

    void eat(){
        //cout << "They even ate the packaging" << endl;
        Chocolate::eat();

    };
    void describe() override
    {
        Chocolate::describe();
    }
    void melt() {cout << "Is melt?: " << IsMelting << endl;}
};

RitterSport::RitterSport() : Chocolate(ChocolateTaste::Milky, ChocolateColorPack::White, 1000, 100.0)
{}

RitterSport::~RitterSport()
{}




//фабричный метод создания класса
enum class ChocolateType : int
{
    Milka = 1,
    AlpenGold = 2,
    RitterSport = 3,

    Undefined = 0
};

Chocolate *CreateChocolate(ChocolateType type)
{
    Chocolate *newChocolate = nullptr;

    if(type == ChocolateType::Milka)
    {
        newChocolate = new Milka;
    }
    else if(type == ChocolateType::AlpenGold)
    {
        newChocolate = new AlpenGold;
    }
    else if(type == ChocolateType::RitterSport)
    {
        newChocolate = new RitterSport;
    }

    return newChocolate;
}

void AllItems(Iterator<Chocolate*> *iterator)
{
    for (iterator->First(); !iterator->IsDone(); iterator->Next())
    {
        Chocolate* choco = iterator->GetCurrent();
        choco->eat();
        choco->describe();
        choco->melt();
    }
}

// Декоратор итератора для выделения расстаявших шоколодок

class ChocolateMeltDecorator : public IteratorDecorator<class Chocolate*>
{
private:
    bool TargetMelt;

public:
    ChocolateMeltDecorator(Iterator<Chocolate*> *it, bool isMelt)
    : IteratorDecorator<Chocolate*>(it), TargetMelt(isMelt) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->IsMelt() != TargetMelt)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->IsMelt() != TargetMelt);
    }
};

//декоратор для выделение шоколада по цене

class ChocolatePriceDecorator : public IteratorDecorator<class Chocolate*>
{
private:
    int TargetPrice;

public:
    ChocolatePriceDecorator(Iterator<Chocolate*> *it, int price)
    : IteratorDecorator<Chocolate*>(it), TargetPrice(price) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetPrice() >= TargetPrice)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetPrice() >= TargetPrice);
    }
};

// Декоратор итератора для выделения шоколада по цвету

class ChocolateColorDecorator : public IteratorDecorator<class Chocolate*>
{
private:
    ChocolateColorPack TargetColor;

public:
    ChocolateColorDecorator(Iterator<Chocolate*> *it, ChocolateColorPack color)
    : IteratorDecorator<Chocolate*>(it), TargetColor(color) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetColorEnum() != TargetColor)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetColorEnum() != TargetColor);
    }
};






// Функция, позволяющая съесть любые шоко из любого контейнера

void EatEmAll(Iterator<Chocolate*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Chocolate *currentChocolate = it->GetCurrent();

        currentChocolate->describe();
        currentChocolate->eat();
    }
}

// Функция, позволяющая съесть только фиолетовые шоколадки
void EatEmAllPurple(Iterator<Chocolate*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Chocolate *currentChocolate = it->GetCurrent();
        if(currentChocolate->GetColorEnum() != ChocolateColorPack::Purple) continue;

        currentChocolate->describe();
        currentChocolate->eat();
    }
}

// Функция, позволяющая съесть только шоколадки дешевле 100
void EatEmAllPrice(Iterator<Chocolate*> *it, int price)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Chocolate *currentChocolate = it->GetCurrent();
        if(currentChocolate->GetPrice() >= price) continue;

        currentChocolate->describe();
        currentChocolate->eat();
    }
}

// Функция, позволяющая съесть только не расстаявщие шоколадки
void EatEmAllNotMelt(Iterator<Chocolate*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Chocolate *currentChocolate = it->GetCurrent();
        if(currentChocolate->IsMelt()) continue;

        currentChocolate->describe();
        currentChocolate->eat();
    }
}




int main()
{
    size_t N = 30;

    // стек шоколадок
    StackClass <Chocolate*> chocolateStack;
    for (size_t i=0;i<N;i++)
    {
        int number = rand()%3+1;
        ChocolateType choco_type = static_cast<ChocolateType>(number);
        Chocolate *choco1 = CreateChocolate(choco_type);
        chocolateStack.Push(choco1);
    }

    cout << "stack size of chocolate: " << chocolateStack.Size() << endl;

    // Обход всех не расстаявщих шоколадок
    cout << endl << "Eating all not melt using iterator:" << endl;
    Iterator<Chocolate*> *meltIt = new ChocolateMeltDecorator(chocolateStack.GetIterator(), false);
    EatEmAll(meltIt);
    delete meltIt;

    // Обход всех фиолетовых шоколадок
    cout << endl << "Eating all purple using iterator:" << endl;
    Iterator<Chocolate*> *purpleIt = new ChocolateColorDecorator(chocolateStack.GetIterator(), ChocolateColorPack::Purple);
    EatEmAllPurple(purpleIt);
    delete purpleIt;

    // Обход всех шоколадок ниже 100
    cout << endl << "Eating all the chocolate for less than 100 iterator:" << endl;
    Iterator<Chocolate*> *priceIt = new ChocolatePriceDecorator(chocolateStack.GetIterator(), 100);
    EatEmAllPrice(priceIt, 100);
    delete priceIt;

    // Обход всех фиолетовых, не расстаявших шоколадок
    cout << endl << "Eating all purple and not melt using iterator:" << endl;
    Iterator<Chocolate*> *purplemeltIt = new ChocolateMeltDecorator(new ChocolateColorDecorator(chocolateStack.GetIterator(), ChocolateColorPack::Purple), false);
    EatEmAll(purplemeltIt);
    delete purplemeltIt;

    // демонстрация адаптера

    vector<Chocolate*> chocoVector;
    for(size_t i=0; i<N; i++)
    {
        int choco_num = rand()%3+1;
        ChocolateType choco_type = static_cast<ChocolateType>(choco_num);
        Chocolate *newChocolate = CreateChocolate(choco_type);
        chocoVector.push_back(newChocolate);
    }

    cout << endl << "The size of the chocolate vector: " << chocoVector.size() << endl;

    // Демонстрация работы адаптера
    cout << endl << "Eating all good purple chocolate using adapted iterator:" << endl;

    //Создаем адаптер для STL-контейнера
    Iterator<Chocolate*>* adaptedIt = new ConstIteratorAdapter<vector<Chocolate*>, Chocolate*>(&chocoVector);

    //Комбинируем декораторы: сначала фильтр по цвету, потом по состоянию
    Iterator<Chocolate*>* adaptedDecoratedIt =
        new ChocolateMeltDecorator(
            new ChocolateColorDecorator( adaptedIt, ChocolateColorPack::Purple), false);
    EatEmAll(adaptedDecoratedIt);
    delete adaptedDecoratedIt;



    return 0;
}
