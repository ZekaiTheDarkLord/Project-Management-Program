// Final Project
// Tianye Ding
// 5/1/2022
#ifndef ISSUE_H
#define ISSUE_H

#include <memory>
#include <string>
#include <vector>
#include "IssueStatus.hpp"
#include "IssueType.hpp"

using namespace std;

class Project;
class User;

struct Comment
{
    User *poster;
    int time;
    string content;

    string out_string() const;
};

class Issue
{
    string id;
    int priority;
    User *assignee;
    User *reporter;
    int createDate;
    int dueDate;
    Project *parent;
    IssueType type;
    IssueStatus status;
    string description;
    vector<Comment *> comments;

public:
    Issue(string in_id, int in_prior, User *in_report, int in_create, int in_due, Project *in_parent, IssueType in_type, string in_des) : id(in_id), priority(in_prior), reporter(in_report), assignee(nullptr), createDate(in_create), dueDate(in_due), parent(in_parent), type(in_type), status(IssueStatus::open), description(in_des)
    {
        comments = vector<Comment *>();
    }

    // getters
    string getId() const { return id; }
    int getPriority() const { return priority; }
    User *getAssignee() const { return assignee; }
    User *getReporter() const { return reporter; }
    int getCreate() const { return createDate; }
    int getDue() const { return dueDate; }
    Project *getParent() const { return parent; }
    IssueType getType() const { return type; }
    IssueStatus getStatus() const { return status; }
    string getDescription() const { return description; }
    vector<Comment *> getComments() const { return comments; }

    // setters
    void setId(string other) { id = other; }
    void setPriority(int other) { priority = other; }
    void assign(User *other) { assignee = other; }
    void setDue(int other) { dueDate = other; }
    void setType(IssueType other) { type = other; }
    void setStatus(IssueStatus other) { status = other; }
    void setDescription(string other) { description = other; }

    void addComment(Comment *other) { comments.push_back(other); }
    void removeComment(int index) { comments.erase(comments.begin() + index); }

    // file o
    string out_string() const;

    ~Issue()
    {
        for (auto c : comments)
            delete c;
    }
};

#endif
