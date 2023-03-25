// Final Project
// Tianye Ding
// 5/1/2022
#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <string>
#include "Sprint.hpp"
#include "Issue.hpp"
#include "UserRole.hpp"

using namespace std;

class User;

class Project
{
    string name;
    User *owner;
    string description;
    int issueCount;
    vector<User *> lead;
    vector<User *> member;
    vector<Issue *> todo;
    vector<Sprint *> inProgress;
    vector<Issue *> done;

public:
    Project(string in_name, User *in_owner, string in_desc) : name(in_name), owner(in_owner), description(in_desc), issueCount(0)
    {
        lead = vector<User *>();
        member = vector<User *>();
        todo = vector<Issue *>();
        inProgress = vector<Sprint *>();
        done = vector<Issue *>();
    }

    // getters
    string getName() const { return name; }
    User *getOwner() const { return owner; }
    int getIssueCount() const { return issueCount; }
    string getDescription() const { return description; }
    vector<User *> getLead() const { return lead; }
    vector<User *> getMember() const { return member; }
    vector<Issue *> getTodo() const { return todo; }
    vector<Sprint *> getInProgress() const { return inProgress; }
    vector<Issue *> getDone() const { return done; }

    // setters
    void setName(string other) { name = other; }
    void setIssueCount(int other) { issueCount = other; }
    void setDescription(string other) { description = other; }
    void setTodo(vector<Issue *> other) { todo = other; }
    void setinProgress(vector<Sprint *> other) { inProgress = other; }
    void setDone(vector<Issue *> other) { done = other; }

    User *searchName(string name);
    void invite(User *, UserRole);
    bool containsUser(string);
    UserRole getRole(string);
    // member -> lead
    void promoteMember(string);
    // lead -> member
    void downgradeLead(string);
    void removeMember(string);

    Issue *getIssue(string);
    void addTodo(int, User *, int, int, IssueType, string);
    void addTodo(Issue *);
    Issue *popTodo(string);
    void pushSprint(int);
    Sprint *popSprint();
    void addDone(Issue *other) { done.push_back(other); }

    // file o
    string out_string() const;

    // update by day count
    void updateDay(int);

    ~Project()
    {
        for (auto i : todo)
            delete i;
        for (auto s : inProgress)
            delete s;
        for (auto i : done)
            delete i;
    }
};

#endif
