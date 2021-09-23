//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa color (plik .cpp)                                 //
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

#include "color.h"
#include <iostream> // Dla bledow

namespace KrawczykS {

    // Funkcja pomocnicza

        namespace {

            unsigned char checkIfGoodColor(unsigned char toCheck, unsigned char maxVal) {   // Ta funkcja naprawia wyrzucany blad,
                                                                                            //  poniewaz jest uzywana w konstruktorze
                try {

                    if (toCheck < 0 || toCheck > maxVal) {

                        throw "Niepoprawna wartosc liczbowa";
                    }
                    return toCheck;
                }
                catch (const char* err) {

                    std::clog << "\n Blad: " << err << "\nZmiana wartosci na " << (unsigned short)maxVal << "\n";
                    return maxVal;
                }
            }
        }
    //


    // Konstruktory i destruktor, operator=

        color::color(unsigned char R_, unsigned char G_, unsigned char B_, unsigned char A_)
            :
                _R(R_)  // unsigned char przyjmuje wartosci od 0 do 255,
            ,   _G(G_)  //  czyli nie ma mozliwosci wprowadzenia blednych danych koloru
            ,   _B(B_)
            ,   _A(checkIfGoodColor(A_, 100))   // alpha to 0.00 do 1.00, ale mozna tez zapisac w przedziale 0 - 100
        {}

        color::color(const color& copy_)
            :
                _R(copy_._R)
            ,   _G(copy_._G)
            ,   _B(copy_._B)
            ,   _A(copy_._A)
        {}

        color::~color() {}


        color& color::operator=(const color& copy_) {

            if (this != &copy_) {
                _R = copy_._R;
                _G = copy_._G;
                _B = copy_._B;
                _A = copy_._A;
            }
            return *this;
        }
    //


    // Settery, Gettery

        void color::setValue(unsigned char R_, unsigned char G_, unsigned char B_) {

            setR(R_);
            setG(G_);
            setB(B_);
        }

        void color::setValue(unsigned char R_, unsigned char G_, unsigned char B_, unsigned char A_) {

            setValue(R_, G_, B_);
            setA(A_);
        }

        unsigned char color::setR(unsigned char R_) { _R = R_; return _R; }
        unsigned char color::setG(unsigned char G_) { _G = G_; return _G; }
        unsigned char color::setB(unsigned char B_) { _B = B_; return _B; }
        unsigned char color::setA(unsigned char A_) { _A = checkIfGoodColor(A_, 100); return _A; }

        unsigned char color::getR() const { return _R; }
        unsigned char color::getG() const { return _G; }
        unsigned char color::getB() const { return _B; }
        unsigned char color::getA() const { return _A; }
    //


    //Operatory logiczne 

        bool operator==(const color& C1, const color& C2) {

            if (C1._R != C2._R) {
                return false;
            }
            else if (C1._G != C2._G) {
                return false;
            }
            else if (C1._B != C2._B) {
                return false;
            }
            else if (C1._A != C2._A) {
                return false;
            }
            else {
                return true;
            }
        }

        bool operator!=(const color& C1, const color& C2) {

            return !operator==(C1, C2);
        }

        bool operator<(const color& C1, const color& C2) {

                   if (C1.getR() < C2.getR()) {
                return true;
            } else if (C1.getG() < C2.getG()) {
                return true;
            } else if (C1.getB() < C2.getB()) {
                return true;
            } else if (C1.getA() < C2.getA()) {
                return true;
            } else {
                return false;
            }
        }
    //

        std::ostream& operator<<(std::ostream& O_, const color& C_) {

            O_ << (unsigned short)C_.getR() << " " << (unsigned short)C_.getG() << " " << (unsigned short)C_.getB() << " " << (unsigned short)C_.getA();
            return O_;
        }
}


