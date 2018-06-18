#include <iostream>
using namespace std;


class ArrayRect
{
	int** table;
	
	public:
	ArrayRect(int e, int n)
	{
		table = new int*[3];
		for(int i=0;i<3;i++)
		{
			table[i] = new int[n+1];
			table[i][0] = n;
			for(int j=1;j<=n;j++)
			{
				table[i][j]=e;
			}
		}
	}
	
	ArrayRect(int **arr, int n)
	{
		table = new int*[3];
		for(int i=0;i<3;i++)
		{
			table[i] = new int[n+1];
			table[i][0] = n;
			for(int j=1;j<=n;j++)
			{
				table[i][j] = arr[i][j-1];
			}
		}	
	}	
	
	ArrayRect(const ArrayRect& ar)
	{
		table = new int*[3];
		for(int i=0;i<3;i++)
		{
			table[i] = new int[ar.table[i][0]+1];  //dlugosc tamtej tablicy + 1 
			table[i][0] = ar.table[i][0];
			for(int j=1;j<=ar.table[i][0];j++)
			{
				table[i][j] = ar.table[i][j];
			}
		}
	}
	
	~ArrayRect()
	{
		for(int i=0;i<3;i++)
		{
			cout <<"Usuwam wiersz " << i+1 <<". o elementach: ";
			for(int j=1;j<=table[i][0];j++) cout <<table[i][j] << " ";
			cout <<endl;
			delete table[i];
		}
		delete table;
	}
	
	ArrayRect* addRow(int e, int p)
	{
		int min = table[0][0];
		int indexMin = 0;
		for(int i=1;i<3;i++)
		{
			if(table[i][0] < min)
			{
				indexMin = i;
				min = table[i][0];
			}
		}
		if(p>table[indexMin][0]) return this;
		else
		{
			ArrayRect *old = new ArrayRect(*this);
			int * newRow = new int[table[indexMin][0]+1];
			newRow[0] = table[indexMin][0]+1;
			int offset = 0;
			for(int i=0;i<newRow[0];i++)
			{
				if(i==p)
				{
					newRow[i+1] = e;
					offset = 1;
				}
				else newRow[i+1] = table[indexMin][i+1-offset];
			}
			delete table[indexMin];
			table[indexMin] = newRow;
			return old;
		}
	}
	
	int max()
	{
		int max = table[0][1];
		for(int i=0;i<3;i++)
		{
			for(int j=1;j<=table[i][0];j++)
			{
				if(max < table[i][j]) max = table[i][j];
			}
		}
		return max;
	}
	
	int longest()
	{
		int max = table[0][0];
		for(int i=1;i<3;i++)
		{
			if(max<table[i][0]) max = table[i][0];
		}
		return max;
	}
	
	bool ifRext()
	{
		int d = table[0][0];
		for(int i=1;i<3;i++)
			if(d!=table[i][0]) return false;
		return true;
	}
	
	ArrayRect* delRow(int p)
	{
		int max = table[0][0];
		int indexMax = 0;
		for(int i=1;i<3;i++)
		{
			if(max < table[i][0])
			{
				max = table[i][0];
				indexMax = i;
			}
		}
		if(p>table[indexMax][0]) return this;
		else
		{
			ArrayRect *old = new ArrayRect(*this);
			int * newRow = new int[table[indexMax][0]-1];
			newRow[0] = table[indexMax][0]-1;
			int offset = 0;
			for(int i=0;i<table[indexMax][0];i++)
			{
				if(i==p)
				{
					offset = 1;
				}
				else newRow[i+1-offset] = table[indexMax][i+1];
			}
			delete table[indexMax];
			table[indexMax] = newRow;
			return old;
		}
	}
};

int main()
{
	ArrayRect a = ArrayRect(3,5);
	ArrayRect *b = a.addRow(8,1);
	delete b;
	b = a.addRow(10,1);
	delete b;
	b = a.addRow(11,1);
	delete b;
	b = a.addRow(11,1);
	cout <<a.max() <<endl;
	cout <<a.longest() <<endl;
	cout <<a.ifRext() <<endl;
	cout <<b->ifRext() <<endl;
	delete b;
	b = a.delRow(1);
	delete b;
}
