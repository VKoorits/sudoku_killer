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

    do{//start menu
        cout << "\t\t*****SUDOKU KILLER******\n\nHi, it`s sudoku killer. Select a mode of operating:" << endl;
        cout << "1. Create sudoku" << endl;
        cout << "2. decision sudoku"  << endl;
        cin >> menu;
        system("cls");
        if(!cin >> menu || (menu!='1' && menu!='2')){
            cin.clear();
            while(cin.get()!='\n');
        }else
            break;
    }while(1);

    if(menu=='1'){//generating
        menu='0';
        do{//level
            cout << "\t\t*****SUDOKU KILLER******\n\nGenerating sudoku\nSelect difficulty level ( form 1 to 5)" << endl;
            cout << "Difficulty level:\t";
            cin >> menu;
            system("cls");
            if(!cin >> menu || int(menu)>53 || int(menu)<49){
                cin.clear();
                while(cin.get()!='\n');
            }else
                break;
        }while(1);

        generator_sudoku(&sudoku[0][0], count_zero, int(menu)-48);
        cout << "\t\t*****SUDOKU KILLER******\n\n";
        cout << "Is your sudoku a " << int(menu)-48 << " level of difficulty" << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\nIf you want to see the answer for this sudoku pressany key";

        _getch();
        system("cls");

        cout << "\t\t*****SUDOKU KILLER******\n\n";
        cout << "Genrating sudoku  a " << int(menu)-48 << " level of difficulty" << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\nIt`s unique decusion for this sudoku";
        reshenie(&sudoku[0][0], 1);

    }
    else if(menu=='2'){
        menu='0';
        system("cls");
        do{
            cout << "\t\t*****SUDOKU KILLER******\nDecision sudoku\n\nGet sudoku from:\n";
            cout << "1. File" << endl;
            cout << "2. Keyboaerd"  << endl;
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
            cout << "\t\t*****SUDOKU KILLER******\nDecision sudoku\n\nEnter a path to file:\t";
            char filename[255];
            cin.getline(filename, 255);
            fin.open(filename);
            system("cls");
            if(fin.is_open()){
                read_sudoku(&sudoku[0][0], fin, 'f');

                cout << "\t\t*****SUDOKU KILLER******\nDecision sudoku\n\nSudoku from your file:";
                write_sudoku(&sudoku[0][0]);
                reshenie(&sudoku[0][0], 1);
                break;
            }


            }while(1);
        }else if(menu=='2'){
            cout << "\t\t*****SUDOKU KILLER******\nDecision sudoku\n\nEnter from keyboard (Enter strings without space)" << endl;
            read_sudoku(&sudoku[0][0], cin, 'c');
            cout << "\t\t*****SUDOKU KILLER******\nDecision sudoku\n\nEntered sudoku";
            system("cls");
            write_sudoku(&sudoku[0][0]);
            int level;
            level=reshenie(&sudoku[0][0], 1);
            if(level<6)
                cout << "This is a sudoku a " << level << " level of difficulty" << endl;
        }
    }
_getch();
}
