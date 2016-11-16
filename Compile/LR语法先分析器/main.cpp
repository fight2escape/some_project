#include<iostream>
#include<string>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

/*
词法分析部分
*/
fstream fin("in.txt");
string input;
char token[255]="";
int p_input;
int p_token;
string word[2];
char ch;
int row;
string tab[100] = {"if","then","else","end","procedure","repeat","while","do","read","write","int","until","char","const","break","eof"};

void getbc(){
    while(ch==' '||ch=='\t')
    {
        ch = input[p_input];
        p_input++;

    }
}
int letter()
{
    return (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')?1:0;
}
int digit()
{
    return (ch>='0'&&ch<='9')?1:0;
}
char m_getch()
{
    ch = input[p_input];
    p_input++;
    return ch;
}
void concat()
{
    token[p_token] = ch;
    p_token++;
    token[p_token] = '\0';
}
string reserve()
{
    int i=0;
    char buf[100];
    while(tab[i]!="eof")
    {
        if(tab[i]==token)
        {
        	sprintf(buf,"%d",i+1);//将int转换成string，先寄存在缓存buf中
        	string str(buf);//然后定义一个string类型的，以buf赋初值
            return str;//关键字
        }
        i++;
    }
    string str = "100";//标识符
    return str;
}
void retract()
{
    p_input--;
}
string scaner()
{
    p_token = 0;
    m_getch();
    getbc();
    if(letter())
    {
        while(letter()||digit())
        {
            concat();
            m_getch();
        }
        retract();
        if(reserve() == "100")
        {
            word[0] = "100";
            word[1] = token;  //标识符
        }
        else    //关键字
        {
            word[0] = reserve();
            word[1] = token;
        }

    }
    else if(digit())
    {
        while(digit())
        {
            concat();
            m_getch();
        }
        retract();
        word[0] = "101";
        word[1] = token;
    }
    else switch(ch)
        {
        case '=':
            m_getch();
            if(ch=='=')
            {
                word[0] = "102";
                word[1] = "==";

            }
            else
            {
                retract();
                word[0] = "103";
                word[1] = "=";

            }
            break;
        case '+':
            word[0] = "104";
            word[1] = "+";
            break;
        case '*':
            word[0] = "106";
            word[1] = "*";
            break;
        case '/':
            m_getch();
            if(ch=='/')
            {
                word[0] = "107";
                word[1] = "//";
                while(m_getch() && ch!='\n')
                {
                    cout<<ch;
                }
                cout<<endl;
            }
            else
            {
                retract();
                word[0] = "108";
                word[1] = "/";
            }
            break;
        case '%':
            word[0] = "109";
            word[1] = "%";
            break;
        case '<':
            m_getch();
            if(ch=='>')
            {
                word[0] = "110";
                word[1] = "<>";
            }
            else if(ch=='<')
            {
                word[0] = "111";
                word[1] = "<<";
            }
            else
            {
                retract();
                word[0] = "112";
                word[1] = "<";
            }
            break;
        case '>':
            m_getch();
            if(ch=='>')
            {
                word[0] = "113";
                word[1] = ">>";
            }
            else
            {
                retract();
                word[0] = "114";
                word[1] = ">";
            }
            break;
        case '{':
            word[0] = "115";
            word[1] = "{";
            break;
        case '}':
            word[0] = "116";
            word[1] = "}";
            break;
        case ';':
            word[0] = "117";
            word[1] = ";";
            break;
        case '[':
            word[0] = "118";
            word[1] = "[";
            break;
        case ']':
            word[0] = "119";
            word[1] = "]";
            break;
        case '\'':
            word[0] = "120";
            word[1] = "\'";
            break;
        case '(':
            word[0] = "121";
            word[1] = "(";
            break;
        case ')':
            word[0] = "122";
            word[1] = ")";
            break;
        case '-':
            m_getch();
            if(ch == '>'){
                word[0] = "123";
                word[1] = "->";
            }else{
                retract();
                word[0] = "105";
                word[1] = "-";
            }
            break;
        case '|':
            word[0] = "124";
            word[1] = "|";
            break;
        default:
            if(p_input>input.size()){
                word[0] = "998";
                word[1] = "endl";
            }else{
                word[0] = "999";
                word[1] = ch;
            }
        }
    //cout<<"( "<<word[0]<<" , "<<word[1]<<" )\n";
    return  word[0];
}
void print_line(){
    cout<<"\n===================ROW "<<row<<": ";
    for(int i=0; i<input.size(); i++)
    {
        cout<<input[i];
    }
    cout<<""<<endl;
}

/*
LR语法分析部分：***********************************************************
*/
void error_show(string);
void match(string ,string);
void program();
void oneline();
void getge();
void getvt();
bool vt_exist(string);
void mk_table();
void make_tb();


string vts[30];// 存储非终结符的string数组
int vts_k = 0;// 非终结符的数量
string ges[30][30];// 存储文法的二维数组，每行是一行文法的存储，每个单元格是一个字符
int ges_k = 0;// 文法表达式的行数
int ges_k_k[30];// 每行表达式的字符数量
string state;
string table[20][100] = {
    {
        " ","+","*","(",")","i","#","E","T","F"
    },
    {
        "0"," "," ","S4"," ","S5"," ","1","2","3"
    },
    {
        "1","S6"," "," "," "," ","ACC"," "," "," "
    },
    {
        "2","R2","S7"," ","R2"," ","R2"," "," "," "
    },
    {
        "3","R4","R4"," ","R4"," ","R4"," "," "," "
    },
    {
        "4"," "," ","S4"," ","S5"," ","8","2","3"
    },
    {
        "5","R6","R6"," ","R6"," ","R6"," "," "," "
    },
    {
        "6"," "," ","S4"," ","S5"," "," ","9","3"
    },
    {
        "7"," "," ","S4"," ","S5"," "," "," ","10"
    },
    {
        "8","S6"," "," ","S11"," "," "," "," "," "
    },
    {
        "9","R1","S7"," ","R1"," ","R1"," "," "," "
    },
    {
        "10","R3","R3"," ","R3"," ","R3"," "," "," "
    },
    {
        "11","R5","R5"," ","R5"," ","R5"," "," "," "
    }
};

//判断字符是否是终结符
bool vt_exist(string str){
    for(int i=0;i<vts_k;i++){
        if(str == vts[i]){
            return true;
            break;
        }
    }
    return false;
}
//获取文法的lastvt()集合
//获取终结符
void getvt(){
    p_input = 0;
    getline(fin,input);
    print_line();
    while(p_input<input.size()-1){
        scaner();
        vts[vts_k++] = word[1];
    }
//    cout<<"读取第一行得到非终结符：";
//    for(int i=0;i<vts_k;i++){
//        cout<<vts[i]<<"  ";
//        //table[0][i+1] = vts[i];//算符分析表
//        //table[i+1][0] = vts[i];//算符分析表
//    }
//    cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;;
    //算符分析表 初态
    cout<<"算符优先分析表：---------------------------------------"<<endl;
    for(int i=0;i<13;i++){
        cout<<"|  ";
        for(int j=0;j<10;j++){
            cout<<table[i][j]<<"    ";
        }
        cout<<"      |"<<endl;
    }
    cout<<"-------------------------------------------------------"<<endl;
}
//获取算符文法G[E]
void getge(){
    getline(fin,input);
    row++;
    int n = input[0]-'0';
    //cout<<"G[E]的表达式有:"<<n<<"行"<<endl;
    for(int i=0;i<n;i++){
        getline(fin,input);
        row++;
        print_line();
        p_input = 0;

        ges_k_k[i] = 0;
        while(p_input < input.size()){
            scaner();
            ges[ges_k][ges_k_k[i]] += word[1];
            ges_k_k[i]++;
        }
        ges_k++;
//        cout<<"本行文法: ";
//        for(int j=0;j<ges_k_k[i];j++){
//            cout<<ges[i][j]<<"";
//        }
//        cout<<endl;
    }
}
int getRow(string str){
    for(int i=1;i<9;i++){
        if(str == table[i][0]){
            return i;
        }
    }
    return 0;
}
int getCol(string str){
    for(int i=1;i<9;i++){
        if(str == table[0][i]){
            return i;
        }
    }
    return 0;
}
void oneline(){
    string todo;
    string stk_anl = "#";
    int stk_k = 1;
    string s_input = input;
    state = "0";
    int row;
    int col;
    int ge_k;
    while(){
        row = getRow(state);
        col = getCol(word[1]);
        todo = table[row][col];
        if(isdigit(todo[0])){
            state = todo;
        }else{
            if(todo[0]=="S"){
                if(todo.size()>2){
                    state = todo[1]+todo[2];
                }else{
                    state = todo[1];
                }
                stk_anl[stk_k] = word[1];
                scaner();
            }else if(todo[0]=="R"){
                if(todo.size()>2){
                    state = todo[1]+todo[2];
                    ge_k = todo[1]-'0';
                    ge_k *= 10;
                    ge_k += todo[2]-'0';
                }else{
                    state = todo[1];
                    ge_k = todo[1]-'0';
                }
                ge_k--;
                stk_k -= ges[ge_k].size()-3-1;
                stk_anl[stk_k] = ges[ge_k][0];
                //cout<<stk_anl<<endl;
            }else{

            }
        }
    }
}
//逐行读取，逐行处理
void program(){
    bool flag_end = false;//是否已经读取到文件末尾
    while(getline(fin,input))
    {
        p_input = 0;
        scaner();
        // 空行跳过
        while(word[1]=="endl"){
            if(getline(fin,input)){
                row++;
                //print_line();
                p_input = 0;
                scaner();
            }else{
                flag_end = true;//已经到末尾，标注后，下面不再进行匹配,直接break退出
                break;
            }
        }
        if(flag_end){
            break;
        }
        //格式好看点
        cout<<"|\n|\n|\n|\n|\n";
        for(int i=0;i<3;i++){
            cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        }
        print_line();
        row++;
        //
        oneline();
    }
    cout<<"\n\n\n";
    return;
}
void match(string str,string err_info){
    if(str!=word[1]){
        error_show(err_info);
    }else{
        scaner();
    }
}
void error_show(string info){
    cout<<"+-----------------------------------------error row "<<row<<": "<<info<<endl;
}


int main()
{
    row=1;
    getvt();
    getge();
    program();
    return 0;
}

