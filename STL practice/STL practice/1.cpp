#include <iostream>
#include <algorithm>
#include<numeric>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>

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














    //--------------标准库容器练习---------------


    //常用容器有string，vector，list，set，map，multimap，以及set map系列的四个无序版


    //----  string

        // = 等号赋值的使用方法。下列代码输出str1都为"abc"。
    string str1; str2 = "abc";
    str1 = "abc";
    str1 = { 'a','b','c' };
    str1 = str2;
    
        //assign  下列代码输出str1都为"abc"。
    str2 = "abc";
    str1.assign(str2);
    list <char> list_char; list_char.push_back('a'); list_char.push_back('b'); list_char.push_back('c');
    str1.assign(list_char.begin(), list_char.end());//list_char换成别的vector <char>或者string也行，即保证iterator的值为char即可。

        //front和back，以及可以用[]访问元素
    cout << str1.front() << str1.back() << endl;//输出两个字符ac

        //size 输出含有的char个数
        
        //empty 输出bool值，是否为空。

        //erase 此处仅列出两种常用用法
    str1 = "abcd";
    str1.erase(str1.begin());//删除一个元素
    str1.erase(str1.end()-1);//删除最后一个元素（注意与insert的区别）
    str1.erase(str1.begin(), str1.begin() + 2);//删除一串元素(2个)
    str1 = "abcd";
    str1.erase(2,3);//输出"a,b"

        //clear 清除内容

        //insert  此处仅列出两种常用用法
    str1 = "abc";
    str1.insert(str1.end() - 1, 'f');//在容器中间插入一个元素，如果str1 = "abc"则插入结果为"abfc"
    str1 = "abc";
    str1.insert(str1.end(), 'f');//在容器末尾插入一个元素，如果str1 = "abc"则插入结果为"abcf"
    str1 = "abc";
    str2 = "ff";
    str1.insert(str1.begin() + 1, str2.begin(),str2.end());//插入一串元素

        //push_back和pop_back，还有append等，建议用insert和erase来代替。

        //+=操作符，string特有。在后面添加东西。
    str1 = "abc";
    str1 += str1;//输出"abcabc"


        //compare 略复杂，后面再说

        //starts_with，ends_with，contains 输出bool值，判断前缀，后缀以及子串存在
    //cout << str1.starts_with('ab'); //C++20才有。输出true。其余函数同理。

        //resize 改变大小
    str1.resize(20);//如果resize后变大，则默认填充'\0'在后面。可以再给resize加一个参数指定填充元素。


        //find可以用std::search代替

        //----下列为与string有关的全局函数。

        //>,<,>=,<=,==,!=比较运算符  按字典顺序比较
    bool test_bool = (string("aaa") > string("aa"));//输出true
    test_bool = (string("aaa") > string("Aaa"));//输出true，因为ascii里大写字母在前

        //stoi, stol, stoll 转换成整数
    str1 = "123";
    int int_fr_st;
    int_fr_st = stoi(str1);//输出123
    str1 = "123.5";
    int_fr_st = stoi(str1);//输出123
    str1 = "123.5 abc";
    int_fr_st = stoi(str1);//输出123（数字必须在string开头，如果数字之前有其他字符则报错）

        //stof, stod, stold 转换成浮点数
    str1 = "123.5";
    float f_fr_st = stof(str1);//输出123.5

        //to_string 将数字转换成string，对于浮点数一般保留6位小数
    str1 = to_string(123);//输出"123"
    str1 = to_string(123.3);//输出"123.300000"
    str1 = to_string(1111123.3);//"1111123.300000"

    



    //----  vector

        //用assign和=赋值
    vector <int> vec1 = { 1,2,3,4};
    vector <int> vec2 = vec1;
    vec2 = { 1,2,3,4 };
    vec2.assign(vec1.begin(), vec1.end());

        //用[]访问元素

        //empty，size等和string类似

        //修改元素的操作：clear，insert，erase，pop_pack，push_back，resize
    vec1 = { 1,2,3,4 };
    vec1.insert(vec1.end(), 1);//输出{ 1,2,3,4,1}
    vec1.erase(vec1.end() - 1);//输出{ 1,2,3,4}。如果删除的元素在容器中间，则自动连接两端。
    //vec1.erase(1, 2);这种表达式是错误的。string可以用常数指定删除范围，vector不可以。
    vec1.push_back(1);//输出{ 1,2,3,4,1}
    vec1.pop_back();//输出{ 1,2,3,4}
    vec1.resize(5, 1);//输出{ 1,2,3,4,1}
    vec1.resize(6);//输出{ 1,2,3,4,1,0} 默认用0填充

        //逻辑运算符：>,<,>=,<=,==，!=  按照字典顺序比较两个vector
    vec1 = { 1,2,3,4 };
    vec2 = { 1,2,3,3,1 };
    test_bool = vec1 > vec2;//输出true
    vec1 = { 1,2,3,4 };
    vec2 = { 1,2,3,4,1 };
    test_bool = vec1 > vec2;//输出false


    


    //list



    //----------- set
        //C++ STL 标准库为 set 容器配置的迭代器类型为双向迭代器。这意味着，假设 p 为此类型的迭代器，则其只能进行 ++p、p++、--p、p--、*p 操作，并且 2 个双向迭代器之间做比较，也只能使用 == 或者 != 运算符。
        //=操作符
    set <int> set1 = { 1,2,3,4,5,4};//set1为{ 1,2,3,4,5}
    set1 = { 1,2,3 };//set1为{ 1,2,3 }
    set <int> set2 = set1;

        //用itetator遍历(只能挨个遍历，不能像别的容器string,vector等一样跳跃)
    for (auto it_set = set1.begin(); it_set != set1.end(); it_set++)
    {
        cout << *(it_set);
    }cout << endl;

        //empty, size同vector

        //clear, insert, erase
    set1.clear();
    set1 = { 1,2,3,4,5 };
    set1.insert(0);//插入一个元素并自动排序，输出{ 0,1,2,3,4,5 }。插入一个元素的时间复杂度为logN （2为底）。
    set2 = { 1,6,7 };
    set1.insert(set2.begin(), set2.end());//插入一串元素，输出{ 0,1,2,3,4,5,6,7 }
    auto it_set = set1.end();
    it_set--;
    set1.erase(it_set);//删除末尾元素,输出{ 0,1,2,3,4,5,6}。这里只展示删除单个元素。可以用first last来界定删除范围。
    for (it_set = set1.begin(); it_set != set1.end(); it_set++)
    {
        if (*it_set == 2) 
        {
            it_set = set1.erase(it_set);//用it删除指定元素。某次循环中删除操作完成后，返回it_set指向的end，set1变为{ 0,1,3,4,5,6 }。时间复杂度：常数
            break;
        }
    }
    set1.erase(3);//根据key值删除单个元素，输出set1={ 0,1,4,5,6 }
    it_set = set1.begin();
    set1.erase(it_set);//根据it删除单个元素但不返回，此时it_set被修改为set1.end()。输出set1为{ 1,4,5,6 }

        
        //find  时间复杂度logN。可以使用STL自带的find函数来查找，但更花时间。
    it_set = find(set1.begin(),set1.end(), 1);//更耗时
    it_set = set1.find(1);//logN


        //逻辑运算符：>,<,>=,<=,==，!=  按照字典顺序比较两个set
    set1 = { 1,2,3,4 };
    set2 = { 1,2,3,3,1 };
    test_bool = set1 > set2;//输出true
    set1 = { 1,2,3,4 };
    set2 = { 1,2,3,4,1 };
    test_bool = set1 > set2;//输出false



    //--------map
        //map的iterator类型和set是一样的。元素（即*iterator）为一个pair

        //=操作符
    map <int, int> map1 = { {1,1},{2,1},{4,5},{3,2} };//会自动按key值升序排列元素。
    map <int, int> map2 = map1;
    map2 = { {1,1},{2,1},{4,5},{6,2} };
        
        //用iterator遍历方式与set相同
    auto it_map = map1.begin();
    for (it_map = map1.begin(); it_map != map1.end(); it_map++)
    {
        cout << (*(it_map)).second;
    }//输出1125

        //[]的用法：访问与插入，时间复杂度logN
    cout << map1[2];//访问key=2的元素并输出其value。
    map1[5] = 10;//插入{5,10}
    map1[6]++;//因为容器内本没有key-6，所以插入{6,1}

        //empty，size用法同vector

        //clear, insert, erase。仅介绍erase。erase的参数可以是key值或者iterator，返回分别为01或者iterator。
    map1 = { {1,1},{2,1},{4,5},{3,2} };
    it_map = map1.begin();
    for (; it_map != map1.end(); )
    {
        if (it_map->first == 1 || it_map->first == 2)
        {
            it_map = map1.erase(it_map);//每次执行完删除操作后，返回的it为指向下一个元素的it。
        }
        else it_map++;
    }//循环结束后map1只剩{{3,2}, {4,5}}
    map1.erase(3);//根据key值删除元素。删掉后只剩下{{4,5}}。注意这种写法返回值是0或者1，而不是iterator。
    auto ret = map1.erase(4);//返回ret为1。set里根据key值删除也会有类似返回。
    map1.erase(3);//企图删除不存在的key，还是得{{4,5}}
        //erase也可以删除范围。

        //find  复杂度logN
    map1 = { {1,1},{2,1},{4,5},{3,2} };
    it_map = map1.find(2);

        //逻辑运算符：>,<,>=,<=,==，!=  按照字典顺序比较两个map的key


       
    //-------unordered_map
        //迭代器类型为LegacyForwardIterator，只能有=，==，++的操作。遍历哈希表没啥意义。

        //=操作符

        //[]操作符访问或插入元素。复杂度一般为O（1），最坏情况为O（N）
        
        //可以说除了iterator与算法时间复杂度与map不同以外，其他函数用法与map完全相同。



    
















    return 0;

}
