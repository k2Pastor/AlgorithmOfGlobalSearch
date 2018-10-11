#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double f(double x)
{
	return pow((x), 2);
}


int main()
{
	vector<double> VectorOfPoints;
	VectorOfPoints.reserve(100);
	
	vector<double> VectorOfValues;
	VectorOfValues.reserve(100);

	double a, b; // концы отрезка [a;b];
	double accuracy; // точность алгоритма;
	double M;
	double m; // константа Липшица;
	double r = 2.0; // заданный параметр метода;
	double R; // характеристика;
	double NewValueOfX; // k-точка;
	double DotOfGlobalMin;
	double ValueOfGlobalMin;
	int IndexOfGlobalMin;
	int iterations; // количество итераций;
	int k = 0; // количество проведенных испытаний;
	int t = 0; // индекс характеристического интервала;


	cout << "Enter ends of the segment: " << endl;
	cin >> a >> b;
	cout << "Enter number of the iterations: " << endl;
	cin >> iterations;
	cout << "Enter value of the accuracy: " << endl;
	cin >> accuracy;
	
	VectorOfPoints.push_back(a);
	VectorOfPoints.push_back(b);

	cout << "Value of the function at the ends of the segment: " << endl;
	cout << "f(a): " << f(a) << endl;
	cout << "f(b): " << f(b) << endl;

	VectorOfValues.push_back(f(a));
	VectorOfValues.push_back(f(b));
	
	k = 2;

	do
	{
		M = 0.0;
		R = -100000.0;

		for (int i = 1; i < k; i++)
		{
			double FakeM = fabs((VectorOfValues[i] - VectorOfValues[i - 1]) / (VectorOfPoints[i] - VectorOfPoints[i - 1]));

			if (M < FakeM)
			{
				M = FakeM;
			}
		}
		if ( M > 0 )
		{
			m = r * M;
		}
		else m = 1.0;

	

		for (int i = 1; i < k; i++)
		{
			double FakeR = m * (VectorOfPoints[i] - VectorOfPoints[i - 1]) + (pow((VectorOfValues[i] - VectorOfValues[i - 1]), 2)) /
				m * (VectorOfPoints[i] - VectorOfPoints[i - 1]) - 2 * (VectorOfValues[i] + VectorOfValues[i - 1]);
			if (R < FakeR)
			{
				R = FakeR;
				t = i;
			}

		}

		

		NewValueOfX = 0.5 * (VectorOfPoints[t] + VectorOfPoints[t - 1]) - (VectorOfValues[t] - VectorOfValues[t - 1]) /
			(2 * m);

		VectorOfPoints.push_back(NewValueOfX);

		VectorOfValues.push_back(f(VectorOfPoints[k]));
		VectorOfValues[k] = f(VectorOfPoints[k]);
		
		sort(VectorOfPoints.begin(), VectorOfPoints.end());
		k++;


	} while ((VectorOfPoints[t] - VectorOfPoints[t - 1] > accuracy) && (k - 2) <= iterations);
	
	
	
	

	
	sort(VectorOfValues.begin(), VectorOfValues.end());
	cout << "Global Minimum:" << VectorOfValues[0] << endl;
	for (int i = 0; i < VectorOfPoints.size(); i++)
	{
		if (f(VectorOfPoints[i]) == VectorOfValues[0])
		{
			DotOfGlobalMin = VectorOfPoints[i];
		}
	}
	cout << "Dot of Global Minimum:" << DotOfGlobalMin << endl;  

	cout << "Number of experiments:" << k << endl;
	

	return 0;
}