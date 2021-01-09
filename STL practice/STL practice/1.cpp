#include <iostream>
#include <algorithm>
#include<numeric>
#include <vector>
#include <string>
#include <list>
#include <deque>

using namespace std;

//C++ class 演示
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












//mismatch演示函数
string mirror_ends(const string& in)
{
    return string(in.begin(), mismatch(in.begin(), in.end(), in.rbegin()).first);
}


int main()
{

    list<int> list_int;


    //--------------标准库函数练习---------------

    //partial_sum   https://www.jianshu.com/p/e68a11d5b316
        //复杂度N
    list_int = { 1,2,3,4,5 };
    list<int>list_result;
    list_result.resize(list_int.size());
    partial_sum(list_int.begin(), list_int.end(), list_result.begin());//累加,若输入list_int = { 1,2,3,4,5 }则输出list_result = {1,3,6,10,15}
    partial_sum(list_int.begin(), list_int.end(), list_result.begin(),multiplies<int>());//累乘,若输入list_int = { 1,2,3,4,5 }则输出list_result = {1,2,6,24,120}

    //lambda表达式简易版
    list_int = { 1,2,3,4,5 };
    int n = count_if(list_int.begin(), list_int.end(), [](int x) {return x >= 2; });//x是形参，被iterator赋值。运行结果输出n=4

    //all_of, none_of, any_of
        //复杂度N
    bool yn;
    yn = all_of(list_int.begin(), list_int.end(), [](int i) { return i % 2 == 0; });//输出yn=false
    yn = all_of(list_int.begin(), list_int.end(), [](int i) { return i >= 0; });//输出yn=true。any_of none_of用法差不多
    
    //for_each和for_each_n效果类似于用for循环遍历容器。没啥意义。

    //count, count_if
        //复杂度N
    int target = 1;
    n = count(list_int.begin(), list_int.end(), target);//输出n=1,count_if的例子见lambda表达式例子

    //mismatch
    //复杂度：N （第一个容器的大小）
    //输入为四个，分别是第一个容器的始终iterator和第二个容器的始终iterator。也就是二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义。若不提供 last2 ，则它指代 first2 + (last1 - first1) 。
    //返回一个pair，这个pair第一个元素是两个容器第一次出现元素不相同时的第一个容器的iteratr，
    //第二个元素是两个容器第一次出现元素不相同时的第二个容器的iteratr。如果两个容器序列完全相同，则输出的是两个容器的.end()。
    //以下程序可以计算一个输入字符串里，确定同时在起始与在其结尾按逆序同时找到的最长相同子串（可能重叠）。
        cout << mirror_ends("abXYZba") << '\n'
            << mirror_ends("abca") << '\n'
            << mirror_ends("aba") << '\n';
    //输出结果：ab
        //a
        // aba


   //find, find_if
        //复杂度：N
        //find输入有三个，分别是始终iterator和目标值。返回仅一个iterator，为target第一次出现时的位置。如未找到目标值则返回.end()
        target = 2;
        auto it = find(list_int.begin(), list_int.end(), target);//找到第一个2的位置
        //find_if输入也有三个，类似于count_if,返回仅一个iterator
        it = find_if(list_int.begin(), list_int.end(), [](int x) { return x % 2 == 0; });//找到第一个偶数的位置


    list_int = { 1,2,3,4,5 };
    list<int> list_int2 = { 2,3,4};
    //find_end
        //复杂度：至多比较 S*(N-S+1) 次，其中 S = distance(s_first, s_last) 而 N = distance(first, last) 。
        //在范围 [first, last) 中搜索序列 [s_first, s_last) 的最后一次出现位置，返回iterator。如未找到则返回.end. 
        //当然也可以增加lambda表达式来改变“相等”的比较策略。
    it = find_end(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end());//若输入list_int2 = { 2,3,4}则输出it为指向list_int中元素2的iterator
    int dist = distance(list_int.begin(),it);//计算得到it所指元素的index为 1。注意distance函数里面的两个参数顺序不可调换。是第二个iterator减去第一个iterator（否则会因为链表闭环结构的iterator而出错）。


    list_int2 = { 4,2,4 };
    //find_first_of
        //复杂度：至多做 (S*N) 次比较，其中 S = distance(s_first, s_last) 而 N = distance(first, last) 。
        //从头遍历 [first, last) ，每到一个元素便和 [s_first, s_last) 中的任何元素进行比较，如果找到相同元素，则输出此时位于[first, last)中的iterator。
        //当然，这里的“相同”比较策略也可以
    it = find_first_of(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end());//若输入list_int2 = { 4,2,4 }则输出it为指向list_int中元素2的iterator
    it = find_first_of(list_int.begin(), list_int.end(), list_int2.begin(), list_int2.end(), [](float a, float b) { return a / b == 1.25; });//输出it为指向list_int中元素5的iterator



    //附：string和vector互相转换。将string转化成标准库容器再处理其实不错。
    string str = "abcddea";
    vector<char>vec_char;
    vec_char.assign(str.begin(), str.end());//string to vector
    string str2;
    str2.assign(vec_char.begin(), vec_char.end());//vector to string

    //adjacent_find
        //复杂度:N
        //从头遍历 [first, last) ，每到一个元素便和下一个元素进行比较，如果相同，则输出第一个元素的iterator。“相同”策略可以换成别的。
    auto it_vec_char = adjacent_find(vec_char.begin(), vec_char.end());//如果vec_char内容为abcddea，则返回一个指向vec_char中第一个d的it
    auto itt = adjacent_find(str.begin(), str.end());//如果str内容为abcddea，则返回一个指向str中第一个d的指针。d也是一个string，内容是"ddea"。
    it_vec_char = adjacent_find(vec_char.begin(), vec_char.end(), greater<char>());//返回一个指向vec_char中e的it。因为用了greater作为比较函数。此方法可以判断序列是否为升序。less的话可以判断降序。



    //search
        //复杂度：至多做 (S*N) 次比较，其中 S = distance(s_first, s_last) 而 N = distance(first, last) 。
        //搜索范围 [first, last - (s_last - s_first)) 中元素子序列 [s_first, s_last) 的首次出现。返回iterator指向子序列第一次出现的位置。否则输出last。
    string str3 = "abcddea, er, asd , 123, er1,as";
    string str4 = "3, e";
    auto it_str = search(str3.begin(), str3.end(), str4.begin(), str4.end());//如果str3为"abcddea, er, asd , 123, er1,as"，str4为"3, e"则返回一个ite（指针），指向"3, er1,as"这个string。
        //注意search源代码里，传给predicate的是两个元素。predicate会被循环调用，挨个元素比较子串str4和str3中某个地方开始的部分
    it_str = search(str3.begin(), str3.end(), str4.begin(), str4.end(), [](char c1, char c2) {return c2 == c1  && c2 != ' '; });//要求子串存在于str3中且子串中不能有空格。此处因找不到而返回str3.end()。


    //copy, copy_if
        //复杂度：使用N次pred，以及使用N次赋值。
        //可以在同一个容器中进行复制，只要两段的范围不同。copy_if就可以加pred限制条件。
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = "3, e";
    copy(str4.begin(), str4.end(), str3.begin());//将str4全部范围内的值拷贝并覆盖到str3头部。因为使用了.begin所以str3必须必str4大。
    str3 = "abcddea, er, asd , 123, er1,as";
    string str6;
    copy(str3.begin(), str3.end(), back_inserter(str6));//将str3全部范围内的值拷贝并覆盖到str6头部。因为使用了back_inserter所以str6不必比str3大。


    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = "3, e";
    copy_if(str4.begin(), str4.begin() + 3, str3.begin(), [](char a) {return a != ' '; });//仅将str4中前3个不为空格的字符复制并覆盖到str3中头部。如果str3为"abcddea, er, asd , 123, er1,as"，str4为"3, e"则结束后str3 = "3,cddea, er, asd , 123, er1,as"


    //copy_backward可以通过copy用rbegin等来实现。逆序读取复制来源范围。
    str3 = "abcddea, er, asd , 123, er1,as";
    copy_if(str4.rbegin(), str4.rbegin() + 3, str3.begin(), [](char a) {return a != ' '; });//str3为"e,cddea, er, asd , 123, er1,as"

    //move：将一段范围内的元素移动到另一范围内。对于不能copy的元素有奇效，比如thread。

    //fill
        //赋值给定的 value 给 [first, last) 中的元素。没有pred。
    string str5 = "123";
    fill(str5.begin(), str5.end(), 's');//"sss"

    //fill_n
        //若 count > 0 ，则赋值给定的 value 给始于 的范围的首 count 个元素。否则不做任何事。
    str5 = "123";
    fill_n(str5.begin(), 2, 's');//"ss3"

    //transform,generate略


    //remove,remove_if  堪称STL里最容易让人混淆的函数  https://blog.csdn.net/vbanglev/article/details/1512521
        //因为remove无法知道它正在操作的容器，所以remove不可能从一个容器中除去元素。这解释了另一个令人沮丧的观点——从一个容器中remove元素不会改变容器中元素的个数
        //remove将需要删除的元素往容器后方移动，将需要保留的元素往容器前方移动。返回一个指向第一个待删除元素的iterator。remove搭配各种容器自带的erase函数就可以完成删除元素的操作。
        //（remove返回的iterator指向该容器中的某个位置，这个位置及以后都是待删除元素）  
        //复杂度：使用N次pred
    str3 = "abcddea, er, asd , 123, er1,as";

        //下列代码从 string 移除所有空格
    str3.erase(remove(str3.begin(), str3.end(), 'a'), str3.end());//如果str3 = "abcddea, er, asd , 123, er1,as"则输出str3为"abcddea,er,asd,123,er1,as"
        //remove_if 可以将“相等”比较策略用pred替换
    str4= "abcddea,\ner,\tasd ,\f123, er1,as";
    str4.erase(remove_if(str4.begin(), str4.end(), [](char x) {return isspace(x);}), str4.end());//如果str4 = "abcddea,\ner,\tasd ,\f123, er1,as"则输出str4为"abcddea,er,asd,123,er1,as"


    //remove_copy可以通过copy_if来实现

    //replace略

    //swap
    int a = 5;
    int b = 3;
    swap(a, b);//a与b的值互相交换


    //swap_ranges
        //复杂度：N
        //在范围 [first1, last1) 和始于 first2 的另一范围间交换元素。
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = str3;
    for (auto it_str = str4.begin(); it_str != str4.end(); it_str++) { *it_str = toupper(*it_str); }//str4变成"ABCDDEA, ER, ASD , 123, ER1,AS"
    swap_ranges(str4.begin() + 1, str4.begin() + 2, str3.begin() + 1);//str3变成"aBcddea, er, asd , 123, er1,as"，str4变成"AbCDDEA, ER, ASD , 123, ER1,AS"

    
    //reverse
        //复杂度：N
        //反转 [first, last) 范围中的元素顺序
    str3 = "abcddea, er, asd , 123, er1,as";
    reverse(str3.begin() + 1, str3.end() - 1);//str3变成"aa,1re ,321 , dsa ,re ,aeddcbs"


    //rotate
        //复杂度：N
        //三个参数(first, n_first, last)交换范围 [first, last) 中的元素，使得元素 n_first 成为新范围的首个元素，而 n_first - 1 成为最后元素(轮转）
    str3 = "abcddea, er, asd , 123, er1,as";
    rotate(str3.begin(), str3.begin() + 9, str3.end());//str3变成"er, asd , 123, er1,asabcddea, "相当于从原str3第10个字符开始轮转

    //shift略

    //random_shuffle和sample略

    //unique
        //复杂度：N
        //从来自范围 [first, last) 的相继等价元素组消除首元素外的元素，并返回范围的新逻辑结尾的尾后迭代器。
        //该操作和remove的相同之处在于只能将待删除元素移动到容器后部，必须借助容器自身的erase函数来完成删除。
        //“相同”的判断策略也可以用pred来替换，类似于remove_if
    str3 = "abcddea, er, asd , 123333, er1,aaaas";
    str3.erase(unique(str3.begin(), str3.end()), str3.end());//如果str3 = "abcddea, er, asd , 123333, er1,aaaas"则输出str3为"abcdea, er, asd , 123, er1,as"
    vector <float> vec_unique = { 1,1.5,1.75,2,3,4,5,6 };
    vec_unique.erase(unique(vec_unique.begin(), vec_unique.end(), [](float x, float y) {return abs(x - y) <= 1; }), vec_unique.end());//删除了连续的差值在1以内的元素，输出{1,3,5}


    //stable_partition
         //复杂度：N (有充足内存时），否则为NlogN
        //重排序范围 [first, last) 中的元素，使得谓词 p 对其返回 true 的元素前于谓词 p 对其返回 false 的元素。保持相对顺序。
        //返回指向第二组元素首元素的迭代器。
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    it_str = stable_partition(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });//如果输入str3 = "abcddea, er, ASd , 123, er1,as{():";则输出str3为":)({,1 , ,3, 21  ,dSAreaeredasdcba"
        //返回的it_str指向":)({,1 , ,3, 21  ,dSAreaeredasdcba"中第一个d
        //partition略


    //is_partitioned
        //复杂度：N
        //若范围 [first, last) 中的所有满足 p 的元素都出现在所有不满足的元素前则返回 true 。若 [first, last) 为空亦返回 true 。
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    it_str = stable_partition(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });
    bool _is_partitioned = is_partitioned(str3.begin(), str3.end(), [](char c) {return c < 'A' || c > 'z'; });//返回true


    //sort, stable_sort,is_sorted
        //复杂度：sort应用pred NlogN次,stable_sort应用pred Nlog(N^2)次（内存充足则 NlogN次），is_sorted复杂度为N
    str3 = "abcddea, er, ASd , 123, er1,as{():";
    sort(str3.begin() + 1, str3.end(), [](char a, char b) {return b < a; });//降序，返回str3="a{srreeedddcbaaSA:3211,,,,,)(     "。如不及加pred则默认升序
    bool _is_sorted_dec = is_sorted(str3.begin() + 1, str3.end(), [](char a, char b) {return b < a; });//返回true。如不及加pred则默认升序


    
    //binary_search
        //复杂度：以2为底的log（N）
        //仅能在已 升序 排序后的序列上使用。
          //返回bool
    bool _found = binary_search(str3.begin() + 1, str3.end(), 'a');//返回false,因为str3不是升序排序


    //merge
        //复杂度：至多 std::distance(first1, last1) + std::distance(first2, last2) - 1 次比较。
        //将两个按照相同排序规则排好的序列归并成一个序列，输出到第三个序列里。
    str3 = "abcddea, er, asd , 123, er1,as";
    str4 = str3;
    string result;
    for (auto it_str = str4.begin(); it_str != str4.end(); it_str++) { *it_str = toupper(*it_str); }//str4变成"ABCDDEA, ER, ASD , 123, ER1,AS"
    sort(str3.begin(), str3.end());//"     ,,,,,1123aaaabcdddeeerrss"
    sort(str4.begin(), str4.end());//"     ,,,,,1123AAAABCDDDEEERRSS"
    merge(str4.begin(), str4.end(), str3.begin(), str3.end(), back_inserter(result));//输出result = "          ,,,,,,,,,,11112233AAAABCDDDEEERRSSaaaabcdddeeerrss"

    //inplace_merge略


    //include貌似可以用search来代替，但include的时间复杂度为2·(N1+N2-1)而search为N1·N2


    //set_difference
        //复杂度：2·(N1+N2-1)
        //将两个按照相同排序规则排好的序列进行比较，输出集合1减去集合2（注意顺序）的差集到第三个序列里。注意其对两个集合中数量不同但值相同的元素的处理。
    vector<int> v1 = { 1, 2, 5, 5, 5, 9 };
    vector<int> v2 = { 2, 5, 7 };
    vector<int> diff;
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(diff));//输出diff为{1,5,5,9}
    diff = {};
    set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), back_inserter(diff));//输出diff为{7}

    //set_intersection
        //复杂度：2·(N1+N2-1)
        //将两个按照相同排序规则排好的序列进行比较，输出交集。注意其对两个集合中数量不同但值相同的元素的处理。
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> intersection;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(intersection));//输出intersection为{2,5,5}

    //set_symmetric_difference
        //复杂度：2·(N1+N2-1)
        //将两个按照相同排序规则排好的序列进行比较，输出对称差集。注意其对两个集合中数量不同但值相同的元素的处理。
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> s_diff;
    set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(s_diff));//输出s_diff为{1,5,7,9}

    //set_union
        //复杂度：2·(N1+N2-1)
        //将两个按照相同排序规则排好的序列进行比较，输出并集。注意其对两个集合中数量不同但值相同的元素的处理。
    v1 = { 1, 2, 5, 5, 5, 9 };
    v2 = { 2, 5, 5, 7 };
    vector<int> _union;
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_union));//输出_union为{1,2,5,5,5,7,9}



    //equal可以用mismatch代替


    //is_permutation
        //复杂度：N^2
        //若存在范围 [first1, last1) 中元素的排列，使得该范围等于 [first2,last2) ，则返回 true ，若不给出，则其中 last2 代表 first2 + (last1 - first1) 。
    v1 = { 1, 2, 4,3,5 };
    v2 = { 1, 2, 5, 4, 3 };
    bool is_per = is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end());//返回true

    //next_permutation
        //复杂度：N/2次比较
        //变换范围 [first, last) 为来自所有按相对于 operator< 或 comp 的字典序的下个排列。若这种排列存在则返回 true ，否则变换范围为首个排列（如同用 std::sort(first, last) ）并返回 false 。
    v1 = { 1, 2, 3 };
    bool next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成132，输出true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成213，输出true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成231，输出true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成312，输出true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成321，输出true
    next_per_exist = next_permutation(v1.begin(), v1.end());//v1变成123，输出false

    //prev_permutation用法类似

    //accumulate等数值运算函数  略



    return 0;

}
