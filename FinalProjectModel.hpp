#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "Issue.hpp"
#include "Sprint.hpp"
#include "Project.hpp"
#include "User.hpp"

using namespace std;

class FinalProjectModel
{
private:
    User *currentUser;
    Project *currentProject;
    int permissionLevel; // the permission level of users ranging from 0-2. 0 is the lowest and 2 is the highest
    vector<User *> userList;
    vector<Project *> projectList;
    int dayCount;

public:
    // the constructor
    FinalProjectModel()
    {
        this->currentUser = nullptr;
        this->currentProject = nullptr;
        this->dayCount = 0;
    }

    FinalProjectModel(User *cu, Project *cp, vector<User *> ul, vector<Project *> pl)
    {
        this->currentUser = cu;
        this->currentProject = cp;
        this->userList = ul;
        this->projectList = pl;
        this->dayCount = 0;
    }

    // getters
    User *getCurrentUser();

    Project *getCurrentProject();

    int getPermissionLevel();

    vector<User *> getUserList();

    vector<Project *> getProjectList();

    int getDayCount() const { return dayCount; }

    // returns true if permission level > 0 returns false vice versa.
    bool isLeader();

    // returns true if permission level == 2
    bool isOwner();

    // setters
    void setCurrentUser(User *u);

    void setCurrentProject(Project *p);

    void setPermissionLevel(int i);

    void setUserList(vector<User *> ul);

    void setProjectList(vector<Project *> pl);

    void setDayCount(int other) { dayCount = other; }

    void updatePermissionLevel();

    //------------------------------------fileIO---------------------

    void readFrom(string fileName);

    void writeTo(string fileName);

    //------------------------------------change status--------------

    // add the user into the user list
    void addUser(User* u);

    // add the project into the project list
    void addProject(Project* p);
  

    // enter the index of the user in the user list and change the current user to that selected one. If the index<0 or index> userList.size(), it will change nothing.
    void changeCurrentUser(int index);

    // enter the permissionLevel: 0 = developer, 1 = lead, 2 = creator
    // and the index, change the project into the the entered project under that user. If no project can be find, nothing changes.
    void changeCurrentProject(int role, int index);

    // create a project with input project name and project description. The owner will be the current user.
    // add a project into currentuser, add a user in to current project
    void createProject(string name, string description);

    // create a issue, the reporter will be the current user
    // the operation of this is depend on the permission level of the user
    // for the field of assignee:
    // if permission level == 0: can only assign to the creator
    // if permission level >= 1: can self-assign or assign to other developer
    void createIssue(int in_prior, User *in_report, int in_create, int in_due, IssueType in_type, string in_des, User *assignee);

    // update an issue by commenting on it and assign it to another user.
    // permission level == 0: update issue assign to them
    // permission level >= 1: update any issue
    // if input issueID is invalid, nothing happens.
    void updateIssue(string issueID, User *in_assignee, string comment);

    //------------------------------------for leaders--------------------
    // all the following method requires permission level > 0(isLeader() == true)

    // change project name
    void changeProjectName(string newName);

    // change the project description
    void changeProjectDes(string newDes);

    // set up a member's permission level
    void promoteMember(string name);

    void downgradeLead(string name);

    // reomve a member from the project
    void kick(string name);

    // invite a user in the user list by entering the name of it
    void invite(string name, int level);

    // create a new sprint for current project, the parent project will be the current project
    void createSprint(int duration);

    // change the duration for a sprint
    void changeSprintDuration(int index, int d);

    // add an issue to a sprint
    void addToSprint(string id, int index);

    // *project owner only delete current project
    void deleteProject();

    // change a issue's property (to be expanded)
    void changeIssueID(string id, string newID);

    void changeIssuePriority(string id, int newP);

    void changeIssueAssignee(string id, User *u);

    void changeIssueDueDate(string id, int newDue);

    void changeIssueStatus(string id, IssueStatus newStatus);

    void changeIssueType(string id, IssueType newType);

    void changeIssueDescription(string id, string newDes);

    // given the issue id, remove the issue from the todo list
    void removeTodo(string id);

    // move issue between sprint (sprint should be updated)
    void moveBetween(string issueID, int index1, int index2);

    //------------------------------------view---------------------------
    // return a string, show all the information for the current project including project name, description, collaborators.
    string showProjectInfo();

    // return a string, show issues in todo with all the information in the current project
    string showTodo();

    // return a string, return the in progress todo
    string showInProcess();

    // return a string, return the finished issues
    string showWorkDone();

    // view an existing issue by inputing the id of it, shows the priority, status
    // if input id is invalid, nothing happens.
    string showIssue(string issueID);

    // proceed to the next day and make state changes
    void updateDay();

    // destructor
    ~FinalProjectModel() {
        for (auto p : projectList)
            delete p;
        for (auto u : userList)
            delete u;
    }
};

#endif
