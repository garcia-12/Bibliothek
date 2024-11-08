#include "cds.h"

#include <iomanip>


#include <string>
#include <iostream>

using namespace std;

CDs::CDs(string _autor, string _title, string _spieldaeur)
    :Medien(_autor, _title), spieldauer(_spieldaeur)
{
    Medien::setIsCD(true);
}

CDs::CDs(int _id, string _autor, string _title, string _spieldaeur)
    :Medien(_id, _autor, _title), spieldauer(_spieldaeur)
{
    Medien::setIsCD(true);
}

CDs::~CDs()
{

}


string CDs::getSeitenanzahlDauer()
{
    return spieldauer;
}

void CDs::setSpieldauer(double newSpieldauer)
{
    spieldauer = newSpieldauer;
}

void CDs::anzeigen()
{
    cout << setw(8) << CDs::getID() << " | " << setw(30) << CDs::getAutor() << " | "
         <<setw(50) << CDs::getTitle()
         << " | " << setw(10);
    if(CDs::getIsLoan()){
        cout << "( " << CDs::getName_borrower() << " )"<< " | ";
    }
    cout<< setw(10) << CDs::getSeitenanzahlDauer()<< " St. " << endl;
}
