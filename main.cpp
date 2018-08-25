#include <QCoreApplication>
#include <QtXlsx>
#include "smtp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //    Widget w;
    //    w.show();


    QXlsx::Document xlsx;
    if(!xlsx.selectSheet("station"))
    {
        xlsx.addSheet("station");
    }
    xlsx.write(1, 1, "x");
    xlsx.write(1,2, "y");
    xlsx.write(1, 3, "v");
    xlsx.write(2, 1, 100);
    xlsx.write(2,2, 100);
    xlsx.write(2, 3, 20);
    xlsx.saveAs("./agv.xlsx");

    //读取
    QXlsx::Document xlsxx("./agv.xlsx");
    xlsx.selectSheet("station");
    QXlsx::CellRange range;
    range = xlsxx.dimension();
    int rowCount = xlsxx.dimension().rowCount();//获取行数
    for(int i = 1; i < rowCount + 1; i ++)
    {
        qDebug()<<QString::number(i)<<xlsxx.cellAt(i,1)->value().toString()<<xlsxx.cellAt(i,2)->value().toString()
               <<xlsxx.cellAt(i,3)->value().toString();
    }


    int i =0;

    Smtp smtp("*******@163.com","hahaha123");

    smtp.send("***********@gmail.com","测试邮件","这是一封测试邮件123^_^");

    //    exit(0);


    return a.exec();
    //    return 0;
}
