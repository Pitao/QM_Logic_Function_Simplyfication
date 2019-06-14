#include "QMLOG.h"

//�Էֲ���
template<class T>
int find(vector<T> vect,T elem)
{
	int left = 0;
	int right = vect.size() - 1;
	while(left<=right)
	{
		int mid = (left + right) / 2;
		if (vect[mid] == elem)
			return mid;
		else if (vect[mid] < elem) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}
vector<int> dfs(vector<int> depth, string Consum,
	vector<string> Table,
	vector<QM_CONSOLIDATION> ConsolidationTable, 
	const string & normal)
{
	//���dfs���׻��߷���������������
	if (Table.empty() || Consum == normal)
	{
		return depth;
	}
	//��״dfs
	vector<int> ans(1, 0);
	for (int i =depth[0]; i < Table.size(); i++)
	{

		string str = Table[i];
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == '1')
				Consum[j] = '1';
		}
		depth[depth[0] + 1] = ConsolidationTable[i].PopIndex();
		//depth.push_back(ConsolidationTable[i].PopIndex());
		depth[0]++;
		//Table.erase(Table.begin() + i);
		//ConsolidationTable.erase(ConsolidationTable.begin() + i);
		vector<int> temp=dfs(depth, Consum, Table, ConsolidationTable,normal);
		if (temp[0] < ans[0] ||ans[0]==0)
			ans = temp;
		depth[0]--;
	}
	return ans;
}
//���鹹�캯��
QMLOG::QMLOG(int arr[], int n)
{
	vector<int> temp(arr, arr + n);
	PutItem(temp);
}

//�������캯��
QMLOG::QMLOG(vector<int> & vect)
{
	PutItem(vect);
}

//�������캯��
QMLOG::QMLOG(QMLOG & copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConMinItem = copy.GetSinplest();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();
}

//Ĭ�Ϲ��캯��
QMLOG::QMLOG() :size(0) {}
//��������
QMLOG::~QMLOG() {}

//������=����
void QMLOG::operator=(QMLOG& copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();

}

