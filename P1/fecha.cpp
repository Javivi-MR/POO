#include "fecha.hpp"
#include <iostream>
#include <ctime>
#include <cstring>
#include <locale>
#include <exception>

using namespace std;

time_t now = time(nullptr);
tm *dt = localtime(&now);

void Fecha::EstablecerAnno(unsigned anno)
{
    if (anno == 0)
    {
        a = dt->tm_year + 1900;
    }
    else
    {
        if (anno < Fecha::AnnoMinimo || anno > Fecha::AnnoMaximo)
        {
            throw Invalida("ERROR: anno mayor o menor al establecido");
        }
        else
        { 
            if (anno < 0)
            {
                throw Invalida("anno no valido");
            }
            else
            {
                a = anno;
            }
        }
    }
}

void Fecha::EstablecerMes(unsigned mes)
{
    if (mes == 0)
    {
        m = dt->tm_mon + 1;
    }
    else
    {
        if (mes < 0 || mes > 12)
        {
            throw Invalida("ERROR: El mes debe estar comprendido entre 1 y 12");
        }
        else
        {
            m = mes;
        }
    }
}

void Fecha::EstablecerDia(unsigned dia, unsigned mes, unsigned anno)
{
    if(dia == 0)
    {
        d = dt->tm_mday;
    }
    else
    {
        if(dia > 31 && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) // meses 31
        {
            throw Invalida("ERROR: el mes debe tener de 1 a 31 dias");
        }
        else{
            if(dia > 30 && (mes == 4 || mes == 6 || mes ==9  || mes == 11)) // meses 30
            {
                throw Invalida("ERROR: el mes debe tener de 1 a 30 dias");
            }
            else
            {
                if(mes == 2)
                {
                    if(dia > 28 && (anno % 4 != 0 && (anno % 400 == 0 || anno % 100 != 0)))
                    {
                        throw Invalida("ERROR: el mes debe tener de 1 a 28 dias"); // no es bisiesto
                    }
                    else
                    {
                        if(dia > 29)
                        {
                            throw Invalida("ERROR: el mes debe tener de 1 a 29 dias"); // es bisiesto
                        }
                    }
                }
                
            }
        }
		d = dia;    
	}
}


Fecha::Fecha(unsigned dia, unsigned mes, unsigned anno) //constr 3 par.
{
    EstablecerAnno(anno);
    EstablecerMes(mes);
    EstablecerDia(dia,mes,anno);
}

Fecha::Fecha(const char *F)
{
    int dia = 0;
    int mes = 0;
    int anno = 0;
    int comprobar = std::sscanf(F, "%d/%d/%d", &dia, &mes, &anno);

    if (comprobar != 3)
    {
        throw Invalida("Formato de fecha incorrecta debe ser DD/MM/AAAA");
    }
    else
    {
        EstablecerAnno(anno);
        EstablecerMes(mes);
        EstablecerDia(dia, mes, anno);
    }
}

//Fecha::Fecha(const Fecha &f) : d(f.d), m(f.m), a(f.a) {}

//Fecha &Fecha::operator=(const Fecha& f) //constr de asignacion
//{
//    d = f.d;
//    m = f.m;
//    a = f.a;
//    return *this;
//}


//observadores
int Fecha::dia() const //observar dia
{
    return d;
}

int Fecha::mes() const //observar mes
{
    return m;
}

int Fecha::anno() const //observar anno
{
    return a;
}

const char *Fecha::cadena() const //expl conversion (cadena P1)
{
    locale::global(locale("es_ES.UTF-8"));
    // setlocale(LC_TIME,"spanish");
    tm *f = localtime(&now);
    f->tm_mday = d;
    f->tm_mon = m - 1;
    f->tm_year = a - 1900;
    static char buffer[80];
    mktime(f);
    strftime(buffer, 80, "%A %d de %B de %Y", f);
    return buffer;
}

//operadores
Fecha operator+(const Fecha f, int n)
{
    Fecha aux = f;
    return aux += n;
}

Fecha operator-(const Fecha &f, int n)
{
    Fecha aux = f;
    return aux += -n;
}

Fecha& operator++(Fecha &f)
{
    return f += 1;
}

Fecha operator++(Fecha &f, int n)
{
    Fecha aux = f;
    f += 1;
    return aux;
}

Fecha& operator--(Fecha &f)
{
    return f += -1;
}

Fecha operator--(Fecha &f, int n)
{
    Fecha aux = f;
    f += -1;
    return aux;
}

Fecha& operator+=(Fecha &f, int n)
{
    tm *fecha_n = localtime(&now);
    fecha_n->tm_mday = f.d + n;
    fecha_n->tm_mon = f.m - 1;
    fecha_n->tm_year = f.a - 1900;

    mktime(fecha_n);
    f.d = fecha_n->tm_mday;
    f.m = fecha_n->tm_mon + 1;

    f.EstablecerAnno(fecha_n->tm_year + 1900);

    return f;
}

Fecha& operator-=(Fecha &f, int n)
{
    return f += -n;
}

//logicos
bool operator==(const Fecha &f1, const Fecha &f2)
{
    return (f1.d == f2.d && f1.m == f2.m && f1.a == f2.a);
}

bool operator!=(const Fecha &f1, const Fecha &f2)
{
    return !(f1 == f2);
}

bool operator<(const Fecha &f1, const Fecha &f2)
{
    if (f1.anno() < f2.anno())
    {
        return true;
    }
    else
    {
        if (f1.anno() == f2.anno())
        {
            if (f1.mes() < f2.mes())
                return true;
            else {
                if (f1.mes() == f2.mes())
                {
                    if(f1.dia() < f2.dia())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool operator> (const Fecha &f1, const Fecha &f2)
{
    return !((f1 <= f2));
}

bool operator<= (const Fecha &f1, const Fecha &f2)
{
    return ((f1 == f2) || (f1 < f2));
}

bool operator>= (const Fecha &f1, const Fecha &f2)
{
    return ((f1 == f2) || (f1 > f2));
}

std::istream &operator>> (std::istream& is, Fecha& f)
{
    char cadena[20];
    is >> cadena;
    if (strlen(cadena) > 10)
    {
        is.setstate(ios::failbit);
        throw Fecha::Invalida("Desbordamiento en la extraccion");
    }
    
    try
    {
        Fecha cad{cadena};
        f = cad;
    }
    catch (const Fecha::Invalida &e)
    {
        is.setstate(ios::failbit);
        throw Fecha::Invalida("Entrada Invalida");
    }
    return is;
}

ostream &operator<< (ostream &os, const Fecha &f)
{

    os << f.cadena();

    return os;
}
