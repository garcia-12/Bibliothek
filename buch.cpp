#include "buch.h"
#include <iomanip>


#include <string>
#include <iostream>

using namespace std;


Buch::Buch(string _autor, string _titel, string _seitenr)
    :Medien(_autor, _titel), seitenanzahl(_seitenr)
    {
    Medien::setIsCD(false);
}

Buch::Buch(int _id, string _autor, string _titel, string _seitenr)
    :Medien(_id, _autor, _titel), seitenanzahl(_seitenr)
{
    Medien::setIsCD(false);
}

Buch::~Buch()
{

}



string Buch::getSeitenanzahlDauer()
{
    return seitenanzahl;
}

void Buch::setSeitenanzahl(int newSeitenanzahl)
{
    seitenanzahl = newSeitenanzahl;
}

void Buch::anzeigen()
{
    cout << setw(8) << Buch::getID() << " | " << setw(30) << Buch::getAutor() << " | "
         <<setw(50);
        if(Buch::getIsLoan()){
            cout << "( " << Buch::getName_borrower() << " )";
        }
        cout<< Buch::getTitle()
         << " | ";

        cout<< setw(10) << Buch::getSeitenanzahlDauer()<<" pages" << endl;
}
