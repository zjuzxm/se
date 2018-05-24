#include "assembler.h"

//The map of register's address
Assembler::Assembler()
{    reg_addr = QMap<QString, QString>({
               {"$zero","00000"},
               {"$at","00001"},
               {"$v0","00010"},
               {"$v1","00011"},
               {"$a0","00100"},
               {"$a1","00101"},
               {"$a2","00110"},
               {"$a3","00111"},
               {"$t0","01000"},
               {"$t1","01001"},
               {"$t2","01010"},
               {"$t3","01011"},
               {"$t4","01100"},
               {"$t5","01101"},
               {"$t6","01110"},
               {"$t7","01111"},
               {"$s0","10000"},
               {"$s1","10001"},
               {"$s2","10010"},
               {"$s3","10011"},
               {"$s4","10100"},
               {"$s5","10101"},
               {"$s6","10110"},
               {"$s7","10111"},
               {"$t8","11000"},
               {"$t9","11001"},

               {"$k0","11010"},
               {"$k1","11011"},
               {"$gp","11100"},
               {"$sp","11101"},
               {"$fp","11110"},
               {"$ra","11111"}
            });
     PC=1000;//The initial PC value

}


QString Assembler::GeneratetoBin(QString& mips_code)
{
    machinecode_list.clear();
    //Deal the input mips language
    QListIterator<QString> itr1(Preprocess(mips_code));
    int ins_address = 1000;
    PC=1000;
    //Deal the label
    while (itr1.hasNext())
    {
        QString temp_mips  = itr1.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);

            if(!label.isEmpty()){
                QString mips_address = QString::number(ins_address,10);
                label_addr.insert(label, mips_address);
                QMap<QString, QString>::iterator mi;
            }
            ins_address += 4;
    }
     QListIterator<QString> itr(Preprocess(mips_code));

     //Translate the mips code into machine code
    while (itr.hasNext())
    {
        QString temp_mips  = itr.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);      
        temp_machine = Encode_mips(temp_mips.left(temp_mips.indexOf('#', 0)));
        if (!temp_machine.isEmpty())
        {
            bool ok;
            QString hex_machinecode = QString("%1").arg(temp_machine.toLongLong(&ok,2), 8, 16, QChar('0'));
            QString mips_address = QString::number(PC,10);
            machinecode_list.append(temp_machine);
            PC += 4;
        }
        
    }
    QString machinecode =machinecode_list.join("\n");
    return machinecode;

}

QString Assembler::GeneratetoCoe(QString& mips_code)
{
    machinecode_list.clear();
    //Deal the input mips language
    QListIterator<QString> itr1(Preprocess(mips_code));
    int ins_address = 1000;
    PC=1000;
    //Deal the label
    while (itr1.hasNext())
    {
        QString temp_mips  = itr1.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);

            if(!label.isEmpty()){
                QString mips_address = QString::number(ins_address,10);
                label_addr.insert(label, mips_address);
                QMap<QString, QString>::iterator mi;
            }
            ins_address += 4;
    }
     QListIterator<QString> itr(Preprocess(mips_code));

     //Translate the mips code into machine code
    while (itr.hasNext())
    {
        QString temp_mips  = itr.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);
        temp_machine = Encode_mips(temp_mips.left(temp_mips.indexOf('#', 0)));
        if (!temp_machine.isEmpty())
        {
            bool ok;
            QString hex_machinecode = QString("%1").arg(temp_machine.toLongLong(&ok,2), 8, 16, QChar('0'));
            QString mips_address = QString::number(PC,10);
            machinecode_list.append(hex_machinecode);
            PC += 4;
        }

    }
    QString machinecode =machinecode_list.join("\n");
    return machinecode;

}
QString Assembler::Compile(QString& mips_code)
{
    machinecode_list.clear();
    //Deal the input mips language
    QListIterator<QString> itr1(Preprocess(mips_code));
    int ins_address = 1000;
    //Deal the label
    PC=1000;
    while (itr1.hasNext())
    {
        QString temp_mips  = itr1.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);

            if(!label.isEmpty()){
                QString mips_address = QString::number(ins_address,10);
                label_addr.insert(label, mips_address);
                QMap<QString, QString>::iterator mi;
            }
            ins_address += 4;
    }
     QListIterator<QString> itr(Preprocess(mips_code));

     //Translate the mips code into machine code
    while (itr.hasNext())
    {
        QString temp_mips  = itr.next();
        QString temp_machine,label;
        temp_mips = temp_mips.left(temp_mips.indexOf('#', 0));
        label= temp_mips.left(temp_mips.indexOf(':', 0));
        temp_mips = temp_mips.right(temp_mips.length()-temp_mips.indexOf(':', 0)-1);
        temp_machine = Encode_mips(temp_mips.left(temp_mips.indexOf('#', 0)));
        if (!temp_machine.isEmpty())
        {
            bool ok;
            QString hex_machinecode = QString("%1").arg(temp_machine.toLongLong(&ok,2), 8, 16, QChar('0'));
            QString mips_address = QString::number(PC,10);
            QString final_string = mips_address + " : " + hex_machinecode;
            machinecode_list.append(final_string);
            PC += 4;
        }

    }
    QString machinecode =machinecode_list.join("\n");
    return machinecode;

}
//This function can delete the unused symbol of mips code
QStringList Assembler::Preprocess(QString& mips_code)
{
    mips_code.replace("(","  ");
    mips_code.replace(")","  ");
    mips_code.replace(",","  ");
    mips_code.replace("，","  ");
    QStringList tokens = mips_code.split('\n');
    return tokens;
}

