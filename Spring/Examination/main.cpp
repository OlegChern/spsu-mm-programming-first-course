#include <bits/stdc++.h>
using namespace std;

template <class T> class Format
{
	T x;
};

template<> class Format<int>{
	int a, b, c;
	public:
		Format(int x, int t)
		{
            c = x + t;
		    if (x > 100)
                c = x * t;
			a = x;
			b = t;
		}
		int getx()
		{
		    if (a <= 100)
            {
                cout << "Your number less or equal 100\n";
			    cout << "Added to number " << a << " number " << b << " : ";
            }
            else
            {
                cout << "Your number bigger then 100\n";
			    cout << "Multiply to number " << a << " number " << b << " : ";
            }
			return c;
		}
};

template<> class Format<string>{
	string x, newX;
	int len;
	public:
		Format(string x)
		{
		    len = x.size();
		    if (len % 2 == 0)
			    newX = "++" + x + "++";
            else
                newX = "Hello_" + x + "_world";
		}
		string getx()
		{
			cout << "Updated string: ";
			return newX;
		}
};

int main()
{
    int x, y;
    string s;
    cout << "Enter a two integers and then a line\n";
    cin >> x >> y;
    Format<int> a(x, y);
    cout << a.getx() << "\n";
    cin >> s;
    Format<string> b(s);
    cout << b.getx() << "\n";
}
