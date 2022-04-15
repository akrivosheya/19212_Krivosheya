#ifndef LOADERANDSAVER_H
#define LOADERANDSAVER_H

#include <vector>
#include <QDataStream>

class LoaderAndSaver
{
public:
    bool LoadData(QDataStream& out,
                  std::vector<std::vector<bool> >& matrix,
                  std::vector<std::vector<bool> >& rules);
    void SaveData(QDataStream& out,
                  std::vector<std::vector<bool> >& matrix,
                  std::vector<std::vector<bool> >& rules);

private:
    bool GetRules(QDataStream& in,
                  std::vector<std::vector<bool> >& rules);
    bool GetSize(QDataStream& in,
                 std::vector<int>& size,
                 int limit);
    bool GetMatrix(QDataStream& in,
                   std::vector<std::vector<bool> >& matrix);
    static constexpr int maxSize = 100;
    static constexpr int maxNeighbours = 8;
    static constexpr int countOfRules = 2;
};

#endif // LOADERANDSAVER_H
