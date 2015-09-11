#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "SIMPLEParser.h"
#include "SIMPLERules.h"

using namespace std;

vector<string> tokenized_program; // Stores the SIMPLE program
int index = 0;					  // Keeps track of the tokens in tokenized_program

bool endOfProgram() {
	return index == tokenized_program.size() - 1;
}

bool parseExpression() {
	string token = tokenized_program[index];
	if (isFactor(token)) {
		index += 1;
		return true;
	}
	else if (token == "+"
			|| token == "-"
			|| token == "*"
			|| token == "/") {
		// Make sure we don't have consecutive operators
		if (isFactor(tokenized_program[index - 1])) {
			index += 1;
			return parseExpression();
		}
		else {
			cout << "Invalid expression: Consecutive operators.\n";
			return false;
		}
	}
	else {
		cout << "Invalid expression.\n";
		return false;
	}
}

bool parseAssign() {
	string token = tokenized_program[index];
	if (!isName(token)) {
		cout << "Assign statement does not have a valid variable name.\n";
		return false;
	}

	index += 1;
	token = tokenized_program[index];

	if (token != "="){
		cout << "Assign statement does not have an equal sign.\n";
		return false;
	}

	index += 1;

	if (parseExpression()) {
		token = tokenized_program[index];
		if (token == ";") {
			index += 1;
			return true;
		}
		else {
			cout << "Assign statement does not have delimiter.\n";
			return false;
		}
	}
	else {
		return false;
	}
}

bool parseWhile() {
	if (endOfProgram()) {
		cout << "End of program reached while attempting to parse while statement.\n";
		return false;
	}

	string token = tokenized_program[index];
	string next_token = tokenized_program[index + 1];

	if (isName(token) && next_token == "{") {
		index += 2;

		if (!parseStmtList()) {
			cout << "There was an error parsing this while statement's statement list.\n";
			return false;
		}

		if (tokenized_program[index] == "}") {
			index += 1;
			return true;
		}
		else {
			cout << "Error: While statement has no closing brace.\n";
			return false;
		}
	}
	else {
		cout << "This is not a valid While statement.\n";
		return false;
	}
}

bool parseStmt() {
	if (tokenized_program[index] == "while") {
		index += 1;
		return parseWhile();
	}
	else {
		return parseAssign();
	}
}

// Keep parsing statements until closing brace of procedure is encountered.
bool parseStmtList() {
	if (parseStmt()) {
		if (!endOfProgram() && tokenized_program[index] == "}") {
			return true;
		}
		else {
			parseStmtList();
		}
	}
	else {
		cout << "No valid statements inside this statement list.\n";
		return false;
	}
}

bool parseProcedure() {
	if (endOfProgram()) {
		cout << "End of program reached while attempting to parse procedure.\n";
		return false;
	}
	
	string token = tokenized_program[index];
	string next_token = tokenized_program[index + 1];

	if(isName(token) && next_token == "{"){
		index += 2;

		if (!parseStmtList()) {
			cout << "There was an error parsing this procedure's statement list.\n";
			return false;
		}

		if (tokenized_program[index] == "}") {
			index += 1;
			return true;
		}
		else {
			cout << "Error: Procedure has no closing brace.\n";
			return false;
		}
	}
	else {
		cout << "This is not a valid procedure.\n";
		return false;
	}
}

// Returns a fully tokenized program, or an empty vector if there are errors.
vector<string> parseProgram(vector<string> program) {
	tokenized_program = program;
	string token = program[0];
	
	while (!endOfProgram()) {
		if (token.find("procedure") != string::npos) {
			index += 1;

			if (!parseProcedure()) {
				cout << "Error parsing procedure.\n";
				tokenized_program.clear();
				break;
			};
		}
		else {
			cout << "Cannot continue parsing because no procedure was found.\n";
			tokenized_program.clear();
			break;
		}
	}

	return tokenized_program;
}