#include"methods_decision.h"

//решение
void podbor(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool);//прототип для reshenie()
void sposobi(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool){
    char a,b,c,d,w='t';
    do{
        //одиночки
        a=w;
        w=search_clear_numbers(sudoku, variants, count_zero);
        //cout << "clear " << w << endl;
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter)+=1;
            continue;
        }

        //скрытые одиночки
        b=w;
        w=search_hidden_clear_numbers(sudoku, variants, count_zero);
        //cout << "hidden_clear ******* " << w << endl;
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+1)+=1;
            continue;
        }

        //поиск по областям
        c=w;
        w=search_candidate_in_square(sudoku, variants);
        //cout << "candidate_in_square ************** " << w << endl;
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+2)+=1;
            continue;
        }else
            break;

        //cкрытые пары
        d=w;
        w=test_on_hidden_pair(sudoku, variants);
        //cout << "hidden_pair  ************************************ " << w << endl;
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+3)+=1;
            continue;
        }

    }while((a=='t' || b=='t' || c=='t' || d=='t') && *count_zero!=0);

    if(*count_zero==0){
        *count_resheniy+=1;
        if(*count_resheniy==1){
            if(boool){
                write_sudoku(sudoku);

            }
            if(counter[5]<=51 && counter[0]<=7 && counter[1]+counter[2]+counter[3]+counter[4]==0)
                *level=1;
            else if(counter[0]<=10 && counter[1]+counter[2]+counter[3]+counter[4]==0)
                *level=2;
            else if(counter[2]+counter[3]<=3 && counter[4]==0)
                *level=3;
            else if(counter[4]<3)
                *level=4;
            else
                *level=5;
        }
        return;
    }else{
        *(counter+4)+=1;
        //cout << "podbor podbor podbor podbor ******************************" << endl;
        podbor(sudoku, variants, count_zero, count_resheniy, counter, level, boool);
    }
}
void podbor(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool){
    if(*count_resheniy>1)
        return;
    int min_variants=10;
    int x,y;
        //поиск места для вставки с наименьшим количеством вариантов
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                if(*(sudoku+i*9+j)==0 && *(variants+90*i+10*j)<min_variants){
                    min_variants=*(variants+90*i+10*j);*(variants+90*i+10*j);
                    x=i;
                    y=j;
                }


        for(int num_variant=1; num_variant<=min_variants; num_variant++){
            //создание судоку, которое можно изменять этой подфункции
            int temp_sudoku[9][9];
            for(int i=0; i<9; i++)
                for(int j=0; j<9; j++)
                    temp_sudoku[i][j]=*(sudoku+i*9+j);

            int temp_variants[9][9][10];
            for(int i=0; i<9; i++)
                for(int j=0; j<9; j++)
                    for(int k=0; k<10; k++)
                        temp_variants[i][j][k]=*(variants+i*90+j*10+k);

            int lev[6]={*(counter),*(counter+1),*(counter+2),*(counter+3),*(counter+4), *(counter+5)};

            int temp_count_zero=*count_zero;
            temp_sudoku[x][y]=*(variants+90*x+10*y+num_variant);
            searched_number(&temp_sudoku[0][0], &temp_variants[0][0][0], x, y, *(variants+90*x+10*y+num_variant), &temp_count_zero);

            //вызов рекурсии подбор вариантов

            sposobi(&temp_sudoku[0][0], &temp_variants[0][0][0], &temp_count_zero, count_resheniy, &lev[0], level, boool);
        }

}

int reshenie(int *sudoku_vxod, bool boool){
    int sudoku[9][9];
    int level=-1;
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            sudoku[i][j]=*(sudoku_vxod+i*9+j);
    int count_zero=0;
    long count_resheniy=0;
    int count_variants=9,line=-1,column=-1;

    int variants[9][9][10];
    //обнуление элементов массива вариантов
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            for(int k=0; k<10; k++)
                variants[i][j][k]=0;

    zapolnenie(&sudoku[0][0], &variants[0][0][0], &count_zero);
    if(count_zero>64){
        if(boool)
            cout << "Судоку имеет меньше 17 подсказок. Невозможно решить единственным способом" << endl;
        return 1000;
    }
    int counter[6]={0,0,0,0,0, count_zero};
    sposobi(&sudoku[0][0], &variants[0][0][0], &count_zero, &count_resheniy, &counter[0], &level,  boool);

    if(count_resheniy==1){
        if(boool)
            cout << "Судоку имеет единственное решение" << endl;
        return level;
    }else{
        if(boool)
            if(count_resheniy==0)
                cout << "Cудоку не имеет решний" << endl;
            else
                cout << "Судоку нельзя решить единственным способом" << endl;
        return 1000;
    }
}
