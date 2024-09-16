#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Token types
enum TokenType {
	// Keywords
	IF, ELSE, WHILE, FOR, FUNCTION, RETURN, VAR, CONST, TRUE, FALSE,

	// Operators
	OPERATION,

	// Punctuation
	COMMA, SEMICOLON, COLON, DOT, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,

	// Literals
	INT, DOUBLE, STRING, IDENTIFIER, LITERAL,

	// Functions
	PRINT, 

	// End of file
	END
};

struct Token {
	TokenType type;
	std::string val;
};

std::string toString(char x) {
	std::string s(1, x);
	return s;
}

std::vector<Token> tokenize(std::string code) {
	int pos = 0;
	char c;
	std::string str = "";
	std::vector<Token> tokens;
	while (pos < code.length() - 1) {
		c = code[pos];
		if (std::isspace(c)) continue;
		if (c == '/' && pos < code.length() - 1) {
			while (code[pos + 1] != '\n') {
				pos++;
			}
		}
		else if (isalpha(c)) {
			// eat the entire word
			while (!std::isspace(code[pos] )) {
				c = code[pos++];
				str += c;
				if (pos > code.length() - 1) break;
			}
			// check for keywords
			if (str == "intywinty") tokens.push_back({ INT , ""});
			else if (str == "floatywoaty") tokens.push_back({ DOUBLE, "" });
			else if (str == "stwing") tokens.push_back({ STRING, "" });
			else if (str == "pouncesOnU") tokens.push_back({ LEFT_PAREN, "" });
			else if (str == "pouncesOff") tokens.push_back({RIGHT_PAREN, ""});
			else if (str == "noticesBulgyWulgy") tokens.push_back({ LEFT_BRACE, "" });
			else if (str == "looksAway") tokens.push_back({RIGHT_BRACE, ""});
			else if (str == "rawr") tokens.push_back({RETURN, ""});
			else if (str == "uwu") tokens.push_back({SEMICOLON, ""});
			else if (str == "pwint") tokens.push_back({PRINT, ""});
			else tokens.push_back({IDENTIFIER, str});
		}
		else if (c == '=' || c == '+' || c == '-'||c == '/'||c == '*'||c == '!'||c == '%') {
			tokens.push_back({OPERATION, toString(c)});
		}
		else if (isalnum(c) || c == '\"') {
			while (!isspace(code[pos])) {
				c = code[pos++];
				str += c;
				if (pos > code.length() - 1) break;
			}
			tokens.push_back({LITERAL, str});
		}
		pos++;
		str = "";
	}
	return tokens;
}

std::string transpile(std::vector<Token> tokens) {
	std::string output = "#include <cstdio>\n";
	for (auto tok : tokens) {
		switch (tok.type) {
		case(INT):
			output += "int ";
			break;
		case(DOUBLE):
			output += "double ";
			break;
		case(STRING):
			output += "char* ";
			break;
		case(LEFT_PAREN):
			output += "(";
			break;
		case(RIGHT_PAREN):
			output += ")";
			break;
		case(LEFT_BRACE):
			output += "{";
			break;
		case(RIGHT_BRACE):
			output += "}";
			break;
		case(RETURN):
			output += "return ";
			break;
		case(PRINT):
			output += "printf";
			break;
		case(IDENTIFIER):
			output += tok.val;
			break;
		case(LITERAL):
			output += tok.val;
			break;
		case(OPERATION):
			output += tok.val;
			break;
		case(SEMICOLON):
			output += ";";
		default:
			break;
		}
	}
	return output;
}

int main() {
	std::string test = "intywinty main pouncesOnU pouncesOff noticesBulgyWulgy rawr 0 uwu looksAway";
	std::vector<Token> toks = tokenize(test);
	std::string out = transpile(toks);
	std::cout << out << std::endl;


	return 0;
}