// Final Project
// Tianye Ding
// 5/1/2022
#ifndef SPRINT_H
#define SPRINT_H

#include "Issue.hpp"

class Project;

class Sprint
{
    vector<Issue *> todo;
    Project *parent;
    int startDate;
    int endDate;

public:
    Sprint(Project *in_parent, int in_start, int duration) : parent(in_parent), startDate(in_start), endDate(in_start + duration)
    {
        todo = vector<Issue *>();
    }

    // getters
    Project *getParent() const { return parent; }
    vector<Issue *> getTodo() const { return todo; }
    int getStart() const { return startDate; }
    int getEnd() const { return endDate; }
    // setters
    void setStart(int other) { startDate = other; }
    void setEnd(int other) { endDate = other; }

    void addIssue(Issue *other) { todo.push_back(other); }
    Issue *popIssue(string id);

    // file o
    string out_string() const;

    ~Sprint()
    {
        for (auto i : todo)
            delete i;
    }
};

#endif
