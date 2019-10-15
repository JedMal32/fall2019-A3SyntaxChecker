#include <iostream>
#include <fstream>
#include <string>
#include "GenStack.cpp"

using namespace std;

int main (int argc, char **argv){
  GenStack<char> delimiters = GenStack<char>();
  GenStack<int> delimiterLines = GenStack<int>();
  char failedStack = ' ';
  char failedComparison = ' ';
  bool emptyStack = false;
  bool noErrors = true;
  int lineErrorStack = 0;
  int lineErrorComp = 0;
  bool keepGoing = true;
  string fileName = argv[1];

  while(keepGoing){
    int lineNumber = 0;
    ifstream input(fileName);
    for(string line; getline(input, line);){
      ++lineNumber;
      for(int i = 0; i < line.length() ; i++){
        char c = line[i];
        if(c == '{' || '[' || '(' || '}' || ']' || ')'){
          if(c == '{'){
            delimiters.push(c);
            delimiterLines.push(lineNumber);
          }
          if(c == '['){
            delimiters.push(c);
            delimiterLines.push(lineNumber);
          }
          if(c == '('){
            delimiters.push(c);
            delimiterLines.push(lineNumber);
          }
          if(c == '}'){
            if(delimiters.peek()=='{'){
              delimiters.pop();
              delimiterLines.pop();
            }else{
              if(delimiters.getTop()>-1){
                failedStack = delimiters.pop();
                lineErrorStack = delimiterLines.pop();
              }else{
                emptyStack = true;
              }
              if(noErrors){
                failedComparison = c;
                noErrors = false;
                lineErrorComp = lineNumber;
              }
            }
          }
          if(c == ']'){
            if(delimiters.peek()=='['){
              delimiters.pop();
              delimiterLines.pop();
            }else{
              if(delimiters.getTop()>-1){
                failedStack = delimiters.pop();
                lineErrorStack = delimiterLines.pop();
              }else{
                emptyStack = true;
              }
              if(noErrors){
                failedComparison = c;
                noErrors = false;
                lineErrorComp = lineNumber;
              }
            }
          }
          if(c == ')'){
            if(delimiters.peek()=='('){
              delimiters.pop();
              delimiterLines.pop();
            }else{
              if(delimiters.getTop()>-1){
                failedStack = delimiters.pop();
                lineErrorStack = delimiterLines.pop();
              }else{
                emptyStack = true;
              }
              if(noErrors){
                failedComparison = c;
                noErrors = false;
                lineErrorComp = lineNumber;
              }
            }
          }
        }
      }
    }
    if(noErrors && delimiters.getTop()>-1){
        failedStack = delimiters.pop();
        lineErrorStack = delimiterLines.pop();
    }
    if(noErrors){
      if(emptyStack){
        cout << "Missing opening delimiter for " << failedComparison << " from line: " << lineErrorComp << endl;
        keepGoing = false;
      }else{
        if(failedStack == ' '){
          cout << "Syntax is correct" << endl;
        }else{
          cout << "Missing closing delimiter for " << failedStack << " from line: " << lineErrorStack << endl;
          keepGoing = false;
        }
      }
    }else{
      if(emptyStack){
        cout << "Missing opening delimiter for " << failedComparison << " from line: " << lineErrorComp << endl;
        keepGoing = false;
      }else{
        cout << "Missing closing delimiter for " << failedStack << " from line: " << lineErrorStack << endl;
        keepGoing = false;
      }
    }

    if(keepGoing){
      string continueResponse;
      cout << "Would you like to continue? (y/n): ";
      cin >> continueResponse;
      if(continueResponse == "n"){
        keepGoing = false;
      }else if(continueResponse == "y"){
        cout << "What is the location of the new file: ";
        cin >> fileName;
      }else{
        cout << "Not a 'y' or an 'n', will continue" << endl;
      }
    }

  }

}
