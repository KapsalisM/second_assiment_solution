#include <iostream>
#include <stack>
#include <string>
#include <array>

int main()
{
    std::stack<char> stack;
    std::string syntaxtable[4][8];
    int lengthx = 4;
    int lengthy = 8;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            syntaxtable[i][j] = "null";
        }

    }
    syntaxtable[0][0] = ")M(";
    syntaxtable[1][0] = "ZY";
    syntaxtable[1][2] = "ZY";
    syntaxtable[1][3] = "ZY";
    syntaxtable[2][0] = "G";
    syntaxtable[2][2] = "a";
    syntaxtable[2][3] = "b";
    syntaxtable[3][1] = "";
    syntaxtable[3][4] = "M*";
    syntaxtable[3][5] = "M-";
    syntaxtable[3][6] = "M+";
    
    std::array<char,11> translation;
    translation[0] = 'G';
    translation[1] = 'M';
    translation[2] = 'Y';
    translation[3] = 'Z';
    translation[4] = '(';
    translation[5] = ')';
    translation[6] = 'a';
    translation[7] = 'b';
    translation[8] = '*';
    translation[9] = '-';
    translation[10] = '+';

    stack.push('G');
    std::string user_string = "((a-b)*(a+b))";
    bool sucess_result = true;
    int count = 0;
    std::string current_stack_status = "G";

    while (!stack.empty()) {
        std::cout << "iteration [" << count << "]" << std::endl;
        std::cout << "The current string is: " << user_string << std::endl;
        std::cout << "The current stack is: " << current_stack_status << std::endl;

        char stack_character = stack.top();
        //we remove the top character from the stack
        stack.pop();
        current_stack_status.pop_back();
        char user_string_first_character;

        //first fail condition
        if (user_string.empty()) {
            std::cout << "the string is not recongized, because the user string was fully used, but the stack is not empty." << std::endl;
            sucess_result = false;
            break;
        }

        user_string_first_character = (char)user_string[0];

        //translation
        int positionX = -1;
        int positionY = -1;
        bool stack_character_is_final = true;
        for (int i = 0; i < translation.size(); i++) {
            if (stack_character == translation[i]) {
                positionX = i;
                //check if the stack character is final or not
                if (i < 4) {
                    stack_character_is_final = false;
                }
                else {
                    stack_character_is_final = true;
                }
            }
              
            if (user_string_first_character == translation[i]) {
                positionY = i - 4;
            }
        }     

        //if the string contains a character that is not recognized by the grammar
        if (positionY == -1) {
            std::cout << "the string you have given contains a character that is not recognized by the syntax rules/given grammar.";
            sucess_result = false;
            break;
        }

        //case where the top stack character is final
        if (stack_character_is_final) {
            if (stack_character != user_string_first_character) {
                std::cout << "the string is not recongized, because the at this iteration the final " <<
                "character of the stack : " << stack_character << " is not the same as the " <<
                "first character of the string : " << user_string_first_character << std::endl;
                sucess_result = false;
                break;
            }
            //otherwise
            //just remove the first character
            user_string.erase(0, 1);
        }
        //case where the top stack character is not final
        else {
            std::string temp = syntaxtable[positionX][positionY];
            if (temp == "null") {
                std::cout << "the string is not recognized, because there is not a suitable production rule for this combination";
                sucess_result = false;
                break;
            }
            for (int i = 0; i < temp.size(); i++) {
                stack.push(temp[i]);
            }
            current_stack_status += temp;
        }
        count++;
    }

    std::cout << "\n";
    if (sucess_result)
        std::cout << "the string is syntactically correct." << std::endl;


}

     