#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <cmath>
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//must use GNU GCC compiler to build and run this code

using namespace std;

const int MAXNUM = 1000;

float result_of_coupling[7];

struct a_heap//存储裂分峰数据的结构//using a custom heap to store data of splitted NMR peaks
{
    double array[MAXNUM];
    int left;
    int right;
    int is_valid[MAXNUM];
}heap;

struct peak//存储输入数据的结构//data structure for storaging input
{
    double delta;
    float height;
};

peak input[64];
double peak_height_1[64];
double temp_store[1000];


void find_int_ratio(peak* object, int number_of_peaks)//将积分面积化为最简整数比//convert integrated area of peaks into integer ratios
{
    int i, temp_store[1000];//临时存储空间用于存储化简后的峰高度//temp storage space of converted areas
    double frac_ratio;
    int low_int_ratio, high_int_ratio;


    temp_store[0] = 1;//根据核磁共振裂分峰的特点，边上的峰的相对强度总是1//the peak at left or right most position in NMR is always having an area of 1 after the below conversion
    temp_store[number_of_peaks - 1] = 1;//同上//same as above
    if (number_of_peaks % 2 == 0)//如果裂分峰是偶数个//if splitted peak is of even number
    {
        for (i = 1; i < number_of_peaks / 2; i++)
        {
            frac_ratio = object[i].height / object[0].height;//计算第i个峰的高度与边上峰的高度比//calculate the peak highet ration between the i th peak and the left/right most peak
            low_int_ratio = floor(frac_ratio);//取比例的整数部//only takes the integer part
            high_int_ratio = ceil(frac_ratio);//取比例的向上取整部//take ceiling

            if (frac_ratio - low_int_ratio < 0.5)
            {
                temp_store[i] = low_int_ratio;//将化简后的峰高度存入临时存储空间//store the simplified peak hights into the temp space
            }
            else
            {
                if (high_int_ratio - frac_ratio < 0.5)
                {
                    temp_store[i] = high_int_ratio;//将化简后的峰高度存入临时存储空间//store the simplified peak hights into the temp space
                }
            }

        }

        for (i = 0; i < number_of_peaks / 2; i++)
        {
            object[i].height = temp_store[i];
            object[number_of_peaks - i - 1].height = temp_store[i];//根据对称规律，将用户输入的非整比峰高度用最简整比高度替换//according to the symmetric rule of data, replace the user-input non-integer ratio with the simplified one
        }
    }
    else//如果裂分峰是奇数个//if the splitted peaks is of even number 
    {
        for (i = 1; i < (number_of_peaks + 1) / 2; i++)
        {
            frac_ratio = object[i].height / object[0].height;
            low_int_ratio = floor(frac_ratio);
            high_int_ratio = ceil(frac_ratio);

            if (frac_ratio - low_int_ratio < 0.5)
            {
                temp_store[i] = low_int_ratio;
            }
            else
            {
                if (high_int_ratio - frac_ratio < 0.5)
                {
                    temp_store[i] = high_int_ratio;
                }
            }

        }

        for (i = 0; i < (number_of_peaks - 1) / 2; i++)
        {
            object[i].height = temp_store[i];
            object[number_of_peaks - i - 1].height = temp_store[i];
        }
        object[i].height = temp_store[(number_of_peaks - 1) / 2];
    }


}

bool flag = false;


