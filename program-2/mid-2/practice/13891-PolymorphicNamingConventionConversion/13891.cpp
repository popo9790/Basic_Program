#include "function.h"
#include <iostream>
#include <string>
using namespace std;

ostream &operator<<(ostream &os, Case &data)
{
    data.show(os);
    return os;
}

void convert_revert(Case &data)
{
    if (!data.is_converted())
        data.convert();
    else
        data.revert();
}

int main()
{
    string input_string;
    getline(cin, input_string);

    SnakeCase snake(input_string);
    convert_revert(snake);
    cout << "Snake Case (converted): " << snake << "\n";
    convert_revert(snake);
    cout << "Snake Case (reverted): " << snake << "\n";

    CamelCase camel(input_string);
    convert_revert(camel);
    cout << "Camel Case (converted): " << camel << "\n";
    convert_revert(camel);
    cout << "Camel Case (reverted): " << camel << "\n";
    return 0;
}
