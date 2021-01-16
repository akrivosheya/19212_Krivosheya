#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "RenderArea.h"
#include "Game.h"
#include "Translater.h"
#include "DataMaster.h"
#include "Informant.h"
#include "Timer.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window() = default;

public slots:
    void SetRulesForGame();
    void ResizeGame();
    void SaveGame();
    void LoadGame();
    void ActivateGame();
    void DiactivateGame();
    void PlayGame();
    void ClearGame();
    void ChangeRectOfMatrix(int idx1, int idx2);

private:
    std::unique_ptr<Game> game;
    std::unique_ptr<Translater> translater;
    std::unique_ptr<DataMaster> dataMaster;
    std::unique_ptr<RenderArea> renderArea;
    std::unique_ptr<QPushButton> playButton;
    std::unique_ptr<QPushButton> stopButton;
    std::unique_ptr<QPushButton> saveButton;
    std::unique_ptr<QPushButton> loadButton;
    std::unique_ptr<QPushButton> clearButton;
    std::unique_ptr<QPushButton> setRulesButton;
    std::unique_ptr<QPushButton> setSizeButton;
    std::unique_ptr<QLineEdit> modeLine;
    std::unique_ptr<QLineEdit> widthLine;
    std::unique_ptr<QLineEdit> heightLine;
    std::unique_ptr<QLabel> widthLabel;
    std::unique_ptr<QLabel> heightLabel;
    std::unique_ptr<Informant> informant;
    std::unique_ptr<Timer> timer;
};
#endif
