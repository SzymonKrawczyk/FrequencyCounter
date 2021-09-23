//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa freqcounter                                       //
//                                                                                      //
//  Jest to klasa kontenerowa majaca za zadanie przechowywac okreslony typ danych       //
//  oraz ilosc wystapien kazdego elementu                                               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//      Dla poprawnego dzialania wszystkich metod, klasa wymaga od dowolnego typu       //
//      danych T operatorow == oraz <                                                   //
//                                                                                      //
//   Dostepna funkcjonalnosc:                                                           //
//      (gdy fc_T to freqcounter<T>)                                                    //
//                                                                                      //
//      fc_T.size()    const;       // Zwraca ilosc elementow                           //
//      fc_T.sumSize() const;       // Zwraca sume liczebnosci wszystkich elementow     //
//      fc_T.biggest() const;       // Zwraca najwieksza liczebnosc w zbiorze           //
//                                                                                      //
//      fc_T.addData(T);            // Dodaje dana do kontenera,                        //
//                                  //  Wymaga operatora== dla typu T                   //
//                                                                                      //
//      fc_T.[T];                   // Zwraca liczebnosc podanego elementu              //
//                                  //  Wymaga operatora== dla typu T                   //
//                                                                                      //
//      fc_T.at(long index);        // Zwraca element z podanej pozycji                 //
//                                                                                      //
//      fc_T.show(std::ostream&) const;         // Wyswietla zawartosc                  //
//                                              // (elementy i ich liczebnosc)          //
//                                              // np.: na cout albo ostream (do pliku) //
//                                                                                      //
//      fc_T.sort();                // Sortuje wzgledem T (a nie np. liczebnosci)       //
//                                  //  Wymaga operatora<  dla typu T                   //
//                                                                                      //
//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
//                                                                                      //
//   Funkcjonalnosc niepubliczna:                                                       //
//                                                                                      //
//      fc_T.getDataTab();                      // Zwraca  vector z danymi              //
//                                                                                      //
//      fc_T.setDataTab(const vector<dataT>);   // Ustawia vector z danymi              //
//                                                                                      //
//      Klasa dataT na pojedynczy 'rekord' - posiada pola na dana typu T i liczebnosc   //
//      typu long. Dostepne operacje:                                                   //
//                                                                                      //
//                  dataT.operator==(const T)       // Porownuje pole T z dana T        //
//                                                                                      //
//                  dataT.operator< (const dataT)   // Porownuje pola T (a nie long)    //
//                                                                                      //
//                  ++dataT                         // Zwieksza liczebnosc o 1L         //
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
//  23/12/2019  | Utworzenie klasy                                  | Szymon Krawczyk   //
//              |                                                   |                   //
//  25/12/2019  | Dodanie i redefinicja wiekszosci metod            | Szymon Krawczyk   //
//              |                                                   |                   //
//  28/12/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              |                                                   |                   //
//  01/01/2020  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef FREQCOUNTER_H
#define FREQCOUNTER_H

#include <vector>
#include <iostream>     // std::clog
#include <algorithm>    // std::sort

using std::vector;

namespace KrawczykS {

    template<typename T>
    class freqcounter {

    protected:

        class dataT {   // Klasa pomocnicza
                        // (nie posiada wszystkiego co potrzebuje klasa normalnie,
                        // jednak nie jest widoczna poza ta klasa i klasami pochodnymi)
        public:

            //Pola

                T    _item;
                long _count;
            //

            //Metody

                dataT(T in_, long ct_ = 1L)
                    : 
                        _item (in_)
                    ,   _count(ct_)
                {};

                virtual ~dataT() {};

                bool operator== (const T& in_) {
                    return (_item == in_);
                }

                bool operator< (const dataT& in_) {
                    return (_item <  in_._item);
                }

                dataT& operator++ () {
                    ++_count;
                    return *this;
                }
            //
        };

        vector<dataT>& getDataTab()                        { return _dataTab; };
        void           setDataTab(const vector<dataT> cp_) { _dataTab = cp_; };


    private:

        vector<dataT> _dataTab;


