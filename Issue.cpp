// Final Project
// Tianye Ding
// 5/1/2022
#include "Issue.hpp"
#include "User.hpp"

using namespace std;

string Comment::out_string() const
{
    return "Comment:\n" + poster->getName() + '\n' + to_string(time) + '\n' + content + '\n';
}

string Issue::out_string() const
{
    string output = "Issue:\n" + id + '\n' + to_string(priority) + '\n';
    if (assignee == nullptr)
        output += "NULL" + '\n';
    else
        output += assignee->getName() + '\n';

    output += reporter->getName() + '\n' + to_string(createDate) + '\n' + to_string(dueDate) + '\n';
    switch (type)
    {
    case IssueType::userStory:
        output += "userStory\n";
        break;
    case IssueType::task:
        output += "task\n";
        break;
    case IssueType::build:
        output += "build\n";
        break;
    case IssueType::test:
        output += "test\n";
        break;
    case IssueType::debug:
        output += "debug\n";
        break;
    case IssueType::documentation:
        output += "documentation\n";
        break;
    default:
        output += "other\n";
    }

    switch (status)
    {
    case IssueStatus::open:
        output += "open\n";
        break;
    case IssueStatus::inProgress:
        output += "inProgress\n";
        break;
    case IssueStatus::done:
        output += "done\n";
        break;
    default:
        output += "overdue\n";
        break;
    }

    output += description + '\n';
    for (auto c : comments)
        output += c->out_string();

    return output + '\n';
}