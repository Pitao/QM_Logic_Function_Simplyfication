#include "QM_CONSOLIDATION.h"

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
	int len = bit.size(); //bit����
	int diff = 0;        //��ͬλ����
	int pos = -1;		//��ͬλλ��
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
ostream& operator<<(ostream & out, QM_CONSOLIDATION me)
{
	cout << me.PopIndex();
	cout << " |";
	for_each(me.PopBit().begin(), me.PopBit().end(), [&](int x) {out << ' ' << x; });
	cout << " |";
	for_each(me.PopNum().begin(), me.PopNum().end(), [&](int x) {out << ' ' << x; });
	cout << endl;
	return out;
}
