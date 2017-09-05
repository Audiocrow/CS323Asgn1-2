// Member Names:
// Alexander Edgar
// Daniel Domingo
// Sean Wulwick

#include <exception>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <string>

using namespace std;

/***************************************************/
/*Function: isOperator                             */
/*Input: char                                      */
/*Output: boolean true false                       */
/*                                                 */
/*This function takes in a char checking if it is a*/
/*operation character, +, -, *, /, and returns a   */
/*value of true or false based on the input.       */
/***************************************************/

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	else
		return false;
}

/***************************************************/
/*Function: promptContinue                         */
/*Input: N/A                                       */
/*Output: boolean true false                       */
/*                                                 */
/*This function asks the user via a prompt if they */
/*would like to continue running the program. If   */
/*the user replys with a 'y' the program prompts   */
/*the user for another postfix string. If any other*/
/*input is recieved the program terminates         */
/***************************************************/

bool promptContinue()
{
	cout << "Continue (y/n)?";
	char c;
	cin.get(c);
	cin.ignore();
	if (c == 'y') { return true; }
	return false;
}

int main(int argc, char* argv[]) {
	
	//Variable Declaration
	stack<int> myStack;
	map<string, int> myMap;
	int value, tempValueOne, tempValueTwo;
	string postfix;
	string::iterator myStringIt;
	regex operExpr("[+-/*$]");
	regex wordExpr("([a-zA-Z0-9]+)");

	while (1) {
		//Ask for initial user input of postfix statment
		cout << "Enter a postfix expression with a $ at the end:";
		
		//Store postfix statment
		getline(cin, postfix);

		//Ensure postfix statment ends with '$'
		if (postfix.back() != '$') {
			cout << "\tInvalid expression: does not end with $" << endl;
			//In the event that the statmenet does not end with a '$' the user is asked
			//if they would like to continue or to terminate the program
			if (promptContinue()) { continue; }
			return 0;
		}
		sregex_iterator myRegIt(postfix.begin(), postfix.end(), 
		for(auto myRegIt=sregex_iterator(postfix.begin(), postfix.end(), expr); myRegIt!=sregex_iterator(); ++myRegIt) {
			smatch result = *myRegIt;
			if(myMap.find(result.str()) == myMap.end()) {
				try {
					value = stoi(result.str());
				}
				catch(invalid_argument&) { 
					cout << "Enter the value of " << result.str() << ":";
					cin >> value;
					cin.ignore();
					myMap.emplace(result.str(), value);
				}
			}
		}
		if (promptContinue()) { 
			myMap.clear();
			continue; 
		}
		return 0;
	}
	return 0;
}