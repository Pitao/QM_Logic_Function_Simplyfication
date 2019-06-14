#include"QMLOG.h"
#include"myhead.h"
int main()
{
	//QM_CONSOLIDATION qm1(15,4);
	cout << "欢迎使用QM化简程序" << endl;
	cout << "请输入最小项个数"<<endl;
	int count;
	cin >> count;
	vector<int> v1 (count);
	cout << "请输入最小项表达式" << endl;
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