#include "QMLOG.h"

//�ϲ��� ���캯�� ��̬λ
QM_CONSOLIDATION::QM_CONSOLIDATION(int n)
{
	num.push_back(n);
	int finger = 0;
	while (n > 0)
	{
		n /= 2;
		finger++;
	}
	bit.assign(finger, 0);
	SetBit();
}
//�ϲ��� ���캯�� �̶�λ
QM_CONSOLIDATION::QM_CONSOLIDATION(int n, int finger)
{
	num.push_back(n);
	this->finger = finger;
	bit.assign(finger, 0);
	SetBit();
}
//�ϲ��� ��������
QM_CONSOLIDATION::~QM_CONSOLIDATION()
{
}
//����������ARBITRARY
const vector<int>& QM_CONSOLIDATION::PopNum()
{
	return num;
}
//���λ����
const vector<int>& QM_CONSOLIDATION::PopBit()
{
	return bit;
}
//�����ʶ
int QM_CONSOLIDATION::PopIndex()
{
	return index;
}
//���ñ�ʶ
void QM_CONSOLIDATION::PushIndex(int num)
{
	index = num;
}
//�ҵ������ϲ���Ĳ�ͬλ
int QM_CONSOLIDATION::diff(QM_CONSOLIDATION& right)
{
	int len = bit.size();
	int diff = 0;
	int pos = -1;
	for (int i = 0; i < len; i++)
	{
		if (bit[i] != right.bit[i])
		{
			diff++;
			pos = i;
		}
		if (diff > 1) return -1;
	}
	return pos;
}
//����λ����
void QM_CONSOLIDATION::SetBit()
{

	int origin = num[0];
	int len = finger;
	while (origin > 0 && len > 0)
	{
		len--;
		bit[len] = (origin % 2);
		origin /= 2;
	}
}
//�ϲ��ϲ���
bool QM_CONSOLIDATION::Merge(QM_CONSOLIDATION& right)
{
	int pos = diff(right);
	if (pos != -1)
	{
		bit[pos] = X;
		num.insert(num.end(), right.num.begin(), right.num.end());
		return true;
	}
	else return false;
}
//�ϲ��ϲ��� ���ز�����
bool QM_CONSOLIDATION::operator+=(QM_CONSOLIDATION& right)
{
	int pos = diff(right);
	if (pos != -1)
	{
		bit[pos] = X;
		num.insert(num.end(), right.num.begin(), right.num.end());
		return true;
	}
	else return false;
}
bool QM_CONSOLIDATION::operator==(QM_CONSOLIDATION& right)
{
	if (bit == right.bit) 
		return true;
	else 
		return false;
}
//��ӡ ����<<
ostream& operator<<(ostream& out, QM_CONSOLIDATION me)
{
	cout << me.PopIndex();
	cout << " |";
	for_each(me.PopBit().begin(), me.PopBit().end(), [&](int x) {out << ' ' << x; });
	cout << " |";
	for_each(me.PopNum().begin(), me.PopNum().end(), [&](int x) {out << ' ' << x; });
	return out;
}


QMLOG::QMLOG(int arr[], int n)
	:size(n)
{
	MinItem.assign(arr, arr + n);
	sort(MinItem.begin(), MinItem.end());
}

QMLOG::QMLOG( vector<int> & vect)
	:MinItem(vect)
{
	sort(MinItem.begin(), MinItem.end());
}

QMLOG::QMLOG(QMLOG & copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConMinItem = copy.GetSinplest();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();
}

QMLOG::QMLOG() :size(0) {}

QMLOG::~QMLOG() {}

//������<<����
void QMLOG::operator=(QMLOG& copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();
}

void QMLOG::InitConList()
{

}

void QMLOG::Consolidation()
{

}

void QMLOG::InitProductTable()
{

}

void QMLOG::SelectLessItem()
{

}

void QMLOG::AddRemainItem()
{

}

//
QMLOG& QMLOG::PutItem(vector<int>& vect)
{
	size = vect.size();
	MinItem = vect;
	return *this;
}

vector<int>& QMLOG::GetSinplest()
{
	InitConList();
	Consolidation();
	InitProductTable();
	SelectLessItem();
	AddRemainItem();
	return ConMinItem;
}




ostream& operator<<(ostream& out, QMLOG me)
{
	int size = me.Size();
	vector<int> MinItem = me.PopMinItem();			//��С��
	vector<int> ConMinItem = me.GetSinplest();	//���
	vector<QM_CONSOLIDATION> ConsolidationTable = me.PopConsolidationTable();	//�ϲ���
	vector<QM_CONSOLIDATION> ProductTable = me.PopProductTable();				//�˻���

	out << "����: " << size << endl;
	out << "��������ʽ" << endl;
	//for_each(MinItem.begin(), MinItem.end(), [&](int x) {out <<'m'<< x << " + "; });
	out<<'m' << MinItem[0];
	for (int i = 1; i < MinItem.size(); i++)
	{
		out << " + m" << MinItem[i];
	}
	out << endl;
	out << "�ϳɱ�" << endl;
	out << "P | A B C D E | NUM" << endl;
	out << "-------------------" << endl;
	for_each(ConsolidationTable.begin(), ConsolidationTable.end(), [&](QM_CONSOLIDATION x)
		{
			out << x << endl;
		});
	out << "�˻���" << endl;
	out << "P&M";
	for_each(MinItem.begin(), MinItem.end(), [&](int x) {out << ' ' << x; });
	out << endl;
	for_each(ConsolidationTable.begin(), ConsolidationTable.end(), [&](QM_CONSOLIDATION x)
		{
			out << x.PopIndex();
			for (int i = 0; i < MinItem.size(); i++)
			{
				vector<int> num = ConsolidationTable[i].PopNum();
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
	return out;
	// TODO: �ڴ˴����� return ���}
}
