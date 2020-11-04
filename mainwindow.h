#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timeUpdate();
    void showFrame_MultipleVideo();
    void showFrame_LocalVideo();
    void showFrame_FaceFeatures();
    void showFrame_Settings();


private:
    Ui::MainWindow *ui;
    QLabel *statusBarTimeLabel;
    QLabel *statusBarMsgLabel;

    void initForm();
    void initControl();
    void initStyle();
};

#endif // MAINWINDOW_H
