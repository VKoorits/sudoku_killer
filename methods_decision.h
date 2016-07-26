#include"utility_functions.h"

//������� �������
char search_clear_numbers(int *sudoku, int *variants, int *count_zero){//����� ��������
    char returner='f';
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            if(*(variants+i*90+j*10)==1){
                //���� ����� ��������� ��� �����
                *(sudoku+i*9+j)=*(variants+i*90+j*10+1);
                *(variants+i*90+j*10)=0;
                searched_number(sudoku, variants, i, j, *(variants+i*90+j*10+1), count_zero);//������������ � ������ ������� ���������� �����
                returner='t';
            }else if(*(variants+i*90+j*10)==0 && *(sudoku+i*9+j)==0){
                //��� ���������, �� ������ �����
                return 'e';
            }
    return returner;
}
char search_hidden_clear_numbers(int *sudoku, int *variants, int *count_zero){//����� ������� ��������
    char returner='f';
    int count_this_num_in=0;//���������� ����� poisk � ������ ������� ��������
    //���� count_this_num_in == 1, �� ���� ������� ��������
    int x,y;//x=i(string); y=j(column)

    for(int poisk=1; poisk <=9; poisk++){//����� ������� �������� �� 1 �� 9
        //�������� ������
        for(int i=0; i<9; i++){
            if(!search_in_arr(sudoku+i*9, poisk, 0, 1)){//���� � ������ ��� ��� ����� poisk �� ������������� i-��� ������
                count_this_num_in=0;
                for(int j=0; j<9; j++)
                    if(*(sudoku+i*9+j)==0 && search_in_arr(variants+i*90+j*10, poisk, 1, 1)){//���� �  i j ������ ����� ��������� poisk
                        count_this_num_in++;
                        x=i;
                        y=j;
                    }
                if(count_this_num_in==1){//���� ��� ����� ����� ��������� ������ � ���� ����� ������, �� ������
                    *(sudoku+x*9+y)=poisk;
                    returner='t';
                    searched_number(sudoku, variants, x, y, poisk, count_zero);
                }else if(count_this_num_in==0)
                    return 'e';//� ������� ��� ������ ����� � ��� ������ ������ ���������
            }
        }//end string

        //�������� �������
        for(int j=0; j<9; j++){
            if(!search_in_arr(sudoku+j, poisk, 0, 9)){//���� � ������ ��� ��� ����� poisk �� ������������� i-��� ������
                count_this_num_in=0;
                for(int i=0; i<9; i++)
                    if(*(sudoku+i*9+j)==0 && search_in_arr(variants+i*90+j*10, poisk, 1, 1)){//���� �  i j ������ ����� ��������� poisk
                        count_this_num_in++;
                        x=i;
                        y=j;
                    }
                if(count_this_num_in==1){//���� ��� ����� ����� ��������� ������ � ���� ����� ������, �� ������
                    *(sudoku+x*9+y)=poisk;
                    returner='t';
                    searched_number(sudoku, variants, x, y, poisk, count_zero);
                }else if(count_this_num_in==0)
                    return 'e';//� ������ ��� ������ ����� � ��� ������ ������ ���������
            }
        }//end column

        //�������� �������
        for(int i=0; i<3; i++)//������� ������
            for(int j=0; j<3; j++){//������� �������
                count_this_num_in=0;
                for(int a=0; a<3; a++)//��������� ������
                    for(int b=0; b<3; b++)//��������� �������
                        if(*(sudoku+(i*3+a)*9+(j*3+b))==0 && search_in_arr(variants+(i*3+a)*90+(j*3+b)*10, poisk, 1, 1)){//���� � ������ ����� ��������� poisk
                            count_this_num_in++;
                            x=i*3+a;
                            y=j*3+b;
                        }
                if(count_this_num_in==1){//���� ��� ����� ����� ��������� ������ � ���� ����� �������, �� ������
                    *(sudoku+x*9+y)=poisk;
                    returner='t';
                    searched_number(sudoku, variants, x, y, poisk, count_zero);
                }
            }//end box
    }//end poisk
    return returner;
}
char search_candidate_in_square(int *sudoku, int *variants){//����� ���������� � ��������
    char returner='f';
    int count_place=0, num_square[3]={-1,-1,-1};

    for(int poisk=1; poisk<10; poisk++){
    //int poisk=4, i=2;
        //����� ���������� �� �������
        for(int i=0; i<9; i++){
            if(!search_in_arr(sudoku+i*9, poisk, 0, 1)){
                count_place=0;
                num_square[0]=num_square[1]=num_square[2]=-1;
                for(int j=0; j<9; j++)
                    if(search_in_arr(variants+i*90+j*10, poisk, 1, 1)){
                        count_place++;
                        if(count_place==4)//4 ����� ������ �� ����������
                            break;
                        num_square[count_place-1]=i*3+j;
                    }
                if(count_place!=4 && count_place>1 && num_square[0]==num_square[1] && (num_square[1]==num_square[2] || num_square[2]==-1)){
                    //���� ��� ��������� � ����� �������� �� ������� ���������� poisk �� ��������� ������
                    for(int x=(num_square[0]/3)*3; x<(num_square[0]/3)*3+3; x++)
                        for(int y=(num_square[0]%3)*3; y<(num_square[0]%3)*3+3; y++)
                            if(x!=i && *(sudoku+x*9+y)==0){
                                delete_from_arr(variants+x*90+y*10, poisk);
                                returner='t';
                            }
                }
            }
        }//end string

        //����� ���������� �� ��������
        for(int j=0; j<9; j++){
            if(!search_in_arr(sudoku+j, poisk, 0, 9)){
                count_place=0;
                num_square[0]=num_square[1]=num_square[2]=-1;
                for(int i=0; i<9; i++)
                    if(search_in_arr(variants+i*90+j*10, poisk, 1, 1)){
                        count_place++;
                        if(count_place==4)//4 ����� ������ �� ����������
                            break;
                        num_square[count_place-1]=i*3+j;
                    }
                if(count_place!=4 && count_place>1 && num_square[0]==num_square[1] && (num_square[1]==num_square[2] || num_square[2]==-1)){
                    //���� ��� ��������� � ����� �������� �� ������� ���������� poisk �� ��������� ������
                    for(int x=(num_square[0]/3)*3; x<(num_square[0]/3)*3+3; x++)
                        for(int y=(num_square[0]%3)*3; y<(num_square[0]%3)*3+3; y++)
                            if(y!=j && *(sudoku+x*9+y)==0){
                                delete_from_arr(variants+x*81+y*9, poisk);
                                returner='t';
                            }
                }
            }
        }//end column

        //����� ���������� � �������
        for(int i=0; i<3; i++)//������� ������
            for(int j=0; j<3; j++){//������� �������
                count_place=0;
                int coordinate[2][3]={{-1,-1,-1},{-1,-1,-1}};//coordinate[0]->i; coordinate[1]->j
                for(int a=0; a<3; a++)//��������� ������
                    for(int b=0; b<3; b++)//��������� �������
                        if(*(sudoku+(i*3+a)*9+(j*3+b))==0 && search_in_arr(variants+(i*3+a)*90+(j*3+b)*10, poisk, 1, 1)){//���� � ������ ����� ��������� poisk
                            count_place++;
                            if(count_place<4){//4 ����� ������ �� ����������
                            coordinate[0][count_place-1]=i*3+a;
                            coordinate[1][count_place-1]=j*3+b;
                            }
                        }
                if(count_place<4 && count_place>1){//���� ��� ����� ����� ��������� ������ � ���� ������/������� �������
                    if(coordinate[0][0]==coordinate[0][1] && (coordinate[0][1]==coordinate[0][2] || coordinate[0][2]==-1)){//������ � ����� ������
                        for(int x=0; x<9; x++)
                            if(x!=coordinate[1][0] && x!=coordinate[1][1] && (x!=coordinate[1][2] || coordinate[1][2]==-1))
                                if(search_in_arr(variants+coordinate[0][0]*90+x*10, poisk, 1, 1)){
                                    delete_from_arr(variants+coordinate[0][0]*90+x*10, poisk);
                                    returner='t';
                                }
                                //cout << "� �������" << coordinate[0][0]/3 << " " <<  coordinate[1][0]/3 <<  "  � ������ " << coordinate[0][0] << " ��������� ���� " << poisk   << "�����������"<< endl;
                    }else if(coordinate[1][0]==coordinate[1][1] && (coordinate[1][1]==coordinate[1][2] || coordinate[1][2]==-1)){
                        for(int x=0; x<9; x++)
                            if(x!=coordinate[0][0] && x!=coordinate[0][1] && (x!=coordinate[0][2] || coordinate[0][2]==-1))
                                if(search_in_arr(variants+x*90+coordinate[1][0]*10, poisk, 1, 1)){
                                    delete_from_arr(variants+x*90+coordinate[1][0]*10, poisk);
                                    returner='t';
                                }
                                //cout << "� �������" << coordinate[0][0]/3 << " " <<  coordinate[1][0]/3 <<  "  � ������� " << coordinate[1][0] << " ��������� ���� " << poisk << endl;

                    }
                }
            }//end box

    }//end poisk
    return returner;
}