//��ʼ���ϳɱ�
void QMLOG::InitConList()
{
	int max = *(MinItem.end() - 1); //������ֵ
	int finger = 0;//λ����1
	
	while (max>0)
	{
		max /= 2;
		finger++;
	}
	QMLOG::finger = finger;
	for (int i = 0; i < size; i++)
	{
		ConsolidationTable.push_back({ MinItem[i], finger });
	}
}
//�ϲ�����
void QMLOG::Consolidation()
{
	/*����һ����ʱ�ϲ����汾�κϲ������Ŀ
	  ���κϲ�ɾ���ɵĿɺϲ��ĺϲ���
	  �ܺϲ������ӱ��κϲ����ʽ��
	*/
	vector<QM_CONSOLIDATION> temp_con;
	
	bool over_flag = false; //ȫ���ϲ����
	int size = ConsolidationTable.size();
	bool* single_flag = new bool(size);
	memset(single_flag, false, size);
	//��ѯ
	for (int i = 0; i < size-1; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			//�������ֻ��һλ��ͬ����ϲ����ұ��
			if (Diff(ConsolidationTable[i], ConsolidationTable[j])>=0)
			{
				temp_con.push_back(Merge(ConsolidationTable[i], ConsolidationTable[j]));//�µĺϳ���
				over_flag = true;
				single_flag[i] = true;
				single_flag[j] = true;
			}
		}
	}
	//ɾ���Ѻϲ��ĺϲ���
	for (int i = size-1; i >=0; i--)
	{
		if (single_flag[i])
		{
			ConsolidationTable.erase(ConsolidationTable.begin() + i);
		}
	}
	if (over_flag)
	{
		ConsolidationTable.insert(ConsolidationTable.end(), temp_con.begin(), temp_con.end());
		//copy(temp_con.begin(), temp_con.end(), ConsolidationTable.end());
		Consolidation();
		//delete[] single_flag;
	}

}
//��ʼ���˻���
void QMLOG::InitProductTable()
{

	//ɾ���ϳɱ��е���ͬ��
	for (int i = 0; i < ConsolidationTable.size()-1; i++)
	{
		for (int j = ConsolidationTable.size()-1; j > i; j--)
		{
			if (ConsolidationTable[i] == ConsolidationTable[j])
				ConsolidationTable.erase(ConsolidationTable.begin() + j);
		}
	}
	//for (auto i = ConsolidationTable.begin(); i < ConsolidationTable.end()-1; i++)
	//{
	//	for (auto j = ConsolidationTable.end()-1; j>i; j--)
	//	{
	//		if (*i == *j)
	//			ConsolidationTable.erase(j);
	//	}
	//}
	int MinItem_size = MinItem.size();
	int ConsoTable_size = ConsolidationTable.size();

	//����p���(index)
	for (int i = 0; i < ConsoTable_size; i++)
	{
		ConsolidationTable[i].PushIndex(i);
	}

	MinItem_Flag.assign(MinItem_size, false);  //��С������������
	Index_Flag.assign(ConsoTable_size, false);//�ϳ���������
	//�˻�������
	ProductTable.resize(ConsoTable_size);
	for_each(ProductTable.begin(), ProductTable.end(), [&](vector<int> & x) {
		x.assign(MinItem_size, 0);
		});
	//�˻����������
	/*
	  ��MinItem�л�ȡ��ֵ������ConsolidationTable��Ѱ��
	  �ҵ���¼��ǲ�����
	*/
	for (int i = 0; i < MinItem_size; i++)
	{
		int num = MinItem[i];
		int count = 0;
		vector<int> index_vect;
		for (int j = 0; j < ConsoTable_size; j++)
		{
			auto num_vect = ConsolidationTable[j].PopNum();
			for_each(num_vect.begin(), num_vect.end(), [&](int x) {
				if (x == num)
				{
					count++;
					index_vect.push_back(j);
				}
			});
		}
		for (int j = 0; j < index_vect.size(); j++)
		{
			int line = index_vect[j];
			ProductTable[line][i] = count;
		}
	}
}
//ѡ����С��
void QMLOG::SelectLessItem()
{
	//line p��ʶ��
	//list ��С������
	int line = ConsolidationTable.size();
	int list = MinItem.size();
	//������ά��Ѱ��ֻ����ʶһ�ε���С��������С��Ͷ�Ӧ��p��ʶ
	for (int i = 0; i < list; i++)
	{
		for (int j = 0; j < line; j++)
		{
			if (ProductTable[j][i] == 1)
			{
				Index_Flag[j] = true;
				//MinItem_Flag[i] = true;
				//�����ϱ�׼�ĺϳ�����������С��ȫ�����
				for (int x : ConsolidationTable[j].PopNum())
				{
					int pos = find(MinItem, x);
					if(pos>=0) 
						MinItem_Flag[pos] = true;
				}

			}
		}
	}


}
//����ʣ����
void QMLOG::AddRemainItem()
{
	//���ö�̬�滮�Ż�
	//Ŀǰʹ��dfs
	auto ReMinItem = MinItem;
	auto ReCon = ConsolidationTable;
	//��ʼ��ʣ����
	for (int i = Index_Flag.size()-1; i >=0; i--)
	{
		if (Index_Flag[i])
		{
			ReCon.erase(ReCon.begin() + i);
		}
	}
	for (int i = MinItem_Flag.size() - 1; i >= 0; i--)
	{
		if (MinItem_Flag[i])
		{
			ReMinItem.erase(ReMinItem.begin() + i);
		}
	}
	//��ʼ��ʣ���
	vector<string> ReTable;
	for (int i = 0; i < ReCon.size(); i++)
	{
		string temp;
		//auto vect = ReCon[i].PopNum;
		for (int j = 0; j < ReMinItem.size(); j++)
		{
			bool flag = false;
			//Ѱ�ҵ���
			for (int x : ReCon[i].PopNum())
			{
				if (x == ReMinItem[j]) flag = true;
			}
			if (flag)
				temp += "1";
			else
				temp += "0";
		}
		ReTable.push_back(temp);
	}
	string temp;
	string normal;
	for (int i = 0; i < ReMinItem.size(); i++)
	{
		temp += "0";
		normal += "1";
	}
	vector<int> vect(ReMinItem.size()+1,0);
	vect=dfs(vect,temp, ReTable, ReCon,normal);
	for (int x : vect)
	{
		Index_Flag[x] = true;
	}
}

