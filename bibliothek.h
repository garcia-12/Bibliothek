#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include "medien.h"


#include <vector>
#include <string>

using namespace std;


class Bibliothek
{
public:
    Bibliothek();
    ~Bibliothek();
    void dialog();
    void displayMedien(vector<Medien *> &b) const;
    Medien* MediaFinden(const int &nummer = 0, const string& Name_borrower = "");
    void BibliothekLaden(vector<Medien *> &medien, const string& myLibrary);
    void BibliothekSpeichern(const vector <Medien*>& buecher, const string& myLibrary);
    void bubbleSort(vector<Medien *> &b);

private:
    vector <Medien*> medien;

};

#endif // BIBLIOTHEK_H
