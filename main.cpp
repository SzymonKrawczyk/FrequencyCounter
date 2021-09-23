//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//               Klasa freqcounter (plik pokazujacy mozliwosci klasy)                   //
//                                                                                      //
//  Autor: Szymon Krawczyk                                                              //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
// Changelog:                                                                           //
//  Data        |  Zmiany                                           | Przez kogo        //
// -------------|-------------------------------------------------- |------------------ //
//  23/12/2019  | Testowanie freqcounter na int                     | Szymon Krawczyk   //
//              |                                                   |                   //
//  24/12/2019  | Testowanie freqcounter na char                    | Szymon Krawczyk   //
//              |                                                   |                   //
//  25/12/2019  | Testowanie freqcounter na string                  | Szymon Krawczyk   //
//              | Utworzenie rozbudowanej struktury programu        |                   //
//              |                                                   |                   //
//  28/12/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              | Konczenie zycia zmiennych gdy przestaja byc       |                   //
//              |  potrzebne (oszczednosc pamieci).                 |                   //
//              | Przebudowa programu pod katem obslugi bledow      |                   //
//              | Testowanie freqcounter na color                   |                   //
//              | Dodanie konwersji pliku graficznego .ppm na       |                   //
//              |  posortowane kolory i jego zapis!                 |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include <ctime>
#include <random>

#include <string>

#include <stdlib.h>             // exit(EXIT_FAILURE)

#include "freqcounter.h"
#include "MyException_base.h"   // wyjatki
#include "ppm.h"                // ppm, color


using std::cout;
using std::cin;

using KrawczykS::freqcounter;

using KrawczykS::myException_BadOpen;
using KrawczykS::myException_Base;

using KrawczykS::color;
using KrawczykS::ppm;
using std::string;


