//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa ppm (plik .cpp)                                   //
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
//              | Dodanie wlasnych wyjatkow                         |                   //
//              | Usuniecie obslugi wyjatkow w metodach             |                   //
//              | Dodanie obslugi wyjatkow w konstruktorze          |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include "ppm.h"
#include "MyException_base.h"   // Wyjatki
#include <iostream>             // std::clog
#include <string>               // Latwiejsza kontrola bledow w nazwie pliku

namespace KrawczykS {

    // Konstruktory, destruktor, operator=

        ppm::ppm()
            :
                obraz()
        {}

        ppm::ppm(const char* file_name_)
            :
                obraz()
        {
            // Nalezy obsluzyc wyjatki w konstruktorze, poniewaz konstruktor nie powinien ich wyrzucac
            //
            try {
                loadFromFile(file_name_);
            }
            catch (myException_Base& error) {   // Obsluga wszystkich klas pochodnych

                std::clog << "\nError: " << error.what() << "\n";
                std::clog << "Utworzony obiekt bedzie domyslny\n";

                deleteColorTab();
                setWidth      (0);
                setHeight     (0);
                setDepth      (0);
                setcolorTab   (nullptr);
            }
            catch (...) {
                std::clog << "\nError: ??\n";
            }
        }

        ppm::ppm(unsigned int w_, unsigned int h_, unsigned int d_) 
            :
                obraz()
        {
            setWidth (w_);
            setHeight(h_);
            setDepth (d_);

            createEmptyColorTab();
        }


        ppm::ppm(const ppm& copy_) 
            :
                obraz(copy_)
        {}

        ppm::ppm(const obraz& copy_)
            :
                obraz(copy_)
        {}

        ppm::~ppm() {}


        ppm& ppm::operator=(const ppm& copy_) {
        
            if (this != &copy_) {
                obraz::operator=(copy_);
            }
            return *this;
        }
    //


    // Wczytaj z pliku

        void ppm::loadFromFile(const char* file_name_) {

            std::string temp_name_ = file_name_;

            if ((temp_name_[temp_name_.size() - 3] != 'p')
             || (temp_name_[temp_name_.size() - 2] != 'p')
             || (temp_name_[temp_name_.size() - 1] != 'm')) {

                temp_name_ += ".ppm";               // Jesli nie ma formatu .ppm, dodaj go
            }

            std::ifstream fileIn;
            fileIn.open(temp_name_.c_str());

            if (fileIn.is_open()) {

                {   // Sprawdz format, pomin komentarze

                    int c = 0;
                    std::string temp;

                    getline(fileIn, temp);
                    if (temp != "P3") {

                        throw myException_BadFormat("Zly format pliku!");
                    }

                    while (!isdigit(c = fileIn.peek())) {   // Pomijaj linie, az trafisz na liczby

                        getline(fileIn, temp);
                    };
                }
                
                {   // Ustaw pola

                    deleteColorTab();

                    int temp = 0;

                    fileIn >> temp;
                    setWidth(temp);

                    fileIn >> temp;
                    setHeight(temp);

                    fileIn >> temp;
                    setDepth(temp);

                    createEmptyColorTab();
                }
                

                unsigned short tempR = 0;
                unsigned short tempG = 0;
                unsigned short tempB = 0;

                for (unsigned int i = 0; i < getHeight(); i++) {

                    for (unsigned int j = 0; j < getWidth(); j++) {

                        
                        fileIn >> tempR;
                        fileIn >> tempG;
                        fileIn >> tempB; 

                        setColor(j, i, tempR, tempG, tempB);
                    }
                    
                }
                fileIn.close();
            }
            else {
                throw myException_BadOpen("Blad odczytu pliku");
            }
        }
    //


    // Zapisz do pliku

        void ppm::saveAs(const char * file_name_) const {

            std::string temp_name_ = file_name_;

            if ((temp_name_[temp_name_.size() - 3] != 'p')
             || (temp_name_[temp_name_.size() - 2] != 'p')
             || (temp_name_[temp_name_.size() - 1] != 'm')) {

                temp_name_ += ".ppm";               // Jesli nie ma formatu .ppm, dodaj go
            }

            std::ofstream fileOut;
            fileOut.open(temp_name_.c_str());

            if (fileOut.is_open()) {

                fileOut << "P3\n";
                fileOut << "# Created by Krawczyk Szymon\n";
                fileOut << getWidth() << " " << getHeight() << "\n";
                fileOut << getDepth() << "\n";

                color temp;
                unsigned short counter = 0;

                for (unsigned int i = 0; i < getHeight(); i++) {

                    for (unsigned int j = 0; j < getWidth(); j++) {

                        temp = getColor(j, i);
                        fileOut << (unsigned short)temp.getR() << " ";
                        fileOut << (unsigned short)temp.getG() << " ";
                        fileOut << (unsigned short)temp.getB() << " ";

                        if (++counter >= 5) {   // Formatowanie, co piec kolorow nowa linijka

                            counter = 0;
                            fileOut << "\n";
                        }
                    }

                }
                fileOut.close();
            }
            else {
                throw myException_BadOpen("Blad odczytu pliku");
            }
            
        }
    //
}
