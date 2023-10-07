/*
╔══╦══╦╗╔╗
║╔═╣╔═╣║║║
║║─║║─║╚╝║
║║─║║─║╔╗║
║╚═╣╚═╣║║║
╚══╩══╩╝╚╝
CCH
Changing Code Handwriting v0

By Emperor of Mankind

*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <climits>
#include <cstring>
#include <complex>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <ctime>
#include <set>
#include <map>
#include <iomanip>
#include <unordered_map>
#include <bitset>
#include <stack>
#include <type_traits>
#include <random>
#include<chrono>
using namespace std;
string code [ 2000 ] ;  // матрица кода
vector<vector<string>> codes (2000) ;  // матрица кода
set < string > ban ; // слова которые отвечаюь за функции, и их не трогать
map<string,string> mp_pere;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<string> type;

long long power_plagiat;
    int num = 1 ;
    string norm_str(string s,bool type)
    {
        string t;
        string t2;
        int flag=0;
        int e=-1;
        for (int i=0;i<s.size();i++)
        {

            if (s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'||s[i]=='_'||s[i]>='0'&&s[i]<='9')
            {
                if (flag==0)
                {

                    flag=1;

                }
                if (flag==0||flag==1) t.push_back(s[i]);
            }
            else
            {
                if (s[i]=='\\') flag=2;
                if (flag==1) flag=2;
            }
            e=i;
            if (flag==2) {t2.push_back(s[i]);}
        }
       // cout<<s<<" "<<t<<" "<<t2<<"ABAB\n";
        if (type==0)  return t;
        else return t2;
    }
void write_code(bool debug)
{
    for (int i=1;i<=num;i++)
    {
        if (debug==1) cout<<i<<" ";
        bool hash_fl=0;
        for (int j=0;j<codes[i].size();j++)
        {
            if (codes[i][j][0]=='#') hash_fl=1;
            //cout<<"A";
//            cout<<codes[i][j];
            if (mp_pere[norm_str(codes[i][j],0)].size()!=0&&hash_fl==0) cout<<mp_pere[norm_str(codes[i][j],0)]<<norm_str(codes[i][j],1);
           else cout<<codes[i][j];
           //cout<<"B";
           if (debug==1) cout<<" ";
        }
        cout<<'\n';
    }

}
bool prov_symbol(string x)
{

for(int i=0;i<x.size();i++)
{

    if (x[i]>='a'&&x[i]<='z'||x[i]>='A'&&x[i]<='Z') return 1;
}
    return 0;
}
bool check_type(string s)
{
    for (int i=0;i<type.size();i++)
    {

        if (s==type[i]) return 1;
    }
    return 0;
}
string generic_string(int sz)
{
    string st;
    for (int i=0;i<sz;i++)
    {
        char s;
        if (rng()%2==0)
        {
         s='a'+(rng()%26);
        }
        else
        {
         s='A'+(rng()%26);
        }
        st.push_back(s);
    }
    return st;
}
int main ( )
{

    freopen("input.txt","r",stdin);

    /*
    Сначала идея
    Надо код поделить на блоки, т.е. на "Шапку", "Блок переменных" "функции" эти же блоки делить на подблоки
    на "ифы", "циклы", "операции"

    Что такое почерк?
    Почерк кода это способы которыми использует сам человек, почерк может содержать определённые название масивов(Переменых), для разных функций, или определённое структура кода
    или шапкой. По почерку вполне можно определить что за человек писал этот код.

    Главная задача программы изменять почерк кода так что бы алгоритмы anti-плагиата площадки codeforces не смогли обнаружить плагиат, и возможно побудить
    создать более совершенную систему анти-плагиата, так как система на площадке не совершенна.

    v0  будет сначала считывать сам код с txt файла и выписывать его в другой txt файл. При этом изменяя название переменных. Структура данных пока не затрагиваеться.
    */

    type.push_back("string");
    type.push_back("int");
    type.push_back("long");
    type.push_back("char");
    type.push_back("bool");
    type.push_back("double");
    type.push_back("void");
    type.push_back("map");
    type.push_back("set");
    type.push_back("unordered_map");
    type.push_back("unordered_set");
    type.push_back("multiet");
    type.push_back("auto");
    type.push_back("vector");
    type.push_back("pair");
    bool return_detected = 0 ;
    while (1!=0)
    {
        getline(cin,code[num]) ;
        //cout<<code[num]<<'\n';
       // if (code[num]=="}") break;
        if (code[num]=="return 0;"){return_detected=1;break;}
    num++;
    }
    if (return_detected==1)
    {

        num++;
        code[num]="}";

    }
    // заполняем список бана
    ban.insert("for");
    ban.insert("if");
    ban.insert("long");
    ban.insert("int");
    ban.insert("double");
    ban.insert("bool");
    ban.insert("vector");


    // сейчас нам надо представить код в более удобной форме, тоесть все слова разделить от симоволов и т.д
    for (int i=1;i<=num;i++)

    {
        string s;
        bool space_unable=0;
        bool push=0;
        bool flag_bibli=0;
        for (int j=0;j<code[i].size();j++)
        {
           /* if (code[i][j]=='#') flag_bibli=1;
            if (flag_bibli==1)
            {
                if (code[i][j]==' ')
                {
                     codes[i].push_back(s);

                s.clear();
                s.push_back(code[i][j]);
                codes[i].push_back(s);
                s.clear();
                continue;

                }
                 s.push_back(code[i][j]);
            }
            */

            if (code[i][j]=='\\'||(code[i][j]=='&'&&code[i][j+1]=='=')||(code[i][j]=='|'&&code[i][j+1]=='=')||(code[i][j]=='|'&&code[i][j+1]=='|')||(code[i][j]=='&'&&code[i][j+1]=='&')||(code[i][j]=='<'&&code[i][j+1]=='<')||(code[i][j]=='>'&&code[i][j+1]=='>')||(code[i][j]=='-'&&code[i][j+1]=='-')||(code[i][j]=='+'&&code[i][j+1]=='+')||(code[i][j]=='='&&code[i][j+1]=='=')||(code[i][j]=='<'&&code[i][j+1]=='=')||(code[i][j]=='>'&&code[i][j+1]=='=')||(code[i][j]=='!'&&code[i][j+1]=='=')||(code[i][j]=='+'&&code[i][j+1]=='=')||(code[i][j]=='-'&&code[i][j+1]=='=')||(code[i][j]=='*'&&code[i][j+1]=='=')||(code[i][j]=='/'&&code[i][j+1]=='='))
            {
                if (s.size()!=0) codes[i].push_back(s);
                s.clear();
                s.push_back(code[i][j]);
                s.push_back(code[i][j+1]);

                codes[i].push_back(s);
                s.clear();
                j++;
                continue;
            }
            if (code[i][j]=='*'||code[i][j]=='/'||code[i][j]=='.'||code[i][j]=='}'||code[i][j]=='{'||code[i][j]=='&'||code[i][j]=='|'||code[i][j]=='^'||code[i][j]=='<'||code[i][j]=='>'||code[i][j]==9||code[i][j]==' '||code[i][j]==';'||code[i][j]=='('||code[i][j]==')'||code[i][j]=='='||code[i][j]=='-'||code[i][j]=='+'||code[i][j]==','||code[i][j]==']'||code[i][j]=='[')
            {
                codes[i].push_back(s);

                s.clear();
                s.push_back(code[i][j]);
                codes[i].push_back(s);
                s.clear();
                continue;
            }
            s.push_back(code[i][j]);
        }
        codes[i].push_back(s);
    }


    vector<string> pere;
    bool pere_on;
    string s;
