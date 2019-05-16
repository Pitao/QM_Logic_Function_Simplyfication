#pragma once

/*
step��
	1������С��ת���ɶ����Ʊ����
	2���������Ʊ����д��ϲ���
	3���ϲ��ϲ���
	4������޷������ϲ�����������򷵻�step3
	5��ͨ���б�ѡ����С�˻���
	6����ʣ��˻����
	7������޷�������������������򷵻�step6
	8�������������С��
*/
#ifndef _QMLOG_

#define _QMLOG_
#include"myhead.h"
#include"QM_CONSOLIDATION.h"
#define FALSE 0
#define TRUE 1
#define X 2
using namespace std;

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
	int index=-1;	//��ʶ
	int finger;		//λ��
	vector<int> num;//�������
	vector<int> bit;//λ����
};

/********************************************************************
 class:		QM�߼����ʽ
 function:	���������ʽ

********************************************************************/
class QMLOG
{
public:
	QMLOG(int arr[], int n);
	QMLOG(vector<int>& vect);
	QMLOG(QMLOG& copy);
	QMLOG();
	~QMLOG();
	
	QMLOG& PutItem(vector<int>& Min_Item);//���������ʽ


	vector<int>& GetSinplest();//�õ����ʽ

	//�����������
	const int Size() { return size; }							//���
	const vector<int>& PopMinItem() { return MinItem;}			//�����С��
	const vector<QM_CONSOLIDATION>& PopConsolidationTable() { return ConsolidationTable; }	//����ϲ���
	const vector<QM_CONSOLIDATION>& PopProductTable() { return ProductTable; }				//����˻���
	
	//���������غ���
	void operator =(QMLOG& copy);//���ƹ��캯��
	friend ostream& operator <<(ostream& out,QMLOG & me);
private:
	//vector<int>* PMin_Item;//��С��
	//vector<int>* PCon_Min_Item;//���
	//vector<QM_CONSOLIDATION>* PConsolidation_Table;//�ϲ���
	//vector<QM_CONSOLIDATION>* PProduct_Table;//�˻���	

	//˽�г�Ա����
	void InitConList();			//1����ʼ���ϲ��� ,�ó�λ��������consolidation_table
	void Consolidation();		//�ϲ�ʽ��,�ϲ�consolidation_table
	void InitProductTable();	//��ʼ���˻���,Product_Table
	void SelectLessItem();		//�б�ѡ�����ٳ˻���
	void AddRemainItem();		//����ʣ����
	//˽�г�Ա����
	int size;									//��С������
	vector<int> MinItem;						//��С��
	vector<int> ConMinItem;						//���
	vector<QM_CONSOLIDATION> ConsolidationTable;//�ϲ���
	vector<QM_CONSOLIDATION> ProductTable;		//�˻���

};

#endif