#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

#include "DataMaster.h"

void DataMaster::Save(std::vector<std::vector<bool> >& matrix, std::vector<int>& rules){
    QString fileName = QFileDialog::getSaveFileName(nullptr,
     tr("Save"), "",
     tr("(*.rle);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"),
                                    file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << (qint32)rules[0] << (qint32)rules[1] << (qint32)rules[2]
                << (qint32)matrix[0].size() << (qint32)matrix.size();
        for(auto iter1 = matrix.begin(); iter1 != matrix.end(); ++iter1){
            for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
                out << (qint32)*iter2;
            }
        }
     }
}

void DataMaster::Load(std::vector<std::vector<bool> >& matrix, std::vector<int>& rules){
    QString fileName = QFileDialog::getOpenFileName(nullptr,
     tr("Load"), "",
     tr("(*.rle);;All Files (*)"));
    if (fileName.isEmpty())
            return;
    else {
            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(nullptr, tr("Unable to open file"),
                                        file.errorString());
                return;
            }

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);
            std::vector<int> newRules(3);
            in >> newRules[0] >> newRules[1] >> newRules[2];
            if(!(newRules[0] >= 0 && newRules[0] <= 8 &&
                 newRules[1] >= 0 && newRules[2] <= 8 && newRules[1] <= newRules[2])){
                QMessageBox::information(nullptr, tr("Error"),
                                        "Wrong format");
                return;
            }
            int newWidth, newHeight;
            in >> newWidth >> newHeight;
            if(!(newWidth > 0 && newWidth <= 100 &&
                 newHeight > 0 && newHeight <= 100)){
                QMessageBox::information(nullptr, tr("Error"),
                                        "Wrong format");
                return;
            }
            int tmp;
            std::vector<std::vector<bool> > newMatrix(newHeight, std::vector<bool>(newWidth));
            for(auto iter1 = newMatrix.begin(); iter1 != newMatrix.end(); ++iter1){
                for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
                    if(in.atEnd()){
                        QMessageBox::information(nullptr, tr("Error"),
                                                "Wrong format");
                        return;
                    }
                    in >> tmp;
                    if(!(tmp == 0 || tmp == 1)){
                        QMessageBox::information(nullptr, tr("Error"),
                                                "Wrong format");
                        return;
                    }
                    *iter2 = tmp;
                }
            }
            rules = std::move(newRules);
            matrix = std::move(newMatrix);
    }
}