int main() {

    std::ifstream fileIn;
    std::ofstream fileOut;

    
            {
                // Test operatora []
                //
                // Zauwazmy, ze nie korzystamy z addData()

                freqcounter <string> test;

                cout << "Wielkosc test: " << test.size() << "\n";

                cout << "test[\"styczen\"] = 120;" << "\n";
                         test ["styczen"]  = 120;

                cout << "Wielkosc test: " << test.size() << "\n";

                cout << "\nzawartosc test: \n";
                test.show(cout);
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


    try {
            {
                cout << "\n Losowe liczby od 0 do 999 milion razy.\n\n";
                srand(time(NULL));

                freqcounter<int> fc_i;

                cout << "losowanie...\n";
                for (int i = 0; i < 1000000; ++i) {
                    fc_i.addData(rand() % 1000);
                }

                cout << "sortowanie...\n\n";
                fc_i.sort();

                cout << "Elementow: "  << fc_i.sumSize() << "\n"
                     << "Unikalnych: " << fc_i.size()    << "\n\n";

                cout << "Zapisywanie do pliku \"histogram_int.txt\"...\n";
                fileOut.open("histogram_int.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_int.txt\""));
                }
                fc_i.show(fileOut);

                fileOut.close();
                cout << "Zapis pomyslny!\n\n\n";


                cout << "Tworzenie wykresu w formacie graficznym .ppm ...\n";

                ppm histInt(fc_i.biggest(), fc_i.size());

                unsigned int howMany = 0;
                const color paint(255, 140, 0);     // 'darkorange'

                for (unsigned int i = 0; i < fc_i.size(); i++) {

                    howMany = fc_i[fc_i.at(i)];

                    for (unsigned int a = 0; a < howMany; ++a) {    // Ustaw tyle pikseli na dany kolor,
                                                                    //  ile wynosi liczebnosc danego elementu
                                                                    //  (reszta linii bedzie domyslnie biala)
                        histInt.setColor(a, i, paint);
                    }
                }

                histInt.saveAs("histogram_int_graficznie.ppm");
                cout << "Zapis pomyslny!\n";

            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_pl - znaki\n\n";
                freqcounter<char> fc_ch;

                fileIn.open("biblia-pl.txt");
                cout << "Otwieranie pliku \"biblia-pl.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-pl.txt\""));
                }

                cout << "Odczytywanie znakow...\n\n";

                char tempCh = '\0';
                while ((tempCh = fileIn.get()) != EOF) {
                    fc_ch.addData(tempCh);
                }
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_ch.sort();

                cout << "Zapisywanie do pliku \"histogram_char_pl.txt\"...\n";
                fileOut.open("histogram_char_pl.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_char_pl.txt\""));
                }
                fc_ch.show(fileOut);
                fileOut.close();

                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_pl - slowa\n\n";
                freqcounter<string> fc_s;

                fileIn.open("biblia-pl.txt");
                cout << "Otwieranie pliku \"biblia-pl.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-pl.txt\""));
                }

                cout << "Odczytywanie slow...\n\n";
                string tempS = "";
                while (fileIn >> tempS) {
                    fc_s.addData(tempS);
                }
                fileIn.clear();
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_s.sort();

                cout << "Zapisywanie do pliku \"histogram_string_pl.txt\"...\n";
                fileOut.open("histogram_string_pl.txt");

                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_string_pl.txt\""));
                }

                fc_s.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_en - znaki\n\n";
                freqcounter<char> fc_ch;

                fileIn.open("biblia-en.txt");
                cout << "Otwieranie pliku \"biblia-en.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-en.txt\""));
                }

                cout << "Odczytywanie znakow...\n\n";
                char tempCh = '\0';
                while ((tempCh = fileIn.get()) != EOF) {
                    fc_ch.addData(tempCh);
                }
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_ch.sort();

                cout << "Zapisywanie do pliku \"histogram_char_en.txt\"...\n";
                fileOut.open("histogram_char_en.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_char_en.txt\""));
                }
                fc_ch.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_en - slowa\n\n";
                freqcounter<string> fc_s;

                fileIn.open("biblia-en.txt");
                cout << "Otwieranie pliku \"biblia-en.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-en.txt\""));
                }

                cout << "Odczytywanie slow...\n\n";
                string tempS = "";
                while (fileIn >> tempS) {
                    fc_s.addData(tempS);
                }
                fileIn.clear();
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_s.sort();

                cout << "Zapisywanie do pliku \"histogram_string_en.txt\"...\n";
                fileOut.open("histogram_string_en.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_string_en.txt\""));
                }
                fc_s.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_it - litery\n\n";
                freqcounter<char> fc_ch;

                fileIn.open("biblia-it.txt");
                cout << "Otwieranie pliku \"biblia-it.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-it.txt\""));
                }

                cout << "Odczytywanie znakow...\n\n";
                char tempCh = '\0';
                while ((tempCh = fileIn.get()) != EOF) {
                    fc_ch.addData(tempCh);
                }
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_ch.sort();

                cout << "Zapisywanie do pliku \"histogram_char_it.txt\"...\n";
                fileOut.open("histogram_char_it.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_char_it.txt\""));
                }
                fc_ch.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


            {
                cout << "\n Biblia_it - slowa\n\n";
                freqcounter<string> fc_s;

                fileIn.open("biblia-it.txt");
                cout << "Otwieranie pliku \"biblia-it.txt\"...\n";
                if (!fileIn.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"biblia-it.txt\""));
                }

                cout << "Odczytywanie slow...\n\n";
                string tempS = "";
                while (fileIn >> tempS) {
                    fc_s.addData(tempS);
                }
                fileIn.clear();
                fileIn.close();

                cout << "sortowanie...\n\n\n";
                fc_s.sort();

                cout << "Zapisywanie do pliku \"histogram_string_it.txt\"...\n";
                fileOut.open("histogram_string_it.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_string_it.txt\""));
                }
                fc_s.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n";
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");
            

            {
                cout << "\n Lena - kolory\n\n";

                freqcounter<color> fc_c;
                ppm tempPPM;
                tempPPM.loadFromFile("Lena.ppm");   // Bledy sa wyrzucane w metodzie
                color tempC;

                for (unsigned int i = 0; i < tempPPM.getHeight(); i++) {

                    for (unsigned int j = 0; j < tempPPM.getWidth(); j++) {

                        tempC = tempPPM.getColor(j, i);
                        fc_c.addData(tempC);
                    }

                }
                fileIn.clear();
                fileIn.close();

                cout << "\nsortowanie...\n\n\n";
                fc_c.sort();

                cout << "Zapisywanie do pliku \"histogram_color.txt\"...\n";
                fileOut.open("histogram_color.txt");
                if (!fileOut.is_open()) {
                    throw(myException_BadOpen("Nieudana proba otworzenia pliku \"histogram_color.txt\""));
                }
                fc_c.show(fileOut);
                fileOut.close();
                cout << "Zapis pomyslny!\n\n\n";



                cout << "Posortowane kolory w formie obrazka!\n";

                ppm sortedPPM(tempPPM.getWidth(), tempPPM.getHeight()); // Zachowaj oryginalne wymiary

                unsigned int counter  = 0;  // odpowiada za szerokosc
                unsigned int counter2 = 0;  // odpowiada za wysokosc
                color tempC2;

                for (unsigned int i = 0; i < fc_c.size(); i++) {

                    tempC2 = fc_c.at(i);
                    for (unsigned int j = 0; j < fc_c[fc_c.at(i)]; ++j) {

                        sortedPPM.setColor(counter, counter2, tempC2);
                        ++counter;

                        if (counter >= sortedPPM.getWidth()) {  // Dotarcie do konca szerokosci?

                            ++counter2;                         // to nastepna linijka
                            counter = 0;                        // i od poczatku
                        }
                    }
                }

                sortedPPM.saveAs("sortedPPM.ppm");              // Bledy sa wyrzucane w metodzie
            }


            cout << "\n - - <Enter> aby kontynuowac - - \n";
            cin.get();
            system("CLS");


    }
    catch (myException_Base& err) {

        std::clog << "\n\n  :( \nCos poszlo nie tak!\n" << err.what() << "\n";
        std::clog << "\tZamkniecie programu...\n";
        cin.get();
        exit(EXIT_FAILURE);
    }
    catch (...) {           // Wszystkie wyjatki nieobsluzone wczesniej

        std::clog << "\n\n  :( \nCos poszlo nie tak!\n(i nie wiadomo co!)\n";
        std::clog << "\tZamkniecie programu...\n";
        cin.get();
        exit(EXIT_FAILURE);
    }

    cout << "\n - - Koniec - - \n";
    cin.get();

    return 0;
}