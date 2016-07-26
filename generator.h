//������������� ������� �����
void transposing(int *sudoku){//������� ���������� �������� � ��������
    for(int i=8; i>0; i--)
        for(int j=0; j<=i; j++)
            swap(*(sudoku+i*9+j), *(sudoku+j*9+i));
}
void swap_strings_small(int *sudoku){//����� ���� ����� � �������� ������ ������
    int oblast, str1, str2;

    oblast=rand()%3;
    str1=oblast*3+rand()%3;
    do{
        str2=oblast*3+rand()%3;
    }while(str1==str2);

    for(int j=0; j<9; j++)
        swap(*(sudoku+str1*9+j), *(sudoku+str2*9+j));

}
void swap_columns_small(int *sudoku){//����� ���� �������� � �������� ������ ������
    int oblast, col1, col2;

    oblast=rand()%3;
    col1=oblast*3+rand()%3;
    do{
        col2=oblast*3+rand()%3;
    }while(col1==col2);

    for(int i=0; i<9; i++)
        swap(*(sudoku+i*9+col1), *(sudoku+i*9+col2));

}
void swap_strings_area(int *sudoku){//����� ������� �����
    int str1, str2;

    str1=rand()%3;
    do{
        str2=rand()%3;
    }while(str1==str2);

    for(int j=0; j<9; j++)
        for(int k=0; k<3; k++)
            swap(*(sudoku+(str1*3+k)*9+j), *(sudoku+(str2*3+k)*9+j));
}
void swap_columns_area(int *sudoku){//����� ������� ��������
    int col1, col2;

    col1=rand()%3;
    do{
        col2=rand()%3;
    }while(col1==col2);

    for(int i=0; i<9; i++)
        for(int k=0; k<3; k++)
            swap(*(sudoku+i*9+(col1*3+k)), *(sudoku+i*9+(col2*3+k)));
}

void generator_sudoku(int *sudoku, int &count_zero, int level){
    int x, y, temp, count_prosmotrov, this_level, temp_level;
    bool prosmotr[81], work;

    do{
        //���������� ������� �����
        for(int b=0; b<3; b++)// big string
            for(int k=0; k<3; k++){//small string
            x=(b+1)+k*3;
            for(int j=0; j<9; j++){
                if(j==0)
                    *(sudoku+(b*3+k)*9+j)=x;
                else{
                    if(*(sudoku+(b*3+k)*9+j-1)==9)
                        *(sudoku+(b*3+k)*9+j)=1;
                    else
                        *(sudoku+(b*3+k)*9+j)=*(sudoku+(b*3+k)*9+j-1)+1;
                }
            }
        }

        count_prosmotrov=count_zero=0;
        for(int b=0; b<81; b++)
            prosmotr[b]=false;

        for(int i=0; i<20; i++){//�������������
        x=rand()%5;
        switch(x){
            case 0:
                transposing(sudoku);
            break;
            case 1:
                swap_strings_small(sudoku);
            break;
            case 2:
                swap_columns_small(sudoku);
            break;
            case 3:
                swap_strings_area(sudoku);
            break;
            case 4:
                swap_columns_area(sudoku);
            break;
        }
    }
        while(count_prosmotrov!=81){//������������ ��������
            do{//����� ��������� ������
                x=rand()%9;
                y=rand()%9;
            }while(*(sudoku+x*9+y)==0 || prosmotr[x*9+y]==true);

            count_prosmotrov++;
            //cout << count_prosmotrov;
            prosmotr[x*9+y]=true;
            temp=*(sudoku+x*9+y);
            *(sudoku+x*9+y)=0;
            temp_level=reshenie(sudoku, 0);
            if(temp_level>level){//���� ���������� ������ ����� ����� ������� �������, �� ������
                *(sudoku+x*9+y)=temp;
            }else{
                count_zero++;
                this_level=temp_level;
                work=true;
            }
        }

    }while(this_level!=level);
}
