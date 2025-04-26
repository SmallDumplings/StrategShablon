#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Pattern.h"

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

//реализация Стратегии

enum class EatingMannerEnum : int
{
  chocBreak = 1,
  chompChunk = 2,
  meltInMouth = 3,
  chocoShred = 4,
  chocCrush = 5,

  None = 0
};

/*
string MannerToString(EatingMannerEnum manner) {
    switch(color) {
        case EatingMannerEnum::chocBreak: return "chocBreak";
        case EatingMannerEnum::chompChunk: return "chompChunk";
        case EatingMannerEnum::meltInMouth: return "meltInMouth";
        case EatingMannerEnum::chocoShred: return "chocoShred";
        case EatingMannerEnum::chocCrush: return "chocCrush";

        default: return "Unknown";
    }
}
*/

class EatingStrategy
{
public:
  virtual ~EatingStrategy() {}
  virtual void eat() = 0;
  virtual EatingMannerEnum GetMannerEnum() const = 0;
};

class ChocBreakStrategy : public EatingStrategy
{
  void eat() { cout << "Breaking chocolate into perfect slices..."; }
  EatingMannerEnum GetMannerEnum() const override { return EatingMannerEnum::chocBreak; }
};

class ChompChunkStrategy : public EatingStrategy
{
  void eat() { cout << "Taking a bold whole bite of chocolate..."; }
  EatingMannerEnum GetMannerEnum() const override { return EatingMannerEnum::chompChunk; }
};

class MeltInMouthStrategy : public EatingStrategy
{
  void eat() { cout << "Letting chocolate melt slowly on the tongue..."; }
  EatingMannerEnum GetMannerEnum() const override { return EatingMannerEnum::meltInMouth; }
};

class ChocoShredStrategy : public EatingStrategy
{
  void eat() { cout << "Shredding chocolate into delicate flakes..."; }
  EatingMannerEnum GetMannerEnum() const override { return EatingMannerEnum::chocoShred; }
};

class ChocCrushStrategy : public EatingStrategy
{
  void eat() { cout << "Crushing chocolate into tiny fragments..."; }
  EatingMannerEnum GetMannerEnum() const override { return EatingMannerEnum::chocCrush; }
};

// Фабричный метод для создания стратегий
EatingStrategy* CreateEatingStrategy(EatingMannerEnum eatingManner)
{
    switch(eatingManner)
    {
        case EatingMannerEnum::chocBreak: return new ChocBreakStrategy();
        case EatingMannerEnum::chompChunk: return new ChompChunkStrategy();
        case EatingMannerEnum::meltInMouth: return new MeltInMouthStrategy();
        case EatingMannerEnum::chocoShred: return new ChocoShredStrategy();
        case EatingMannerEnum::chocCrush: return new ChocCrushStrategy();

        default: return nullptr;
    }
}



//фабричный метод создания класса
enum class ChocolateType : int
{
    Milka = 1,
    AlpenGold = 2,
    RitterSport = 3,

    Undefined = 0
};

string TypeToString(ChocolateType type) {
    switch(type) {
        case ChocolateType::Milka: return "Milka";
        case ChocolateType::AlpenGold: return "AlpenGold";
        case ChocolateType::RitterSport: return "RitterSport";
        default: return "Unknown";
    }
}






class Chocolate{
private:
    ChocolateTaste Taste;
    int price;
    double weight;
    ChocolateColorPack ColorPack;

    EatingStrategy *EatingManner;

    void DoEatUsingStrategy()
    {
      if(EatingManner == nullptr)
      {
        // Способ съедания не задан, ничего не делаем
        cout << "Do nothing!";
        return;
      }
      else
      {
        // Съесть заданным способом
        EatingManner->eat();
      }
    }

    void DetectMeltOrNot()
    {
      if(IsMelt())
      {
          cout << " Type: Melting";
      }
      else
      {
          cout << " Type: Perfect";
      }
    }



protected:
    bool IsMelting;

public:
    Chocolate(ChocolateTaste taste, ChocolateColorPack colorPack, int price, double weight)
    : Taste(taste), ColorPack(colorPack), price(price), weight(weight), IsMelting(false), EatingManner(nullptr){
        IsMelting = static_cast<bool>(rand()%2);
    }
    virtual ~Chocolate(){if(EatingManner != nullptr) delete EatingManner;}

    string GetTaste() const { return TasteToString(Taste); }
    //ChocolateTaste GetTaste() const {return Taste; }

    string GetColorPack() const {return ColorToString(ColorPack); }

    ChocolateColorPack GetColorEnum() const { return ColorPack; }

    int GetPrice() const {return price;}

    bool IsMelt() const {return IsMelting;}


