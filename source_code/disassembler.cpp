#include "disassembler.h"

//The constructor of disassembler
Disassembler::Disassembler()
{   //The register name and address
    reg_name = QMap<QString, QString>({
                                           {"00000","$zero"},
                                           {"00001","$at"},
                                           {"00010","$v0"},
                                           {"00011","$v1"},
                                           {"00100","$a0"},
                                           {"00101","$a1"},
                                           {"00110","$a2"},
                                           {"00111","$a3"},
                                           {"01000","$t0"},
                                           {"01001","$t1"},
                                           {"01010","$t2"},
                                           {"01011","$t3"},
                                           {"01100","$t4"},
                                           {"01101","$t5"},
                                           {"01110","$t6"},
                                           {"01111","$t7"},
                                           {"10000","$s0"},
                                           {"10001","$s1"},
                                           {"10010","$s2"},
                                           {"10011","$s3"},
                                           {"10100","$s4"},
                                           {"10101","$s5"},
                                           {"10110","$s6"},
                                           {"10111","$s7"},
                                           {"11000","$t8"},
                                           {"11001","$t9"},
                                           {"11010","$k0"},
                                           {"11011","$k1"},
                                           {"11100","$gp"},
                                           {"11101","$sp"},
                                           {"11110","$fp"},
                                           {"11111","$ra"}
            });

}

//This function can convert the machine code to the mips code
QString Disassembler::Discompile(QString& hex_machinecode)
{
    mips_list.clear();
    QListIterator<QString> itr(Preprocess(hex_machinecode));
    while (itr.hasNext())
    {
        QString temp_machinecode  = itr.next();
        bool ok;
        QString std_machine = temp_machinecode.right(temp_machinecode.length()-temp_machinecode.indexOf(':', 0)-1);
        std_machine = std_machine.replace(" ","");
        QString temp_machinecode2 = QString("%1").arg(std_machine.toLongLong(&ok,16), 32, 2, QChar('0'));
        QString temp_mips ;
        temp_mips = Decode_mips(temp_machinecode2);
        if (!temp_mips.isEmpty())
        {
            mips_list.append(temp_mips);
        }

    }
    QString mips_code = mips_list.join("\n");
    return mips_code;
}

QString Disassembler::LoadtoCoe(QString& hex_machinecode)
{
    mips_list.clear();
    QListIterator<QString> itr(Preprocess(hex_machinecode));
    while (itr.hasNext())
    {
        QString temp_machinecode  = itr.next();
        bool ok;
        QString std_machine = temp_machinecode.right(temp_machinecode.length()-temp_machinecode.indexOf(':', 0)-1);
        std_machine = std_machine.replace(" ","");
        QString temp_machinecode2 = QString("%1").arg(std_machine.toLongLong(&ok,16), 32, 2, QChar('0'));
        QString temp_mips ;
        temp_mips = Decode_mips(temp_machinecode2);
        if (!temp_mips.isEmpty())
        {
            mips_list.append(temp_mips);
        }

    }
    QString mips_code = mips_list.join("\n");
    return mips_code;
}
QString Disassembler::LoadtoBin(QString& machine_code)
{
    mips_list.clear();
    QListIterator<QString> itr(Preprocess(machine_code));
    while (itr.hasNext())
    {
        QString temp_machinecode  = itr.next();
        bool ok;
        QString std_machine = temp_machinecode.right(temp_machinecode.length()-temp_machinecode.indexOf(':', 0)-1);
        std_machine = std_machine.replace(" ","");
        QString temp_machinecode2 = std_machine;
        QString temp_mips ;
        temp_mips = Decode_mips(temp_machinecode2);
        if (!temp_mips.isEmpty())
        {
            mips_list.append(temp_mips);
        }

    }
    QString mips_code = mips_list.join("\n");
    return mips_code;
}

QStringList Disassembler::Preprocess(QString& machine_code)
{

    QStringList tokens = machine_code.split('\n');
    return tokens;
}

