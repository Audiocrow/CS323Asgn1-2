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
	if (c == 'y' || c == 'Y') { return true; }
	return false;
}

int main(int argc, char* argv[]) {
	
	//Variable Declaration
	stack<double> myStack;
	map<string, double> myMap;
	double value, tempOne, tempTwo;
	string postfix;
	string::iterator myStringIt;
	regex operExpr("([+-/*])");
	regex wordExpr("([a-zA-Z0-9.]+)");
	smatch match;
	bool noErrors = true;

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
		//Find operators (+, -, /, *) with regex search
		while(regex_search(postfix, match, operExpr)) {
			//With each operator found, the prefix of the
			//regex match should contain the operands -
			//find them with an iterative regex search
			string operands = match.prefix().str();
			for(auto myRegIt=sregex_iterator(operands.begin(), operands.end(), wordExpr); myRegIt!=sregex_iterator(); ++myRegIt) {
				smatch result = *myRegIt;
				//We want to push the value of this operand onto
				//the stack, but it might be a variable
				try {
					value = stod(result.str());
					myStack.push(value);
				}
				catch(invalid_argument&) {
					//If this is a variable and we don't already
					//know its value, prompt the user for the value
					auto tempIt = myMap.find(result.str());
					if(tempIt == myMap.end()) {
						cout << "\tEnter the value of " << result.str() << ":";
						cin >> value;
						cin.ignore();
						myMap.emplace(result.str(), value);
						myStack.push(value);
					}
					//Otherwise we already know the value
					//And can immediately put it on the stack
					else { myStack.push(tempIt->second); }
				}
			}
			//Pop two values from the stack and perform
			//this operator match on them. Fails if there
			//are not two values on the stack.
			if(myStack.size() < 2) {
				cout << "\tFailed to perform '" << match.str() << "' because two values were not on the stack. The postfix expression may be invalid." << endl;
				noErrors = false;
				break;
			}
			tempTwo = myStack.top(); myStack.pop();
			tempOne = myStack.top(); myStack.pop();
			switch(match.str()[0]) {
				case '+': myStack.push(tempOne+tempTwo); break;
				case '-': myStack.push(tempOne-tempTwo); break;
				case '/': myStack.push(tempOne/tempTwo); break;
				case '*': myStack.push(tempOne*tempTwo); break;
			}
			//Continue with the outside loop (finding operators)
			//on the remainder of the postfix
			postfix = match.suffix().str();
		}
		if(noErrors) {
			if(myStack.size() == 1) {
				cout << "\tFinal Value=" << myStack.top() << endl;
			}
			else if(myStack.size() > 1) {
				cout << "\tError: more than one value exists on the stack at the end of evaluating the postfix expression, therefore it may be invalid." << endl;
			}
			else if(myStack.size() == 0) {
				cout << "\tError: nothing remained on the stack at the end of evaluating the postfix expression, therefore it may be invalid." << endl;
			}
		}
		myMap.clear();
		while(!myStack.empty()) { myStack.pop(); }
		noErrors = true;
		if(!promptContinue()) { break; }
	}
	return 0;
}
