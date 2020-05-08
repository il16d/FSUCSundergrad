#include <iostream>
#include "mystring.h"

using namespace std;

MyString::MyString()
{
    size=1;
    array = new char [size];
    array[0]='\0'; //null character of the array
}

MyString::MyString(const char *cstring)
{

    int counter = 0;

    for(int i = 0; cstring[i] != '\0'; i++)
        counter++;

    size= counter+1;



    array= new char [size];

    int i;
    for(i=0; i<size; i++)
        array[i]=cstring[i];

    array[i]='\0';



}
MyString::MyString(int digits)
{
    size=0;
    int newnumber= digits;

    while(digits)
    {
        digits/=10;
         size++;
        }

    digits=newnumber;
    array=new char[size];
    for(int i=size-1; i>-1;i--)
    {
        array[i]=(digits%10)+'0';
        digits/=10;
    }

}

MyString::~MyString()
{
    delete [] array;
}

MyString::MyString(const MyString& copy) {

    size = copy.size;
    array = new char[size];
    for (int i = 0; i <size; i++) {
        array[i] = copy.array[i];
    }

}

int MyString::getLength() const
{


    return size;
}

const char* MyString::getCString() const
{
    return array;
}
MyString& MyString::insert(unsigned int index, const MyString &st)
{

    char *array1 = new char[index];
    char *array2= new char[size-index];

    for(int i=0; i<index; i++)
    {
        array1[i]=array[i];
    }
    for(int i=index; i<size; i++)
    {
        array2[i-index]=array[i];
    }
    delete [] array;
    size+=st.size;
    array=new char [size];
    for(int i=0; i<index; i++)
    {
        array[i]=array1[i];
    }
    for(int i=0; i<st.size; i++)
    {
        array[i+index]=st.array[i];
    }

int hold= size-st.size-index;
    for(int i=0; i<hold; i++) {
        int hold2=i+index+st.size;
        array[hold2] = array2[i];

    }
    delete[] array1;
    delete[]array2;

}

MyString& MyString:: operator=(const MyString& st)
{

    if(*this != st)
    {
        delete [] array;
        size = st.size;
        array=new char [size];

        for(int i = 0; i < size; i++)
        {
            array[i] = st.array[i];
        }
        array[size - 1] = '\0';
    }
    return *this;

}
ostream& operator<< (ostream& out, const MyString& st)
{
    for(int i = 0; st.array[i]!= '\0'; i++)
        out << st.array[i];

    return out;
}


istream& operator>>(istream& in, MyString& st)
{

    delete [] st.array;
    int length = 1;
    char * newarray = new char[length];

    int index;

    while (in.peek()==' ') {
        in.ignore();
    }
    index = 0;

    while(in.peek()!=' ') {

        in >> newarray[index];
        length++;
        index++;
    }
    length++;
    index++;
    newarray[index] = '\0';
    st.array = newarray;
    return in;
}


istream& getline(istream& in, MyString& st, char delim) {


    delete [] st.array;

    int index = 0;
    int length = 1;
    char *newarray = new char[length + 1];

    while(in.peek() != delim){
        newarray[index] = in.get();
        index++;
        length++;
    }
    in.ignore();
    index++;
    newarray[index] = '\n';
    st.array = newarray;

    return in;



}



/*istream& getline(istream& in, MyString& st, char delim = '\n') {


    delete [] st.array;

    int index = 0;
    int length = 1;
    char *newarray = new char[length + 1];

    while(in.peek() != delim){
        newarray[index] = in.get();
        index++;
        length++;
    }
    in.ignore();
    index++;
    newarray[index] = '\n';
    st.array = newarray;

    return in;



}
 */



MyString operator+(const MyString& left, const MyString& right)
{

MyString add;

    add.size = (left.size + right.size - 1);

    add.array = new char[add.size];

    int i;
    for(i = 0; left.array[i] != '\0'; i++)
        add.array[i] = left.array[i];


    int k, j;
    for(j = i, k = 0; j < add.size; k++, j++)
        add.array[j] = right.array[k];

    add.array[j] = right.array[k];

    return add;
}


MyString& MyString::operator+=(const MyString &st)
{
    int newsize= (st.size+size)-1;
    char *newdata=new char[newsize];
    int i;
    for(i=0; array[i]!='\0'; i++)
    {
        newdata[i]=array[i];
    }
    int index;
    for(int j=i, index=0; j<size; index++, j++)
    {

    newdata[j]=st.array[index];

    }

    delete[]array;
    array=newdata;

    return *this;
}

const char& MyString:: operator[](unsigned int ind)const
{
    if(ind<size) {

        return array[ind];
    } else
        return array[size-1];

}

char& MyString::operator[](unsigned int ind)
{

    if(ind<size)
        return array[ind];

    else
    {
     int newsize=size;
        char *newarray=new char[newsize];
        for(int i=0; i<size-1; i++)
        {
            newarray[i]=array[i];

        delete[]array;
        size=ind+1;
        array=new char[size];
        }

        for(int i=0; i<newsize; i++)
        {
            array[i]=newarray[i];
        }
      
        delete []newarray;
        return array[ind];
    }

}int MyString::indexOf(const MyString &st) const
{
    int impossible=-1;
    int index=0;
    if(st.size>size)
        return impossible;
    for(int i=0; i<size; i++)
    {
       int possible=0;
        if(array[i]==st.array[i])
        {
         index=i;
        }
        while(array[i]==st.array[possible] && possible<st.size)
        {
            i++;
            possible++;
            if(possible==st.size)
                return i;
        }
    }
    return impossible;

}

MyString MyString::substring(unsigned int ind) const
{
    MyString substring;
    substring.size=size-ind;
    delete[] substring.array;
    substring.array=new char[substring.size];
    for(int i=0; i<substring.size; i++)
    {
        substring.array[i]=array[i+ind];
    }
    return substring;
}

MyString MyString::substring(unsigned int ind, unsigned int siz) const
{
    MyString substring;
    substring.size=siz;
    delete[]substring.array;
    substring.array = new char[substring.size];
    int tempsize=siz;
    if(siz>size-ind)
    {
        tempsize= size-ind;
    }
    for(int i=0; i<tempsize; i++)
    {
        substring.array[i]=array[i+ind];
    }

    return substring;

}

 bool operator<(const MyString &st1, const MyString &st2)
{

    int flag=0;
    while (st1.array[flag]==st2.array[flag])
    {
        flag++;
    }
    int lenght= st1.array[flag]- st2.array[flag];
   if (lenght>=0)
       return false;
     else
       return true;

}

bool operator>(const MyString &st1, const MyString &st2)
{

    return !(st1<st2);
}
 bool operator<=(const MyString &st1, const MyString &st2)
{
    if(st1>st2||st1==st2)
        return true;
    else
        return false;
}

bool operator>=(const MyString &st1, const MyString &st2)
{
    return!(st1<=st2);

}
 bool operator==(const MyString &st1, const MyString &st2)
{
    if(st1.size!=st2.size)
    return false;
    for(int i=0; i<st1.size; i++)
     {
        if (st1.array[i]!=st2.array[i])
        {
            return false;
        }
     }
return true;
}
bool operator!=(const MyString &st1, const MyString &st2)
{
return!(st1==st2);

}



