#include"QMLOG.h"
#include"myhead.h"
int main()
{
	//QM_CONSOLIDATION qm1(15,4);
	cout << "欢迎使用QM化简程序" << endl
		<< "请输入最小项表达式" << endl;
	vector<int> v1 = { 0,2,3,8,10,14,15,22,24,27,31 };
	QMLOG qm1(v1);
	qm1.GetSinplest();
	cout << qm1;
	return 0;
}