#include "medien.h"

int Medien::nextId = 1;

Medien::Medien(string _autor, string _titel)
        :autor(_autor), title(_titel)
{
    Medien::nextId++;
}

Medien::Medien(int _id, string _autor, string _titel)
    :ID(_id), autor(_autor), title(_titel){


}

Medien::~Medien()
{

}

string Medien::getAutor() const
{
    return autor;
}

void Medien::setAutor(const string &newAutor)
{
    autor = newAutor;
}

string Medien::getTitle() const
{
    return title;
}

void Medien::setTitle(const string &newTitle)
{
    title = newTitle;
}

int Medien::getID() const
{
    return ID;
}

bool Medien::getIsLoan() const
{
    return isLoan;
}

void Medien::setLoan(bool value)
{
    isLoan = value;
}

void Medien::setName_borrower(string name)
{
    Name_borrower = name;
}

string Medien::getName_borrower() const
{
    return Name_borrower;
}

void Medien::setNextId(int value)
{
    nextId = value;
}

bool Medien::getIsCD() const
{
    return isCD;
}

void Medien::setIsCD(bool newIsCD)
{
    isCD = newIsCD;
}

