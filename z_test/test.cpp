#include <iostream>
#include <string.h>
using namespace std;

class mystring 
{
private:
    char* buf;
public:
    mystring()
    {
        buf=new char[1];
        *buf='\0';
        cout<<"construct 0"<<endl;
    }
    mystring(char* ch)    
    {
        int l=strlen(ch);
        buf=new char[l];
        strcpy(buf, ch);  
        cout<<"construct 1"<<endl;
    }    
    ~mystring()
    {
        delete[] buf;
        cout<<"destruct"<<endl;
    }
    mystring& operator=(const mystring& ms)
    {
        delete[] buf;
        buf=new char[strlen(ms.buf)+3];
        buf[0]='\0';
        strcpy(buf,"c++");
        strcpy(buf,ms.buf);
        return *this; 
    }
    friend ostream& operator<<(ostream& cout, const mystring& ms);
};

ostream& operator<<(ostream& cout, const mystring &ms)
{
    cout<<ms.buf;
}

int main()
{
    char ch[999];
    cin>>ch;
    
    mystring str1(ch);
    mystring str2;
    str2=str1;
    cout<<str1<<endl;
    cout<<str2<<endl;
 }