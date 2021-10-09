#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
int word_sum;//������ 
int hang_sum;//������ 
int ans_sum;//������ 
class Sensitive//���д��� 
{
public:
	string Word;//������ 
	int Num;//����� 
	int Length;//�ʳ��� 
	bool kind;//���д����� 
}SENSITIVE[105];
class Text//�ı��� 
{
public:
	string Line;//������ 
	int Num;//�к� 
	int Length;//�г��� 
}TEXT[5005];
class Ans//���� 
{
public:
	//	string ans;//������ 
	int Head;//�������е�ͷ 
	int End;//�������е�β 
	int Sensitive_num;//Ŀ�����дʵ���� 
	int Line_num;//Ŀ�����д������� 
}ANS[1005];
void read(char* add1, char* add2)//����words��org 
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
		if (SENSITIVE[i].Word[0] > 0)SENSITIVE[i].kind = 0; //Ӣ������Ϊ0 
		else SENSITIVE[i].kind = 1;//��������Ϊ1 
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
void search(int w, int l)//�ڵ�l����������w�����д� 
{
	int i = 0, j = 0;
	if (SENSITIVE[w].kind)//����Ϊ���� 
	{
		while (i < TEXT[l].Length)
		{
			if (TEXT[l].Line[i] == SENSITIVE[w].Word[j] && TEXT[l].Line[i + 1] == SENSITIVE[w].Word[j + 1] && TEXT[l].Line[i + 2] == SENSITIVE[w].Word[j + 2])//�������� 
			{
				if (j == 0) ANS[ans_sum].Head = i;
				j = j + 3;
				i = i + 2;
			}
			else if (TEXT[l].Line[i] == SENSITIVE[w].Word[0] && TEXT[l].Line[i + 1] == SENSITIVE[w].Word[1] && TEXT[l].Line[i + 2] == SENSITIVE[w].Word[2])//����һ��Ŀ�꺺�ֲ�ͬ�����뿪ͷ������ͬ������ 
			{
				j = 3;
				ANS[ans_sum].Head = i;
				i = i + 2;
			}
			if (j == SENSITIVE[w].Length)//��⵽֮����������� 
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
		while (i < TEXT[l].Length)//Ӣ���������� 
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
void print(char* add)//����� 
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