#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cassert>
#include "Hash.hpp"
#include "String.hpp"
#include <cerrno>
#include <iostream>

using namespace std;

#define GoldSection (sqrt(5)-1)/2


int test1();
int test2();
int test3();
int test4();
int test5();
int test6();
int test7();
int test8();
size_t hash1(const size_t &key);
size_t hash2(const int &key);
size_t hash3(const bool &key);
size_t hash4(const String &key);
size_t hash5(const int &key);
size_t hash6(const size_t &key);
size_t hash7(const String &key);
size_t hash8(const String &key);
size_t HashCodeMap1(const String &key);
size_t HashCodeMap2(const String &key);
char* Function1(FILE *fin, size_t *k);
int toInt (const char *s, int *xp);
void erro (const char *s);
typedef int (*func_t) ();


int main (int argc, char *argv[]) {
    int n;
    cout << endl;
    func_t fun[]={ test1, test2, test3, test4, test5, test6,test7,test8};

    if (argc == 1)
    {
        for(size_t i = 0; i<8; i++)
        {
            try
            {
                fun[i]();
            }
            catch (...)
            {
                return -1;
            }

        }
        return 0;
    }
    if (argc != 2 && argc != 1)
    {
        erro(argv[0]);
        return -1;
    }

    if (!toInt(argv[1], &n))
    {
        erro(argv[0]);
        return -1;
    }
    if ((n < 8) && (n > -1) )
    {
        try
        {
            fun[n]();
        }
        catch (...)
        {
            return -1;
        }
        return 0;
    }
    return -1;
}

#include <stdio.h>
void erro (const char *s) {

    fprintf (stderr, "%s <Nomer Testa>\n",s);
    fprintf (stderr, "TEST #1 Constructor copy \n");
    fprintf (stderr, "TEST #2 Operator = \n");
    fprintf (stderr, "TEST #3 operator == \n");
    fprintf (stderr, "TEST #4 Insert, Remove, CardinalHash \n");
    fprintf (stderr, "TEST #5 Counting numbers in a file\n");
    fprintf (stderr, "TEST #6 Number generation\n");
    fprintf (stderr, "TEST #7 White Fang. Word frequency\n");
    fprintf (stderr, "TEST #8 English words\n");

    return;
}
#include <cstdlib>
#include <limits.h>
int toInt (const char *s, int *xp) {
    char *e;
    long l;

    errno = 0;
    l = strtol (s, &e, 10);

    if (!errno && *e == '\0') {
        if (INT_MIN <= l && l <= INT_MAX) {
            *xp = (int) l;
            return 1; // Good
        }
    }

    return 0; // Bad
}


int test1()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #1 Constructor copy" << endl<<endl;
    Hash<size_t,char,5,hash1> m;
    m.Insert(23,'c');
    m.Insert(12,'k');
    m.Insert(2,'e');
    Hash<size_t,char,5,hash1> M(m);
    cout << "Hash<size_t,char,5,hash1> m" << endl << "m.Insert(23,'c')  m.Insert(12,'k')  m.Insert(2,'e')" << endl<< endl;
    cout << "Hash<size_t,char,5,hash1> M(m)" << endl;
    cout << "cout << m" << endl<<endl;
    cout << m;
    cout << endl << endl;
    cout << "cout << M" << endl<< endl;
    cout << M;
    cout << endl <<endl;
    assert (*M.get(23) == 'c');
    assert(*M.get(12) == 'k');
    assert (*M.get(2) == 'e');
    assert (M.get(1) == 0);
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}

size_t hash1(const size_t &key)
{
       return (size_t)key%5;
}

int test2()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #2 Operator =" << endl<<endl;
    Hash<int,bool,5,hash2> m;
    m.Insert(-13,false);
    m.Insert(2,true);
    m.Insert(-4,false);
    Hash<int,bool,5,hash2> M = m;

    cout << "Hash<int,bool,5,hash1> m" << endl << "m.Insert(-13,false)  m.Insert(2,true)  m.Insert(-4,false)" << endl<<endl;
    cout << "Hash<int,bool,5,hash1> M = m" << endl;
    cout << "cout << m" << endl<<endl;
    cout << m;
    cout << endl << endl;
    cout << "cout << M" << endl<< endl;
    cout << M;
    cout << endl<<endl;
    cout << "M = M" << endl;
    cout << "cout << M"<< endl << endl;
    cout << M;
    cout <<endl;
    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}
size_t hash2(const int &key)
{
       return (size_t)key%5;
}

