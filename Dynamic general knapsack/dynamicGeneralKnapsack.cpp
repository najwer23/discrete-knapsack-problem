#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

// PRZEDMIOT
class Item
{
public:
    int id;
    string name;
    int weight;
    int price;
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
    item.weight=(rand()%8)+1;
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
    void dynamicAlgorithmGGK();
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

void showMatrix(int Y, int X, int **matrix)
{
    for(int i=0; i<Y; i++)
    {
        for(int j=0; j<X; j++)
        {
            cout.width(3);
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

// mozna ja bardziej podzielic
void BackPack::dynamicAlgorithmGGK()
{
    valueBackPack=0;
    int capacity=sizeBackPack+1;

    // INICJALIZACJA TABLIC
    int sizeItems=items.size()+1;
    int **matrixPrice=new int*[sizeItems];

    for (int i = 0; i <sizeItems; i++) // Y
        matrixPrice[i] = new int [capacity]; // X

    for(int i=0; i<sizeItems; i++)
        for(int j=0; j<capacity; j++)
            matrixPrice[i][j]=0;

    //ALGORYTM
    int w;
    int p;
    int oldPrice;
    int newPrice;

    for(int i=1; i<sizeItems; i++)
    {
        w=items[i-1].weight;
        p=items[i-1].price;
        for(int j=1; j<=capacity; j++)
        {
            oldPrice=matrixPrice[i-1][j];

            if(w>j)
                matrixPrice[i][j]=oldPrice;
            else
            {
                newPrice=matrixPrice[i-1][j-w]+p;
                if(newPrice>=oldPrice)
                    matrixPrice[i][j]=newPrice;
                else
                    matrixPrice[i][j]=oldPrice;
            }
        }
    }

    cout<<endl<<"Algorytm. Maicierz Przedmiotow: "<<endl;
    showMatrix(sizeItems, capacity, matrixPrice);

    // KTORE PRZEDMIOTY SA W PLECAKU
    int i=sizeItems-1;
    int line=capacity-1;
    vector <Item> copyItems;
    while(i>0)
    {
        if(matrixPrice[i][line]-matrixPrice[i-1][line-items[i-1].weight]==items[i-1].price)
        {
            //cout<<"I: "<<i-1<<endl;
            line-=items[i-1].weight;
            copyItems.push_back(items[i-1]);
            i--;
        }
        else
            i--;
    }

    valueBackPack=matrixPrice[sizeItems-1][capacity-1];
    items.clear();
    items=copyItems;

    delete [] matrixPrice;
}

void BackPack::show()
{
    for(int i=0; i<items.size(); i++)
    {
        cout.width(2);
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
    int maxItems=15;

    cout<<"Ilosc mozliwych przedmiotow:"<<maxItems<<endl;
    cout<<"Maksymalna pojemnosc plecaka:"<<maxSizeBackPack<<endl;

    //OUT
    srand(time(NULL));

    BackPack backPack;
    backPack=backPack.loadBackPack(maxSizeBackPack, maxItems);
    cout<<endl<<"Dostepne przedmioty"<<endl;
    backPack.show();

    backPack.dynamicAlgorithmGGK();

    cout<<endl<<"Zawartosc plecaka: "<<endl;
    backPack.show();

    return 0;
}
