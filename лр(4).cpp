#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;
const int MAX_RECORDS = 100;
const string FILENAME = "library.txt";
struct LibraryRecord
{
    string author;
    string title;
    int year = 0;
    string publisher;
};
// Функция для отображения меню
void displayMenu();
// Функция для добавления записи в библиотеку
void addRecord(LibraryRecord library[], int& numRecords);
// Функция для удаления записи по автору
void deleteRecord(LibraryRecord library[], int& numRecords);
// Функция для редактирования записи по автору
void editRecord(LibraryRecord library[], int numRecords);
// Функция для просмотра всех записей в библиотеке
void viewRecords(const LibraryRecord library[], int numRecords);
// Функция для просмотра записей по указанному автору
void viewByAuthor(const LibraryRecord library[], int numRecords);
// Функция для просмотра записей в указанный период
void viewByPeriod(const LibraryRecord library[], int numRecords);
// Функция для добавления записи в начало библиотеки
void addRecordAtBeginning(LibraryRecord library[], int& numRecords);
// Функция для добавления записи в конец библиотеки
void addRecordAtEnd(LibraryRecord library[], int& numRecords);
// Функция для добавления записи на указанную позицию в библиотеке
void addRecordAtPosition(LibraryRecord library[], int& numRecords);
// Функция для удаления записи по позиции
void deleteRecordByNumber(LibraryRecord library[], int& numRecords);
// Функция для редактирования записи по позиции
void editRecordByNumber(LibraryRecord library[], int numRecords);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LibraryRecord library[MAX_RECORDS];
    int numRecords = 0;
    ifstream inFile(FILENAME);
    if (inFile.is_open())
    {
        while (numRecords < MAX_RECORDS &&
            getline(inFile, library[numRecords].author) &&
            getline(inFile, library[numRecords].title) &&
            inFile >> library[numRecords].year >> ws &&
            getline(inFile, library[numRecords].publisher))
        {
            numRecords++;
        }
        inFile.close();
        cout << "Файл загружен успешно." << endl;
    }
    else
    {
        cout << "Ошибка открытия файла. Возможно, файл будет создан при добавлении записей." << endl;
    }
    int choice;
    do
    {
        displayMenu();
        cout << "Введите ваш выбор: ";
        while (!(cin >> choice) || choice < 1 || choice > 12)
        {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Некорректный ввод. Пожалуйста, выберите правильный пункт меню: ";
        }
        switch (choice)
        {
        case 1:
            addRecord(library, numRecords);
            break;
        case 2:
            deleteRecord(library, numRecords);
            break;
        case 3:
            editRecord(library, numRecords);
            break;
        case 4:
            viewRecords(library, numRecords);
            break;
        case 5:
            viewByAuthor(library, numRecords);
            break;
        case 6:
            viewByPeriod(library, numRecords);
            break;
        case 7:
            addRecordAtBeginning(library, numRecords);
            break;
        case 8:
            addRecordAtEnd(library, numRecords);
            break;
        case 9:
            addRecordAtPosition(library, numRecords);
            break;
        case 10:
            deleteRecordByNumber(library, numRecords);
            break;
        case 11:
            editRecordByNumber(library, numRecords);
            break;
        case 12:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный ввод. Пожалуйста, выберите правильный пункт меню." << endl;
        }
    } while (choice != 12);
    ofstream outFile(FILENAME);
    if (outFile.is_open())
    {
        for (int i = 0; i < numRecords; i++)
        {
            outFile << library[i].author << endl
                << library[i].title << endl
                << library[i].year << endl
                << library[i].publisher << endl;
        }
        outFile.close();
        cout << "Записи сохранены в файл." << endl;
    }
    else
    {
        cout << "Ошибка сохранения файла." << endl;
    }
    return 0;
}
void deleteRecordByPosition(LibraryRecord library[], int& numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста. Нечего удалять." << endl;
        return;
    }
    int position;
    cout << "Введите номер записи, которую вы хотите удалить (от 1 до " << numRecords << "): ";
    cin >> position;
    if (position >= 1 && position <= numRecords)
    {
        for (int i = position - 1; i < numRecords - 1; i++)
        {
            library[i] = library[i + 1];
        }
        numRecords--;
        cout << "Запись удалена успешно." << endl;
    }
    else
    {
        cout << "Некорректный номер записи." << endl;
    }
}
void editRecordByPosition(LibraryRecord library[], int numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста. Нечего изменять." << endl;
        return;
    }
    int position;
    cout << "Введите номер записи, которую вы хотите изменить (от 1 до " << numRecords << "): ";
    cin >> position;
    if (position >= 1 && position <= numRecords)
    {
        cout << "Введите нового автора: ";
        cin.ignore();
        getline(cin, library[position - 1].author);
        cout << "Введите новое название: ";
        getline(cin, library[position - 1].title);
        cout << "Введите новый год издания: ";
        cin >> library[position - 1].year;
        cin.ignore();
        cout << "Введите новое издательство: ";
        getline(cin, library[position - 1].publisher);
        cout << "Запись изменена успешно." << endl;
    }
    else
    {
        cout << "Некорректный номер записи." << endl;
    }
}
void displayMenu()
{
    cout << "\nМеню:" << endl;
    cout << "1. Добавить запись" << endl;
    cout << "2. Удалить запись по автору" << endl;
    cout << "3. Корректировать запись по автору" << endl;
    cout << "4. Просмотреть все записи" << endl;
    cout << "5. Просмотреть записи указанного автора" << endl;
    cout << "6. Просмотреть записи в указанный период" << endl;
    cout << "7. Добавить запись в начало" << endl;
    cout << "8. Добавить запись в конец" << endl;
    cout << "9. Добавить запись на заданную позицию" << endl;
    cout << "10. Удалить запись по номеру" << endl;
    cout << "11. Корректировать запись по номеру" << endl;
    cout << "12. Выход" << endl;
}
void addRecord(LibraryRecord library[], int& numRecords)
{
    if (numRecords < MAX_RECORDS)
    {
        LibraryRecord newRecord;
        cin.ignore();
        cout << "Введите автора: ";
        getline(cin, newRecord.author);
        while (newRecord.author.empty()) {
            cout << "Пожалуйста, введите автора (не может быть пустым): ";
            getline(cin, newRecord.author);
        }
        cout << "Введите название: ";
        getline(cin, newRecord.title);
        while (newRecord.title.empty()) {
            cout << "Пожалуйста, введите название (не может быть пустым): ";
            getline(cin, newRecord.title);
        }
        cout << "Введите год издания: ";
        cin >> newRecord.year;
        cin.ignore();
        cout << "Введите издательство: ";
        getline(cin, newRecord.publisher);
        while (newRecord.publisher.empty()) {
            cout << "Пожалуйста, введите издательство (не может быть пустым): ";
            getline(cin, newRecord.publisher);
        }
        library[numRecords] = newRecord;
        numRecords++;
        cout << "Запись добавлена успешно." << endl;
    }
    else
    {
        cout << "Достигнут максимальный лимит записей. Невозможно добавить больше записей." << endl;
    }
}
void deleteRecord(LibraryRecord library[], int& numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста. Нечего удалять." << endl;
        return;
    }
    cout << "Введите автора записи, которую хотите удалить: ";
    string authorToDelete;
    cin.ignore();
    getline(cin, authorToDelete);
    auto it = find_if(library, library + numRecords, [&](const LibraryRecord& record) {
        return record.author == authorToDelete;
        });
    if (it != library + numRecords)
    {
        std::copy(it + 1, library + numRecords, it);
        numRecords--;
        cout << "Запись удалена успешно." << endl;
    }
    else
    {
        cout << "Запись с указанным автором не найдена." << endl;
    }
}
void editRecordByNumber(LibraryRecord library[], int numRecords)
{
    int number;
    cout << "Введите номер записи, которую вы хотите изменить (от 1 до " << numRecords << "): ";
    cin >> number;
    if (number >= 1 && number <= numRecords)
    {
        cout << "Введите нового автора: ";
        cin.ignore();
        getline(cin, library[number - 1].author);
        cout << "Введите новое название: ";
        getline(cin, library[number - 1].title);
        cout << "Введите новый год издания: ";
        cin >> library[number - 1].year;
        cin.ignore();
        cout << "Введите новое издательство: ";
        getline(cin, library[number - 1].publisher);
        cout << "Запись изменена успешно." << endl;
    }
    else
    {
        cout << "Некорректный номер записи." << endl;
    }
}
void deleteRecordByNumber(LibraryRecord library[], int& numRecords)
{
    int number;
    cout << "Введите номер записи, которую вы хотите удалить (от 1 до " << numRecords << "): ";
    cin >> number;
    if (number >= 1 && number <= numRecords)
    {

        for (int i = number - 1; i < numRecords - 1; i++)
        {
            library[i] = library[i + 1];
        }
        numRecords--;
        cout << "Запись удалена успешно." << endl;
    }
    else
    {
        cout << "Некорректный номер записи." << endl;
    }
}
void editRecord(LibraryRecord library[], int numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста. Нечего изменять." << endl;
        return;
    }
    cout << "Введите автора записи, которую хотите изменить: ";
    string authorToEdit;
    cin.ignore();
    getline(cin, authorToEdit);
    auto it = find_if(library, library + numRecords, [&](const LibraryRecord& record) {
        return record.author == authorToEdit;
        });
    if (it != library + numRecords)
    {
        cout << "Введите нового автора: ";
        getline(cin, it->author);
        cout << "Введите новое название: ";
        getline(cin, it->title);
        cout << "Введите новый год издания: ";
        cin >> it->year;
        cin.ignore();
        cout << "Введите новое издательство: ";
        getline(cin, it->publisher);
        cout << "Запись изменена успешно." << endl;
    }
    else
    {
        cout << "Запись с указанным автором не найдена." << endl;
    }
}
void viewRecords(const LibraryRecord library[], int numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста." << endl;
    }
    else
    {
        cout << "\nЗаписи в библиотеке:" << endl;
        for (int i = 0; i < numRecords; i++)
        {
            cout << i + 1
                << ", Автор: " << library[i].author
                << ", Название: " << library[i].title
                << ", Год издания: " << library[i].year
                << ", Издательство: " << library[i].publisher << endl;
        }
    }
}
void viewByAuthor(const LibraryRecord library[], int numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста." << endl;
        return;
    }
    cout << "Введите автора, чтобы получить список его литературы: ";
    string authorToFind;
    cin.ignore();
    getline(cin, authorToFind);
    cout << "\nЛитература автора " << authorToFind << ":" << endl;
    for (int i = 0; i < numRecords; i++)
    {
        if (library[i].author == authorToFind)
        {
            cout << "Номер записи: " << i + 1
                << ", Название: " << library[i].title
                << ", Год издания: " << library[i].year
                << ", Издательство: " << library[i].publisher << endl;
        }
    }
}
void viewByPeriod(const LibraryRecord library[], int numRecords)
{
    if (numRecords == 0)
    {
        cout << "Библиотека пуста." << endl;
        return;
    }
    int startYear, endYear;
    cout << "Введите начальный год периода: ";
    cin >> startYear;
    cout << "Введите конечный год периода: ";
    cin >> endYear;
    cout << "\nЛитература в период с " << startYear << " по " << endYear << ":" << endl;
    for (int i = 0; i < numRecords; i++)
    {
        if (library[i].year >= startYear && library[i].year <= endYear)
        {
            cout << "Номер записи: " << i + 1
                << ", Автор: " << library[i].author
                << ", Название: " << library[i].title
                << ", Год издания: " << library[i].year
                << ", Издательство: " << library[i].publisher << endl;
        }
    }
}
void addRecordAtBeginning(LibraryRecord library[], int& numRecords)
{
    if (numRecords < MAX_RECORDS)
    {
        LibraryRecord newRecord;
        cin.ignore();
        cout << "Введите автора: ";
        getline(cin, newRecord.author);
        while (newRecord.author.empty()) {
            cout << "Пожалуйста, введите автора (не может быть пустым): ";
            getline(cin, newRecord.author);
        }
        cout << "Введите название: ";
        getline(cin, newRecord.title);
        while (newRecord.title.empty()) {
            cout << "Пожалуйста, введите название (не может быть пустым): ";
            getline(cin, newRecord.title);
        }
        cout << "Введите год издания: ";
        cin >> newRecord.year;
        cin.ignore();
        cout << "Введите издательство: ";
        getline(cin, newRecord.publisher);
        while (newRecord.publisher.empty()) {
            cout << "Пожалуйста, введите издательство (не может быть пустым): ";
            getline(cin, newRecord.publisher);
        }
        for (int i = numRecords; i > 0; i--)
        {
            library[i] = library[i - 1];
        }
        library[0] = newRecord;
        numRecords++;
        cout << "Запись добавлена успешно в начало." << endl;
    }
    else
    {
        cout << "Достигнут максимальный лимит записей. Невозможно добавить больше записей." << endl;
    }
}
void addRecordAtEnd(LibraryRecord library[], int& numRecords)
{
    if (numRecords < MAX_RECORDS)
    {
        LibraryRecord newRecord;
        cin.ignore();

        cout << "Введите автора: ";
        getline(cin, newRecord.author);
        while (newRecord.author.empty()) {
            cout << "Пожалуйста, введите автора (не может быть пустым): ";
            getline(cin, newRecord.author);
        }
        cout << "Введите название: ";
        getline(cin, newRecord.title);
        while (newRecord.title.empty()) {
            cout << "Пожалуйста, введите название (не может быть пустым): ";
            getline(cin, newRecord.title);
        }
        cout << "Введите год издания: ";
        cin >> newRecord.year;
        cin.ignore();
        cout << "Введите издательство: ";
        getline(cin, newRecord.publisher);
        while (newRecord.publisher.empty()) {
            cout << "Пожалуйста, введите издательство (не может быть пустым): ";
            getline(cin, newRecord.publisher);
        }
        library[numRecords] = newRecord;
        numRecords++;
        cout << "Запись добавлена успешно в конец." << endl;
    }
    else
    {
        cout << "Достигнут максимальный лимит записей. Невозможно добавить больше записей." << endl;
    }
}
void addRecordAtPosition(LibraryRecord library[], int& numRecords)
{
    if (numRecords < MAX_RECORDS)
    {
        int position;
        cout << "Введите позицию, на которую вы хотите добавить запись (от 1 до " << numRecords + 1 << "): ";
        cin >> position;
        if (position >= 1 && position <= numRecords + 1)
        {
            LibraryRecord newRecord;
            cin.ignore();
            cout << "Введите автора: ";
            getline(cin, newRecord.author);
            while (newRecord.author.empty()) {
                cout << "Пожалуйста, введите автора (не может быть пустым): ";
                getline(cin, newRecord.author);
            }
            cout << "Введите название: ";
            getline(cin, newRecord.title);
            while (newRecord.title.empty()) {
                cout << "Пожалуйста, введите название (не может быть пустым): ";
                getline(cin, newRecord.title);
            }
            cout << "Введите год издания: ";
            cin >> newRecord.year;
            cin.ignore();
            cout << "Введите издательство: ";
            getline(cin, newRecord.publisher);
            while (newRecord.publisher.empty()) {
                cout << "Пожалуйста, введите издательство (не может быть пустым): ";
                getline(cin, newRecord.publisher);
            }
            for (int i = numRecords; i >= position; i--)
            {
                library[i] = library[i - 1];
            }
            library[position - 1] = newRecord;
            numRecords++;
            cout << "Запись добавлена успешно на позицию " << position << "." << endl;
        }
        else
        {
            cout << "Некорректная позиция." << endl;
        }
    }
    else
    {
        cout << "Достигнут максимальный лимит записей. Невозможно добавить больше записей." << endl;
    }
