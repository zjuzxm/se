#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

//The function is to implement the graphical user interface
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     assembler = new Assembler();
     disassembler = new Disassembler();
    ui->actionNew->setShortcuts(QKeySequence::New);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionOpen->setShortcuts(QKeySequence::Open);
    ui->actionCopy->setShortcuts(QKeySequence::Copy);
    ui->actionPaste->setShortcuts(QKeySequence::Paste);


    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newfile()));
    connect(ui->actionCompile, SIGNAL(triggered(bool)), this, SLOT(compile()));
    connect(ui->actionDiscompile_2, SIGNAL(triggered(bool)), this, SLOT(discompile()));
    connect(ui->actionGenerate_bin, SIGNAL(triggered(bool)), this, SLOT(generate_bin()));
    connect(ui->actionGenerate_coe, SIGNAL(triggered(bool)), this, SLOT(generate_coe()));
    connect(ui->actionLoad_bin, SIGNAL(triggered(bool)), this, SLOT(load_bin()));
    connect(ui->actionLoad_coe, SIGNAL(triggered(bool)), this, SLOT(load_coe()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

//The open action
void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}
//The action to load the bin file into the disassembler
void MainWindow::load_bin()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Bin Files(*.bin)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = disassembler->LoadtoBin(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QMessageBox::about(this, tr("About Load"),
             tr("Load bin complete!"));
}
//The function is to load the coe file into the application for discompile
void MainWindow::load_coe()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Coe Files(*.coe)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = disassembler->LoadtoCoe(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QMessageBox::about(this, tr("About Load"),
             tr("Load Coe complete!"));
}
//The function is to save the current file
void MainWindow::save()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Txt Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->assemblyText->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}
//The function is to generate the machine code to the bin file
void MainWindow::generate_bin()
{
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = assembler->GeneratetoBin(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Bin Files(*.bin)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->assemblyText->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
    QMessageBox::about(this, tr("About Generate"),
             tr("Generate to bin complete!"));
}

//The function is to generate the machine code to the coe file
void MainWindow::generate_coe()
{
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = assembler->GeneratetoCoe(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Coe Files(*.coe)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->assemblyText->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
    QMessageBox::about(this, tr("About Generate"),
             tr("Generate to coe complete!"));
}

//The function is to help the user to know about how to use the application
void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("This is a simple application which can encode mips code to "
               "hexdecimal machine code and decode hexdecimal machine code "
               "to mipscode"));
}

//The function is create the newfile
void MainWindow::newfile()
{
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);

}

//The function is to compili=e the mips code
void MainWindow::compile()
{
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = assembler->Compile(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QMessageBox::about(this, tr("About Compile"),
             tr("Compile complete!"));
}
//The function is to discompile the machine code
void MainWindow::discompile()
{
    QString textEditPlainText = ui->textEdit->document()->toPlainText();
    QString result = disassembler->Discompile(textEditPlainText);
    ui->assemblyText->document()->setPlainText(result);
    QMessageBox::about(this, tr("About Discompile"),
             tr("Disompile complete!"));
}
