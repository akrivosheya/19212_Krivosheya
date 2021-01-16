#include <QFileDialog>

#include "DataMaster.h"

int DataMaster::Save(std::vector<std::vector<bool> >& matrix,
                     std::vector<std::vector<bool> >& rules,
                     QString& error){
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Save", "",
                                                    "(*.rle);;All Files (*)");
    if (fileName.isEmpty())
        return emptyName;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            error = file.errorString();
            return unableToOpen;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        helper.SaveData(out, matrix, rules);
        return success;
    }
}

int DataMaster::Load(std::vector<std::vector<bool> >& matrix,
                     std::vector<std::vector<bool> >& rules,
                     QString& error){
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Load", "",
                                                    "(*.rle);;All Files (*)");
    if (fileName.isEmpty())
        return emptyName;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            error = file.errorString();
            return unableToOpen;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        if(!helper.LoadData(in, matrix, rules)){
            return wrongFormat;
        }
        return success;
    }
}
