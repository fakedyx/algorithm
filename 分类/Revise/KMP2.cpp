#include <iostream>
#include <string>
using namespace std;

int* getNext(string& s) {
	int* next = new int[s.length()];
	next[0] = -1;  //important
	int j = 0, k = -1;
	while(j < s.length()) {
		if(k == -1 || s[j] == s[k]) {
			k++;
			j++;
			next[j] = k;
		}else{
			k = next[k];
		}
	}
	return next;
}

int KMP(string& s1, string& s2) {
	int* next = getNext(s2);
	int i = 0, j = 0;
	while(i < s1.length() && j < s2.length()) {
		if(s1[i] == s2[j] || next[j] == -1) {
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
	if(next) delete[] next;
	if(j == s2.length()) return i - j;
	return -1;
}

int main()
{
	string s1("ababaabababcab");
	string s2("abcab");
	cout << KMP(s1, s2) << endl;
	return 0;
}