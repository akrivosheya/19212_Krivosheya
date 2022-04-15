#ifndef INFORMANT_H
#define INFORMANT_H

#include <QMessageBox>

class Informant
{
public:
    Informant() = default;
    void InformWrongSize(){
        QMessageBox::information(nullptr, "Error",
                                "Wrong size");
    }
    void InformWrongRule(){
        QMessageBox::information(nullptr, "Error",
                                "Wrong rule");
    }
    void InformWrongFormat(){
        QMessageBox::information(nullptr, "Error",
                                "Wrong format");
    }
    void InformUnable(QString err){
        QMessageBox::information(nullptr, "Error",
                                err);
    }
    void InformSuccessfulSaving(){
        QMessageBox::information(nullptr, "OK",
                                "Successful saving");
    }
    void InformSuccessfulLoading(){
        QMessageBox::information(nullptr, "OK",
                                "Successful loading");
    }
};

#endif // INFORMANT_H
