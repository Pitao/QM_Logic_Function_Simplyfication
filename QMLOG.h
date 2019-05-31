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


	string& GetSinplest();//�õ����ʽ

	//�����������
	const int Size() { return size; }							//���
	const vector<int>& PopMinItem() { return MinItem;}			//�����С��
	const vector<QM_CONSOLIDATION>& PopConsolidationTable() { return ConsolidationTable; }	//����ϲ���
	const vector<vector<int>>& PopProductTable() { return ProductTable; }				//����˻���
	
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
	const QM_CONSOLIDATION  Merge(QM_CONSOLIDATION & left, QM_CONSOLIDATION & right);		//�ϲ��ϲ���
	int Diff(QM_CONSOLIDATION& left, QM_CONSOLIDATION& right);//�ϲ���Ƚ�

	//˽�г�Ա����
	int size=0;									//��С������
	int finger=0;								//��С��λ��
	vector<int> MinItem;						//��С��
	string ConMinItem;						//���
	vector<QM_CONSOLIDATION> ConsolidationTable;//�ϲ���
	vector<vector<int>> ProductTable;		//�˻���
	
	vector<bool>Index_Flag;
	vector<bool>MinItem_Flag;
};

#endif