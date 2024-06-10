#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <ctype.h>
#include <QDir>

float* readFile(QString file_path)
{
    QFile file(file_path);
    int size;
    float* array;

    if(!file.exists())
    {
        qCritical() << "File not found";
        return nullptr;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return nullptr;
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> size;
    qInfo() << "Successfully loaded array of size:" << size;
    array = (float*) malloc(size*sizeof(float));

    for (int i = 0; i < size; i++) {
        stream >> array[i];
    }

    file.close();
    return array;
}

void writeFile(QString file_name, float* array)
{
    int size = sizeof(array);
    qInfo() << "Items to write: " << size;
    if (size == 0) {
        qInfo() << "Array is empty.";
        return;
    }

    // Check if directory for reports exists
    if (!QDir("Deserialized_files").exists()) {
        QDir().mkdir("Deserialized_files");
    }
    file_name = "Deserialized_files/" + file_name;
    QFile file(file_name);

    // Quit when file is not accessible
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "6. Could not open file!";
        qCritical() << file.errorString();
        return;
    }
    // Write simulated data into file
    else {
        qInfo() << "6. Writing into file" << file_name;
        QTextStream stream(&file);
        //stream.setByteOrder(QDataStream::LittleEndian);

        for (int i = 0; i < size; i++) {
            stream << QString::number(array[i]) + ",";
        }

        qInfo() << "File written successfuly";
    }


    file.close();

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    float* array;

    qInfo() << "Available commands:";
    qInfo() << "read <absolute path to file>";
    qInfo() << "write <file name.format>";
    qInfo() << "quit";

    QTextStream stream(stdin);
    int i = 0;
    while (true) {
        qInfo() << "Enter a command: ";
        QString line = stream.readLine();
        QStringList list = line.split(" ");

        if (list.size() <= 0) {
            break;
        }

        QString command = list.at(0).toUpper();

        if (command == "QUIT") {
            break;
        }

        if (command == "READ") {
            array = readFile(list.at(1));
            qInfo() << "Reading - DONE";
        }

        if (command == "WRITE") {
            writeFile(list.at(1), array);
            qInfo() << "Writing - DONE";
        }
        i++;
    }
    //return a.exec();
    return 0;
}
