#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <iterator>

class Cadena{
    public:
        //constructores
        explicit Cadena(unsigned t = 0, char c = ' '); // cosntructor 2/1/0 par.
        Cadena(const Cadena& R); // constructor copia a otra cadena (objeto).
        Cadena(const char* R); // constructor a partir de una cadena.
        Cadena(Cadena&& R);//constructor copia 
        //constructores (asignacion)
        Cadena& operator= (const Cadena& R); // constructor asignacion a otra cadena (objeto)
        Cadena& operator= (const char* R); // constructor asignacion a otra cadena.
        Cadena& operator= (Cadena&& R);  // asignacion movimiento

        char at (unsigned i) const; //consultar indice
        char& at (unsigned i); // consultar indice
        char operator[](int i) const; // consultar indice
        char& operator[](int i); // consultar indice
        
        //operator const char*() const; //P0 (sustituido por c_str)
        const char* c_str() const; // transf a cadena standar (P1)
        unsigned length() const;  // operacion observadora
        Cadena substr(unsigned i,unsigned t) const; //devuelve cadena reformada
    
        //operadores
        Cadena& operator+=(const Cadena& R); //suma con asignacion
        friend Cadena operator+(const Cadena& R1,const Cadena& R2); // posibilita a la creacion de cadena a partir de una suma de cadenas 

        //iteradores
        //tipos
        typedef char* iterator ;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator; 
        //funciones
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        ~Cadena()               //destructor (liberacion de memoria reservada)
        {
            delete[] s_;
        }

    private:
        char* s_;
        unsigned tam_;
};

//operadores
Cadena operator+(const Cadena& R1, const Cadena& R2); // suma de dos cadenas
// operadores logicos 
bool operator== (const Cadena& R1, const Cadena& R2); // igualdad
bool operator!= (const Cadena& R1, const Cadena& R2); // distinto
bool operator> (const Cadena& R1, const Cadena& R2);// mayor 
bool operator< (const Cadena& R1, const Cadena& R2);// menor
bool operator>= (const Cadena& R1, const Cadena& R2);// mayor igual
bool operator<= (const Cadena& R1, const Cadena& R2);// menor igual
//flujo
std::istream& operator >>(std::istream& is, Cadena& R); 
std::ostream& operator <<(std::ostream& os, const Cadena& R);

#endif
