#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <mem.h>
#include <stdlib.h>
#include <cmath>
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int MAXNUM=1000;

float result_of_coupling[7];

struct a_heap//�洢�ѷַ����ݵĽṹ
{
    double array[MAXNUM];
    int left;
    int right;
    int is_valid[MAXNUM];
}heap;

struct peak//�洢�������ݵĽṹ
{
    double delta;
    float height;
};

peak input[64];
double peak_height_1[64];
double temp_store[1000];


void find_int_ratio(peak*object,int number_of_peaks)//�����������Ϊ���������
{
    int i,temp_store[1000];//��ʱ�洢�ռ����ڴ洢�����ķ�߶�
    double frac_ratio;
    int low_int_ratio,high_int_ratio;


    temp_store[0]=1;//���ݺ˴Ź����ѷַ���ص㣬���ϵķ�����ǿ������1
    temp_store[number_of_peaks-1]=1;//ͬ��
    if(number_of_peaks%2==0)//����ѷַ���ż����
    {
    for(i=1;i<number_of_peaks/2;i++)
    {
        frac_ratio=object[i].height/object[0].height;//�����i����ĸ߶�����Ϸ�ĸ߶ȱ�
        low_int_ratio=floor(frac_ratio);//ȡ������������
        high_int_ratio=ceil(frac_ratio);//ȡ����������ȡ����

        if(frac_ratio-low_int_ratio<0.5)
        {
            temp_store[i]=low_int_ratio;//�������ķ�߶ȴ�����ʱ�洢�ռ�
        }
        else
        {
           if(high_int_ratio-frac_ratio<0.5)
           {
               temp_store[i]=high_int_ratio;//�������ķ�߶ȴ�����ʱ�洢�ռ�
           }
        }

    }

    for(i=0;i<number_of_peaks/2;i++)
    {
        object[i].height=temp_store[i];
        object[number_of_peaks-i-1].height=temp_store[i];//���ݶԳƹ��ɣ����û�����ķ����ȷ�߶���������ȸ߶��滻
    }
    }
    else//����ѷַ���������
    {
      for(i=1;i<(number_of_peaks+1)/2;i++)
    {
        frac_ratio=object[i].height/object[0].height;
        low_int_ratio=floor(frac_ratio);
        high_int_ratio=ceil(frac_ratio);

        if(frac_ratio-low_int_ratio<0.5)
        {
            temp_store[i]=low_int_ratio;
        }
        else
        {
           if(high_int_ratio-frac_ratio<0.5)
           {
               temp_store[i]=high_int_ratio;
           }
        }

    }

    for(i=0;i<(number_of_peaks-1)/2;i++)
    {
        object[i].height=temp_store[i];
        object[number_of_peaks-i-1].height=temp_store[i];
    }
    object[i].height=temp_store[(number_of_peaks-1)/2];
    }


}

bool flag = false;


void analyze(a_heap& object,float frequency)//������������ÿһ��ĺ���
{
    int level_number=1;
    int q=0;
    while(object.left!=object.right)//����ݹ��ѭ��,���������Ĳ���ֻ��һ��Ԫ��ʱ��ֹ
    {

    int i,j,k,length_of_level=object.right-object.left+1,i_for_temp;//�Զ�������һ����в���
    double distance;

    for(i=1;i<=object.right-object.left;i++)//i����������1��ʼ
    {

        memset(temp_store,0,sizeof(double));//���¶��岽��ʱ���Ѵ洢���ڹ�����һ������������ݵ���ʱ�洢�ռ����
        i_for_temp=0;

        for(j=object.left;j<=object.right;j++)
        {
            object.is_valid[j]=0;//���¶��岽��ʱ���Ѳ�������Ԫ������Ϊδ���ʹ�
        }

        j=object.left;//jΪɨ������Ƿ����ļ�����

        distance=object.array[object.left+i]-object.array[object.left];//�̶�i�£������ɨ�貽��


        while(j<=object.right)//�������ƥ�����
        {
            if(object.is_valid[j]==1)
            {
                j++;
                continue;
            }

            for(k=j+i;k<=object.right;)//�̶�j����j�����濪ʼѰ�ҺϷ�λ��
            {
                if(object.is_valid[k]==1)//�ж�k��ָ��Ԫ���Ƿ��ѱ��Ϸ���
                {
                    k++;
                    continue;
                }

                if(object.is_valid[j]==0&&object.is_valid[k]==0&&abs(object.array[k]-object.array[j]-distance)<(distance/10))//����ƥ��
                {
                    object.is_valid[j]=1;
                    object.is_valid[k]=1;//��ƥ�䲽��������Ԫ�غϷ���
                    temp_store[i_for_temp]=(object.array[j]+object.array[k])/2;//�������ڹ�����������һ���Ԫ�أ��浽��ʱ�洢�ռ�temp_store��
                    i_for_temp++;
                    break;
                }
                else
                {
                    k++;//������ƥ��
                    continue;
                }
            }

            j++;

        }

        for(j=object.left;j<=object.right;j++)//�ж϶�������һ���е�Ԫ�صľ����Ƿ�ȫ���Ϸ�
        {

            if(object.is_valid[j]==0)
             break;
        }

        if(j==object.right+1) //��ѡ����i����
        {
            result_of_coupling[q]=distance*frequency;
            q++;
            break;
        }

     }

        object.right=object.left-1;
        object.left=object.right+1-length_of_level/2;//�������������һ������½�

        for(i=object.left,i_for_temp=0;i<=object.right;i++,i_for_temp++)
        {
            object.array[i]=temp_store[i_for_temp];//�������������һ��
        }

        memset(temp_store,0,sizeof(double));

        level_number++;//�������������һ��

    }

}

