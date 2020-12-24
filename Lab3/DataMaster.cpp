#include <QFileDialog>
#include <QMessageBox>

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
        bool bitForWriting = matrix[0][0];
        int counter = 0;
        for(auto iter1 = matrix.begin(); iter1 != matrix.end(); ++iter1){
            for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
                if(bitForWriting != *iter2){
                    out << (qint32)counter << (qint32)bitForWriting;
                    bitForWriting = *iter2;
                    counter = 1;
                }
                else{
                    ++counter;
                }
            }
        }
        out << (qint32)counter << (qint32)bitForWriting;
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
            if(!GetVector(in, newRules, maxRule)){
                QMessageBox::information(nullptr, tr("Error"),
                                        "Wrong format");
                return;
            }

            std::vector<int> size(2);
            if(!GetVector(in, size, maxSize) ||
                    size[0] == 0 || size[1] == 0){
                QMessageBox::information(nullptr, tr("Error"),
                                        "Wrong format");
                return;
            }
            std::vector<std::vector<bool> > newMatrix(size[1], std::vector<bool>(size[0]));
            if(!GetMatrix(in, newMatrix)){
                QMessageBox::information(nullptr, tr("Error"),
                                        "Wrong format");
                return;
            }

            rules = std::move(newRules);
            matrix = std::move(newMatrix);
    }
}

bool DataMaster::GetVector(QDataStream& in, std::vector<int>& someVector, int limit){
    for(auto iter = someVector.begin(); iter != someVector.end(); ++iter){
        in >> *iter;
        if(in.atEnd() || *iter < 0 || *iter > limit){
            return false;
        }
    }
    return true;
}

bool DataMaster::GetMatrix(QDataStream& in, std::vector<std::vector<bool> >& matrix){
    int counter = 0;
    int bitForLoading;
    for(auto iter1 = matrix.begin(); iter1 != matrix.end(); ++iter1){
        for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
            if(!counter){
                if(in.atEnd()){
                    return true;
                }
                else{
                    in >> counter;
                }
                if(in.atEnd()){
                    return false;
                }
                else{
                    in >> bitForLoading;
                }
            }
            *iter2 = bitForLoading;
            --counter;
        }
    }
    if(!in.atEnd()){
        return false;
    }
    return true;
}
