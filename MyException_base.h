//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasy myException                                       //
//                                                                                      //
//  Klasy maja za zadanie sluzyc jako rozroznialne typy obiektow wyrzucanych jako       //
//  wyjatki w innych klasach. Sa proste i nie posiadaja wszystkich konstruktorow        //
//  poniewaz ich nie potrzebuja, z zalozenia sluza tylko by wyrzucac ich obiekty        //
//  jako wyjatki.                                                                       //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//   Dostepna funkcjonalnosc:                                                           //
//                                                                                      //
//    myException(const char* )    // Sluzy do utworzenia obiektu z zadana wiadomoscia  //
//                                 // Z zamyslem stosowania w taki sposob:              //
//                                 //     throw MyException("error message");           //
//                                                                                      //
//    myException.what()           // Zwraca pole z wiadomoscia podana w konstruktorze  //
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
//  14/12/2019  | Utworzenie klasy                                  | Szymon Krawczyk   //
//              | Dodanie komentarzy                                |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <string>

namespace KrawczykS {

    // Baza
        class myException_Base {

        private:

            std::string errorMsg;

        public:

            myException_Base(const char* error) : errorMsg(error) {};
            virtual ~myException_Base() {};

            virtual std::string what() const { return errorMsg; };

        };
    //

    // Klasy pochodne

        class myException_BadFormat : public myException_Base {

        public:

            myException_BadFormat(const char* error) : myException_Base(error) {};
            virtual ~myException_BadFormat() {};

        };


        class myException_BadOpen : public myException_Base {

        public:

            myException_BadOpen(const char* error)   : myException_Base(error) {};
            virtual ~myException_BadOpen() {};

        };
    //
}

#endif