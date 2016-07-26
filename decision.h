#include"methods_decision.h"

//decicion
void podbor(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool);//прототип для reshenie()
void sposobi(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool){
    char a,b,c,d,w='t';
    do{
        a=w;
        w=search_clear_numbers(sudoku, variants, count_zero);
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter)+=1;
            continue;
        }

        b=w;
        w=search_hidden_clear_numbers(sudoku, variants, count_zero);
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+1)+=1;
            continue;
        }

        c=w;
        w=search_candidate_in_square(sudoku, variants);
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+2)+=1;
            continue;
        }else
            break;

        d=w;
        w=test_on_hidden_pair(sudoku, variants);
        if(w=='e')
            return;
        else if(w=='t'){
            *(counter+3)+=1;
            continue;
        }

    }while((a=='t' || b=='t' || c=='t' || d=='t') && *count_zero!=0);//while serve at least one methods

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
        podbor(sudoku, variants, count_zero, count_resheniy, counter, level, boool);
    }
}
void podbor(int *sudoku, int *variants, int *count_zero, long *count_resheniy, int *counter, int *level, bool boool){
    if(*count_resheniy>1)
        return;
    int min_variants=10;
    int x,y;
        //search optimaly cell for insert (cell where mimimum count variants)
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                if(*(sudoku+i*9+j)==0 && *(variants+90*i+10*j)<min_variants){
                    min_variants=*(variants+90*i+10*j);*(variants+90*i+10*j);
                    x=i;
                    y=j;
                }


        for(int num_variant=1; num_variant<=min_variants; num_variant++){
            //copy sudoku for recursive function
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

            //recursion
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

    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            for(int k=0; k<10; k++)
                variants[i][j][k]=0;

    zapolnenie(&sudoku[0][0], &variants[0][0][0], &count_zero);
    if(count_zero>64){
        if(boool)
            cout << "There are few numbers in sudoku (less then 17 ). It`s haven`t decusion" << endl;
        return 1000;
    }
    int counter[6]={0,0,0,0,0, count_zero};
    sposobi(&sudoku[0][0], &variants[0][0][0], &count_zero, &count_resheniy, &counter[0], &level,  boool);

    if(count_resheniy==1){
        if(boool)
            cout << "Your sudoku have one decusion!!!" << endl;
        return level;
    }else{
        if(boool)
            if(count_resheniy==0)
                cout << "It`s haven`t decusion" << endl;
            else
                cout << "It`s haven`t more then one decusion" << endl;
        return 1000;
    }
}