void delete_for_hidden_pair(const int cn, int *variants, const int *information, const int *combo, char &returner){//�������� ���������� �� ������� ����


    int count_number_in_arr=0;
    int count_xy_in_arr=0;
    int inf_for_del[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    for(int n=0; n<cn; n++){//������������� ��� ����� �� ����������

        inf_for_del[count_xy_in_arr]=*(combo+n);
        count_xy_in_arr+=1;

        if(*(information+10*(*(combo+n)-1))>cn)
            return;

        for(int k=1; k<=*(information+10*(*(combo+n)-1)); k++)//������ xy ��� ������� �����
            for(int b=5; b<10; b++){
                if(*(inf_for_del+b)==*(information+10*(*(combo+n)-1)+k))
                    break;
                else if(*(inf_for_del+b)==-1){
                    *(inf_for_del+b)=*(information+10*(*(combo+n)-1)+k);
                    break;
                }
            }
    }
    /*cout << "inf_for_del" << endl;
    for(int i=0; i<10; i++)
        cout << *(inf_for_del+i) << " ";
    cout << "\n";*/


    if(inf_for_del[cn]==-1 && inf_for_del[cn-1]!=-1 && inf_for_del[5+cn]==-1 && inf_for_del[4+cn]!=-1){
                    //�������� ������ ��������� �� ������ �� �������� ������/��������/����������
                    for(int j=5; j<5+cn; j++){
                        for(int n=1; n<10; n++)
                            if(n!=inf_for_del[0] && n!=inf_for_del[1] && n!=inf_for_del[2] && n!=inf_for_del[3])//���� ����� ������� n
                                if(search_in_arr(variants+inf_for_del[j]*10, n, 1, 1)){
                                    delete_from_arr(variants+inf_for_del[j]*10, n);
                                    returner='t';
                                    //cout << "�������� ������ ��������� �� ������ �� �������� " << cn << "-����" << endl;
                                }
                    }
                }

}
void search_hidden_pair_in_arr(int *variants, char &returner){//����������� ����������
    int counter(0), numbers[9], inf_for_del[10];//
    int information[9][10];//information[number-1][0]->������� ��� ����������� �����, ��������� 4 ������ ��� �������� �������
    int combo[4];//����� ������� ���������� � ����������
    bool sovpadenie[4];

    for(int a=0; a<9; a++){//�������� ���������� �� ������� ������
            for(int b=0; b<10; b++){
                if(b==0)
                    information[a][b]=0;
                else
                information[a][b]=-1;
            }
        }
    for(int j=0; j<9; j++){//��������� ���������� � ����� ������
        for(int k=1; k<=*(variants+j*10); k++){
            information[*(variants+j*10+k)-1][0]+=1;
            information[*(variants+j*10+k)-1/*�������-1*/][information[*(variants+j*10+k)-1][0]/*������ � �����*/]=j;
        }
    }
    for(int k=0; k<9; k++)
        if(information[k][0]!=0){
            numbers[counter]=k+1;
            counter++;
        }

    /*cout << "information " << endl;
    for(int j=0; j<9; j++){
        cout << "����� " << j+1 << "\t" << information[j][0] << "  ";
        for(int k=1; k<10; k++){
            cout << information[j][k] << " ";
        }
        cout << endl;
    }*/

    for(int cn=2; cn<5; cn++){//������ ���������� � ������ cn->���������� ���� � ����������
        for(int a=0; a<=counter-cn; a++){//������ ������� ����� �� ����������
            combo[1]=combo[2]=combo[3]=-1;
            combo[0]=numbers[a];
            for(int b=a+1; b<=counter+1-cn; b++){
                combo[1]=numbers[b];
                if(cn==2){
                    delete_for_hidden_pair(cn, variants, &information[0][0], &combo[0], returner);
                }else{//e��� ������ ������ ��� �������
                    for(int c=b+1; c<=counter+2-cn; c++){
                        combo[2]=numbers[c];
                        if(cn==3)
                            delete_for_hidden_pair(cn, variants, &information[0][0], &combo[0], returner);
                        else{//e��� ������ �������
                            for(int d=c+1; d<=counter+3-cn; d++){
                                combo[3]=numbers[d];
                                delete_for_hidden_pair(cn, variants, &information[0][0], &combo[0], returner);
                                //cout << combo[0] << " and " << combo[1] << " and " << combo[2] << " and " << combo[3]  << endl;
                            }//for d
                        }
                    }//for c
                }
            }//for b
        }//for a
    }//end analiz
}
char test_on_hidden_pair(int *sudoku, int *variants){//������� �����/��������/��������

    char returner='f';
    int copy_variants[9][10];

    for(int i=0; i<9; i++){//������������� ������ ������
        search_hidden_pair_in_arr(variants+90*i, returner);
    }

    for(int j=0; j<9; j++){//��������� ������ �������
        for(int i=0; i<9; i++)//������� �����
            for(int k=0; k<10; k++)
                copy_variants[i][k]=*(variants+90*i+10*j+k);
        search_hidden_pair_in_arr(&copy_variants[0][0], returner);
        for(int i=0; i<9; i++)//��������� ���������
            for(int k=0; k<10; k++)
                *(variants+90*i+10*j+k)=copy_variants[i][k];
    }

    for(int a=0; a<3; a++)
        for(int b=0; b<3; b++){//������������� ������ �������

            for(int x=a*3; x<a*3+3; x++)
                for(int y=b*3; y<b*3+3; y++)
                    for(int k=0; k<10; k++)
                        copy_variants[(x%3)+(y%3)*3][k]=*(variants+90*x+10*y+k);

            search_hidden_pair_in_arr(&copy_variants[0][0], returner);

            for(int x=a*3; x<a*3+3; x++)
                for(int y=b*3; y<b*3+3; y++)
                    for(int k=0; k<10; k++)
                        *(variants+90*x+10*y+k)=copy_variants[(x%3)+(y%3)*3][k];
        }

    return returner;
}

