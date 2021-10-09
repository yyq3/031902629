#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
int word_sum;//词总数 
int hang_sum;//行总数 
int ans_sum;//答案总数 
class Sensitive//敏感词类 
{
public:
	string Word;//词内容 
	int Num;//词序号 
	int Length;//词长度 
	bool kind;//敏感词类型 
}SENSITIVE[105];
class Text//文本类 
{
public:
	string Line;//行内容 
	int Num;//行号 
	int Length;//行长度 
}TEXT[5005];
class Ans//答案类 
{
public:
	//	string ans;//答案内容 
	int Head;//答案所在行的头 
	int End;//答案所在行的尾 
	int Sensitive_num;//目标敏感词的序号 
	int Line_num;//目标敏感词所在行 
}ANS[1005];
void read(char* add1, char* add2)//读入words和org 
{
	//string add1;
	//cin >> add1;
	string temp;
	ifstream fp1;
	fp1.open(add1);
	if (!fp1)cout << "error!!!" << endl;
	int i = 0;
	while (!fp1.eof())
	{
		if (fp1.peek() == EOF)break;
		getline(fp1, temp);
		//cout<<temp<<endl;
		SENSITIVE[i].Word = temp;
		SENSITIVE[i].Num = i;
		word_sum = i + 1;
		SENSITIVE[i].Length = temp.length();
		if (SENSITIVE[i].Word[0] > 0)SENSITIVE[i].kind = 0; //英文类型为0 
		else SENSITIVE[i].kind = 1;//汉字类型为1 
		i++;
	}
	fp1.close();
	//	for(int j=0;j<i;j++)
	//	cout<<SENSITIVE[j].Word<<" "<<SENSITIVE[j].Num<<" "<<SENSITIVE[j].Length<<" "<<SENSITIVE[j].kind<<endl;
//	string add2;
//	cin >> add2;
	ifstream fp2;
	fp2.open(add2);
	if (!fp2)cout << "error!!!" << endl;
	i = 0;
	while (!fp2.eof())
	{
		if (fp2.peek() == EOF)break;
		getline(fp2, temp);
		TEXT[i].Line = temp;
		TEXT[i].Num = i;
		hang_sum = i + 1;
		TEXT[i].Length = temp.length();
		i++;
	}
	fp2.close();
	//	for(int j=0;j<i;j++)
	//	cout<<TEXT[j].Line<<" "<<TEXT[j].Num<<" "<<TEXT[j].Length<<endl;
}
void search(int w, int l)//在第l行里搜索第w个敏感词 
{
	int i = 0, j = 0;
	if (SENSITIVE[w].kind)//类型为汉字 
	{
		while (i < TEXT[l].Length)
		{
			if (TEXT[l].Line[i] == SENSITIVE[w].Word[j] && TEXT[l].Line[i + 1] == SENSITIVE[w].Word[j + 1] && TEXT[l].Line[i + 2] == SENSITIVE[w].Word[j + 2])//搜索汉字 
			{
				if (j == 0) ANS[ans_sum].Head = i;
				j = j + 3;
				i = i + 2;
			}
			else if (TEXT[l].Line[i] == SENSITIVE[w].Word[0] && TEXT[l].Line[i + 1] == SENSITIVE[w].Word[1] && TEXT[l].Line[i + 2] == SENSITIVE[w].Word[2])//与下一个目标汉字不同，但与开头汉字相同需重置 
			{
				j = 3;
				ANS[ans_sum].Head = i;
				i = i + 2;
			}
			if (j == SENSITIVE[w].Length)//检测到之后给答案类数组 
			{
				ANS[ans_sum].End = i + 1;
				ANS[ans_sum].Sensitive_num = w;
				ANS[ans_sum].Line_num = l;
				//	string temp(TEXT[l].Line.substr(ANS[ans_sum].Head,ANS[ans_sum].End));
				//	ANS[ans_sum].ans=temp;
				ans_sum++;
				j = 0;
			}
			i++;
		}
	}
	else
	{
		while (i < TEXT[l].Length)//英文类型搜索 
		{
			if (TEXT[l].Line[i] == SENSITIVE[w].Word[j] || TEXT[l].Line[i] == SENSITIVE[w].Word[j] + 32 && SENSITIVE[w].Word[j] > 'A' || TEXT[l].Line[i] == SENSITIVE[w].Word[j] - 32 && TEXT[l].Line[i] > 'A')
			{
				if (j == 0) ANS[ans_sum].Head = i;
				j++;
			}
			else if (TEXT[l].Line[i] == SENSITIVE[w].Word[0] || TEXT[l].Line[i] == SENSITIVE[w].Word[0] + 32 && SENSITIVE[w].Word[j] > 'A' || TEXT[l].Line[i] == SENSITIVE[w].Word[0] - 32 && TEXT[l].Line[i] > 'A')
			{
				j = 1;
				ANS[ans_sum].Head = i;
			}
			else if (TEXT[l].Line[i] >= 'A' && TEXT[l].Line[i] <= 'Z' || TEXT[l].Line[i] >= 'a' && TEXT[l].Line[i] <= 'z')j = 0;
			if (j == SENSITIVE[w].Length)
			{
				ANS[ans_sum].End = i + 1;
				ANS[ans_sum].Sensitive_num = w;
				ANS[ans_sum].Line_num = l;
				//	string temp(TEXT[l].Line.substr(ANS[ans_sum].Head,ANS[ans_sum].End));
				//	ANS[ans_sum].ans=temp;
				ans_sum++;
				j = 0;
			}
			i++;
		}
	}
}
void print(char* add)//输出答案 
{
	//string add;
	//cin >> add;
	ofstream fp;
	fp.open(add);
	if (!fp) cout << "error!!!" << endl;
	fp << "Total:" << ans_sum << endl;
	for (int i = 0; i < ans_sum; i++)
	{
		fp << "Line" << ANS[i].Line_num + 1 << ":<" << SENSITIVE[ANS[i].Sensitive_num].Word << ">";//<<ANS[i].ans;
		for (int j = ANS[i].Head; j < ANS[i].End; j++)  fp << TEXT[ANS[i].Line_num].Line[j];
		fp << endl;
	}
	fp.close();
}
int cmp(Ans& ANS, Ans& b)
{
	if (ANS.Line_num > b.Line_num)return 0;
	else if (ANS.Line_num == b.Line_num)
	{
		if (ANS.Head > b.Head)return 0;
		else return 1;
	}
	else return 1;
}
int main(int argc, char* argv[])
{
	system("chcp 65001");
	read(argv[1], argv[2]);
	for (int i = 0; i < word_sum; i++)
		for (int j = 0; j < hang_sum; j++)
			search(i, j);
	sort(ANS, ANS + ans_sum, cmp);
	print(argv[3]);
	return 0;

}