void analyze(a_heap& object, float frequency)//分析堆的每一层的函数//a function that analyzes each layer of heap
{
    int level_number = 1;
    int q = 0;
    while (object.left != object.right)//替代递归的循环,当堆的层中只有一个元素时终止//loop to analyze
    {

        int i, j, k, length_of_level = object.right - object.left + 1, i_for_temp;//对堆的一层进行操作//for each layer
        double distance;

        for (i = 1; i <= object.right - object.left; i++)//i代表步长，从1开始//i is the step size, starting from 1
        {

            memset(temp_store, 0, sizeof(double));//重新定义步长时，把存储用于构建下一层堆的数据的临时存储空间清空//re-define step size, and clear the temp space for the next layer
            i_for_temp = 0;

            for (j = object.left; j <= object.right; j++)
            {
                object.is_valid[j] = 0;//重新定义步长时，把层中所有元素重设为未访问过//set the elements in that layer as unvisited when redefining the step size
            }

            j = object.left;//j为扫描距离是否合理的计数器//j is a counter that monitors the scan distance

            distance = object.array[object.left + i] - object.array[object.left];//固定i下，定义的扫描步长//the scan distance under a certain i


            while (j <= object.right)//贪心法算出步长匹配组合//greedy algorithm that gives the matching step sizes
            {
                if (object.is_valid[j] == 1)
                {
                    j++;
                    continue;
                }

                for (k = j + i; k <= object.right;)//固定j，从j的右面开始寻找合法位置//fix j and look to the right of j to find the valid position
                {
                    if (object.is_valid[k] == 1)//判断k所指的元素是否已被合法化//judge if the element pointed by k is validated
                    {
                        k++;
                        continue;
                    }

                    if (object.is_valid[j] == 0 && object.is_valid[k] == 0 && abs(object.array[k] - object.array[j] - distance) < (distance / 10))//步长匹配//stepsize matching
                    {
                        object.is_valid[j] = 1;
                        object.is_valid[k] = 1;//将匹配步长的两个元素合法化//validate the two elements of matching step size
                        temp_store[i_for_temp] = (object.array[j] + object.array[k]) / 2;//计算用于构建上一层堆的元素，存到临时存储空间temp_store中//calculate the elements to contstruct the previous layer of the heap and store them into a temp space
                        i_for_temp++;
                        break;
                    }
                    else
                    {
                        k++;//步长不匹配//if stepsize mismatches
                        continue;
                    }
                }

                j++;

            }

            for (j = object.left; j <= object.right; j++)//判断heap的一层中的元素的距离是否全部合法//see if every distance between the elements in the heap is valid
            {

                if (object.is_valid[j] == 0)
                    break;
            }

            if (j == object.right + 1) //所选步长i合理//if step size i is valid
            {
                //cout<<"偶合常数 "<<level_number<<" "<<"="<<" "<<distance*frequency<<endl;//完成对一层的操作后，输出偶合常数//after finishing one layer, output the coupling constant
                result_of_coupling[q] = distance * frequency;
                q++;
                break;
            }

        }

        object.right = object.left - 1;
        object.left = object.right + 1 - length_of_level / 2;//定义堆的上一层的上下界//define the upper and lower bound of the previous layer of heap

        for (i = object.left, i_for_temp = 0; i <= object.right; i++, i_for_temp++)
        {
            object.array[i] = temp_store[i_for_temp];//构造堆的上一层//construct the previous layer
        }

        memset(temp_store, 0, sizeof(double));

        level_number++;//进入堆的上一层//go to the previous layer

    }

}
HINSTANCE hInst;

string SS;