    virtual ChocolateType GetType() const = 0;

    virtual void describe()
    {
       cout << "Chocolate taste: " << GetTaste() << ";  "
            << "Chocolate name: " << TypeToString(GetType())
            << ";  " << "Color pack: " << GetColorPack() << endl;
    }

    void eat()
    {   DoEatUsingStrategy();

        DetectMeltOrNot();

        cout << endl;

    };
    virtual void melt () {cout << "Is melt?:" << IsMelting << endl;}
    void SetEatingManner(EatingStrategy *eatingManner) { EatingManner = eatingManner; }
    EatingMannerEnum GetMannerEnum() const {
        if (EatingManner != nullptr) {
            return EatingManner->GetMannerEnum();
        }
        return EatingMannerEnum::None;
    }
};






class Milka : public Chocolate
{
public:
    Milka();
    ~Milka() {};

    void describe() override {Chocolate::describe();}
    void melt() {cout << "Is melt?: " << IsMelting << endl;}
    ChocolateType GetType() const override {return ChocolateType::Milka; }

};

Milka::Milka() : Chocolate(ChocolateTaste::Dark, ChocolateColorPack::Purple, 70, 75.0)
{
    SetEatingManner(CreateEatingStrategy(EatingMannerEnum::chocBreak));
}



class AlpenGold : public Chocolate
{
public:
    AlpenGold();
    ~AlpenGold(){};

    void describe() override
    {
        Chocolate::describe();
    }
    void melt() {
        IsMelting = true;
        cout << "Is melt?: " << IsMelting << endl;}
    ChocolateType GetType() const override { return ChocolateType::AlpenGold; }
};

AlpenGold::AlpenGold() : Chocolate(ChocolateTaste::White, ChocolateColorPack::Blue, 50, 75.0)
{
    SetEatingManner(CreateEatingStrategy(EatingMannerEnum::chompChunk));
}


class RitterSport : public Chocolate
{
public:
    RitterSport();
    ~RitterSport(){};

    void describe() override
    {
        Chocolate::describe();
    }
    void melt() {cout << "Is melt?: " << IsMelting << endl;}
    ChocolateType GetType() const override { return ChocolateType::RitterSport; }
};

RitterSport::RitterSport() : Chocolate(ChocolateTaste::Milky, ChocolateColorPack::White, 1000, 100.0)
{
    SetEatingManner(CreateEatingStrategy(EatingMannerEnum::meltInMouth));
}




Chocolate *CreateChocolate(ChocolateType type, EatingMannerEnum manner)
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

    if(newChocolate)
    {
        newChocolate->SetEatingManner(CreateEatingStrategy(manner));
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

// Декоратор итератора для выделения шоколодок по типу сьедания

class ChocolateMannerDecorator : public IteratorDecorator<class Chocolate*> {
private:
    EatingMannerEnum TargetManner;

public:
    ChocolateMannerDecorator(Iterator<Chocolate*> *it, EatingMannerEnum manner)
    : IteratorDecorator<Chocolate*>(it), TargetManner(manner) {}

    void First() {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetMannerEnum() != TargetManner) {
            It->Next();
        }
    }

    void Next() {
        do {
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->GetMannerEnum() != TargetManner);
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

// Функция, позволяющая съесть любые шоко, которые таят на языке :)
void EatEmAllMannerMeltInMouth(Iterator<Chocolate*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Chocolate *currentChocolate = it->GetCurrent();
        if(currentChocolate->GetMannerEnum() != EatingMannerEnum::meltInMouth) continue;

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
        int number_eat = rand()%5+1;

        ChocolateType choco_type = static_cast<ChocolateType>(number);
        EatingMannerEnum eat_manner = static_cast<EatingMannerEnum>(number_eat);

        Chocolate *choco1 = CreateChocolate(choco_type, eat_manner);
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

    // Обход всех шоколадок, которые скоро растопят
    cout << endl << "A roundup of all the chocolates that are about to be melted:" << endl;
    Iterator<Chocolate*> *mannerIt = new ChocolateMannerDecorator(chocolateStack.GetIterator(), EatingMannerEnum::meltInMouth);
    EatEmAllMannerMeltInMouth(mannerIt);
    delete mannerIt;

    // демонстрация адаптера

    vector<Chocolate*> chocoVector;
    for(size_t i=0; i<N; i++)
    {
        int choco_num = rand()%3+1;
        int number_eat = rand()%5+1;

        ChocolateType choco_type = static_cast<ChocolateType>(choco_num);
        EatingMannerEnum eat_manner = static_cast<EatingMannerEnum>(number_eat);

        Chocolate *newChocolate = CreateChocolate(choco_type, eat_manner);
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