//This function can decode one mips language
const QString Disassembler:: Decode_mips(const QString& temp_machinecode)
{
    if (temp_machinecode.isEmpty())
        return "";

    QString op = temp_machinecode.mid(0,6);
    QString rs = temp_machinecode.mid(6,5);
    QString rt = temp_machinecode.mid(11,5);
    QString rd = temp_machinecode.mid(16,5);
    QString shamt = temp_machinecode.mid(21,5);
    QString funct = temp_machinecode.mid(26);
    QString imm_address = temp_machinecode.mid(16);
    QString target_address = temp_machinecode.mid(6);

    qDebug() << "op" << op << op.length();
    qDebug() << "rs" << rs << rs.length();
    qDebug() << "rt" << rt << rt.length();
    qDebug() << "rt" << rd <<rd.length();
    qDebug() << "shamt" << shamt << shamt.length();
    qDebug() << "funct" << funct << funct.length();
    qDebug() << "imm_address" << imm_address<<imm_address.length();
    qDebug() << "target_address" << target_address<<target_address.length();


    QString mips_code;

    if(op=="000000"&&shamt=="00000"&&funct=="100000"){
        mips_code = "add " + Decode_Reg(rd) + ","+ Decode_Reg(rs) +"," + Decode_Reg(rt);
    }
     else if(op=="000000"&&shamt=="00000"&&funct=="100010"){
         mips_code = "sub " + Decode_Reg(rd) + ","+ Decode_Reg(rs) +"," + Decode_Reg(rt);
     }
     else if(op=="000000"&&shamt=="00000"&&funct=="100100"){
         mips_code = "and " + Decode_Reg(rd) + ","+ Decode_Reg(rs) +"," + Decode_Reg(rt);
     }
     else if(op=="000000"&&shamt=="00000"&&funct=="100101"){
         mips_code = "or " + Decode_Reg(rd) + ","+ Decode_Reg(rs) +"," + Decode_Reg(rt);
     }
     else if(op=="000000"&&shamt=="00000"&&funct=="101010"){
         mips_code = "slt " + Decode_Reg(rd) + ","+ Decode_Reg(rs) +"," + Decode_Reg(rt);
     }
     else if(op=="000000"&&rs=="00000"&&funct=="000000"){
         mips_code = "sll " + Decode_Reg(rd) + ","+ Decode_Reg(rt) +"," + Decode_Shamt(shamt);
     }
     else if(op=="000000"&&rs=="00000"&&funct=="000010"){
         mips_code = "srl " + Decode_Reg(rd) + ","+ Decode_Reg(rt) +"," + Decode_Shamt(shamt);
     }
     else if(op=="100011"){
         mips_code = "lw " + Decode_Reg(rt) + "," + Decode_Immediate(imm_address) + "(" + Decode_Reg(rs) + ")";
     }
     else if(op=="101011"){
         mips_code = "sw " + Decode_Reg(rt) + "," + Decode_Immediate(imm_address) + "(" + Decode_Reg(rs) + ")";
     }
     else if(op=="001000"){
         mips_code = "addi " + Decode_Reg(rt) + "," + Decode_Reg(rs) + "," + Decode_Immediate(imm_address) ;
     }
     else if(op=="001101"){
         mips_code = "ori " + Decode_Reg(rt) + "," + Decode_Reg(rs) + "," + Decode_Immediate(imm_address) ;
     }
     else if(op=="001111"&&rs=="00000"){
         mips_code = "lui " + Decode_Reg(rt) + "," +  Decode_Immediate(imm_address) ;
     }
     else if(op=="001010"){
         mips_code = "slti " + Decode_Reg(rt) + "," + Decode_Reg(rs) + "," + Decode_Immediate(imm_address) ;
     }
     else if(op=="000010"){
         mips_code = "j " + Decode_Address(imm_address) ;
     }
     else if(op=="001101"){
         mips_code = "jal " + Decode_Address(imm_address) ;
     }
     else if(op=="000000"&&rt=="00000"&&rd=="00000"&&shamt=="00000"&&funct=="001000"){
         mips_code = "jr " + Decode_Reg(rs);
     }
     else if(op=="000100"){
         mips_code = "beq " + Decode_Reg(rs) + "," + Decode_Reg(rt) + "," + Decode_Branch(imm_address) ;
     }
     else if(op=="001101"){
         mips_code = "bne " + Decode_Reg(rs) + "," + Decode_Reg(rt) + "," + Decode_Branch(imm_address) ;
     }
    else {
        mips_code = "error";
    }
    return mips_code;
}
//This function can convert machine code to register
const QString Disassembler::Decode_Reg(const QString& reg){
    QMap<QString, QString>::iterator mi;
     mi =reg_name.find(reg);

    QString mipscode = QString(mi->data());
    qDebug() << mipscode;
    return  mipscode;
}
//This function can convert the machine code to mips shamt
const QString Disassembler::Decode_Shamt(const QString& shamt)
{

    bool ok;
    int mips_shamt = shamt.toInt(&ok,2);
    QString mipscode = QString::number(mips_shamt,10);
    qDebug() << "mipscode" <<mipscode;
    return  mipscode;
}

//This function can convert the machine code to mips immediate number
const QString  Disassembler::Decode_Immediate(const QString& immediate){
    bool ok;
    QString mipscode;
    long long  mips_shamt = immediate.toLongLong(&ok,2);
    long long reverse;
    if(immediate[0]=='1'){
        reverse = 0X10000 - mips_shamt;
        qDebug() << "reverse" <<reverse;
        mipscode = "-" + QString::number(reverse,10);
    }
    else{
     mipscode = QString::number(mips_shamt,10);
    }
    qDebug() << "mipscode" <<mipscode;
    return  mipscode;
}

//This function can convert the machine code to the mips address
const QString Disassembler::Decode_Address(const QString& address)
{
    bool ok;
    long long mips_address = address.toLongLong(&ok,2)*4;
    QString mipscode = QString::number(mips_address,10);
    qDebug() << "mipscode" <<mipscode;
    return  mipscode;
}

//This function can convert the machine code to the mips branch
const QString  Disassembler::Decode_Branch(const QString& branch){
    bool ok;
    QString mipscode;
    long long mips_branch = branch.toLongLong(&ok,2);
    int reverse;
    if(branch[0]=='1'){
        reverse = 0X10000 - mips_branch;
        qDebug() << "reverse" <<reverse;
        mipscode = "-" + QString::number(reverse*4,10);
    }
    else{
     mipscode = QString::number(mips_branch*4,10);
    }
    qDebug() << "mipscode" <<mipscode;
    return  mipscode;
}