struct RECTS//windows
{
    RECT arect;
};
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //HWND hwndButton;@

           //HDC hdc;
  //PAINTSTRUCT ps;
  //static RECT rect={0,0,100,100};
  //string s="eee";
  //@

  //HWND hwndButton;@

    HDC hdc;
    PAINTSTRUCT ps;
    RECTS rect_array[6];
    static RECT rect = { 0,0,1000,150 };
    static RECT rect2 = { 0,0,1200,150 };
    static RECT rect3 = { 0,0,1200,200 };
    string title1 = "偶合常数/Hz";
    string title2 = "化学位移/ppm";

    for (int i = 0; i < 6; i++)
    {
        rect_array[i].arect = { 0,0,1000,200 + 50 * i };
    }

    //static RECT rect={0,0,100,100};
    //static RECT rect2={0,0,200,200};
    char s[100][100];
    for (int i = 0; i < 7; i++)
    {
        gcvt(result_of_coupling[i], 4, s[i]);
    }

    //@



    //lable:
    switch (uMsg)
    {

        // case WM_PAINT://@
 //hdc=BeginPaint(hwndDlg,&ps);
 //GetClientRect(hwnd,&rect);
 //DrawText(hdc,s.c_str(),s.size(),&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
 //EndPaint(hwndDlg,&ps);

 //break;
 //@


    case WM_PAINT://@

        hdc = BeginPaint(hwndDlg, &ps);
        //GetClientRect(hwnd,&rect);

        DrawText(hdc, title1.c_str(), title1.size(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        DrawText(hdc, title2.c_str(), title2.size(), &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        DrawText(hdc, s[6], strlen(s[6]), &rect3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        for (int i = 0; i < 6; i++) {
            DrawText(hdc, s[i], strlen(s[i]), &rect_array[i].arect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }EndPaint(hwndDlg, &ps);

        break;
        //@


    case WM_NCHITTEST:
        return FALSE;

    case WM_INITDIALOG:

        MessageBox(hwndDlg, "核磁共振裂分峰解析工具 [版本 1.0.0]\n版权所有 <c> 2013 北京大学化学与分子工程学院 雷浩然。保留所有权利", "欢迎使用", MB_ICONINFORMATION);
        return FALSE;


    case WM_CLOSE:
        MessageBox(hwndDlg, "感谢使用！", "核磁共振裂分峰解析工具 [版本 1.0.0]", MB_ICONINFORMATION);
        EndDialog(hwndDlg, 0);
        flag = true;
        return  TRUE;

        // case WM_CREATE:
            // hwndButton=CreateWindowW(TEXT("button"),TEXT("anniu"),WS_CHILD | WS_VISIBLE,
             //0,0,20,20,hwndButton,(HMENU)0,((LPCREATESTRUCT)lParam)->hins,NULL);


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDC_BTN_ADVANCE:
            MessageBox(hwndDlg, "该程序非法运行，即将终止~~~", "核磁共振裂分峰解析工具 [版本 1.0.0]", MB_ICONERROR);

            EndDialog(hwndDlg, 0);
            flag = true;
            return TRUE;

        case IDC_BTN_QUIT:
            MessageBox(hwndDlg, "感谢使用！", "核磁共振裂分峰解析工具 [版本 1.0.0]", MB_ICONWARNING);

            EndDialog(hwndDlg, 0);
            flag = true;
            return TRUE;


        case IDC_BTN_TEST:
            MessageBox(hwndDlg, "裂分峰解谱即将开始！", "核磁共振裂分峰解析工具 [版本 1.0.0]", MB_ICONWARNING);
            EndDialog(hwndDlg, 0);

            {
                int i, peaknumber, j, number_of_split, temp;
                float frequency;

                //cout<<"核磁共振裂分峰解析工具 [版本 1.0.0]"<<endl<<"版权所有 <c> 2013 北京大学化学与分子工程学院 雷浩然。保留所有权利"<<endl<<endl;

                cout << "请输入裂分峰的数目" << endl;
                cin >> peaknumber;//输入峰数//input number of peaks
                cout << endl;

                cout << "请输入扫场频率（MHz）" << endl;
                cin >> frequency;//输入扫场频率//enter frequency
                cout << endl;

                cout << "请分别输入每个裂分峰的化学位移（ppm）以及积分面积" << endl;
                for (i = 0; i < peaknumber; i++)
                {
                    cin >> input[i].delta >> input[i].height;//输入每个峰的位移和强度，存入顺序表//enter data of each peak
                }
                cout << endl;

                find_int_ratio(input, peaknumber);//将积分面积化为最简整数比//convert integrated area of peaks into integer ratios

                for (i = 0, j = 0; i < peaknumber; i++)
                {
                    temp = j;
                    for (; j < temp + input[i].height; j++)
                    {
                        peak_height_1[j] = input[i].delta;//将强度为n的峰转化为n个强度为1的峰，其位移值存入另一个顺序表//convert a peak whose strength is n into n peaks of strength 1
                    }
                }

                number_of_split = 0;

                for (i = 0; i < peaknumber; i++)
                {
                    number_of_split += input[i].height;//计算强度为1的峰的数目//calculate the number of peaks of strength 1
                }

                j = 0;

                for (i = MAXNUM - number_of_split; i < MAXNUM; i++, j++)
                {
                    heap.array[i] = peak_height_1[j];//将最底层峰的位移数据存入堆的叶节点上//store the chemical shifting data of the lowest level paeks into the leaf nodes of the heap
                }
                heap.left = MAXNUM - number_of_split;
                heap.right = MAXNUM - 1;


                for (i = 0; i < MAXNUM; i++)
                {
                    heap.is_valid[i] = 0;//将峰的初始判断值设为未访问//set all elements in the heap as unvisited
                }

                analyze(heap, frequency);//用重构堆法分析位移数据，得出每一层的偶合常数//using the method of reconstructing the heap to analyze chemical shifting, and give the coupling constant of each layer

                //cout<<endl<<"该氢原子的化学位移为"<<(input[0].delta+input[peaknumber-1].delta)/2<<"ppm"<<endl<<endl;//输出化学位移值
                result_of_coupling[6] = (input[0].delta + input[peaknumber - 1].delta) / 2;
                cout << "************************" << endl << endl << endl;

                MessageBox(hwndDlg, "解谱成功！请在窗口中查看解谱结果.", "核磁共振裂分峰解析工具 [版本 1.0.0]", MB_ICONINFORMATION);
                EndDialog(hwndDlg, 0);
                // hInst = hwndDlg;
                 //(DialogBox(hwndDlg, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc));


                 //goto lable;




            }



            return FALSE;

        }


    }

    return FALSE;

}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;

    while (flag == false && DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc) == FALSE)
    {
        //(DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc));
    }
    return 0;
    //if(DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc)) break;

}