//    sodgjsjdlsdkjbdf
//    hdfjhdkfmhklsfhsdfh
//    sdfh
//    shfsdfhsdfhsdfj
//    sfjsdfjsdfj
    for (int i=1;i<=num;i++)
    {
        bool wait_coma=0;
        pere_on=0;
        for (int j=0;j<codes[i].size();j++)
        {
            if (codes[i][j]=="main") continue;
            if (codes[i][j]=="struct")
            {
                type.push_back(codes[i][j+2]);
            }
            if (check_type(codes[i][j])==1) {
                //    cout<<i<<" "<<j<<'\n';
                pere_on=1;
                s.clear();
                continue;
            }
            if (codes[i][j]==";"||codes[i][j]=="{") {pere_on=0; s.clear();}
            if (codes[i][j]==",") {wait_coma=0;}
           // cout<<codes[i][j][0]<<" "<<prov_symbol(codes[i][j][0])<<"\n";


            if (prov_symbol(codes[i][j])==1&&pere_on==1&&wait_coma==0)
            {
                wait_coma=1;
                pere.push_back(codes[i][j]);
            }


        }

    }
   // cout<<"N";
    for (int i=0;i<pere.size();i++)
    {
        if (mp_pere[pere[i]].size()==0)
        {
        while (1!=0)
        {
        s=generic_string(110);
        if (mp_pere[pere[i]].size()!=0) continue;
        mp_pere[pere[i]]=s;
        break;
        }
        }
      //  cout<<pere[i]<<" "<<mp_pere[pere[i]]<<'\n';
    }
   // cout<<'\n';
/*
A = JDFHGJSUHEG
id="handleOrEmail"
id="password"
class="submit"


time.sleep(5);
search_box_password = driver.find_element(By.ID, "password")
time.sleep(5);
search_box_email.send_keys("Selenium")
time.sleep(10);
*/
write_code(0);
return 0;
}
