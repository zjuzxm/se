#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QRegExp>
//This is the header file of the assembler;
class Assembler
{

public:
    Assembler();
    QString Compile(QString& mips_code);//The function to complie mips code
    QString GeneratetoBin(QString& mips_code);//The function to complie mips code
    QString GeneratetoCoe(QString& mips_code);//The function to complie mips code
    QStringList Preprocess(QString&  mips_code);//The function to delete the comma and blank of the imput code
    const QString Encode_mips( const QString& temp_mips);//The function to encode one mips code
    const QString Encode_Reg( const QString& reg);//The function to encode the register
    const QString Encode_Shamt(const QString& shamt);//The function to encode the shamt
    const QString Encode_Immediate(const QString& immediate);//The function to encode the immediate
    const QString Encode_Address(const QString& address);//The function to encode the target address
    const QString Encode_Branch(const QString& branch);//The function to encode the branch instruction

private:
    QMap<QString, QString> reg_addr;//The map to save the register's address
    QMap<QString, QString> label_addr;//The map to save the label's address
    QStringList machinecode_list;//The list to store the machine code
    int PC;//The current PC value
};
#endif 
