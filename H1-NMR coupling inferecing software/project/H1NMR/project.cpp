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

struct a_heap//�洢�ѷַ����ݵĽṹ//using a custom heap to store data of splitted NMR peaks
{
    double array[MAXNUM];
    int left;
    int right;
    int is_valid[MAXNUM];
}heap;

struct peak//�洢�������ݵĽṹ//data structure for storaging input
{
    double delta;
    float height;
};

peak input[64];
double peak_height_1[64];
double temp_store[1000];


void find_int_ratio(peak* object, int number_of_peaks)//�����������Ϊ���������//convert integrated area of peaks into integer ratios
{
    int i, temp_store[1000];//��ʱ�洢�ռ����ڴ洢�����ķ�߶�//temp storage space of converted areas
    double frac_ratio;
    int low_int_ratio, high_int_ratio;


    temp_store[0] = 1;//���ݺ˴Ź����ѷַ���ص㣬���ϵķ�����ǿ������1//the peak at left or right most position in NMR is always having an area of 1 after the below conversion
    temp_store[number_of_peaks - 1] = 1;//ͬ��//same as above
    if (number_of_peaks % 2 == 0)//����ѷַ���ż����//if splitted peak is of even number
    {
        for (i = 1; i < number_of_peaks / 2; i++)
        {
            frac_ratio = object[i].height / object[0].height;//�����i����ĸ߶�����Ϸ�ĸ߶ȱ�//calculate the peak highet ration between the i th peak and the left/right most peak
            low_int_ratio = floor(frac_ratio);//ȡ������������//only takes the integer part
            high_int_ratio = ceil(frac_ratio);//ȡ����������ȡ����//take ceiling

            if (frac_ratio - low_int_ratio < 0.5)
            {
                temp_store[i] = low_int_ratio;//�������ķ�߶ȴ�����ʱ�洢�ռ�//store the simplified peak hights into the temp space
            }
            else
            {
                if (high_int_ratio - frac_ratio < 0.5)
                {
                    temp_store[i] = high_int_ratio;//�������ķ�߶ȴ�����ʱ�洢�ռ�//store the simplified peak hights into the temp space
                }
            }

        }

        for (i = 0; i < number_of_peaks / 2; i++)
        {
            object[i].height = temp_store[i];
            object[number_of_peaks - i - 1].height = temp_store[i];//���ݶԳƹ��ɣ����û�����ķ����ȷ�߶���������ȸ߶��滻//according to the symmetric rule of data, replace the user-input non-integer ratio with the simplified one
        }
    }
    else//����ѷַ���������//if the splitted peaks is of even number 
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


void analyze(a_heap& object, float frequency)//�����ѵ�ÿһ��ĺ���//a function that analyzes each layer of heap
{
    int level_number = 1;
    int q = 0;
    while (object.left != object.right)//����ݹ��ѭ��,���ѵĲ���ֻ��һ��Ԫ��ʱ��ֹ//loop to analyze
    {

        int i, j, k, length_of_level = object.right - object.left + 1, i_for_temp;//�Զѵ�һ����в���//for each layer
        double distance;

        for (i = 1; i <= object.right - object.left; i++)//i����������1��ʼ//i is the step size, starting from 1
        {

            memset(temp_store, 0, sizeof(double));//���¶��岽��ʱ���Ѵ洢���ڹ�����һ��ѵ����ݵ���ʱ�洢�ռ����//re-define step size, and clear the temp space for the next layer
            i_for_temp = 0;

            for (j = object.left; j <= object.right; j++)
            {
                object.is_valid[j] = 0;//���¶��岽��ʱ���Ѳ�������Ԫ������Ϊδ���ʹ�//set the elements in that layer as unvisited when redefining the step size
            }

            j = object.left;//jΪɨ������Ƿ����ļ�����//j is a counter that monitors the scan distance

            distance = object.array[object.left + i] - object.array[object.left];//�̶�i�£������ɨ�貽��//the scan distance under a certain i


            while (j <= object.right)//̰�ķ��������ƥ�����//greedy algorithm that gives the matching step sizes
            {
                if (object.is_valid[j] == 1)
                {
                    j++;
                    continue;
                }

                for (k = j + i; k <= object.right;)//�̶�j����j�����濪ʼѰ�ҺϷ�λ��//fix j and look to the right of j to find the valid position
                {
                    if (object.is_valid[k] == 1)//�ж�k��ָ��Ԫ���Ƿ��ѱ��Ϸ���//judge if the element pointed by k is validated
                    {
                        k++;
                        continue;
                    }

                    if (object.is_valid[j] == 0 && object.is_valid[k] == 0 && abs(object.array[k] - object.array[j] - distance) < (distance / 10))//����ƥ��//stepsize matching
                    {
                        object.is_valid[j] = 1;
                        object.is_valid[k] = 1;//��ƥ�䲽��������Ԫ�غϷ���//validate the two elements of matching step size
                        temp_store[i_for_temp] = (object.array[j] + object.array[k]) / 2;//�������ڹ�����һ��ѵ�Ԫ�أ��浽��ʱ�洢�ռ�temp_store��//calculate the elements to contstruct the previous layer of the heap and store them into a temp space
                        i_for_temp++;
                        break;
                    }
                    else
                    {
                        k++;//������ƥ��//if stepsize mismatches
                        continue;
                    }
                }

                j++;

            }

            for (j = object.left; j <= object.right; j++)//�ж�heap��һ���е�Ԫ�صľ����Ƿ�ȫ���Ϸ�//see if every distance between the elements in the heap is valid
            {

                if (object.is_valid[j] == 0)
                    break;
            }

            if (j == object.right + 1) //��ѡ����i����//if step size i is valid
            {
                //cout<<"ż�ϳ��� "<<level_number<<" "<<"="<<" "<<distance*frequency<<endl;//��ɶ�һ��Ĳ��������ż�ϳ���//after finishing one layer, output the coupling constant
                result_of_coupling[q] = distance * frequency;
                q++;
                break;
            }

        }

        object.right = object.left - 1;
        object.left = object.right + 1 - length_of_level / 2;//����ѵ���һ������½�//define the upper and lower bound of the previous layer of heap

        for (i = object.left, i_for_temp = 0; i <= object.right; i++, i_for_temp++)
        {
            object.array[i] = temp_store[i_for_temp];//����ѵ���һ��//construct the previous layer
        }

        memset(temp_store, 0, sizeof(double));

        level_number++;//����ѵ���һ��//go to the previous layer

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
    string title1 = "ż�ϳ���/Hz";
    string title2 = "��ѧλ��/ppm";

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

        MessageBox(hwndDlg, "�˴Ź����ѷַ�������� [�汾 1.0.0]\n��Ȩ���� <c> 2013 ������ѧ��ѧ����ӹ���ѧԺ �׺�Ȼ����������Ȩ��", "��ӭʹ��", MB_ICONINFORMATION);
        return FALSE;


    case WM_CLOSE:
        MessageBox(hwndDlg, "��лʹ�ã�", "�˴Ź����ѷַ�������� [�汾 1.0.0]", MB_ICONINFORMATION);
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
            MessageBox(hwndDlg, "�ó���Ƿ����У�������ֹ~~~", "�˴Ź����ѷַ�������� [�汾 1.0.0]", MB_ICONERROR);

            EndDialog(hwndDlg, 0);
            flag = true;
            return TRUE;

        case IDC_BTN_QUIT:
            MessageBox(hwndDlg, "��лʹ�ã�", "�˴Ź����ѷַ�������� [�汾 1.0.0]", MB_ICONWARNING);

            EndDialog(hwndDlg, 0);
            flag = true;
            return TRUE;


        case IDC_BTN_TEST:
            MessageBox(hwndDlg, "�ѷַ���׼�����ʼ��", "�˴Ź����ѷַ�������� [�汾 1.0.0]", MB_ICONWARNING);
            EndDialog(hwndDlg, 0);

            {
                int i, peaknumber, j, number_of_split, temp;
                float frequency;

                //cout<<"�˴Ź����ѷַ�������� [�汾 1.0.0]"<<endl<<"��Ȩ���� <c> 2013 ������ѧ��ѧ����ӹ���ѧԺ �׺�Ȼ����������Ȩ��"<<endl<<endl;

                cout << "�������ѷַ����Ŀ" << endl;
                cin >> peaknumber;//�������//input number of peaks
                cout << endl;

                cout << "������ɨ��Ƶ�ʣ�MHz��" << endl;
                cin >> frequency;//����ɨ��Ƶ��//enter frequency
                cout << endl;

                cout << "��ֱ�����ÿ���ѷַ�Ļ�ѧλ�ƣ�ppm���Լ��������" << endl;
                for (i = 0; i < peaknumber; i++)
                {
                    cin >> input[i].delta >> input[i].height;//����ÿ�����λ�ƺ�ǿ�ȣ�����˳���//enter data of each peak
                }
                cout << endl;

                find_int_ratio(input, peaknumber);//�����������Ϊ���������//convert integrated area of peaks into integer ratios

                for (i = 0, j = 0; i < peaknumber; i++)
                {
                    temp = j;
                    for (; j < temp + input[i].height; j++)
                    {
                        peak_height_1[j] = input[i].delta;//��ǿ��Ϊn�ķ�ת��Ϊn��ǿ��Ϊ1�ķ壬��λ��ֵ������һ��˳���//convert a peak whose strength is n into n peaks of strength 1
                    }
                }

                number_of_split = 0;

                for (i = 0; i < peaknumber; i++)
                {
                    number_of_split += input[i].height;//����ǿ��Ϊ1�ķ����Ŀ//calculate the number of peaks of strength 1
                }

                j = 0;

                for (i = MAXNUM - number_of_split; i < MAXNUM; i++, j++)
                {
                    heap.array[i] = peak_height_1[j];//����ײ���λ�����ݴ���ѵ�Ҷ�ڵ���//store the chemical shifting data of the lowest level paeks into the leaf nodes of the heap
                }
                heap.left = MAXNUM - number_of_split;
                heap.right = MAXNUM - 1;


                for (i = 0; i < MAXNUM; i++)
                {
                    heap.is_valid[i] = 0;//����ĳ�ʼ�ж�ֵ��Ϊδ����//set all elements in the heap as unvisited
                }

                analyze(heap, frequency);//���ع��ѷ�����λ�����ݣ��ó�ÿһ���ż�ϳ���//using the method of reconstructing the heap to analyze chemical shifting, and give the coupling constant of each layer

                //cout<<endl<<"����ԭ�ӵĻ�ѧλ��Ϊ"<<(input[0].delta+input[peaknumber-1].delta)/2<<"ppm"<<endl<<endl;//�����ѧλ��ֵ
                result_of_coupling[6] = (input[0].delta + input[peaknumber - 1].delta) / 2;
                cout << "************************" << endl << endl << endl;

                MessageBox(hwndDlg, "���׳ɹ������ڴ����в鿴���׽��.", "�˴Ź����ѷַ�������� [�汾 1.0.0]", MB_ICONINFORMATION);
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