    public:

        freqcounter();
        freqcounter(const freqcounter&);

        virtual ~freqcounter();     // Destruktor wirtualny zapewnia wywolanie destruktorow klas pochodnych
                                    //  dzieki temu zapobieagmy mozliwym bledom, 
                                    //  poniewaz niewywolanie destruktora klasy pochodnej moze prowadzic do np.: wyciekow pamieci

        freqcounter<T>& operator=(const freqcounter&);

        long size()    const;       // Ilosc elementow
        long sumSize() const;       // Suma liczebnosci wszystkich elementow
        long biggest() const;       // Najwieksza liczebnosc w zbiorze elementow

        T addData(T);               // Wymaga operatora== dla typu T

        long& operator[](T);        // Wymaga operatora== dla typu T
        const T& at(long);          // Zwraca z indeksu pozycji

        std::ostream& show(std::ostream&) const;

        void sort();                // Wymaga operatora<  dla typu T

    };

    template<typename T>
    freqcounter<T>::freqcounter()
        :
            _dataTab()
    {}

    template<typename T>
    freqcounter<T>::freqcounter(const freqcounter& copy_)
        :
            _dataTab(copy_._dataTab)
    {}

    template<typename T>
    freqcounter<T>::~freqcounter() {}

    template<typename T>
    freqcounter<T>& freqcounter<T>::operator=(const freqcounter& copy_) {

        if (this != &copy_) {
            _dataTab = copy_._dataTab;
        }
        return *this;
    }


    template<typename T>
    long freqcounter<T>::size() const {

        return _dataTab.size();
    }

    template<typename T>
    long freqcounter<T>::sumSize() const {

        long sum = 0L;
        for (int i = 0; i < _dataTab.size(); ++i) {

            sum += _dataTab[i]._count;
        }
        return sum;
    }

    template<typename T>
    long freqcounter<T>::biggest() const {

        long max = 0L;

        if (_dataTab.size()) {
            max = _dataTab[0]._count;
        }

        for (int i = 0; i < _dataTab.size(); ++i) {

            if (_dataTab[i]._count > max) {

                max = _dataTab[i]._count;
            }
        }
        return max;
    }


    template<typename T>
    T freqcounter<T>::addData(T input_) {
        
        bool found = false;
        for (int i = 0; i < _dataTab.size(); ++i) {

            if (input_ == _dataTab[i]._item) {          // Jest juz taka dana?

                ++_dataTab[i];                          // Zwieksz jej liczebnosc
                found = true;
                break;
            }
        }

        if (!found) {                                   // Nie ma takiej danej?

            _dataTab.push_back(dataT(input_));          // Dodaj (domyslna liczebnosc = 1)
        }

        return input_;
    }

    template<typename T>
    long& freqcounter<T>::operator[](T toFind_) {       // long&, poniewaz mozna zmieniac wartosc

        bool found = false;
        for (int i = 0; i < _dataTab.size(); ++i) {

            if (_dataTab[i] == toFind_) {               // Znaleziony element z podanym indeksem?

                return _dataTab[i]._count;              // Zwroc liczebnosc
            }
        }

        if (!found) {                                   // Nie ma takiego elementu?

            _dataTab.push_back(dataT(toFind_, 0));      // Dodaj (ale o liczebnosci 0)
            return _dataTab[_dataTab.size()-1]._count;  // Oraz zwroc
        }
    }

    template<typename T>
    const T& freqcounter<T>::at(long from_) {

        return _dataTab.at(from_)._item;
    }

    template<typename T>
    std::ostream & freqcounter<T>::show(std::ostream& outStream_) const {

        for (int i = 0; i < _dataTab.size(); ++i) {     // Wypisz wszystkie elementy i ich liczebnosc

            outStream_ << _dataTab[i]._item << '\t' << _dataTab[i]._count << std::endl;
        }

        return outStream_;
    }

    template<typename T>
    void freqcounter<T>::sort() {

        std::sort(_dataTab.begin(), _dataTab.end());    // std::sort z STL, wymaga operatora< dla danych
    }
}

#endif