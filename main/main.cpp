#include <iostream>
#include "text.h"
#include "text_node.h"

 using namespace std;

int main()
{
	char* temp = "Hello, \n World!\n";
	TText A(temp);
	TTextIter B = A.Find("e");

	A.InsertLine("Forza Ferrari!", B);
	TTextIter C = A.Find("Ferrari");

	A.InsertLine("AND", C);

	cout << A << endl;

	char* const str = "Hello World";
	TText E(str);

	char tmp = 'W';
	TTextIter iter = E.Find(tmp);

	char* res = E.Copy(2, iter);
	cout << res;
	cout << *(E.Find('H').Get());
	cout << *(E.Find('W').Get());
	cout << *(E.Find('r').Get());

	return 0;
}
