#include <string>
using namespace std;

/* string 클래스 맴버함수 compare().
if (s1.compare(s2) == 0) { 
	// 두 문자열이 같을 때 

} 
else if (s1.compare(s2) < 0) { 
	// s1가 s2보다 사전순으로 앞일 때 
} 
else if (s1.compare(s2) > 0) { 
	// s1가 s2보다 사전순으로 뒤일 때 
}
*/

/*
bool operator<(const string& s1, const string& s2);
bool operator<(const string& s1, const string& s2)
{
	if (s1.compare(s2) < 0) {
		// s1가 s2보다 사전순으로 앞일 때 
		return true;
	}
	else {
		// s1가 s2보다 사전순으로 뒤이거나 같을 때 
		return false;
	}
}

bool operator>(const string& s1, const string& s2);
bool operator>(const string& s1, const string& s2)
{
	if (s1.compare(s2) > 0) {
		// s1가 s2보다 사전순으로 뒤일 때 
		return true;
	}
	else {
		// s1가 s2보다 사전순으로 앞이거나 같을 때 
		return false;
	}
}

bool operator<=(const string& s1, const string& s2);
bool operator<=(const string& s1, const string& s2)
{
	if (s1.compare(s2) <= 0) {
		// s1가 s2보다 사전순으로 앞이거나 같을 때 
		return true;
	}
	else {
		// s1가 s2보다 사전순으로 뒤일 때 
		return false;
	}
}

bool operator>=(const string& s1, const string& s2);
bool operator>=(const string& s1, const string& s2)
{
	if (s1.compare(s2) >= 0) {
		// s1가 s2보다 사전순으로 뒤이거나 같을 때 
		return true;
	}
	else {
		// s1가 s2보다 사전순으로 앞일 때 
		return false;
	}
}
*/