#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include <string>
#include <string.h>

using namespace std;

static int epsilon = 7;

static int randomNumber (int maxNum)
{
   return (rand() % maxNum ) + 1;
}

static void pick_actor()
{
   string actors[6] = {"Grocer1", "Grocer2", "Warehouse1", "Warehouse2", "Market1", "Market2"};
   int num = randomNumber(6);
   cout << actors[num-1] << " ";
}

static void pick_action()
{
   string actions[4] = { "buy", "sell", "deliver", "pick up"  };
   int num = randomNumber(4);
   cout << actions[num-1] << " ";
}

static void pick_acted()
{
   string acted[7] = { "rice", "asparagus", "lettuce", "apples", "oranges", "bread", "celery" };
   int num = randomNumber(7);
   cout << acted[num-1] << " ";
}

static void order()
{
    cout << "ORDER : " ;
    pick_actor();
    pick_action();
    pick_acted();
    cout << endl;
}

static void order_list()
{
   while(1)
   { 
     int num = rand() % 100;
     if( num == epsilon )
     {
       cout << "EPSILON" << endl;
       return; 
     }
     order();
   } 
}

static void orders_of_the_day()
{
   cout << "Orders of the day : " << endl;
   cout << "====================" << endl;
   order_list();
}

int main(int argc, char *argv[] )
{
   orders_of_the_day();
}
