#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <ctype.h>
#include <QDir>
#include <tuple>


std::tuple<int, float*> readFile(QString file_path)
{
    QFile file(file_path);
    int size;
    float* array;

    if(!file.exists())
    {
        qCritical() << "File not found";
        return std::make_tuple(0, nullptr);
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return std::make_tuple(0, nullptr);
    }

    QDataStream stream(&file);

    stream >> size;
    qInfo() << "Successfully loaded array of size:" << size;
    array = (float*) malloc(size*sizeof(float));

    for (int i = 0; i < size; i++) {
        stream >> array[i];
    }

    file.close();
    return std::make_tuple(size, array);
}

void writeFile(QString file_name, float* array, int size)
{
    qInfo() << "Items to write: " << size;
    if (size == 0) {
        qInfo() << "Array is empty.";
        return;
    }

    // Check if directory for reports exists
    if (!QDir("Deserialized_files").exists()) {
        QDir().mkdir("Deserialized_files");
    }
    file_name = "Deserialized_files/" + file_name + ".txt";
    QFile file(file_name);

    // Quit when file is not accessible
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not open file!";
        qCritical() << file.errorString();
        return;
    }
    // Write simulated data into file
    else {
        qInfo() << "Writing into file" << file_name;
        QTextStream stream(&file);

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
    float* array = nullptr;
    int size = 0;

    qInfo() << "**********************************";
    qInfo() << "Available commands:";
    qInfo() << "read <path to file>";
    qInfo() << "write <file name>";
    qInfo() << "quit";
    qInfo() << "**********************************";

    QTextStream stream(stdin);

    while (true) {
        qInfo() << "Enter a command: ";
        QString line = stream.readLine();
        QStringList list = line.split(" ");

        if (list.size() <= 0) {
            break;
        }

        QString command = list.at(0).toUpper();

        if (command == "QUIT") {
            qInfo() << "Quiting...";
            break;
        }

        if (command == "READ") {
            const auto result = readFile(list.at(1));
            size = std::get<int>(result);
            array = std::get<float*>(result);
            qInfo() << "Reading finished.\n";
        }

        if (command == "WRITE") {
            writeFile(list.at(1), array, size);
            qInfo() << "Writing finished.\n";
        }
    }
    return 0;
}