int test3()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #3 operator ==" << endl<<endl;
    Hash <bool, int, 5, hash3> m;
    m.Insert(false,3);
    m.Insert(true,4);
    cout << "Hash <bool, int, 5, hash3> m" << endl;
    cout << "m.Insert(false,3)  m.Insert(true,4)"<< endl<< endl;
    cout << "Hash <bool, double, 5, hash3> M" << endl<< endl;
    cout << "assert (!(M == m))" << endl;
    cout << "assert (m == m)" << endl;
    Hash <bool,int,5,hash3> M;
    assert (!(m == M));
    assert (m == m);
    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}

size_t hash3(const bool &key)
{
    double a;
    return ((size_t)5*(modf(key*GoldSection,&a)));
}

int test5()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #5 Insert, Remove, CardinalHash " << endl<<endl;
    Hash<String,String,5,hash4> m;
    cout << "Hash<String,String,5,hash4> m" << endl << "Insert 1) (Ivanov,Pavel) 2) (Buyalova, Ulyana) 3) (Shipilova,Ksenyia) 4(Cuiko,Alexander)" << endl << endl;
    assert (m.CardinalHash() == 0);
    m.Insert(String ("Ivanov",6),String ("Pavel",5));
    assert(m.CardinalHash()==1);
    m.Insert(String ("Buyalova",8),String ("Ulyana", 6));
    assert(m.CardinalHash()==2);
    m.Insert(String ("Shipilova",9),String ("Ksenyia",7));
    assert(m.CardinalHash()==3);
    m.Insert(String ("Cuiko",5),String ("Alexander",9));
    assert(m.CardinalHash() == 4);
    cout << "cout << m" << endl;
    cout << m;
    cout << endl << endl;
    m.Remove(String("Cuiko",5));
    cout << "Remove (Cuiko)" << endl<< endl;
    cout << "cout << m" << endl;
    assert(m.CardinalHash() == 3);
    cout << m;

    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}

size_t hash4(const String &key)
{
       return (size_t)HashCodeMap2(key)%5;
}

int test4()

{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #4 Counting numbers in a file" << endl<<endl;
    FILE *fin;
    fin = fopen("input1.txt","r");
    if (!fin)
        return -1;
    Hash<int,size_t,5,hash5> m;
    cout << "Hash <int,size_t,5,hash5> m" << endl;
    cout << "m.Insert (8,0) (4,0) (2,0) (3,0) (9,0) " << endl << endl;
    m.Insert(8,0);
    m.Insert(4,0);
    m.Insert(2,0);
    m.Insert(3,0);
    m.Insert(9,0);
    cout << "cout << m" << endl;
    cout << m;
    cout << endl << endl;
    cout << "Calculation ....." << endl << endl;
    cout << "cout << m" << endl;
    int i;
    size_t *j;
    while (fscanf(fin,"%d",&i) == 1)
    {
       j = m.get(i);
       if (j != (size_t*)0)
        *j = *j + 1;
    }
    cout << m;
    fclose(fin);
    cout << endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}

size_t hash5(const int &key)
{
       return (37*key + 79) % 5;
}


int test6()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #6 Number generation" << endl<<endl;
    Hash<size_t,size_t, 5,hash6> m;
    for (size_t i = 0; i<5;i++)
        m.Insert(rand()% 100,0);
    cout << "Hash<size_t,size_t, 5,hash6> m" << endl << "Insert (Rand,0) X 5" << endl<< endl;
    cout << "cout << m" << endl;
    cout << m;
    cout << endl << endl << "Calculation ....." << endl<<endl;
    cout << "cout << m" << endl;
    size_t *j;
    for (size_t i = 0 ;i< 1000000; i++)
    {
        j = m.get(rand()%100);
        if (j!= 0)
            *j = *j + 1;
    }
    cout << m;
    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;

}

size_t hash6(const size_t &key)
{
    return (size_t)key%5;
}

int test7 (){
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #7 White Fang. Word frequency" << endl<<endl;
    FILE *fin;
    fin = fopen("london_white.txt","r");
    if (!fin)
        return -1;
    cout << "Open White Fang" << endl << endl;
    cout << "Hash<String,size_t, 9, hash7> m" << endl << "Insert  the, of,a,was,life, like,god,lalalal " << endl << endl;
    Hash<String,size_t, 9,hash7> m;
    m.Insert(String ("the",3),0);
    m.Insert(String ("of",2),0);
    m.Insert(String ("a",1),0);
    m.Insert(String ("was",3),0);
    m.Insert(String ("life",4),0);
    m.Insert(String ("like",4),0);
    m.Insert(String ("god",3),0);
    m.Insert(String ("lalala",6),0);
    cout << "Calculation ...." << endl << endl;
    char *str;
    size_t *lenstring;
    lenstring = new size_t;
    size_t *val;
    while (!feof(fin))
    {
        str = Function1(fin,lenstring);
        if (str == 0)
            return -1;
        String L(str,*lenstring);
        val = m.get(L);
        if (val != 0)
           *val = *val + 1;

    }
    cout << "cout << m" << endl;
    cout << m;
    cout << endl << endl;
    delete lenstring;
    fclose(fin);
    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;

}

