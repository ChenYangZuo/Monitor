#include <QCoreApplication>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QMutex>
#include <QLibrary>
#include <cmath>
#include <complex>

void writeJson();
void readJson();
void initCSV();
void WriteCSV();
void FIR_Lowpass_Filter();
void test_ADD();
void test_List(QList<double>&,double);

QString m_strFilePath;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Hello,World!";

    FIR_Lowpass_Filter();

    qDebug()<<"Goodbye,World!";

    return QCoreApplication::exec();
}

void writeJson(){
    //写入
    QJsonObject obj;
    obj.insert("name",QString("Linus"));
    obj.insert("sex",QString("MAN"));
    obj.insert("IsAlive",QString("false"));
    obj.insert("Comment",QString("yyds"));

    QJsonObject subobj;
    subobj.insert("Father",QString("dad"));
    subobj.insert("Mother",QString("mom"));
    QJsonArray array;
    array.append(QString("1"));
    array.append(QString("2"));
    subobj.insert("Brother",array);

    obj.insert("Family",subobj);

    QJsonDocument doc(obj); //将Json对象，转换成Json文档
    QByteArray json = doc.toJson();

    //写入文件
    QFile file(R"(D:\Project\QtDevelopment\my.json)");
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}

void readJson() {
    //读取文件
    QFile file(R"(D:\Project\QtDevelopment\my.json)");
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(all);//转换成文档对象
    if (doc.isObject()) { //可以不做格式判断，因为，解析的时候已经知道是什么数据了
        QJsonObject obj = doc.object(); //得到Json对象
        QStringList keys = obj.keys(); //得到所有key
        for (int i = 0; i < keys.size(); i++) {
            const QString& key = keys.at(i);
            QJsonValue value = obj.value(key);
            if (value.isBool()) {
                qDebug() << key << ":" << value.toBool();
            } else if (value.isString()) {
                qDebug() << key << ":" << value.toString();
            } else if (value.isDouble()) {
                qDebug() << key << ":" << value.toVariant().toInt();
            } else if (value.isObject()) {
                qDebug() << key << ":";
                QJsonObject subObj = value.toObject();
                QStringList subKeys = subObj.keys();
                for (int k = 0; k < subKeys.size(); ++k) {
                    QJsonValue subValue = subObj.value(subKeys.at(k));
                    if (subValue.isString()) {
                        qDebug() << " " << subKeys.at(k) << ":" << subValue.toString();
                    } else if (subValue.isArray()) {
                        qDebug() << " " << subKeys.at(k);
                        QJsonArray array = subValue.toArray();
                        for (auto && j : array) {
                            qDebug() << " " << j.toString();
                        }
                    }
                }
            }
        }
    }
}

void initCSV(){
    // 我们都放C://CSV文件夹里面吧
    QString strDir = QString("%1/%2").arg(".","CSV");

    // 先检查有没有文件夹存在，没有就让程序创建文件夹先
    QDir dirCSV;
    if (!dirCSV.exists(strDir))
        dirCSV.mkpath(strDir);

    // 使用时间格式进行csv文件命名吧
    m_strFilePath = strDir + "/" + QString("csv%1.csv").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));

    // 因为是文件操作，安全一些都是加个锁
    static QMutex mutex;
    mutex.lock();

    // 判断文件是否不存在
    if (!QFile::exists(m_strFilePath))
    {
        QFile file(m_strFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream in(&file);
            QString strText("");
            // 文件不存在，第一次，我们就给他写个列表名字，这样csv文件打开时候查看的时候就比较清晰
            strText = QString("DateTime,") + QString("Info");
            in << strText << '\n';
            file.close();
        }
    }
    mutex.unlock();
}

void WriteCSV(){
    static QMutex mutex;
    mutex.lock();
    QFile file(m_strFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QString strCurTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
        QTextStream in(&file);
        QString strMessage = QString(u8"%1,%2").arg(strCurTime).arg(rand()%100);
        in << strMessage << '\n';
        file.close();
    }
    mutex.unlock();
}

void FIR_Lowpass_Filter(){
    QList<double> testInput;
    QList<double> buffer;

    QFile file("TEST.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream test(&file);
    for(int i=0;i<1024;i++){
        testInput.append(sin(2 * 3.1415926f * 50 * i / 1000)+sin(2 * 3.1415926f * 200 * i / 1000));
        test << sin(2 * 3.1415926f * 50 * i / 1000)+sin(2 * 3.1415926f * 200 * i / 1000) << '\n';
    }
    file.close();

    //输出原始数据
    file.setFileName("FILTER.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream fil(&file);

    QLibrary myLib("./libfilter_fir.so");
    if(!myLib.load()){
        qDebug() << "load library failed";
        qDebug() << myLib.errorString();
        return;
    }
    typedef double (*FunDef)(QList<double>&,double); //需要声明函数原型的类型
    FunDef filter_fir=(FunDef)myLib.resolve("filter_fir"); //解析DLL中的函数

    for(int i=0;i<testInput.size();i++){
        fil << filter_fir(buffer,testInput.at(i)) << '\n';
    }
    file.close();

    qDebug()<<"Finish";
}

void test_ADD(){
    QLibrary myLib("libADD.dll");
    if(!myLib.load())
    {
        qDebug() << "load library failed";
        qDebug() << myLib.errorString();
        return;
    }

    typedef int (*FunDef)(int,int); //需要声明函数原型的类型
    FunDef L_ADD=(FunDef)myLib.resolve("L_ADD"); //解析DLL中的函数
    if(L_ADD){
        qDebug() << "2 + 3 = " << L_ADD(2, 3);
    }
    else{
        qDebug() << myLib.errorString();
    }
}

void test_List(QList<double>& a, double b){
    a.append(b);
}
