#include<iostream>
#include<fstream>

using namespace std;

//utility functions
void delete_from_arr(int *this_variants, int num){
    if(*(this_variants)!=0){
        int i=1;
        for(i; i<10; i++)
            if(*(this_variants+i)==num){
                *(this_variants+i)=0;
                *(this_variants)=*(this_variants)-1;
                if(i!=9)
                    while(*(this_variants+i+1)!=0){
                        *(this_variants+i)=*(this_variants+i+1);
                        i++;
                    }
                *(this_variants+i)=0;
                break;
            }
    }
}
void searched_number(int *sudoku, int *variants, int i, int j, int num, int *count_zero){
    if(num==0)return;
    *count_zero-=1;
    for(int b=0; b<10; b++)
        *(variants+90*i+10*j+b)=0;
    //viewing a string
    for(int k=0; k<9; k++)
        if(*(sudoku+k*9+j)==0){
            delete_from_arr(variants+k*90+j*10, num);
        }
    //viewing a column
    for(int k=0; k<9; k++)
        if(*(sudoku+i*9+k)==0){
            delete_from_arr(variants+i*90+k*10, num);
        }
    //get coordinate a square 3*3 where is cell (it`s top left angle)
    int x=(i/3)*3;
    int y=(j/3)*3;
    //viewing a square
    for(int a=x; a<x+3; a++)
        for(int b=y; b<y+3; b++)
            if(*(sudoku+a*9+b)==0){
                delete_from_arr(variants+a*90+b*10, num);
            }
}
bool search_in_arr(int *this_variants, int num, int i, int incrementer){
    for(int j=0; j<9; j++)
        if(*(this_variants+j*incrementer+i)==num)//searched elemnt
            return true;
    return false;
}

//input/output information
void read_sudoku(int *sudoku, istream &fin, char file_or_cmd){
    int counter=0;
    int c;
    while(counter!=81){
        c=int(fin.get()-48);
        if(int(c)>=0 && int(c)<=9){
            *(sudoku+counter)=c;
            counter++;
        }
        if(file_or_cmd=='f' && fin.eof())
            break;
    }
}
template <class T>
void write_sudoku(const T *sudoku){
    cout << "\n ----------------------\n";
    for(int i=0; i<9; i++){
        cout << "|";
        for(int j=0; j<9; j++){
            if(*(sudoku +i*9+j)==0)
                cout << "- ";
            else
            cout << *(sudoku +i*9+j) << " ";
            if(j%3==2)
                cout << "| ";
        }
        cout << "\n";
        if(i%3==2)
            cout << " ----------------------\n";
    }
}
void write_variants(const int *variants){
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        cout << "i=" << i << " j=" << j << " " << *(variants+i*90+j*10) << "(";
        if(*(variants+i*90+j*10)<5)
        for(int k=1; k<10; k++){
            if(*(variants+i*90+j*10+k)==0){
                cout << ")\t";
                break;
            }
            cout << *(variants+i*90+j*10+k);
        }
        else
            cout << "       ";
    }
     cout << endl;
}
cout << endl << endl;

}
void zapolnenie(const int *sudoku, int *variants, int *count_zero){
    char choose[9];
    int counter;
    int this_variants[9];
    int x,y;//coordinates top left angle

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){

            //veiw all cell
            if(*(sudoku+i*9+j)==0){
                *count_zero+=1;

                for(int k=0; k<9; k++){
                    choose[k]='o';
                    this_variants[k]=0;
                }
                counter=0;

                //viewng a string
                for(int k=0; k<9; k++)
                    if((sudoku+k*9+j)!=0)
                        choose[*(sudoku+k*9+j)-1]='s';
                //viewing a column
                for(int k=0; k<9; k++)
                    if((sudoku+i*9+k)!=0)
                        choose[*(sudoku+i*9+k)-1]='l';
                //get coordinate a square 3*3 where is cell (it`s top left angle)
                x=(i/3)*3;
                y=(j/3)*3;
                //viewing a square
                for(int a=x; a<x+3; a++)
                    for(int b=y; b<y+3; b++)
                        if(*(sudoku+a*9+b)!=0)
                            choose[*(sudoku+a*9+b)-1]='q';

                //fill variants
                for(int k=0; k<9; k++)
                    if(choose[k]=='o'){
                        counter++;
                        *(variants+i*90+j*10+counter)=k+1;
                    }
                *(variants+i*90+j*10)=counter;
            }
        }
    }
}