const QM_CONSOLIDATION QMLOG::Merge(QM_CONSOLIDATION & left, QM_CONSOLIDATION & right)
{
	auto ans = left;
	ans.Merge(right);
	return ans;
}

int QMLOG::Diff(QM_CONSOLIDATION& left, QM_CONSOLIDATION& right)
{
	return left.diff(right);
}

void QMLOG::LogicExpress()
{
	string cList = "ABCDEFGH";
	string ans;
	int size = ConsolidationTable[0].PopBit().size();
	int len = ConsolidationTable.size();
	for (int i=0;i<len;i++)
	{
		if (Index_Flag[i])
		{
			auto tempBit = ConsolidationTable[i].PopBit();
			for (int j = 0; j < size; j++)
			{
				char index = 'A' + j;
				switch (tempBit[j])
				{
				case 0:
					ans += index;
					ans+= "\'";
					break;
				case 1:
					ans += index ;
					break;
				case 2:
					break;

				}
			}
			ans += '+';
		}
	}
	ans.pop_back();
	ConMinItem = ans;
}



//������С������
QMLOG& QMLOG::PutItem(vector<int>& vect)
{
	//���ø���
	size = vect.size();
	//��������������
	MinItem = vect;
	sort(MinItem.begin(), MinItem.end());
	return *this;
}
//ȡ�ý��
string& QMLOG::GetSinplest()
{
	//����Ѿ��н������ֱ�ӷ��أ��������
	if (ConMinItem.empty()==true)
	{
		InitConList();
		Consolidation();

		InitProductTable();

		SelectLessItem();
		AddRemainItem();
		LogicExpress();
	}
	return ConMinItem;
}
//�������
ostream& operator<<(ostream& out, QMLOG& me)
{
	int size = me.Size();
	vector<int> MinItem = me.PopMinItem();			//��С��
	//vector<int> ConMinItem = me.GetSinplest();	//���
	vector<QM_CONSOLIDATION> ConsolidationTable = me.PopConsolidationTable();	//�ϲ���
	vector<vector<int>> ProductTable = me.PopProductTable();				//�˻���
	//��ӡ��С��
	out << "����: " << size << endl<<endl;
	out << "��������ʽ" << endl;
	//for_each(MinItem.begin(), MinItem.end(), [&](int x) {out <<'m'<< x << " + "; });
	out << 'm' << MinItem[0];
	for (int i = 1; i < MinItem.size(); i++)
	{
		out << " + m" << MinItem[i];
	}
	out << endl << endl;
	//��ӡ�ϳɱ�
	if (ConsolidationTable.empty() == true)
	{
		cout << "�޺ϳɱ�" << endl;
	}
	else
	{ 
		out << "�ϳɱ�" << endl;
		out << "P | A B C D E | NUM" << endl;
		out << "-------------------" << endl;
		for_each(ConsolidationTable.begin(), ConsolidationTable.end(), [&](QM_CONSOLIDATION x){
				out << x << endl;
			});
	}
	//��ӡ�˻���
	if (ConsolidationTable.empty() == true)
	{
		cout << "�޳˻���" << endl;
	}
	else
	{
		out << "�˻���" << endl;
		out << "P&M";
		for_each(MinItem.begin(), MinItem.end(), [&](int x) {out << setw(4) << x; });
		out << endl;
		int line = ProductTable.size();
		int list = MinItem.size();
		for (int i = 0; i < line; i++)
		{
			out << ' ' << ConsolidationTable[i].PopIndex() << ' ';
			for (int j = 0; j < list; j++)
			{
				if (ProductTable[i][j]) out << setw(4) << ProductTable[i][j];
				else out << "    ";
			}
			cout << endl;
		}
	}
	cout << endl;
	//������ʽ
	cout <<"���ʽΪ��"<< me.ConMinItem << endl;
	
	return out;
}

