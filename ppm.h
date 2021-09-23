//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa ppm (plik .h)                                     //
//                                                                                      //
//  Klasa pochodna od klasy obraz, definiuje komuniakacje pomiedzy plikami .ppm         //
//  a programem.                                                                        //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//   Dostepna funkcjonalnosc (z klasy bazowej):                                         //
//                                                                                      //
//    (R, G, B, A to unsigned char, A w przedziale 0-100)                               //
//    (W, H, D to kolejno: szerokosc, wysokosc i glebia kolorow [unsigned int])         //
//                                                                                      //
//                                                                                      //
//    ppm.setColor(W, H, color)               // Ustawia kolor na podanej pozycji       //
//                                                                                      //
//    ppm.setColor(W, H, R, G, B, A = 100)    // Ustawia kolor na podanej pozycji       //
//                                                                                      //
//    ppm.getColor(W, H) const                // Pobiera kolor z podanej pozycji        //
//                                                                                      //
//                                                                                      //
//    ppm.setDepth   (D)              // Ustawia i zwraca glebie                        //
//                                                                                      //
//                                                                                      //
//    ppm.getWidth   () const         // Zwraca szerokosc                               //
//                                                                                      //
//    ppm.getHeight  () const         // Zwraca wysokosc                                //
//                                                                                      //
//    ppm.getDepth   () const         // Zwraca glebie                                  //
//                                                                                      //
//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
//                                                                                      //
//  Funkcjonalnosc niepubliczna:                                                        //
//                                                                                      //
//    ppm.deleteColorTab()            // Usuwa obecna tablice kolorow                   //
//                                                                                      //
//    ppm.createEmptyColorTab()       // Tworzy nowa tablice kolorow na podstawie       //
//                                    // obecnych wymiarow                              //
//                                                                                      //
//                                                                                      //
//    ppm.setcolorTab(color**)        // Ustawia nowa tablice kolorow                   //
//                                    // (kopia powierzchowna)                          //
//                                                                                      //
//    ppm.getcolorTab() const         // Pobiera wskaznik na obecna tablice kolorow     //
//                                                                                      //
//                                                                                      //
//    ppm.setWidth   (W)              // Ustawia i zwraca szerokosc                     //
//                                                                                      //
//    ppm.setHeight  (H)              // Ustawia i zwraca wysokosc                      //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//  Dostepna funkcjonalnosc (z tej klasy):                                              //
//                                                                                      //
//    ppm(const char*)              // Tworzy ppm i wywoluje ppm.loadFromFile           //
//                                                                                      //
//    ppm(const obraz&)             // Tworzy ppm na podstawie innego obiektu           //
//                                  // pochodnego od klasy obraz                        //
//                                                                                      //
//    ppm.loadFromFile(const char*) // Odczyt z pliku                                   //
//                                  // Wyrzucenie bledow:                               //
//                                  //                                                  //
//                                  //  myException_BadOpen, gdy nie udalo sie          //
//                                  //  otworzyc pliku                                  //
//                                  //                                                  //
//                                  //  myException_BadFormat, gdy niepoprawny format   //
//                                  //  pliku (Obsluga tylko P3)                        //
//                                                                                      //
//    ppm.saveAs(const char*) const // Zapis do pliku                                   //
//                                  // Wyrzucenie bledow:                               //
//                                  //                                                  //
//                                  //  myException_BadOpen, gdy nie udalo sie          //
//                                  //  otworzyc pliku                                  //
//                                                                                      //
//  Uwaga: do obslugi i zrozumienia wyjatkow myException, nalezy zapoznac sie           //
//  z odpowiednim plikiem [ MyException_base.h ]                                        //
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
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef PPM_H
#define PPM_H
#include "obraz.h"

namespace KrawczykS {

    class ppm : public obraz {

    public:
        ppm();
        ppm(const char*);
        ppm(unsigned int, unsigned int, unsigned int = 255);
        ppm(const ppm&);
        ppm(const obraz&);
        virtual ~ppm();         // Destruktor wirtualny zapewnia wywolanie destruktorow klas pochodnych
                                //  dzieki temu zapobieagmy mozliwym bledom, 
                                //  poniewaz niewywolanie destruktora klasy pochodnej moze prowadzic do np.: wyciekow pamieci

        ppm& operator=(const ppm&);

        virtual void loadFromFile(const char*);
        virtual void saveAs      (const char*) const;
    };
}

#endif