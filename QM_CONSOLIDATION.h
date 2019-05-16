#pragma once
#include"myhead.h"
using namespace std;
#ifndef _QM_CONSOLIDATION_
#define _QM_CONSOLIDATION_
enum STATUS
{
	FALSE, TRUE, X
};

/********************************************************
class:	�ϲ���
function:��źϲ�����Ϣ
*********************************************************/
class QM_CONSOLIDATION
{
public:
	QM_CONSOLIDATION(int n);			//���캯������̬λ
	QM_CONSOLIDATION(int n, int finger);//���캯�����̶�λ
	~QM_CONSOLIDATION();				//��������
	const vector<int>& PopNum();//����������
	const vector<int>& PopBit();//���λ����
	int	 PopIndex();			//�����ʶ
	void PushIndex(int num);    //�����ʶ
	bool Merge(QM_CONSOLIDATION& right);		//�ϲ��ϲ���
	bool operator +=(QM_CONSOLIDATION& right);	//�ϲ��ϲ��� +=����������
	bool operator ==(QM_CONSOLIDATION& right);  //�Ƚ������ϲ����Ƿ����
	friend ostream& operator <<(ostream& out, QM_CONSOLIDATION me);

private:
	int diff(QM_CONSOLIDATION& right);//�ϲ���Ƚ�
	void SetBit();  //����λ����
	int index = -1;	//��ʶ
	int finger;		//λ��
	vector<int> num;//�������
	vector<int> bit;//λ����
};




#endif // !_QM_CONSOLIDATION_

