
#include <iostream>
using namespace std;

class House{


public:
    House(int siz, char boar='X', char fil='*');
    int GetSize();
    int Perimeter();
    double Area();
    void Grow();
    void Shrink();
    void SetBorder(char boar);
    void SetFill(char fill);
    void Draw();
    void Summary();


private:
    int size;
    char boarder;
    char inside;

};

