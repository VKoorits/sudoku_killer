#include<cstdlib>
#include<ctime>
#include<conio.h>

#include "decision.h"
#include "generator.h"

int main(){
setlocale(0, "rus");
    srand(time(NULL));
    rand();
    int sudoku[9][9], count_zero;
    int level_sudoku(5);
    char menu;

    do{//стартовое меню
        cout << "\t\t*****СУДОКУ-МАСТЕР******\n\nвас приветсвует мастер-судоку. Выберите режим работы:" << endl;
        cout << "1. Генерация судоку" << endl;
        cout << "2. Решение судоку"  << endl;
        cin >> menu;
        system("cls");
        if(!cin >> menu || (menu!='1' && menu!='2')){
            cin.clear();
            while(cin.get()!='\n');
        }else
            break;
    }while(1);

    if(menu=='1'){//генерация
        menu='0';
        do{//level
            cout << "\t\t*****СУДОКУ-МАСТЕР******\n\nГенерация судоку\nВыберите уровень сложности (от 1 до 5)" << endl;
            cout << "Сложность судоку:\t";
            cin >> menu;
            system("cls");
            if(!cin >> menu || int(menu)>53 || int(menu)<49){
                cin.clear();
                while(cin.get()!='\n');
            }else
                break;
        }while(1);

        generator_sudoku(&sudoku[0][0], count_zero, int(menu)-48);
        cout << "\t\t*****СУДОКУ-МАСТЕР******\n\n";
        cout << "сгенерированное судоку " << int(menu)-48 << " уровня сложности " << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\nчтобы посмотреть решение судоку нажмите любую кнопку";

        _getch();
        system("cls");

        cout << "\t\t*****СУДОКУ-МАСТЕР******\n\n";
        cout << "сгенерированное судоку " << int(menu)-48 << " уровня сложности " << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\nединственное решение этого судоку";
        reshenie(&sudoku[0][0], 1);

    }
    else if(menu=='2'){
        menu='0';
        system("cls");
        do{
            cout << "\t\t*****СУДОКУ-МАСТЕР******\nРешение судоку\n\nОткда получить судоку:\n";
            cout << "1. Из файла" << endl;
            cout << "2. С клавиатуры"  << endl;
            cin >> menu;
            system("cls");
            if(!cin >> menu || (menu!='1' && menu!='2')){
                cin.clear();
                while(cin.get()!='\n');
            }else
                break;
        }while(1);
        system("cls");
        if(menu=='1'){
            ifstream fin;

            do{
            cout << "\t\t*****СУДОКУ-МАСТЕР******\nРешение судоку\n\nВведите адрес файла:\t";
            char filename[255];
            cin.getline(filename, 255);
            fin.open(filename);
            system("cls");
            if(fin.is_open()){
                read_sudoku(&sudoku[0][0], fin, 'f');

                cout << "\t\t*****СУДОКУ-МАСТЕР******\nРешение судоку\n\nСудоку из файла";
                write_sudoku(&sudoku[0][0]);
                reshenie(&sudoku[0][0], 1);
                break;
            }


            }while(1);
        }else if(menu=='2'){
            cout << "\t\t*****СУДОКУ-МАСТЕР******\nРешение судоку\n\nВвод с клавиатуры (Вводите строки судоку без пробелов)" << endl;
            read_sudoku(&sudoku[0][0], cin, 'c');
            system("cls");
            cout << "\t\t*****СУДОКУ-МАСТЕР******\nРешение судоку\n\nВведенное судоку";
            write_sudoku(&sudoku[0][0]);
            int level;
            level=reshenie(&sudoku[0][0], 1);
            if(level<6)
                cout << "Данное судоку имеет " << level << " уровень сложгости" << endl;

        }

    }

_getch();
}
