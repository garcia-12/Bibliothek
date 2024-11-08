#ifndef CDS_H
#define CDS_H

#include "medien.h"
#include <string>

using namespace std;


class CDs: public Medien
{
public:
    CDs(string _autor, string _title, string _spieldaeur);
    CDs(int _id, string _autor, string _title, string _spieldaeur);
    virtual ~CDs();
    virtual string getSeitenanzahlDauer() override;
    void setSpieldauer(double newSpieldauer);

    virtual void anzeigen() override;

private:
    string spieldauer;
};

#endif // CDS_H
