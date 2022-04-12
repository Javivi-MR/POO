#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>

class Fecha
{
    public:

        //Constructores
        explicit Fecha(unsigned dia = 0, unsigned mes = 0, unsigned anno = 0); //constr. 1/2/3 par.
        Fecha(const char* cad); //constr. cad
        Fecha(const Fecha& f) = default;
        //Fecha& operator=(const Fecha& f);//asignacion

        
        
        class Invalida
    	{
        	public:
        		Invalida(const char* str):Error(str){}
        		const char* por_que() const;
        	private:
        		const char* Error;
		};
    	
        
        //constantes minimo y maximo
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;

        //observadores
        int dia() const;
        int mes() const;
        int anno() const;

    	friend Fecha& operator+= (Fecha&, int n);
    	friend bool operator== (const Fecha& F, const Fecha& G);

        //eliminado a causa de P1
        //operator const char*() const;

        const char* cadena() const; //expl conversion (cadena P1)

    //Parte privada
    private:
        void EstablecerDia(unsigned,unsigned,unsigned);
        void EstablecerMes(unsigned);
        void EstablecerAnno(unsigned);
        unsigned d;
        unsigned m;
        unsigned a;
};

//suma
Fecha operator+(const Fecha , int n);
//resta
Fecha operator-(const Fecha&, int n);
//post-pre incremento
Fecha& operator++(Fecha&);
Fecha operator++ (Fecha&, int n);
//post-pre incremento
Fecha& operator-- (Fecha&);
Fecha operator-- (Fecha&, int n);
//entero con asignacion
Fecha& operator+= (Fecha&, int n);
Fecha& operator-= (Fecha&, int n);
//operadores logicos
//igual o distinto
bool operator== (const Fecha& f1,const Fecha& f2);
bool operator!= (const Fecha& f1, const Fecha& f2);
//mayores menores (iguales o no)
bool operator< (const Fecha& f1,const Fecha& f2);
bool operator> (const Fecha& f1,const Fecha& f2);
bool operator<= (const Fecha& f1,const Fecha& f2);
bool operator>= (const Fecha& f1,const Fecha& f2);


//AÑADIDO
std::istream& operator>> (std::istream& is, Fecha& f);
std::ostream& operator<< (std::ostream& os,const Fecha& f);

inline const char* Fecha::Invalida::por_que() const
{
    return Error;
}

#endif
