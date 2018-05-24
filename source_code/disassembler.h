#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <QString>
#include <QMap>
#include <QDebug>
#include <QRegExp>
//This is the header file of disassembler
class Disassembler
{

public:
    Disassembler();
    QString Discompile(QString& hex_machinecode);//This function is to discompile the machinecode
    QString LoadtoBin(QString& machine_code);//This function is to discompile the machinecode
    QString LoadtoCoe(QString& hex_machinecode);//This function is to discompile the machinecode
    QStringList Preprocess(QString&  machine_code);//This function is used to  preprocess the machinecode
    const QString Decode_mips( const QString& hex_machinecode);//This function is used to decode the hex_machinecode
    const QString Decode_Reg( const QString& reg);//This function is used to decode the register's address
    const QString Decode_Shamt(const QString& shamt);//This function is used to decode the shamt
    const QString Decode_Immediate(const QString& immediate);//This function is used to decode the immediate number
    const QString Decode_Address(const QString& address);//This function is used to decode the target address
    const QString Decode_Branch(const QString& branch);//This function is used to decode the branch instruction

private:
    QMap<QString, QString> reg_name;//The register's name and address
    QStringList mips_list;//The output mips language
};

#endif // DISASSEMBLER_H
