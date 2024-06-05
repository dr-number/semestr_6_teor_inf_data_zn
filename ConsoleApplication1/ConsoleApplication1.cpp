#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iomanip>

using namespace std;

int main()
{
    setlocale(0, "");

    bool IS_SORT = true;
    bool INIT_FROM_FILE = true;

    const string PATH = "D:\\СИБСТРИН ИНФА\\семестр6\\2324, Теория информации, данные, знания, 12 (экзамен, заоч. (5, 6 сем.) (310а-з, 310з гр.) )\\Лабораторная работа №2\\";
    const string INPUT = "17. Куприн Гранатовый браслет.txt";

    //const string PATH = "D:\\СИБСТРИН ИНФА\\семестр6\\2324, Теория информации, данные, знания, 12 (экзамен, заоч. (5, 6 сем.) (310а - з, 310з гр.))\\Лабораторная работа №3\\";
    //const string INPUT = "7.txt";

    const string INIT_TEXT = "\"Ларионов Никита Юрьевич\" выполняет задание по дисциплине: Теория информации, данные, знания.";

    string pathin = PATH + INPUT; //"input.txt";
    string pathout = PATH + "output_" + INPUT;

    cout << pathin << "\n";

    struct Sym {
    public:
        char symbol;
        int count;
        float frequency;
    public:
        Sym(char _symbol, int _count, float _frequency)  // конструктор объекта
        {
            symbol = _symbol; 
            count = _count;
            frequency = _frequency;
        }
    };

    list<Sym> initList = *new list<Sym>();

    ifstream fin;
    ofstream fout;
    float sumSymbols = 0;

    fin.open(pathin);
    fout.open(pathout);

    int count[256]{};

    if (INIT_FROM_FILE) {
        if (!fin.is_open())
        {
            cout << "Ошибка открытия файла!\n";
        }
        else
        {
            cout << "Файл открыт!\n";
            char ch;
            while (fin.get(ch))
            {
                count[static_cast<int>(ch) + 128]++;
            }
        }
    }
    else {
        for (char ch : INIT_TEXT) {
            count[static_cast<int>(ch) + 128]++;
        }
    }

    int count1[32]{};

    //cout << static_cast<int>('Ё') << endl;
    //cout << static_cast<int>('ё') << endl;

    count1[5] += count[-88 + 128] + \
        count[-72 + 128];

    for (int i = -64 + 128; i < -32 + 128; i++)
    {
        count1[i + 64 - 128] += \
            count[i] + count[i + 32];
        
        sumSymbols += count1[i + 64 - 128];
    }

    cout << "Всего символов в файле: " + to_string(sumSymbols) << endl;

    for (int i = 0; i < 32; i++)
    {

        initList.push_back(*new Sym(static_cast<char>(i - 64), count1[i], count1[i] / sumSymbols));

        //cout << static_cast<char>(i - 64) << \
        //    " " << count1[i] << " " << count1[i]/sumSymbols << endl;
    }

    if (IS_SORT) {
        initList.sort([](const Sym& a, const Sym& b) { return a.count < b.count; }); //Сортировка по количеству символа
        //initList.sort([](const Sym& a, const Sym& b) { return a.frequency < b.frequency; }); //Сортировка по частоте символа
        initList.reverse();
    }


    cout << "Символ" << std::setw(14) << "Количество" << " " << "Частота" << endl;
    for (std::list<Sym>::iterator it = initList.begin(); it != initList.end(); ++it) {
        cout << it->symbol << std::setw(10) << it->count << std::setw(12) << it->frequency << std::setw(6) << endl;
    }
    return 0;
}
