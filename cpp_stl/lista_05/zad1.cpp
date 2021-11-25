#include <iostream>
#include <stack>
#include <queue>

bool isDigit(char token) {
  return '0' <= token && token <= '9';
}

bool isOperator(char token) {
  return token == '+' || token == '-' || token == '*' || token == '/' || token == '^';
}

uint8_t precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      return 0;
  }
}

std::string queueToString(std::queue<std::string> q) {
  std::string result;

  while (!q.empty()) {
    result += q.front() + " ";
    q.pop();
  }

  return result;
}

std::string dijkstra(std::string exp) {
  std::queue<std::string> outputQueue;
  std::stack<char> operatorStack;

  std::string number = "";

  for (auto token : exp) {
    if (isDigit(token)) {
      number += token;
    } else {
      if (number != "") {
        outputQueue.push(number);
        number = "";
      }

      if (token == '(') {
        operatorStack.push(token);
      } else if (token == ')') {
        while (operatorStack.top() != '(') {
          char op = operatorStack.top();
          operatorStack.pop();

          outputQueue.push(std::string(1, op));
        }

        operatorStack.pop();
      } else if (isOperator(token)) {
        while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token)) {
          outputQueue.push(std::string(1, operatorStack.top()));
          operatorStack.pop();
        }

        operatorStack.push(token);
      }
    }
  }

  if (number != "") {
    outputQueue.push(number);
  }

  while (!operatorStack.empty()) {
    outputQueue.push(std::string(1, operatorStack.top()));
    operatorStack.pop();
  }
  return queueToString(outputQueue);
}

int main(int argc, char const *argv[]) {
  std::cout << dijkstra("(1 + 2) * 3") << std::endl;
  std::cout << dijkstra("3 + 4 * 2 / ( 1 - 5 ) ^ 2") << std::endl;

  return 0;
}