//This function can encode one mips code
const QString Assembler:: Encode_mips(const QString& temp_mips)
{
    if (temp_mips.isEmpty())
        return "";
    QString machineCode;
    QStringList tokens = temp_mips.split(QRegExp("(\\s|,)"), QString::SkipEmptyParts);
    if(tokens.at(0)=="add"){
        machineCode = "000000" + Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + "00000100000";
    }
    else if(tokens.at(0)=="sub"){
        machineCode = "000000"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + "00000100010";
    }
    else if(tokens.at(0)=="and"){
        machineCode = "000000"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + "00000100100";
    }
    else if(tokens.at(0)=="or"){
        machineCode = "000000"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + "00000100101";
    }
    else if(tokens.at(0)=="slt"){
        machineCode = "000000"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + "00000101010";
    }
    else if(tokens.at(0)=="sll"){
        machineCode = "00000000000"+Encode_Reg(tokens.at(1)) + Encode_Reg(tokens.at(2)) + Encode_Shamt(tokens.at(3)) + "000000";
    }
    else if(tokens.at(0)=="srl"){
        machineCode = "00000000000"+Encode_Reg(tokens.at(1)) + Encode_Reg(tokens.at(2)) + Encode_Shamt(tokens.at(3)) + "000010";
    }
    else if(tokens.at(0)=="lw"){
        machineCode = "100011"+Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(2));
    }
    else if(tokens.at(0)=="sw"){
         machineCode = "101011"+Encode_Reg(tokens.at(3)) + Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(2));
    }
    else if(tokens.at(0)=="addi"){
         machineCode = "001000"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(3));
    }
    else if(tokens.at(0)=="ori"){
         machineCode = "001101"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(3));
    }
    else if(tokens.at(0)=="lui"){
         machineCode = "00111100000"+Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(3));
    }
    else if(tokens.at(0)=="slti"){
         machineCode = "001010"+Encode_Reg(tokens.at(2)) + Encode_Reg(tokens.at(1)) + Encode_Immediate(tokens.at(3));
    }
    else if(tokens.at(0)=="j"){
         machineCode = "000010"+Encode_Address(tokens.at(1));
    }
    else if(tokens.at(0)=="jal"){
         machineCode = "000011"+Encode_Address(tokens.at(1));
    }
    else if(tokens.at(0)=="jr"){
         machineCode = "000000"+Encode_Reg(tokens.at(1))+"000000000000000001000";
    }
    else if(tokens.at(0)=="beq"){
         machineCode = "000100"+Encode_Reg(tokens.at(1))+Encode_Reg(tokens.at(2))+Encode_Branch(tokens.at(3));
    }
    else if(tokens.at(0)=="bne"){
        machineCode = "000101"+Encode_Reg(tokens.at(1))+Encode_Reg(tokens.at(2))+Encode_Branch(tokens.at(3));
    }
    else{
        machineCode = "sytax error";
    }
  
    return machineCode;
}

//The function can convert the register to the address
const QString Assembler::Encode_Reg(const QString& reg){
    QMap<QString, QString>::iterator mi;
     mi =reg_addr.find(reg);
    QString machinecode = QString(mi->data());
    return  machinecode;
}

//The function can convert the shamt to the machincode
const QString Assembler::Encode_Shamt(const QString& shamt)
{
    qDebug() << QString("%1").arg(shamt.toInt(), 5, 2, QChar('0'));
    QString machinecode = QString("%1").arg(shamt.toLongLong(), 5, 2, QChar('0'));
    return  machinecode;
}

//The function can turn the immediate number to the machine code
const QString  Assembler::Encode_Immediate(const QString& immediate){
    QString machinecode;
    QString reverse;
    long long  complement;
    if(immediate[0]=='-'){
       reverse = immediate.right(immediate.length()-1);      
       complement = 0X10000 - reverse.toLongLong();
       machinecode = QString("%1").arg(complement, 16, 2, QChar('0'));
    }
    else{
        machinecode = QString("%1").arg(immediate.toLongLong(), 16, 2, QChar('0'));
    }
    return machinecode;

}

//The function can encode the j instruction's target address
const QString Assembler::Encode_Address(const QString& address)
{
     QString machinecode ;
    if(address[0]>='0'&&address[0]<='9'){
         machinecode = QString("%1").arg(address.toLongLong()/4, 26, 2, QChar('0'));
    }
    else {
        QMap<QString, QString>::iterator mi;
         mi =label_addr.find(address);
        QString label_address = QString(mi->data());
        machinecode = QString("%1").arg(label_address.toLongLong()/4, 26, 2, QChar('0'));
        }


    return machinecode;
}

//The function can encode the branch's address
const QString  Assembler::Encode_Branch(const QString& branch){

    QString machinecode;
    QString reverse;
    long long  complement;
    if(branch[0]=='-'){
       reverse = branch.right(branch.length()-1);
       complement = 0X10000 - reverse.toLongLong()/4;
       machinecode = QString("%1").arg(complement, 16, 2, QChar('0'));
    }
    else if(branch[0]>='0'&&branch[0]<='9'){
        machinecode = QString("%1").arg(branch.toLongLong()/4, 16, 2, QChar('0'));
    }
    else {
        QMap<QString, QString>::iterator mi;
         mi =label_addr.find(branch);
        QString label_address = QString(mi->data());
        long long  offset = (label_address.toLongLong() - PC -4)/4;
        if(offset>=0){
            machinecode = QString("%1").arg(offset, 16, 2, QChar('0'));
        }
        else{
             complement = 0X10000 + offset;
            machinecode = QString("%1").arg(complement, 16, 2, QChar('0'));
        }

    }
    return machinecode;
}




