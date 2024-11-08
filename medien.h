#ifndef MEDIEN_H
#define MEDIEN_H

#include <string>

using namespace std;

class Medien
{
public:
    Medien(string _autor, string _titel);
    Medien(int _id, string _autor, string _titel);
    virtual ~Medien();
    string getAutor() const;
    void setAutor(const string &newAutor);
    string getTitle() const;
    void setTitle(const string &newTitle);
    int getID() const;
    bool getIsLoan() const;
    void setLoan(bool value);
    void setName_borrower(string name);
    string getName_borrower() const;
    static void setNextId(int value);

    bool getIsCD() const;
    void setIsCD(bool newIsCD);

    virtual void anzeigen() = 0;
    virtual string getSeitenanzahlDauer() = 0;
    // virtual string getSpieldauer();

private:
    string autor;
    string title;
    const int ID = Medien::nextId;
    static int nextId;
    bool isLoan = false;
    string Name_borrower;
    bool isCD = true;
};

#endif // MEDIEN_H
