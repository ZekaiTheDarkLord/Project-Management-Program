// Final Project
// Tianye Ding
// 5/1/2022
#include "Sprint.hpp"

using namespace std;

Issue *Sprint::popIssue(string id)
{
    for (int i = 0; i < todo.size(); i++)
    {
        if (todo.at(i)->getId() == id)
        {
            Issue *temp = todo.at(i);
            todo.erase(todo.begin() + i);
            return temp;
        }
    }

    return nullptr;
}

string Sprint::out_string() const
{
    string output = "Sprint:\n" + to_string(endDate - startDate) + '\n';
    for (auto i : todo)
        output += i->out_string();

    return output + '\n';
}