HINSTANCE hInst;

string SS;

struct RECTS
{
    RECT arect;
};
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;
    RECTS rect_array[6];
    static RECT rect={0,0,1000,150};
    static RECT rect2={0,0,1300,150};
    static RECT rect3={0,0,1300,200};
    string title1="coupling constant/Hz";
    string title2="chemical shift/ppm";

    for(int i=0;i<6;i++)
    {
        rect_array[i].arect={0,0,1000,200+50*i};
    }

    char s[100][100];
    for(int i=0;i<7;i++)
    {
        gcvt(result_of_coupling[i],4,s[i]);
    }

   switch(uMsg)
    {
    case WM_PAINT:

        hdc=BeginPaint(hwndDlg,&ps);

        DrawText(hdc,title1.c_str(),title1.size(),&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        DrawText(hdc,title2.c_str(),title2.size(),&rect2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        DrawText(hdc,s[6],strlen(s[6]),&rect3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        for(int i=0;i<6;i++)
        {
            DrawText(hdc,s[i],strlen(s[i]),&rect_array[i].arect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        EndPaint(hwndDlg,&ps);

        break;

        case WM_NCHITTEST:
             return FALSE;

        case WM_INITDIALOG:

             MessageBox(hwndDlg, "H1-NMR deconvolutor [v 1.0.1]\n <c> 2013 created by CCME Haoran Lei. All rights reserved.", "Welcome", MB_ICONINFORMATION);
             return FALSE;


        case WM_CLOSE:
            MessageBox(hwndDlg, "Thanks for using��", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONINFORMATION);
            EndDialog(hwndDlg, 0);
            flag=true;
            return  TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {

                case IDC_BTN_ADVANCE:
                MessageBox(hwndDlg, "Sorry! This function is not available.", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONERROR);

                    EndDialog(hwndDlg, 0);
                    flag=true;
                    return TRUE;

                case IDC_BTN_QUIT:
                MessageBox(hwndDlg, "Thanks for using��", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONWARNING);

                    EndDialog(hwndDlg, 0);
                    flag=true;
                    return TRUE;


                case IDC_BTN_TEST:
                    MessageBox(hwndDlg, "Deconvolution Starts", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONWARNING);
                    EndDialog(hwndDlg, 0);

                    {
    int i,peaknumber,j,number_of_split,temp;
    float frequency;

    cout<<"Please enter number of peaks"<<endl;
    cin>>peaknumber;//�������
    cout<<endl;

    cout<<"Please enter the freqency of magnetic field sacan��MHz��"<<endl;
    cin>>frequency;//����ɨ��Ƶ��
    cout<<endl;

    cout<<"Please enter the individual chemical shift of each peak��ppm��and ite integrated area size"<<endl;
    for(i=0;i<peaknumber;i++)
    {
        cin>>input[i].delta>>input[i].height;//����ÿ�����λ�ƺ�ǿ�ȣ�����˳���
    }
    cout<<endl;

    find_int_ratio(input,peaknumber);//�����������Ϊ���������

    for(i=0,j=0;i<peaknumber;i++)
    {
        temp=j;
        for(;j<temp+input[i].height;j++)
        {
            peak_height_1[j]=input[i].delta;//��ǿ��Ϊn�ķ�ת��Ϊn��ǿ��Ϊ1�ķ壬��λ��ֵ������һ��˳���
        }
    }

    number_of_split=0;

    for(i=0;i<peaknumber;i++)
    {
        number_of_split+=input[i].height;//����ǿ��Ϊ1�ķ����Ŀ
    }

    j=0;

    for(i=MAXNUM-number_of_split;i<MAXNUM;i++,j++)
    {
        heap.array[i]=peak_height_1[j];//����ײ���λ�����ݴ����������Ҷ�ڵ���
    }
    heap.left=MAXNUM-number_of_split;
    heap.right=MAXNUM-1;


    for(i=0;i<MAXNUM;i++)
    {
        heap.is_valid[i]=0;//����ĳ�ʼ�ж�ֵ��Ϊδ����
    }

    analyze(heap,frequency);//���ع�������������λ�����ݣ��ó�ÿһ���ż�ϳ���

    result_of_coupling[6]=(input[0].delta+input[peaknumber-1].delta)/2;
    cout<<"************************"<<endl<<endl<<endl;

    MessageBox(hwndDlg, "Success!", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONINFORMATION);
    EndDialog(hwndDlg, 0);


        }
            return FALSE;

            }
    }

    return FALSE;

}


int APIENTRY WinMain(HINSTANCE dialogue, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)//����������
{
    hInst = dialogue;

    while(flag==false&&DialogBox(dialogue, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc)==FALSE)
    {
    }
    return 0;

}
