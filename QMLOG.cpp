#include "QMLOG.h"

//数组构造函数
QMLOG::QMLOG(int arr[], int n)
{
	vector<int> temp(arr, arr + n);
	PutItem(temp);
}

//向量构造函数
QMLOG::QMLOG(vector<int> & vect)
{
	PutItem(vect);
}

//拷贝构造函数
QMLOG::QMLOG(QMLOG & copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConMinItem = copy.GetSinplest();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();
}

//默认构造函数
QMLOG::QMLOG() :size(0) {}
//析构函数
QMLOG::~QMLOG() {}

//操作符=重载
void QMLOG::operator=(QMLOG& copy)
{
	size = copy.Size();
	MinItem = copy.PopMinItem();
	ConsolidationTable = copy.PopConsolidationTable();
	ProductTable = copy.PopProductTable();

}

//初始化合成表
void QMLOG::InitConList()
{
	int max = *(MinItem.end() - 1); //获得最大值
	int finger = 0;//位数置1
	
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
//合并函数
void QMLOG::Consolidation()
{
	/*定义一个临时合并表储存本次合并后的项目
	  本次合并删除旧的可合并的合并项
	  总合并表增加本次合并后的式子
	*/
	vector<QM_CONSOLIDATION> temp_con;
	
	bool over_flag = false; //全部合并标记
	int size = ConsolidationTable.size();
	bool* single_flag = new bool(size);
	memset(single_flag, false, size);
	//轮询
	for (int i = 0; i < size-1; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			//如果符合只有一位不同，则合并并且标记
			if (Diff(ConsolidationTable[i], ConsolidationTable[j])>=0)
			{
				temp_con.push_back(Merge(ConsolidationTable[i], ConsolidationTable[j]));//新的合成项
				over_flag = true;
				single_flag[i] = true;
				single_flag[j] = true;
			}
		}
	}
	//删除已合并的合并项
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
	}

}
//初始化乘积表
void QMLOG::InitProductTable()
{
	//设置p标记(index)
	for (int i = 0; i < ConsolidationTable.size(); i++)
	{
		ConsolidationTable[i].PushIndex(i);
	}

	MinItem_Flag.assign(MinItem.size(), false);  //最小项包括标记置零
	Index_Flag.assign(ConsolidationTable.size(), false);//合成项包括标记
	//合成表置零
	ProductTable.resize(ConsolidationTable.size());
	for_each(ProductTable.begin(), ProductTable.end(), [&](vector<int> & x) {
		x.assign(MinItem.size(), 0);
		});

}
//选择最小项
void QMLOG::SelectLessItem()
{
	
}
//增加剩余项
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



//设置最小项向量
QMLOG& QMLOG::PutItem(vector<int>& vect)
{
	//设置个数
	size = vect.size();
	//设置向量并排序
	MinItem = vect;
	sort(MinItem.begin(), MinItem.end());
	return *this;
}
//取得结果
string& QMLOG::GetSinplest()
{
	//如果已经有结果，就直接返回，否则计算
	if (ConMinItem.empty()==true)
	{
		InitConList();
		Consolidation();
		InitProductTable();
		cout << *this << endl; //debug point

		SelectLessItem();
		AddRemainItem();
	}
	return ConMinItem;
}
//输出函数
ostream& operator<<(ostream& out, QMLOG& me)
{
	int size = me.Size();
	vector<int> MinItem = me.PopMinItem();			//最小项
	//vector<int> ConMinItem = me.GetSinplest();	//结果
	vector<QM_CONSOLIDATION> ConsolidationTable = me.PopConsolidationTable();	//合并表
	vector<vector<int>> ProductTable = me.PopProductTable();				//乘积表

	out << "长度: " << size << endl;
	out << "待化简表达式" << endl;
	//for_each(MinItem.begin(), MinItem.end(), [&](int x) {out <<'m'<< x << " + "; });
	out << 'm' << MinItem[0];
	for (int i = 1; i < MinItem.size(); i++)
	{
		out << " + m" << MinItem[i];
	}
	out << endl;

	if (ConsolidationTable.empty() == true)
	{
		cout << "无合成表" << endl;
	}
	else
	{ 
		out << "合成表" << endl;
		out << "P | A B C D E | NUM" << endl;
		out << "-------------------" << endl;
		for_each(ConsolidationTable.begin(), ConsolidationTable.end(), [&](QM_CONSOLIDATION x){
				out << x << endl;
			});
	}

	if (ConsolidationTable.empty() == true)
	{
		cout << "无乘积表" << endl;
	}
	else
	{
		out << "乘积表" << endl;
		out << "P&M";
		for_each(MinItem.begin(), MinItem.end(), [&](int x) {out << ' ' << x; });
		out << endl;
		int line = ProductTable.size();
		int list = MinItem.size();
		for (int i = 0; i < line; i++)
		{
			out << ' ' << ConsolidationTable[i].PopIndex() << ' ';
			for (int j = 0; j < list; j++)
			{
				if (ProductTable[i][j]) out << ' ' << ProductTable[i][j];
				else out << "  ";
			}
			cout << endl;
		}
	}
	return out;
}

