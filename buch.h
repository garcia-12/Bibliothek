#ifndef BUCH_H
#define BUCH_H

#include "medien.h"
#include <string>

using namespace std;

class Buch : public Medien
{
public:
    Buch(string _autor, string _titel, string _seitenr );
    Buch(int _id, string _autor, string _titel, string _seitenr);
    virtual ~Buch();
    virtual string getSeitenanzahlDauer() override;
    void setSeitenanzahl(int newSeitenanzahl);

    virtual void anzeigen() override;

private:
    string seitenanzahl;
};

#endif // BUCH_H
