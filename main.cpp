#include"QMLOG.h"
#include"myhead.h"
int main()
{
	//QM_CONSOLIDATION qm1(15,4);
	cout << "��ӭʹ��QM�������" << endl;
	cout << "��������С�����"<<endl;
	int count;
	cin >> count;
	vector<int> v1 (count);
	cout << "��������С����ʽ" << endl;
	for (int i = 0; i < count; i++)
	{
		cin >> v1[i];
	}
	QMLOG qm1(v1);
	qm1.GetSinplest();
	cout << qm1;
	cout << endl;
	system("pause");
	return 0;
}