size_t hash7(const String &key)
{
    return (size_t)HashCodeMap1(key)%9;
}

size_t HashCodeMap1(const String &key) // sum
   {
       size_t sum = 0;
       for (size_t j = 0; j<key.len;j++)
         sum = sum + key.strin[j];
       return sum;
   }


int test8()
{
    cout << "____________________________________________________________________________________________________" << endl << endl;
    cout << "TEST #8 English words" << endl<<endl;
    char *str;
    Hash<String,size_t, 10,hash8> m;
    for (size_t i = 0; i<10; i++)
    {
        str = new char[3];
        for(size_t j = 0; j<3;j++)
        {
              str[j] = ((rand()%26) + 97);
        }
        String A(str,3);
        m.Insert(A,0);

    }
    cout << "Hash<String,size_t,10,hash8> m" << endl << "Insert  Rand (str) X 10  (Len = 3)  " << endl << endl;
    cout << "cout << m" << endl << m << endl << endl;
    for (size_t i = 0; i<1000000; i++)
    {
        str = new char[3];
        for(size_t j = 0; j<3;j++)
        {
              str[j] = ((rand()%26) + 97);
        }
        size_t *j;
        String A(str,3);
        j = m.get(A);
        if (j != 0)
        {
            *j = *j + 1;
        }
    }
    cout << "Calculation ......" << endl << endl;

    cout << "cout << m" << endl;
    cout << m;
    cout <<endl;
    cout << "____________________________________________________________________________________________________" << endl << endl;
    return 0;
}

size_t hash8(const String &key)
{
    return (size_t)HashCodeMap1(key)%10;
}

size_t HashCodeMap2(const String &key)
{
    size_t sum = 0;
       for (size_t j = 0; j<key.len;j++)
         sum = sum + key.strin[j]*pow(37,j);
       return sum;

}


char* Function1(FILE *fin, size_t *k)
{
    if (feof(fin))
        return 0;
    char a;
    long Fpos;
    Fpos = ftell(fin);
    while (((a = fgetc(fin)) == ' ' || a == '\n')&& !feof(fin) )
    {
        Fpos = ftell(fin);
    }
    size_t i;

    for (i = 1; a = fgetc(fin), a != ' ' && a !='\n' && !feof(fin);i++ );
        *k = i;
    char *s = new char[i];
    fseek(fin,Fpos,SEEK_SET);
    for (size_t j = 0;j<i;j++)
        s[j] = fgetc(fin);
    if (s[i-1] == ',' || s[i-1] == '.' || s[i-1] == ';' || s[i-1] == ':')
    s[i-1] = ' ';
    return s;
}


/*size_t hash1(const int &key)
   {
       return (size_t)key%20; //n!= 2^x n - prime 5 = N! return (size_t)key%N; N - размер таблицы
   }

   size_t hash2(const String &key)
   {
       return (size_t)HashCodeMap1(key)%20;
   }

   size_t hash3(const size_t &key)
   {
       return (size_t)key%5; //n!= 2^x n - prime 5 = N! return (size_t)key%N; N - размер таблицы
   }

   size_t hash4(const int &key)
   {
       return(size_t)10*modf(key*GoldSection,NULL); //хэширование фибоначи return (size_t)N*(key*GoldSection % 1);
   }

   size_t hash5(const int &key) //Mad
   {
       return (37*key + 79) % 10; //MAD co prime (a,n) (a,n) = 1    (a*key + 79) % N
   }

   size_t HashCodeMap1(const String &key) // sum
   {
       size_t sum = 0;
       for (size_t j = 0; j<key.len;j++)
         sum = sum + key.strin[j];
       return sum;

   }

   size_t HashCodeMap2(const char* str, size_t *i)
   {
       size_t sum = 0;
       for (size_t j = 0; j<*i;j++)
         sum = sum + str[j]*pow(37,j);
       return sum;
   }
*/



