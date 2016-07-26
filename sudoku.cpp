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

    do{//��������� ����
        cout << "\t\t*****������-������******\n\n��� ����������� ������-������. �������� ����� ������:" << endl;
        cout << "1. ��������� ������" << endl;
        cout << "2. ������� ������"  << endl;
        cin >> menu;
        system("cls");
        if(!cin >> menu || (menu!='1' && menu!='2')){
            cin.clear();
            while(cin.get()!='\n');
        }else
            break;
    }while(1);

    if(menu=='1'){//���������
        menu='0';
        do{//level
            cout << "\t\t*****������-������******\n\n��������� ������\n�������� ������� ��������� (�� 1 �� 5)" << endl;
            cout << "��������� ������:\t";
            cin >> menu;
            system("cls");
            if(!cin >> menu || int(menu)>53 || int(menu)<49){
                cin.clear();
                while(cin.get()!='\n');
            }else
                break;
        }while(1);

        generator_sudoku(&sudoku[0][0], count_zero, int(menu)-48);
        cout << "\t\t*****������-������******\n\n";
        cout << "��������������� ������ " << int(menu)-48 << " ������ ��������� " << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\n����� ���������� ������� ������ ������� ����� ������";

        _getch();
        system("cls");

        cout << "\t\t*****������-������******\n\n";
        cout << "��������������� ������ " << int(menu)-48 << " ������ ��������� " << endl;
        write_sudoku(&sudoku[0][0]);
        cout << "\n������������ ������� ����� ������";
        reshenie(&sudoku[0][0], 1);

    }
    else if(menu=='2'){
        menu='0';
        system("cls");
        do{
            cout << "\t\t*****������-������******\n������� ������\n\n����� �������� ������:\n";
            cout << "1. �� �����" << endl;
            cout << "2. � ����������"  << endl;
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
            cout << "\t\t*****������-������******\n������� ������\n\n������� ����� �����:\t";
            char filename[255];
            cin.getline(filename, 255);
            fin.open(filename);
            system("cls");
            if(fin.is_open()){
                read_sudoku(&sudoku[0][0], fin, 'f');

                cout << "\t\t*****������-������******\n������� ������\n\n������ �� �����";
                write_sudoku(&sudoku[0][0]);
                reshenie(&sudoku[0][0], 1);
                break;
            }


            }while(1);
        }else if(menu=='2'){
            cout << "\t\t*****������-������******\n������� ������\n\n���� � ���������� (������� ������ ������ ��� ��������)" << endl;
            read_sudoku(&sudoku[0][0], cin, 'c');
            system("cls");
            cout << "\t\t*****������-������******\n������� ������\n\n��������� ������";
            write_sudoku(&sudoku[0][0]);
            int level;
            level=reshenie(&sudoku[0][0], 1);
            if(level<6)
                cout << "������ ������ ����� " << level << " ������� ���������" << endl;
        }
    }
_getch();
}
