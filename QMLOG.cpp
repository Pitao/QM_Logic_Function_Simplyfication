#include "QMLOG.h"

//对分查找
template<class T>
int find(vector<T> vect,T elem)
{
	int left = 0;
	int right = vect.size() - 1;
	while(left<=right)
	{
		int mid = (left + right) / 2;
		if (vect[mid] == elem)
			return mid;
		else if (vect[mid] < elem) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}
vector<int> dfs(vector<int> depth, string Consum,
	vector<string> Table,
	vector<QM_CONSOLIDATION> ConsolidationTable, 
	const string & normal)
{
	//如果dfs触底或者符合条件，就跳出
	if (Table.empty() || Consum == normal)
	{
		return depth;
	}
	//树状dfs
	vector<int> ans(1, 0);
	for (int i =depth[0]; i < Table.size(); i++)
	{

		string str = Table[i];
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == '1')
				Consum[j] = '1';
		}
		depth[depth[0] + 1] = ConsolidationTable[i].PopIndex();
		//depth.push_back(ConsolidationTable[i].PopIndex());
		depth[0]++;
		//Table.erase(Table.begin() + i);
		//ConsolidationTable.erase(ConsolidationTable.begin() + i);
		vector<int> temp=dfs(depth, Consum, Table, ConsolidationTable,normal);
		if (temp[0] < ans[0] ||ans[0]==0)
			ans = temp;
		depth[0]--;
	}
	return ans;
}
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
		//delete[] single_flag;
	}

}
//初始化乘积表
void QMLOG::InitProductTable()
{

	//删除合成表中的相同项
	for (int i = 0; i < ConsolidationTable.size()-1; i++)
	{
		for (int j = ConsolidationTable.size()-1; j > i; j--)
		{
			if (ConsolidationTable[i] == ConsolidationTable[j])
				ConsolidationTable.erase(ConsolidationTable.begin() + j);
		}
	}
	//for (auto i = ConsolidationTable.begin(); i < ConsolidationTable.end()-1; i++)
	//{
	//	for (auto j = ConsolidationTable.end()-1; j>i; j--)
	//	{
	//		if (*i == *j)
	//			ConsolidationTable.erase(j);
	//	}
	//}
	int MinItem_size = MinItem.size();
	int ConsoTable_size = ConsolidationTable.size();

	//设置p标记(index)
	for (int i = 0; i < ConsoTable_size; i++)
	{
		ConsolidationTable[i].PushIndex(i);
	}

	MinItem_Flag.assign(MinItem_size, false);  //最小项包括标记置零
	Index_Flag.assign(ConsoTable_size, false);//合成项包括标记
	//乘积表置零
	ProductTable.resize(ConsoTable_size);
	for_each(ProductTable.begin(), ProductTable.end(), [&](vector<int> & x) {
		x.assign(MinItem_size, 0);
		});
	//乘积表分配内容
	/*
	  从MinItem中获取数值，再在ConsolidationTable中寻找
	  找到记录标记并计数
	*/
	for (int i = 0; i < MinItem_size; i++)
	{
		int num = MinItem[i];
		int count = 0;
		vector<int> index_vect;
		for (int j = 0; j < ConsoTable_size; j++)
		{
			auto num_vect = ConsolidationTable[j].PopNum();
			for_each(num_vect.begin(), num_vect.end(), [&](int x) {
				if (x == num)
				{
					count++;
					index_vect.push_back(j);
				}
			});
		}
		for (int j = 0; j < index_vect.size(); j++)
		{
			int line = index_vect[j];
			ProductTable[line][i] = count;
		}
	}
}
//选择最小项
void QMLOG::SelectLessItem()
{
	//line p标识数
	//list 最小项数量
	int line = ConsolidationTable.size();
	int list = MinItem.size();
	//遍历二维表，寻找只被标识一次的最小项，并标记最小项和对应的p标识
	for (int i = 0; i < list; i++)
	{
		for (int j = 0; j < line; j++)
		{
			if (ProductTable[j][i] == 1)
			{
				Index_Flag[j] = true;
				//MinItem_Flag[i] = true;
				//将符合标准的合成项中所有最小项全部标记
				for (int x : ConsolidationTable[j].PopNum())
				{
					int pos = find(MinItem, x);
					if(pos>=0) 
						MinItem_Flag[pos] = true;
				}

			}
		}
	}


}
//增加剩余项
void QMLOG::AddRemainItem()
{
	//可用动态规划优化
	//目前使用dfs
	auto ReMinItem = MinItem;
	auto ReCon = ConsolidationTable;
	//初始化剩余项
	for (int i = Index_Flag.size()-1; i >=0; i--)
	{
		if (Index_Flag[i])
		{
			ReCon.erase(ReCon.begin() + i);
		}
	}
	for (int i = MinItem_Flag.size() - 1; i >= 0; i--)
	{
		if (MinItem_Flag[i])
		{
			ReMinItem.erase(ReMinItem.begin() + i);
		}
	}
	//初始化剩余表
	vector<string> ReTable;
	for (int i = 0; i < ReCon.size(); i++)
	{
		string temp;
		//auto vect = ReCon[i].PopNum;
		for (int j = 0; j < ReMinItem.size(); j++)
		{
			bool flag = false;
			//寻找单个
			for (int x : ReCon[i].PopNum())
			{
				if (x == ReMinItem[j]) flag = true;
			}
			if (flag)
				temp += "1";
			else
				temp += "0";
		}
		ReTable.push_back(temp);
	}
	string temp;
	string normal;
	for (int i = 0; i < ReMinItem.size(); i++)
	{
		temp += "0";
		normal += "1";
	}
	vector<int> vect(ReMinItem.size()+1,0);
	vect=dfs(vect,temp, ReTable, ReCon,normal);
	for (int x : vect)
	{
		Index_Flag[x] = true;
	}
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

void QMLOG::LogicExpress()
{
	string cList = "ABCDEFGH";
	string ans;
	int size = ConsolidationTable[0].PopBit().size();
	int len = ConsolidationTable.size();
	for (int i=0;i<len;i++)
	{
		if (Index_Flag[i])
		{
			auto tempBit = ConsolidationTable[i].PopBit();
			for (int j = 0; j < size; j++)
			{
				char index = 'A' + j;
				switch (tempBit[j])
				{
				case 0:
					ans += index;
					ans+= "\'";
					break;
				case 1:
					ans += index ;
					break;
				case 2:
					break;

				}
			}
			ans += '+';
		}
	}
	ans.pop_back();
	ConMinItem = ans;
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

		SelectLessItem();
		AddRemainItem();
		LogicExpress();
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
	//打印最小项
	out << "长度: " << size << endl<<endl;
	out << "待化简表达式" << endl;
	//for_each(MinItem.begin(), MinItem.end(), [&](int x) {out <<'m'<< x << " + "; });
	out << 'm' << MinItem[0];
	for (int i = 1; i < MinItem.size(); i++)
	{
		out << " + m" << MinItem[i];
	}
	out << endl << endl;
	//打印合成表
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
	//打印乘积表
	if (ConsolidationTable.empty() == true)
	{
		cout << "无乘积表" << endl;
	}
	else
	{
		out << "乘积表" << endl;
		out << "P&M";
		for_each(MinItem.begin(), MinItem.end(), [&](int x) {out << setw(4) << x; });
		out << endl;
		int line = ProductTable.size();
		int list = MinItem.size();
		for (int i = 0; i < line; i++)
		{
			out << ' ' << ConsolidationTable[i].PopIndex() << ' ';
			for (int j = 0; j < list; j++)
			{
				if (ProductTable[i][j]) out << setw(4) << ProductTable[i][j];
				else out << "    ";
			}
			cout << endl;
		}
	}
	cout << endl;
	//结果表达式
	cout <<"表达式为："<< me.ConMinItem << endl;
	
	return out;
}

