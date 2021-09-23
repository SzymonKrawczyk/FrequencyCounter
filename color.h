//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa color (plik .h)                                   //
//                                                                                      //
//  Klasa sluzy do przechowywania informacji o kolorze (format RGBA)                    //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//   Dostepna funkcjonalnosc:                                                           //
//                                                                                      //
//    (R, G, B, A to unsigned char, A w przedziale 0-100)                               //
//                                                                                      //
//                                                                                      //
//    color.setValue(R, G, B)           // Ustawia trzy pola: R, G, B                   //
//                                                                                      //
//    color.setValue(R, G, B, A)        // Ustawia wszystkie pola, R, G, B, A           //
//                                                                                      //
//                                                                                      //
//    color.setR(unsigned char)         // Ustawia i zwraca pole R, domyslnie 255       //
//                                                                                      //
//    color.setG(unsigned char)         // Ustawia i zwraca pole G, domyslnie 255       //
//                                                                                      //
//    color.setB(unsigned char)         // Ustawia i zwraca pole B, domyslnie 255       //
//                                                                                      //
//    color.setA(unsigned char)         // Ustawia i zwraca pole A, domyslnie 100       //
//                                                                                      //
//                                                                                      //
//    color.getR(unsigned char) const   // Zwraca pole R                                //
//                                                                                      //
//    color.getG(unsigned char) const   // Zwraca pole G                                //
//                                                                                      //
//    color.getB(unsigned char) const   // Zwraca pole B                                //
//                                                                                      //
//    color.getA(unsigned char) const   // Zwraca pole A                                //
//                                                                                      //
//                                                                                      //
//    const color == const color        // Zwraca true, gdy pola obiektow takie same    //
//                                                                                      //
//    const color != const color        // Zwraca !(const color == const color)         //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//  Autor: Szymon Krawczyk                                                              //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
// Changelog:                                                                           //
//  Data        |  Zmiany                                           | Przez kogo        //
// -------------|-------------------------------------------------- |------------------ //
//  06/12/2019  | Utworzenie klasy                                  | Szymon Krawczyk   //
//              |                                                   |                   //
//  14/12/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              |                                                   |                   //
//  28/12/2019  | Dodanie operatora<                                | Szymon Krawczyk   //
//              | Dodanie operatora<<                               |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace KrawczykS {

    class color {

    private: 
        unsigned char _R;
        unsigned char _G;
        unsigned char _B;
        unsigned char _A;

    public:
        color(unsigned char = 255, unsigned char = 255, unsigned char = 255, unsigned char = 100);
        color(const color&);
        virtual ~color();       // Destruktor wirtualny zapewnia wywolanie destruktorow klas pochodnych
                                //  dzieki temu zapobieagmy mozliwym bledom, 
                                //  poniewaz niewywolanie destruktora klasy pochodnej moze prowadzic do np.: wyciekow pamieci

        color& operator=(const color&);

        void setValue(unsigned char, unsigned char, unsigned char);
        void setValue(unsigned char, unsigned char, unsigned char, unsigned char);

        unsigned char setR(unsigned char = 255);
        unsigned char setG(unsigned char = 255);
        unsigned char setB(unsigned char = 255);
        unsigned char setA(unsigned char = 100);

        unsigned char getR() const;
        unsigned char getG() const;
        unsigned char getB() const;
        unsigned char getA() const;

        friend bool operator ==(const color&, const color&);
        friend bool operator !=(const color&, const color&);

        friend bool operator < (const color&, const color&);
        friend std::ostream& operator << (std::ostream&, const color&);

    };
}

#endif