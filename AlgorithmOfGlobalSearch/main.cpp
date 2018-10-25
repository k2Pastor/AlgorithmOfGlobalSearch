
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <iterator>

using namespace std;

struct TestPoint
{
	double x;
	double z;
	TestPoint(double _x = 0, double _z = 0) : x(_x), z(_z) { }
	bool operator () (const TestPoint & tp1, const TestPoint & tp2)
	{
		if (tp1.x == tp2.x)
			return tp1.x < tp2.x;

		return tp1.x < tp2.x;
	}
};

struct Interval
{
	double R1;
	TestPoint* pLeft;
	TestPoint* pRight;
	Interval(double _R = 0, TestPoint *tpLeft = NULL, TestPoint *tpRight = NULL)
		: R1(_R), pLeft(tpLeft), pRight(tpRight) { }
};

bool operator<(const Interval& i1, const Interval& i2) { return (i1.R1 < i2.R1) ? true : false; }

double f(const TestPoint& tp)
{
	return pow((tp.x), 2);
}

double ComputeM(const TestPoint& tpLeft, const TestPoint& tpRight)
{
	double diffX = tpRight.x - tpLeft.x;
	double diffZ = tpRight.z - tpLeft.z;
	return fabs(diffZ / diffX);
}

double ComputeR(const TestPoint& tpLeft, const TestPoint& tpRight, double _m)
{
	double diffX = tpRight.x - tpLeft.x;
	double diffZ = tpRight.z - tpLeft.z;
	return _m * diffX + diffZ * diffZ / (_m * diffX) - 2 * (tpRight.z + tpLeft.z);
} 

double ComputeKPoint(const TestPoint& tpLeft, const TestPoint& tpRight, double _m)
{
	double sumX = tpRight.x + tpLeft.x;
	double diffX = tpRight.z - tpLeft.z;
	return 0.5 * sumX - (diffX / (2 * _m));
}


int main()
{
	list<TestPoint> testPoints; // точки испытаний;
	list<TestPoint>::iterator itLeft, itRight, itLeftMax, itRightMax;
	vector<double> VectorOfm;
	VectorOfm.reserve(100);
	priority_queue<Interval> Queue;

	TestPoint tp1, tp2, tpk, DotOfGM;
	Interval CharacteristicInterval;
	double accuracy; // точность алгоритма;
	int iterations; // количество итераций;
	int k = 0; // количество испытаний;
	int j = 0;
	double M;
	double m; // константа Липшица;
	double r = 2.0; // заданный параметр метода;
	double GlobalMin = 1000.0, DotOfGlobalMin;
	

	cout << "Enter the ends of the segment [a;b] : " << endl;
	cin >> tp1.x >> tp2.x;
	cout << "Enter number of the iterations: " << endl;
	cin >> iterations;
	cout << "Enter value of the accuracy: " << endl;
	cin >> accuracy;

	tp1.z = f(tp1.x);
	tp2.z = f(tp2.x);
	
	testPoints.push_back(tp1);
	testPoints.push_back(tp2);
	
	k = 2;



	do
	{
		M = 0.0;
		itLeft = itRight = testPoints.begin();
		++itRight;

		for (int i = 0; i < k; i++)
		{
			double FakeM = ComputeM(*itLeft, *itRight);

			if (M < FakeM)
			{
				M = FakeM;
			}
		}

		if (M > 0)
		{
			m = r * M;
			VectorOfm.push_back(m);
		}
		else
		{
			m = 1.0;
			VectorOfm.push_back(m);
		}

		tpk.x = ComputeKPoint(*itLeft, *itRight, m);
		tpk.z = f(tpk.x);
		
		if ((VectorOfm.size() >= 2) && (VectorOfm[j + 1] != VectorOfm[j]))
		{
			Queue = priority_queue<Interval>();
			j++;
		}

		while ( itRight != testPoints.end() )
		{
			Queue.push(Interval(ComputeR(*itLeft, *itRight, m), &(*itLeft), &(*itRight)));
			++itLeft;
			++itRight;
		}
			
		if (itRight == testPoints.end())
		{	
			(itRight--);
		}

		testPoints.insert(itRight, tpk);
		testPoints.sort(TestPoint());
		CharacteristicInterval = Queue.top();
		
		k++;
		
		

	} while ((CharacteristicInterval.pRight - CharacteristicInterval.pLeft > accuracy) && (k - 2 ) < iterations); 
	
	
	
	while (!testPoints.empty())
	{
		
		DotOfGM = testPoints.back();

		if (DotOfGM.z < GlobalMin)
		{
			GlobalMin = DotOfGM.z;
			DotOfGlobalMin = DotOfGM.x;
		}

		testPoints.pop_back();
	}

	cout << " Global minimum is: " << GlobalMin << endl;
	cout << " Dot of global minimum is: " << DotOfGlobalMin << endl;
	cout << " Number of experiments is: " << k << endl;

} 