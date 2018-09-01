#include <QApplication>
#include <QtXlsx>
#include "widget.h"
#include "smtp.h"

/*
*
*
*使用时，可修改为用waitforreadyread（）来直接发送命令而不是通过信号槽
*
*
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(800,500);
    w.show();


    //    QXlsx::Document xlsx;
    //    if(!xlsx.selectSheet("station"))
    //    {
    //        xlsx.addSheet("station");
    //    }
    //    xlsx.write(1, 1, "x");
    //    xlsx.write(1,2, "y");
    //    xlsx.write(1, 3, "v");
    //    xlsx.write(2, 1, 100);
    //    xlsx.write(2,2, 100);
    //    xlsx.write(2, 3, 20);
    //    xlsx.saveAs("./agv.xlsx");

    //    //读取
    //    QXlsx::Document xlsxx("./agv.xlsx");
    //    xlsx.selectSheet("station");
    //    QXlsx::CellRange range;
    //    range = xlsxx.dimension();
    //    int rowCount = xlsxx.dimension().rowCount();//获取行数
    //    for(int i = 1; i < rowCount + 1; i ++)
    //    {
    //        qDebug()<<QString::number(i)<<xlsxx.cellAt(i,1)->value().toString()<<xlsxx.cellAt(i,2)->value().toString()
    //               <<xlsxx.cellAt(i,3)->value().toString();
    //    }



    return a.exec();
    //    return 0;
}
