#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// PRZEDMIOT
class Item
{
public:
    int id;
    string name;
    double weight;
    double price;
    double price2WeightRatio;

    Item();
    ~Item();
    Item randomLoad(int id);
};

Item::Item()
    : id(0)
    , name("Unknown")
    , weight(-1)
    , price(0)
    , price2WeightRatio(0)
{
    ;
}

Item::~Item()
{
    ;
}

Item Item::randomLoad(int id)
{
    Item item;

    item.id=id;
    item.weight=(rand()%9)+1;
    item.price=(rand()%50)+1;
    item.price2WeightRatio=item.price/item.weight;

    return item;
}


// PLECAK
class BackPack: private Item
{
    int sizeBackPack;
    int valueBackPack;
    vector <Item> items;
public:
    BackPack();
    ~BackPack();
    BackPack loadBackPack(int maxSizeBackPack, int maxItems);
    void algorithmGGK();
    void show();

};

BackPack::BackPack()
    : sizeBackPack(0)
    , valueBackPack(0)
{
    ;
}

BackPack::~BackPack()
{
    ;
}

BackPack BackPack::loadBackPack(int maxSizeBackPack, int maxItems)
{
    BackPack backPack;
    backPack.sizeBackPack=maxSizeBackPack;
    Item item;

    for(int i=0; i<maxItems; i++)
    {
        item=item.randomLoad(i);
        backPack.items.push_back(item);
    }

    return backPack;
}

//references
//http://www.cplusplus.com/articles/NhA0RXSz/
bool toDownByRatio(const Item &a, const Item &b )
{
    return a.price2WeightRatio > b.price2WeightRatio;
}

void BackPack::algorithmGGK()
{
    valueBackPack=0;
    int capacity=sizeBackPack;

    sort(items.begin(),items.end(), toDownByRatio);
    for(int i=0; i<items.size(); i++)
    {
        if(items[i].weight<capacity)
        {
            valueBackPack+=items[i].price;
            capacity-=items[i].weight;
        }
        else
        {
            items.erase(items.begin()+i);
            i--;
        }
    }
}

void BackPack::show()
{

    cout<<"Zawartosc plecaka: "<<endl;

    for(int i=0; i<items.size(); i++)
    {
        cout<<items[i].id;
        cout<<". "<<"Nazwa: "<<items[i].name;
        cout<<", Waga: ";
        cout.width(1);
        cout<<items[i].weight;
        cout<<", Cena: ";
        cout.width(2);
        cout<<items[i].price;
        cout<<", Stosunek: ";
        cout.width(6);
        cout<<fixed<<setprecision(3)<<items[i].price2WeightRatio<<endl;
        cout<<setprecision(0);
    }

    if(valueBackPack!=0)
        cout<<endl<<"Wartosc plecaka: "<<valueBackPack<<endl;
}

int main()
{
    // IN
    int maxSizeBackPack=10;
    int maxItems=10;

    cout<<"Ilosc mozliwych przedmiotow:"<<maxItems<<endl;
    cout<<"Maksymalna pojemnosc plecaka:"<<maxSizeBackPack<<endl<<endl;

    //OUT
    srand(time(NULL));

    BackPack backPack;
    backPack=backPack.loadBackPack(maxSizeBackPack, maxItems);

    cout<<"Dostepne przedmioty. ";
    backPack.show();

    cout<<endl<<"Wynik algorytmu. ";
    backPack.algorithmGGK();
    backPack.show();

    return 0;
}
