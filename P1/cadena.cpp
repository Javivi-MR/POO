#include "cadena.hpp"

#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iomanip>


Cadena::Cadena(unsigned t, char c)
{
    tam_ = t;
    s_ = new char[t + 1];
    
    for (unsigned i = 0; i < t; i++)
    {
        s_[i] = c;
    }

    s_[t] = '\0';
}

Cadena::Cadena(const Cadena &R)
{
    s_ = new char[R.tam_ + 1];
    tam_ = R.tam_;

    strcpy(s_, R.s_);
}

Cadena::Cadena(const char *R)
{
    tam_ = strlen(R);
    s_ = new char[tam_ + 1];

    strcpy(s_, R);
}

Cadena::Cadena(Cadena&& R) : s_(R.s_), tam_(R.tam_)
{
    R.s_ = nullptr;
    R.tam_ = 0;
}

Cadena &Cadena::operator=(const Cadena& R)
{
    if (this != &R)
    {
        if (tam_ != R.tam_)
        {
            delete[] s_;
            tam_ = R.tam_;

            s_ = new char[R.tam_ + 1];
        }
        strcpy(s_, R.s_);
    }
    return *this;
}

Cadena &Cadena::operator=(const char* R)
{
    if (tam_ != strlen(R))
    {
        delete[] s_;
        tam_ = strlen(R);

        s_ = new char[tam_ + 1];
    }
    strcpy(s_, R);
    return *this;
}

//anadido P1
Cadena &Cadena::operator=(Cadena&& R)
{
    if (this != &R)
    {
        delete[] s_;
        tam_ = R.tam_;
        s_ = R.s_;
        R.tam_ = 0;
        R.s_ = nullptr;
    }

    return *this;
}

char Cadena::at(unsigned i) const
{
    if (i < 0 || i >= tam_)
    {
        throw std::out_of_range("ERROR: indice fuera de rango");
    }

    return s_[i];
}

char &Cadena::at(unsigned i)
{
    if (i < 0 || i > tam_)
    {
        throw std::out_of_range("ERROR: indice fuera de rango");
    }

    return s_[i];
}

char Cadena::operator[](int i) const
{
    return s_[i];
}

char &Cadena::operator[](int i)
{
    return s_[i];
}

//Cadena::operator const char *() const         Eliminado P0!
//{
//    return s_;
//}

//anadido P1
const char *Cadena::c_str() const
{
    return s_;
}

unsigned Cadena::length() const
{
    return tam_;
}

Cadena Cadena::substr(unsigned i, unsigned t) const
{
    
    if (i + t > tam_)
    {
        throw std::out_of_range("Fuera de rango");
    }
    else
    {
        Cadena cade{t};

        for (size_t j = 0; j < t; j++)
        {
            cade[j] = s_[j + i];
        }   

        return cade;
    }  
}

Cadena &Cadena::operator+=(const Cadena& R)
{
    unsigned tam = this->tam_ + R.tam_;
    Cadena cade{tam};
    strcpy(cade.s_, this->s_);
    strcat(cade.s_, R.s_);
    *this = cade;
    return *this;
}

Cadena operator+(const Cadena& R1, const Cadena& R2)
{
    unsigned tam = R1.tam_ + R2.tam_;
    Cadena cade{tam};
    strcpy(cade.s_, R1.s_);
    strcat(cade.s_, R2.s_);
    return cade;
}

bool operator==(const Cadena& R1, const Cadena&R2)
{
    if (strcmp(R1.c_str(), R2.c_str()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(const Cadena& R1, const Cadena& R2)
{
    return !(R1 == R2);
}

bool operator>(const Cadena& R1, const Cadena& R2)
{
    if (strcmp(R1.c_str(), R2.c_str()) > 0)
        return true;
    else
        return false;
}

bool operator<(const Cadena& R1, const Cadena& R2)
{
    return !((R1 > R2) || (R1 == R2));
}

bool operator<=(const Cadena& R1, const Cadena& R2)
{
    return (R1 < R2 || R1 == R2);
}

bool operator>=(const Cadena& R1, const Cadena& R2)
{
    return (R1 > R2 || R1 == R2);
}

//anadido P1

std::istream &operator>>(std::istream& is, Cadena& R)
{
    char str[33];
    str[0] = '\0';
    is >> std::setw(sizeof(str))>>str;
    Cadena cade{str};
    R = std::move(cade);
    return is;
}

//anadido P1

std::ostream &operator<<(std::ostream& os, const Cadena& R)
{
    os << R.c_str();
    return os;
}

//anadido P1

Cadena::iterator Cadena::begin()
{
    return s_;
}

Cadena::iterator Cadena::end()
{
    return s_ + length();
}

Cadena::const_iterator Cadena::begin() const
{
    return cbegin();
}

Cadena::const_iterator Cadena::end() const
{
    return cend();
}

Cadena::const_iterator Cadena::cbegin() const
{
    return s_;
}

Cadena::const_iterator Cadena::cend() const
{
    return s_ + length();
}

Cadena::reverse_iterator Cadena::rbegin()
{
    return reverse_iterator(end());
}

Cadena::reverse_iterator Cadena::rend()
{
    return reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::rbegin() const
{
    return crbegin();
}

Cadena::const_reverse_iterator Cadena::rend() const
{
    return crend();
}

Cadena::const_reverse_iterator Cadena::crbegin() const
{
    return const_reverse_iterator(cend());
}

Cadena::const_reverse_iterator Cadena::crend() const
{
    return const_reverse_iterator(cbegin());
}
