#include <iostream>
#include <algorithm>
#include<numeric>
#include <vector>
#include <string>
#include <list>
#include <deque>

using namespace std;

//C++ class ��ʾ
class point 
{
public:
    pair<int, int> get_position()
    {
        return make_pair(x_cord, y_cord);
    }

    void set_position(int x, int y)
    {
        x_cord = x;
        y_cord = y;
        return;
    }

private:
    int x_cord;
    int y_cord;
};












//mismatch��ʾ����
string mirror_ends(const string& in)
{
    return string(in.begin(), mismatch(in.begin(), in.end(), in.rbegin()).first);
}


int main()
{

    list<int> list_int;


    //--------------��׼�⺯����ϰ---------------

    //partial_sum   https://www.jianshu.com/p/e68a11d5b316
        //���Ӷ�N
    list_int = { 1,2,3,4,5 };
    list<int>list_result;
    list_result.resize(list_int.size());
    partial_sum(list_int.begin(), list_int.end(), list_result.begin());//�ۼ�,������list_int = { 1,2,3,4,5 }�����list_result = {1,3,6,10,15}
    partial_sum(list_int.begin(), list_int.end(), list_result.begin(),multiplies<int>());//�۳�,������list_int = { 1,2,3,4,5 }�����list_result = {1,2,6,24,120}

    //lambda���ʽ���װ�
    list_int = { 1,2,3,4,5 };
    int n = count_if(list_int.begin(), list_int.end(), [](int x) {return x >= 2; });//x���βΣ���iterator��ֵ�����н�����n=4

    //all_of, none_of, any_of
        //���Ӷ�N
    bool yn;
    yn = all_of(list_int.begin(), list_int.end(), [](int i) { return i % 2 == 0; });//���yn=false
    yn = all_of(list_int.begin(), list_int.end(), [](int i) { return i >= 0; });//���yn=true��any_of none_of�÷����
    
    //for_each��for_each_nЧ����������forѭ������������ûɶ���塣

    //count, count_if
        //���Ӷ�N
    int target = 1;
    n = count(list_int.begin(), list_int.end(), target);//���n=1,count_if�����Ӽ�lambda���ʽ����

    //mismatch
    //���Ӷȣ�N ����һ�������Ĵ�С��
    //����Ϊ�ĸ����ֱ��ǵ�һ��������ʼ��iterator�͵ڶ���������ʼ��iterator��Ҳ���Ƕ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ���塣�����ṩ last2 ������ָ�� first2 + (last1 - first1) ��
    //����һ��pair�����pair��һ��Ԫ��������������һ�γ���Ԫ�ز���ͬʱ�ĵ�һ��������iteratr��
    //�ڶ���Ԫ��������������һ�γ���Ԫ�ز���ͬʱ�ĵڶ���������iteratr�������������������ȫ��ͬ���������������������.end()��
    //���³�����Լ���һ�������ַ����ȷ��ͬʱ����ʼ�������β������ͬʱ�ҵ������ͬ�Ӵ��������ص�����
        cout << mirror_ends("abXYZba") << '\n'
            << mirror_ends("abca") << '\n'
            << mirror_ends("aba") << '\n';
    //��������ab
        //a
        // aba


   //find, find_if
        //���Ӷȣ�N
        //find�������������ֱ���ʼ��iterator��Ŀ��ֵ�����ؽ�һ��iterator��Ϊtarget��һ�γ���ʱ��λ�á���δ�ҵ�Ŀ��ֵ�򷵻�.end()
        target = 2;
        auto it = find(list_int.begin(), list_int.end(), target);//�ҵ���һ��2��λ��
        //find_if����Ҳ��������������count_if,���ؽ�һ��iterator
        it = find_if(list_int.begin(), list_int.end(), [](int x) { return x % 2 == 0; });//�ҵ���һ��ż����λ��


    list_int = { 1,2,3,4,5 };
    list<int> list_int2 = { 2,3,4};
    //find_end
        //���Ӷȣ�����Ƚ� S*(N-S+1) �Σ����� S = distance(s_first, s_last) �� N = distance(first, last) ��
        //�ڷ�Χ [first, last) ���������� [s_first, s_last) �����һ�γ���λ�ã�����iterator����δ�ҵ��򷵻�.end. 
        //��ȻҲ��������lambda���ʽ���ı䡰��ȡ��ıȽϲ��ԡ�
    it = find_end(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end());//������list_int2 = { 2,3,4}�����itΪָ��list_int��Ԫ��2��iterator
    int dist = distance(list_int.begin(),it);//����õ�it��ָԪ�ص�indexΪ 1��ע��distance�����������������˳�򲻿ɵ������ǵڶ���iterator��ȥ��һ��iterator���������Ϊ����ջ��ṹ��iterator��������


    list_int2 = { 4,2,4 };
    //find_first_of
        //���Ӷȣ������� (S*N) �αȽϣ����� S = distance(s_first, s_last) �� N = distance(first, last) ��
        //��ͷ���� [first, last) ��ÿ��һ��Ԫ�ر�� [s_first, s_last) �е��κ�Ԫ�ؽ��бȽϣ�����ҵ���ͬԪ�أ��������ʱλ��[first, last)�е�iterator��
        //��Ȼ������ġ���ͬ���Ƚϲ���Ҳ����
    it = find_first_of(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end());//������list_int2 = { 4,2,4 }�����itΪָ��list_int��Ԫ��2��iterator
    it = find_first_of(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end(), [](float a, float b) { return a / b == 1.25; });//���itΪָ��list_int��Ԫ��5��iterator



    //����string��vector����ת������stringת���ɱ�׼�������ٴ�����ʵ����
    string str = "abcddea";
    vector<char>vec_char;
    vec_char.assign(str.begin(), str.end());//string to vector
    string str2;
    str2.assign(vec_char.begin(), vec_char.end());//vector to string

    //adjacent_find
        //���Ӷ�:N
        //��ͷ���� [first, last) ��ÿ��һ��Ԫ�ر����һ��Ԫ�ؽ��бȽϣ������ͬ���������һ��Ԫ�ص�iterator������ͬ�����Կ��Ի��ɱ�ġ�
    auto it_vec_char = adjacent_find(vec_char.begin(), vec_char.end());//���vec_char����Ϊabcddea���򷵻�һ��ָ��vec_char�е�һ��d��it
    auto itt = adjacent_find(str.begin(), str.end());//���str����Ϊabcddea���򷵻�һ��ָ��str�е�һ��d��ָ�롣dҲ��һ��string��������"ddea"��
    it_vec_char = adjacent_find(vec_char.begin(), vec_char.end(), greater<char>());//����һ��ָ��vec_char��e��it����Ϊ����greater��Ϊ�ȽϺ������˷��������ж������Ƿ�Ϊ����less�Ļ������жϽ���



    //search
        //���Ӷȣ������� (S*N) �αȽϣ����� S = distance(s_first, s_last) �� N = distance(first, last) ��
        //������Χ [first, last - (s_last - s_first)) ��Ԫ�������� [s_first, s_last) ���״γ��֡�����iteratorָ�������е�һ�γ��ֵ�λ�á��������last��
    string str3 = "abcddea, er, asd , 123, er1,as";
    string str4 = "3, e";
    auto it_str = search(str3.begin(), str3.end(), str4.begin(), str4.end());//���str3Ϊ"abcddea, er, asd , 123, er1,as"��str4Ϊ"3, e"�򷵻�һ��ite��ָ�룩��ָ��"3, er1,as"���string��
        //ע��searchԴ���������predicate��������Ԫ�ء�predicate�ᱻѭ�����ã�����Ԫ�رȽ��Ӵ�str4��str3��ĳ���ط���ʼ�Ĳ���
    it_str = search(str3.begin(), str3.end(), str4.begin(), str4.end(), [](char c1, char c2) {return c2 == c1  && c2 != ' '; });//Ҫ���Ӵ�������str3�����Ӵ��в����пո񡣴˴����Ҳ���������str3.end()��


    //copy, copy_if
        //���Ӷȣ�ʹ��N��pred���Լ�ʹ��N�θ�ֵ��
        //������ͬһ�������н��и��ƣ�ֻҪ���εķ�Χ��ͬ��copy_if�Ϳ��Լ�pred����������
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = "3, e";
    copy(str4.begin(), str4.end(), str3.begin());//��str4ȫ����Χ�ڵ�ֵ���������ǵ�str3ͷ������Ϊʹ����.begin����str3�����str4��
    str3 = "abcddea, er, asd , 123, er1,as";
    string str6;
    copy(str3.begin(), str3.end(), back_inserter(str6));//��str3ȫ����Χ�ڵ�ֵ���������ǵ�str6ͷ������Ϊʹ����back_inserter����str6���ر�str3��


    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = "3, e";
    copy_if(str4.begin(), str4.begin() + 3, str3.begin(), [](char a) {return a != ' '; });//����str4��ǰ3����Ϊ�ո���ַ����Ʋ����ǵ�str3��ͷ�������str3Ϊ"abcddea, er, asd , 123, er1,as"��str4Ϊ"3, e"�������str3 = "3,cddea, er, asd , 123, er1,as"


    //copy_backward����ͨ��copy��rbegin����ʵ�֡������ȡ������Դ��Χ��
    str3 = "abcddea, er, asd , 123, er1,as";
    copy_if(str4.rbegin(), str4.rbegin() + 3, str3.begin(), [](char a) {return a != ' '; });//str3Ϊ"e,cddea, er, asd , 123, er1,as"

    //move����һ�η�Χ�ڵ�Ԫ���ƶ�����һ��Χ�ڡ����ڲ���copy��Ԫ������Ч������thread��

    //fill
        //��ֵ������ value �� [first, last) �е�Ԫ�ء�û��pred��
    string str5 = "123";
    fill(str5.begin(), str5.end(), 's');//"sss"

    //fill_n
        //�� count > 0 ����ֵ������ value ��ʼ�� �ķ�Χ���� count ��Ԫ�ء��������κ��¡�
    str5 = "123";
    fill_n(str5.begin(), 2, 's');//"ss3"

    //transform,generate��


    //remove,remove_if  ����STL�����������˻����ĺ���  https://blog.csdn.net/vbanglev/article/details/1512521
        //��Ϊremove�޷�֪�������ڲ���������������remove�����ܴ�һ�������г�ȥԪ�ء����������һ�����˾�ɥ�Ĺ۵㡪����һ��������removeԪ�ز���ı�������Ԫ�صĸ���
        //remove����Ҫɾ����Ԫ�����������ƶ�������Ҫ������Ԫ��������ǰ���ƶ�������һ��ָ���һ����ɾ��Ԫ�ص�iterator��remove������������Դ���erase�����Ϳ������ɾ��Ԫ�صĲ�����
        //��remove���ص�iteratorָ��������е�ĳ��λ�ã����λ�ü��Ժ��Ǵ�ɾ��Ԫ�أ�  
        //���Ӷȣ�ʹ��N��pred
    str3 = "abcddea, er, asd , 123, er1,as";

        //���д���� string �Ƴ����пո�
    str3.erase(remove(str3.begin(), str3.end(), 'a'), str3.end());//���str3 = "abcddea, er, asd , 123, er1,as"�����str3Ϊ"abcddea,er,asd,123,er1,as"
        //remove_if ���Խ�����ȡ��Ƚϲ�����pred�滻
    str4= "abcddea,\ner,\tasd ,\f123, er1,as";
    str4.erase(remove_if(str4.begin(), str4.end(), [](char x) {return isspace(x);}), str4.end());//���str4 = "abcddea,\ner,\tasd ,\f123, er1,as"�����str4Ϊ"abcddea,er,asd,123,er1,as"


    //remove_copy����ͨ��copy_if��ʵ��

    //replace��

    //swap
    int a = 5;
    int b = 3;
    swap(a, b);//a��b��ֵ���ཻ��


    //swap_ranges
        //���Ӷȣ�N
        //�ڷ�Χ [first1, last1) ��ʼ�� first2 ����һ��Χ�佻��Ԫ�ء�
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = str3;
    for (auto it_str = str4.begin(); it_str != str4.end(); it_str++) { *it_str = toupper(*it_str); }//str4���"ABCDDEA, ER, ASD , 123, ER1,AS"
    swap_ranges(str4.begin() + 1, str4.begin() + 2, str3.begin() + 1);//str3���"aBcddea, er, asd , 123, er1,as"��str4���"AbCDDEA, ER, ASD , 123, ER1,AS"

    
    //reverse
        //���Ӷȣ�N
        //��ת [first, last) ��Χ�е�Ԫ��˳��
    str3 = "abcddea, er, asd , 123, er1,as";
    reverse(str3.begin() + 1, str3.end() - 1);//str3���"aa,1re ,321 , dsa ,re ,aeddcbs"


    //rotate
        //���Ӷȣ�N
        //��������(first, n_first, last)������Χ [first, last) �е�Ԫ�أ�ʹ��Ԫ�� n_first ��Ϊ�·�Χ���׸�Ԫ�أ��� n_first - 1 ��Ϊ���Ԫ��(��ת��
    str3 = "abcddea, er, asd , 123, er1,as";
    rotate(str3.begin(), str3.begin() + 9, str3.end());//str3���"er, asd , 123, er1,asabcddea, "�൱�ڴ�ԭstr3��10���ַ���ʼ��ת

    //shift��

    //random_shuffle��sample��

    //unique
        //���Ӷȣ�N
        //�����Է�Χ [first, last) ����̵ȼ�Ԫ����������Ԫ�����Ԫ�أ������ط�Χ�����߼���β��β���������
        //�ò�����remove����֮ͬ������ֻ�ܽ���ɾ��Ԫ���ƶ��������󲿣�����������������erase���������ɾ����
        //����ͬ�����жϲ���Ҳ������pred���滻��������remove_if
    str3 = "abcddea, er, asd , 123333, er1,aaaas";
    str3.erase(unique(str3.begin(), str3.end()), str3.end());//���str3 = "abcddea, er, asd , 123333, er1,aaaas"�����str3Ϊ"abcdea, er, asd , 123, er1,as"
    vector <float> vec_unique = { 1,1.5,1.75,2,3,4,5,6 };
    vec_unique.erase(unique(vec_unique.begin(), vec_unique.end(), [](float x, float y) {return abs(x - y) <= 1; }), vec_unique.end());//ɾ���������Ĳ�ֵ��1���ڵ�Ԫ�أ����{1,3,5}


    //stable_partition
         //���Ӷȣ�N (�г����ڴ�ʱ��������ΪNlogN
        //������Χ [first, last) �е�Ԫ�أ�ʹ��ν�� p ���䷵�� true ��Ԫ��ǰ��ν�� p ���䷵�� false ��Ԫ�ء��������˳��
        //����ָ��ڶ���Ԫ����Ԫ�صĵ�������
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    it_str = stable_partition(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });//�������str3 = "abcddea, er, ASd , 123, er1,as{():";�����str3Ϊ":)({,1 , ,3, 21  ,dSAreaeredasdcba"
        //���ص�it_strָ��":)({,1 , ,3, 21  ,dSAreaeredasdcba"�е�һ��d
        //partition��


    //is_partitioned
        //���Ӷȣ�N
        //����Χ [first, last) �е��������� p ��Ԫ�ض����������в������Ԫ��ǰ�򷵻� true ���� [first, last) Ϊ���෵�� true ��
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    it_str = stable_partition(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });
    bool _is_partitioned = is_partitioned(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });//����true


    //sort, stable_sort,is_sorted
        //���Ӷȣ�sortӦ��pred NlogN��,stable_sortӦ��pred Nlog(N^2)�Σ��ڴ������ NlogN�Σ���is_sorted���Ӷ�ΪN
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    sort(str3.begin() + 1, str3.end(), [](char a, char b) {return b < a; });//���򣬷���str3="a{srreeedddcbaaSA:3211,,,,,)(     "���粻����pred��Ĭ������
    bool _is_sorted_dec = is_sorted(str3.begin() + 1, str3.end(), [](char a, char b) {return b < a; });//����true���粻����pred��Ĭ������


    
    //binary_search
        //���Ӷȣ���2Ϊ�׵�log��N��
        //�������� ���� ������������ʹ�á�
          //����bool
    bool _found = binary_search(str3.begin() + 1, str3.end(), 'a');//����false,��Ϊstr3������������


    //merge
        //���Ӷȣ����� std::distance(first1, last1) + std::distance(first2, last2) - 1 �αȽϡ�
        //������������ͬ��������źõ����й鲢��һ�����У�����������������
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = str3;
    string result;
    for (auto it_str = str4.begin(); it_str != str4.end(); it_str++) { *it_str = toupper(*it_str); }//str4���"ABCDDEA, ER, ASD , 123, ER1,AS"
    sort(str3.begin(), str3.end());//"     ,,,,,1123aaaabcdddeeerrss"
    sort(str4.begin(), str4.end());//"     ,,,,,1123AAAABCDDDEEERRSS"
    merge(str4.begin(), str4.end(), str3.begin(), str3.end(), back_inserter(result));//���result = "          ,,,,,,,,,,11112233AAAABCDDDEEERRSSaaaabcdddeeerrss"

    //inplace_merge��


    //includeò�ƿ�����search�����棬��include��ʱ�临�Ӷ�Ϊ2��(N1+N2-1)��searchΪN1��N2


    //set_difference
        //���Ӷȣ�2��(N1+N2-1)
        //������������ͬ��������źõ����н��бȽϣ��������1��ȥ����2��ע��˳�򣩵Ĳ�������������ע���������������������ͬ��ֵ��ͬ��Ԫ�صĴ���
    vector<int> v1 = { 1, 2, 5, 5, 5, 9 };
    vector<int> v2 = { 2, 5, 7 };
    vector<int> diff;
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(diff));//���diffΪ{1,5,5,9}
    diff = {};
    set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), back_inserter(diff));//���diffΪ{7}

    //set_intersection
        //���Ӷȣ�2��(N1+N2-1)
        //������������ͬ��������źõ����н��бȽϣ����������ע���������������������ͬ��ֵ��ͬ��Ԫ�صĴ���
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> intersection;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(intersection));//���intersectionΪ{2,5,5}

    //set_symmetric_difference
        //���Ӷȣ�2��(N1+N2-1)
        //������������ͬ��������źõ����н��бȽϣ�����ԳƲ��ע���������������������ͬ��ֵ��ͬ��Ԫ�صĴ���
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> s_diff;
    set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(s_diff));//���s_diffΪ{1,5,7,9}

    //set_union
        //���Ӷȣ�2��(N1+N2-1)
        //������������ͬ��������źõ����н��бȽϣ����������ע���������������������ͬ��ֵ��ͬ��Ԫ�صĴ���
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> _union;
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_union));//���_unionΪ{1,2,5,5,5,7,9}



    //equal������mismatch����


    //is_permutation
        //���Ӷȣ�N^2
        //�����ڷ�Χ [first1, last1) ��Ԫ�ص����У�ʹ�ø÷�Χ���� [first2,last2) ���򷵻� true ������������������ last2 ���� first2 + (last1 - first1) ��
    v1 = { 1, 2, 4,3,5 };
    v2 = { 1, 2, 5, 4, 3 };
    bool is_per = is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end());//����true

    //next_permutation
        //���Ӷȣ�N/2�αȽ�
        //�任��Χ [first, last) Ϊ�������а������ operator< �� comp ���ֵ�����¸����С����������д����򷵻� true ������任��ΧΪ�׸����У���ͬ�� std::sort(first, last) �������� false ��
    v1 = { 1, 2, 3 };
    bool next_per_exist = next_permutation(v1.begin(), v1.end());//v1���132�����true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1���213�����true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1���231�����true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1���312�����true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1���321�����true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1���123�����false

    //prev_permutation�÷�����

    //accumulate����ֵ���㺯��  ��



    return 0;

}
