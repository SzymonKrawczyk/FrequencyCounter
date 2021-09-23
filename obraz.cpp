//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                              Klasa obraz (plik .cpp)                                 //
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

#include "obraz.h"


namespace KrawczykS {

    void obraz::deleteColorTab() {

        for (int i = 0; i < _width; i++) {
            delete[] _colorTab[i];
        }
        delete[] _colorTab;
    }

    void obraz::createEmptyColorTab() {

        _colorTab = new color*[_width];
        for (int i = 0; i < _width; i++) {
            _colorTab[i] = new color[_height];
        }
    }

    obraz::obraz()
        :
            _width   (0)
        ,   _height  (0)
        ,   _depth   (0)
        ,   _colorTab(nullptr)
    {}

    obraz::obraz(const obraz& copy_)
        :
          _width   (copy_._width)
        , _height  (copy_._height)
        , _depth   (copy_._depth)
        , _colorTab(nullptr)
    {
        createEmptyColorTab();
    }

    obraz::~obraz() { deleteColorTab(); }


    void obraz::setColor(unsigned int x_, unsigned int y_, const color& c0_) {

        _colorTab[x_][y_] = c0_;
    }

    void obraz::setColor(unsigned int x_, unsigned int y_, unsigned char R_, unsigned char G_, unsigned char B_, unsigned char A_) {

        color temp(R_, G_, B_, A_);
        setColor(x_, y_, temp);
    }

    color obraz::getColor(unsigned int x_, unsigned int y_) const {

        return _colorTab[x_][y_];
    }


    unsigned int obraz::setWidth (unsigned int input_) { _width = input_;  return _width; }

    unsigned int obraz::setHeight(unsigned int input_) { _height = input_; return _height; }

    unsigned int obraz::setDepth (unsigned int input_) { _depth = input_;  return _depth; }

    void obraz::setcolorTab(color** input_) { _colorTab = input_; }

    unsigned int obraz::getWidth   () const { return _width; }

    unsigned int obraz::getHeight  () const { return _height; }

    unsigned int obraz::getDepth   () const { return _depth; }

    color **     obraz::getcolorTab() const { return _colorTab; }

}
