#ifndef _HASH_HPP_
#define _HASH_HPP_

#include <stdio.h>
#include <iosfwd>


void print (const int &x);
void print (const double &x);
void print (const size_t &x);
void print (const bool &x);
void print (const char &x);

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
class Hash{
private:
   struct Pair{
   K key;
   V value;
   };
   Pair Label;
   Pair **arr_;
public:

   Hash();
   ~Hash();
   Hash(const Hash &x);
   Hash& operator = (const Hash &x);
   bool operator == (const Hash &x) const;
   int Insert (K const &key,V const &value);
   V* get(K const &key);
   int Remove (K const& key);
   size_t CardinalHash() const;
   size_t Conflict() const;
   template <typename K_, typename V_,size_t N_, size_t (*H_)(const K_&)>
   friend std::ostream& operator << (std:: ostream &out, const Hash<K_,V_,N_,H_> &x);

};


template <typename K, typename V,size_t N, size_t (*H)(const K&)>
Hash<K,V,N,H>::Hash()
{
    arr_ = new Pair*[N];
    for (size_t i = 0; i < N; i++)
        arr_[i] = 0;
}
template <typename K, typename V,size_t N, size_t (*H)(const K&)>
Hash<K,V,N,H>::~Hash()
{
    for (size_t i = 0; i<N; i++)
        if (arr_[i] != 0 )
            delete arr_[i];
    if (arr_ != 0)
        delete []arr_;
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
Hash<K,V,N,H>::Hash(const Hash &x)
{
    arr_ = new Pair*[N];
    Label = x.Label;
    for (size_t i = 0; i < N;i++)
    {
        if (x.arr_[i] == 0)
            arr_[i] = 0;
         else
         {
            arr_[i] = new Pair;
            *arr_[i]= *x.arr_[i];
         }
    }
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
Hash<K,V,N,H>& Hash<K,V,N,H>::operator = (const Hash<K,V,N,H> &x)
{
    Label = x.Label;
    arr_ = new Pair*[N];
    for (size_t i = 0; i<N; i++)
    {
        if (x.arr_[i] == 0)
            arr_[i] = 0;
        else
            arr_[i] = new Pair;
            *arr_[i] = *x.arr_[i];
    }
}
template <typename K, typename V,size_t N, size_t (*H)(const K&)>
bool Hash<K,V,N,H>::operator == (const Hash &x) const
{
    for (size_t i = 0;i<N;i++)
    {

        if (arr_[i] == &Label)
        {
        if (x.arr_[i] != &x.Label)
            return false;
        else continue;
        }

        if (x.arr_[i] == &x.Label)
        {
        if (arr_[i] != &Label)
            return false;
        else continue;
        }

        if(arr_[i] == 0)
        {
            if (x.arr_[i] != 0)
                return false;
            continue;
        }

        if(x.arr_[i] == 0)
        {
            if (arr_[i] != 0)
                return false;
            continue;
        }


        if (arr_[i]-> key != x.arr_[i] -> key)
            return false;
        if (arr_[i]-> value != x.arr_[i] -> value)
            return false;
    }
    return true;
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
int Hash<K,V,N,H>::Insert (K const &key,V const &value)
{

    if (CardinalHash() == N)
    {
        printf( "Error. HashTable max\n\n");
        throw (1);
        return -1;
    }
    Pair* Q = new Pair;

    Q->key = key;
    Q->value = value;
    size_t current = H(key);
    while (arr_[current] != 0 && arr_[current] != &Label)
    {
        if ((arr_[current] -> key == key) && (arr_[current] -> value == value))
            return -1;
        current = (current + 1)%N;
    }
    arr_[current] = Q;
    return 0;
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
V* Hash<K,V,N,H>::get(K const &key)
{

    size_t current = H(key);
    size_t i = 0;
    while ((arr_[current] != 0) && i<N)
    {
        i++;
        if (arr_[current]->key == key)
        {
            return &(arr_[current]->value);
        }
        current = (current + 1)%N;
    }
    return (V*)0;
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
int Hash<K,V,N,H>::Remove (K const &key)
{
    size_t current = H(key);
    if(arr_[current] == 0)
        return -1;
    size_t i = 0;
    while (!(arr_[current] ->key == key) && arr_[(current+1)%N] != 0 && i<N)
    {
        current = (current+1)%N;
        i++;
    }

    if (arr_[current]->key == key)
    {
        if (arr_[(current+1)%N] == 0)
        {
            delete arr_[current];
            arr_[current] = 0;
            return 0;
        }
        delete arr_[current];
        arr_[current] = &Label;
        return 0;
    }
    else
        return -1;
}
template <typename K, typename V,size_t N, size_t (*H)(const K&)>
size_t Hash<K,V,N,H>::Conflict() const
{
    size_t j = 0;
    for (size_t i = 0; i<N;i++)
    {
       if (arr_[i] == 0)
          continue;
       if (H(arr_[i]->key) != i)
          j++;
    }
return j;
}

template <typename K, typename V,size_t N, size_t (*H)(const K&)>
size_t Hash<K,V,N,H>::CardinalHash() const
{
    size_t cardinal = 0;
    for (size_t i = 0; i<N;i++)
        if (arr_[i] != 0 && arr_[i] != &Label)
            cardinal++;
        return cardinal;
}


template <typename K, typename V,size_t N, size_t (*H)(const K&)>
std::ostream& operator << (std:: ostream &out, const Hash<K,V,N,H> &x)
{
    for(size_t i = 0;i < N;i++)
    {
        if (x.arr_[i] == 0 || x.arr_[i] == &x.Label)
            printf ("(NULL) ");
        else
        {
            printf("(");
            print(x.arr_[i]->key);
            printf(" ,");
            print(x.arr_[i] -> value);
            printf(") ");

        }
    }
    return out;
}


void print (const int &x)
{
    printf("%d",x);
}

void print (const double &x)
{
    printf("%f",x);
}

void print (const size_t &x)
{
    printf("%lu",x);
}

void print (const char &x)
{
    printf("%c",x);
}

void print (const bool &x)
{
    printf("%d",x);
}

#endif
