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

struct a_heap//存储裂分峰数据的结构
{
    double array[MAXNUM];
    int left;
    int right;
    int is_valid[MAXNUM];
}heap;

struct peak//存储输入数据的结构
{
    double delta;
    float height;
};

peak input[64];
double peak_height_1[64];
double temp_store[1000];


void find_int_ratio(peak*object,int number_of_peaks)//将积分面积化为最简整数比
{
    int i,temp_store[1000];//临时存储空间用于存储化简后的峰高度
    double frac_ratio;
    int low_int_ratio,high_int_ratio;


    temp_store[0]=1;//根据核磁共振裂分峰的特点，边上的峰的相对强度总是1
    temp_store[number_of_peaks-1]=1;//同上
    if(number_of_peaks%2==0)//如果裂分峰是偶数个
    {
    for(i=1;i<number_of_peaks/2;i++)
    {
        frac_ratio=object[i].height/object[0].height;//计算第i个峰的高度与边上峰的高度比
        low_int_ratio=floor(frac_ratio);//取比例的整数部
        high_int_ratio=ceil(frac_ratio);//取比例的向上取整部

        if(frac_ratio-low_int_ratio<0.5)
        {
            temp_store[i]=low_int_ratio;//将化简后的峰高度存入临时存储空间
        }
        else
        {
           if(high_int_ratio-frac_ratio<0.5)
           {
               temp_store[i]=high_int_ratio;//将化简后的峰高度存入临时存储空间
           }
        }

    }

    for(i=0;i<number_of_peaks/2;i++)
    {
        object[i].height=temp_store[i];
        object[number_of_peaks-i-1].height=temp_store[i];//根据对称规律，将用户输入的非整比峰高度用最简整比高度替换
    }
    }
    else//如果裂分峰是奇数个
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


void analyze(a_heap& object,float frequency)//分析二叉树的每一层的函数
{
    int level_number=1;
    int q=0;
    while(object.left!=object.right)//替代递归的循环,当二叉树的层中只有一个元素时终止
    {

    int i,j,k,length_of_level=object.right-object.left+1,i_for_temp;//对二叉树的一层进行操作
    double distance;

    for(i=1;i<=object.right-object.left;i++)//i代表步长，从1开始
    {

        memset(temp_store,0,sizeof(double));//重新定义步长时，把存储用于构建下一层二叉树的数据的临时存储空间清空
        i_for_temp=0;

        for(j=object.left;j<=object.right;j++)
        {
            object.is_valid[j]=0;//重新定义步长时，把层中所有元素重设为未访问过
        }

        j=object.left;//j为扫描距离是否合理的计数器

        distance=object.array[object.left+i]-object.array[object.left];//固定i下，定义的扫描步长


        while(j<=object.right)//算出步长匹配组合
        {
            if(object.is_valid[j]==1)
            {
                j++;
                continue;
            }

            for(k=j+i;k<=object.right;)//固定j，从j的右面开始寻找合法位置
            {
                if(object.is_valid[k]==1)//判断k所指的元素是否已被合法化
                {
                    k++;
                    continue;
                }

                if(object.is_valid[j]==0&&object.is_valid[k]==0&&abs(object.array[k]-object.array[j]-distance)<(distance/10))//步长匹配
                {
                    object.is_valid[j]=1;
                    object.is_valid[k]=1;//将匹配步长的两个元素合法化
                    temp_store[i_for_temp]=(object.array[j]+object.array[k])/2;//计算用于构建二叉树上一层的元素，存到临时存储空间temp_store中
                    i_for_temp++;
                    break;
                }
                else
                {
                    k++;//步长不匹配
                    continue;
                }
            }

            j++;

        }

        for(j=object.left;j<=object.right;j++)//判断二叉树的一层中的元素的距离是否全部合法
        {

            if(object.is_valid[j]==0)
             break;
        }

        if(j==object.right+1) //所选步长i合理
        {
            result_of_coupling[q]=distance*frequency;
            q++;
            break;
        }

     }

        object.right=object.left-1;
        object.left=object.right+1-length_of_level/2;//定义二叉树的上一层的上下界

        for(i=object.left,i_for_temp=0;i<=object.right;i++,i_for_temp++)
        {
            object.array[i]=temp_store[i_for_temp];//构造二叉树的上一层
        }

        memset(temp_store,0,sizeof(double));

        level_number++;//进入二叉树的上一层

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
            MessageBox(hwndDlg, "Thanks for using！", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONINFORMATION);
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
                MessageBox(hwndDlg, "Thanks for using！", "H1-NMR deconvolutor [v 1.0.1]", MB_ICONWARNING);

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
    cin>>peaknumber;//输入峰数
    cout<<endl;

    cout<<"Please enter the freqency of magnetic field sacan（MHz）"<<endl;
    cin>>frequency;//输入扫场频率
    cout<<endl;

    cout<<"Please enter the individual chemical shift of each peak（ppm）and ite integrated area size"<<endl;
    for(i=0;i<peaknumber;i++)
    {
        cin>>input[i].delta>>input[i].height;//输入每个峰的位移和强度，存入顺序表
    }
    cout<<endl;

    find_int_ratio(input,peaknumber);//将积分面积化为最简整数比

    for(i=0,j=0;i<peaknumber;i++)
    {
        temp=j;
        for(;j<temp+input[i].height;j++)
        {
            peak_height_1[j]=input[i].delta;//将强度为n的峰转化为n个强度为1的峰，其位移值存入另一个顺序表
        }
    }

    number_of_split=0;

    for(i=0;i<peaknumber;i++)
    {
        number_of_split+=input[i].height;//计算强度为1的峰的数目
    }

    j=0;

    for(i=MAXNUM-number_of_split;i<MAXNUM;i++,j++)
    {
        heap.array[i]=peak_height_1[j];//将最底层峰的位移数据存入二叉树的叶节点上
    }
    heap.left=MAXNUM-number_of_split;
    heap.right=MAXNUM-1;


    for(i=0;i<MAXNUM;i++)
    {
        heap.is_valid[i]=0;//将峰的初始判断值设为未访问
    }

    analyze(heap,frequency);//用重构二叉树法分析位移数据，得出每一层的偶合常数

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


int APIENTRY WinMain(HINSTANCE dialogue, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)//窗口主函数
{
    hInst = dialogue;

    while(flag==false&&DialogBox(dialogue, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc)==FALSE)
    {
    }
    return 0;

}
