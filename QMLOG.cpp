#include "QMLOG.h"

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
			cout << *this;
		}
	}
	if (over_flag)
	{
		ConsolidationTable.insert(ConsolidationTable.end(), temp_con.begin(), temp_con.end());
		//copy(temp_con.begin(), temp_con.end(), ConsolidationTable.end());
		cout << *this; //debug point
		Consolidation();
	}

}
//��ʼ���˻���
void QMLOG::InitProductTable()
{

}
//ѡ����С��
void QMLOG::SelectLessItem()
{

}
//����ʣ����
void QMLOG::AddRemainItem()
{

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
vector<int>& QMLOG::GetSinplest()
{
	//����Ѿ��н������ֱ�ӷ��أ��������
	if (ConMinItem.empty()==true)
	{
		InitConList();
		cout << *this << endl; //debug point
		Consolidation();
		InitProductTable();
		SelectLessItem();
		AddRemainItem();
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
	vector<QM_CONSOLIDATION> ProductTable = me.PopProductTable();				//�˻���

	out << "����: " << size << endl;
	out << "��������ʽ" << endl;
	//for_each(MinItem.begin(), MinItem.end(), [&](int x) {out <<'m'<< x << " + "; });
	out << 'm' << MinItem[0];
	for (int i = 1; i < MinItem.size(); i++)
	{
		out << " + m" << MinItem[i];
	}
	out << endl;

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

	if (ConsolidationTable.empty() == true)
	{
		cout << "�޳˻���" << endl;
	}
	else
	{
		out << "�˻���" << endl;
		out << "P&M";
		for_each(MinItem.begin(), MinItem.end(), [&](int x) {out << ' ' << x; });
		out << endl;
		for_each(ProductTable.begin(), ProductTable.end(), [&](QM_CONSOLIDATION x)
			{
				out << x.PopIndex();
				for (int i = 0; i < MinItem.size(); i++)
				{
					vector<int> num = ProductTable[i].PopNum();
					int len = num.size();
					for (int j = 0; j < len; j++)
					{
						if (MinItem[i] == num[j])
							cout << " 1 ";
						else
							cout << "   ";
					}
				}
			});
	}
	return out;
}

