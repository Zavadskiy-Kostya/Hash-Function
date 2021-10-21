#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <stdio.h>
#include <iosfwd>

class String
{
    public :
    const char *strin;
    size_t len;
    bool operator == (const String &x);
    String();
    ~String();
    String(const char* str, const size_t &i);
    String &operator = (const String &x);
    friend std::ostream& operator << (std::ostream &out, const String &x);

};

void print (const String &x);

String::String()
{
    len = 0;
    strin = 0;
}

String::~String()
{
    if (strin != 0)
    delete []strin;
}

String::String(const char* str, const size_t &i)
{
    len = i;
    strin = str;
}

String &String::operator = (const String &x)
{
    len = x.len;
    char *tmp;
    tmp = new char[len];
    for (size_t i = 0; i< len;i++)
        tmp[i] = x.strin[i];
    if (strin != 0 )
        delete []strin;
    strin = tmp;
        return *this;
}

std::ostream& operator << (std::ostream &out, const String &x)
{
    if (x.len == 0)
    {
        print("Empty");
    }
    for (size_t i = 0; i<x.len;i++)
    {
        print (x.strin[i]);
    }
    return out;
}

bool String::operator == (const String &x)
{
    if (len != x.len)
        return false;
    for (size_t i = 0; i < len;i++)
    {
        if (x.strin[i] != strin[i])
            return false;
    }
    return true;
}

void print (const String &x)
{
    if (x.len == 0)
    {
        printf("Empty");
    }
    for (size_t i = 0; i<x.len;i++)
    {
        printf("%c",x.strin[i]);
    }
}

#endif
