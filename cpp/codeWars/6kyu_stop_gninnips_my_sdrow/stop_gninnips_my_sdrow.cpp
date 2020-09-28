/*
Write a function that takes in a string of one or more words, and returns the same string,
but with all five or more letter words reversed (Just like the name of this Kata). Strings
passed in will consist of only letters and spaces. Spaces will be included only when more
than one word is present.

Examples:
spinWords( "Hey fellow warriors" ) => returns "Hey wollef sroirraw"
spinWords( "This is a test") => returns "This is a test"
spinWords( "This is another test" )=> returns "This is rehtona test"

Very interesting Kata
Here i learned about stringstream (ostringstream, istringstream)
and how operator ">>" works with stringstream.
If i knew that before, my solution could have been a lot better.
 
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <fstream>
using namespace std;


vector<string> explode(const string &str, char delim)
{
	vector<string> result;
	istringstream iss(str);
	string token;
	while (getline(iss, token, delim))
	{
        	result.push_back(token);
	}

	return result;
}

string implode(vector<string> &vec, char delim){
	string result;

	for (int i = 0; i < vec.size(); i++)
	{
		result += vec[i];
		if (i < vec.size() - 1) result += delim;
	}

	return result;
}

int main(){

	auto v = explode("hello world foo bar", ' ');	
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
		if (v[i].size() > 4){
			reverse(v[i].begin(), v[i].end());
		}
	}
	string finalResult = implode(v, ' ');
	cout << "Final result: " << finalResult << endl;


	// The next trick is the way to do it, using operator ">>"
	// then the whole solution looks very short and neat
	string str = "Some random text I just wrote";
	stringstream ss(str);

	string buffer;
	string result;
	while (ss >> buffer){
		// operator ">>" can be used as "explode",
		// no need for that function
		if (buffer.size() > 4){
			reverse(buffer.begin(), buffer.end());
		}
		result += buffer + ' ';
	}
	// pop_back just removes the last space character
	result.pop_back();
	cout << result << endl;

	fstream filestream;
	filestream.open("file.txt");
	filestream << "whadsk" << endl;
	filestream.close();
	

}
