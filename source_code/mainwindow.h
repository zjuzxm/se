#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include "assembler.h"
#include "disassembler.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Some function to open,save,about and newfile action
    void open();
    void save();
    void about();
    void newfile();

    //Some functions to compile,discompile,generate and load bin
    void compile();
    void discompile();
    void generate_bin();
    void generate_coe();
    void load_bin();
    void load_coe();


private:
    Ui::MainWindow *ui;

    bool maybeSave();
    Assembler *assembler;
    Disassembler *disassembler;
};

#endif // MAINWINDOW_H
