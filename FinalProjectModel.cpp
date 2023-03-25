#include "FinalProjectModel.hpp"
#include "Issue.hpp"
#include "Project.hpp"
#include "Sprint.hpp"
#include "User.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <class T> bool contains(T element, vector<T> v);

User *FinalProjectModel::getCurrentUser() { return this->currentUser; }

Project *FinalProjectModel::getCurrentProject() { return this->currentProject; }

int FinalProjectModel::getPermissionLevel() { return this->permissionLevel; }

vector<User *> FinalProjectModel::getUserList() { return this->userList; }

vector<Project *> FinalProjectModel::getProjectList() {
  return this->projectList;
}

bool FinalProjectModel::isLeader() { return this->permissionLevel >= 1; }

bool FinalProjectModel::isOwner() { return this->permissionLevel == 2; }

void FinalProjectModel::setCurrentUser(User *u) { this->currentUser = u; }

void FinalProjectModel::setCurrentProject(Project *p) {
  this->currentProject = p;
}

void FinalProjectModel::setPermissionLevel(int p) { this->permissionLevel = p; }

void FinalProjectModel::setUserList(vector<User *> ul) { this->userList = ul; }

void FinalProjectModel::setProjectList(vector<Project *> pl) {
  this->projectList = pl;
}

void FinalProjectModel::updatePermissionLevel() {
  for (auto i : this->currentProject->getMember()) {
    if (this->currentUser->getName() == i->getName()) {
      this->permissionLevel = 0;
    }
  }

  for (auto i : this->currentProject->getLead()) {
    if (this->currentUser->getName() == i->getName()) {
      this->permissionLevel = 1;
    }
  }

  if (this->currentUser->getName() ==
      this->currentProject->getOwner()->getName()) {
    this->permissionLevel = 2;
  }
}

void FinalProjectModel::readFrom(string fileName) {}

void FinalProjectModel::writeTo(string fileName) {}

void FinalProjectModel::addUser(User *u) { this->userList.push_back(u); }

void FinalProjectModel::addProject(Project *p) {
  this->projectList.push_back(p);
}

void FinalProjectModel::changeCurrentUser(int index) {
  if (index < 0 || index >= this->userList.size()) {
    // nothing happens
  } else {
    this->currentUser = userList.at(index);
  }
}

void FinalProjectModel::changeCurrentProject(int role, int index) {
  vector<Project *> copy;
  this->currentProject = NULL;
  if (role < 0 || role > 2 || index < 0) {
  } else {
    if (role == 0) {
      if (index < this->getCurrentUser()->getMemberProjects().size()) {
        this->currentProject =
            this->getCurrentUser()->getMemberProjects().at(index);
      }
    } else if (role == 1) {
      if (index < this->getCurrentUser()->getLeadProjects().size()) {
        this->currentProject =
            this->getCurrentUser()->getLeadProjects().at(index);
      }
    } else if (role == 2) {
      if (index < this->getCurrentUser()->getOwnerProjects().size()) {
        cout << "index" << index<< endl;
        this->currentProject =
            this->getCurrentUser()->getOwnerProjects().at(index);
        
      }
    }
  }
}

void FinalProjectModel::createProject(string name, string description) {
  Project *newProject = new Project(name, this->currentUser, description);

  projectList.push_back(newProject);
  this->currentUser->addOwnerProject(newProject);
}

void FinalProjectModel::createIssue(int in_prior, User *in_report,
                                    int in_create, int in_due,
                                    IssueType in_type, string in_des,
                                    User *assignee) {
  this->currentProject->addTodo(in_prior, in_report, in_create, in_due, in_type,
                                in_des);

  if (isLeader()) {
    this->currentProject->getTodo()
        .at(this->currentProject->getTodo().size() - 1)
        ->assign(assignee);
  } else {
    this->currentProject->getTodo()
        .at(this->currentProject->getTodo().size() - 1)
        ->assign(this->currentUser);
  }
}

void FinalProjectModel::updateIssue(string issueID, User *in_assignee,
                                    string comment) {
  struct Comment *c1;
  c1->poster = this->currentUser;
  c1->time = this->dayCount;
  c1->content = comment;
  if (isLeader()) {
    this->currentProject->getIssue(issueID)->addComment(c1);
    this->currentProject->getIssue(issueID)->assign(in_assignee);
  } else {
    if (this->currentProject->getIssue(issueID)->getReporter()->getName() ==
        this->currentUser->getName()) {
      this->currentProject->getIssue(issueID)->addComment(c1);
    }
  }
}

void FinalProjectModel::changeProjectName(string name) {
  if (isLeader()) {
    this->currentProject->setName(name);
  }
}

void FinalProjectModel::changeProjectDes(string newDes) {
  if (isLeader()) {
    this->currentProject->setDescription(newDes);
  }
}

void FinalProjectModel::promoteMember(string name) {
  if (isLeader()) {
    this->currentProject->promoteMember(name);
  }
}

void FinalProjectModel::downgradeLead(string name) {
  if (isLeader()) {
    this->currentProject->downgradeLead(name);
  }
}

void FinalProjectModel::kick(string name) {
  if (isLeader()) {
    this->currentProject->removeMember(name);
  }
}

void FinalProjectModel::invite(string name, int level) {
  if (isLeader()) {
    UserRole r;
    if (level == 0) {
      r = UserRole::member;
    } else if (level == 1){
      r = UserRole::lead;
    } else {
      r = UserRole::owner;
    }

    for (auto i : this->userList) {
      if (i->getName() == name) {
        this->currentProject->invite(i, r);
      }
    }
  }
}

void FinalProjectModel::createSprint(int in_duration) {
  if (isLeader()) {
    this->currentProject->pushSprint(in_duration);
  }
}

void FinalProjectModel::addToSprint(string id, int index) {
  if (index >= this->currentProject->getInProgress().size()) {
    cout << "Invalid Sprint index" << endl;
    return;
  }

  Issue *temp = this->currentProject->popTodo(id);
  if (temp != nullptr) {
    this->currentProject->getInProgress().at(index)->addIssue(temp);
  }
}

void FinalProjectModel::changeSprintDuration(int index, int d) {
  if (isLeader()) {
    int count = 0;
    for (auto i : this->currentProject->getInProgress()) {
      if (count == index) {
        i->setEnd(i->getStart() + d);
      }
      count++;
    }
  }
}

void FinalProjectModel::deleteProject() {
  if (isOwner()) {
    int index = 0;
    for (auto i : this->projectList) {
      if (this->currentProject->getName() == i->getName()) {

        this->projectList.erase(this->projectList.begin() + index);

        string projectName = i->getName();
        for (auto u : this->userList) {
          u->removeProject(projectName);
        }
        
        delete i;
        break;
      }
      index++;
    }

    this->currentProject = nullptr;
  }
}

void FinalProjectModel::changeIssueID(string id, string newID) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setId(newID);
  }
}

void FinalProjectModel::changeIssuePriority(string id, int newP) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setPriority(newP);
  }
}

void FinalProjectModel::changeIssueAssignee(string id, User *u) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->assign(u);
  }
}

void FinalProjectModel::changeIssueDueDate(string id, int newDue) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setDue(newDue);
  }
}

void FinalProjectModel::changeIssueStatus(string id, IssueStatus newStatus) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setStatus(newStatus);
  }
}

void FinalProjectModel::changeIssueType(string id, IssueType newType) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setType(newType);
  }
}

void FinalProjectModel::changeIssueDescription(string id, string newDes) {
  if (isLeader()) {
    this->currentProject->getIssue(id)->setDescription(newDes);
  }
}

void FinalProjectModel::removeTodo(string id) {
  if (isLeader()) {
    Issue *temp = this->currentProject->popTodo(id);
    delete temp;
  }
}

void FinalProjectModel::moveBetween(string issueID, int index1, int index2) {
  Issue *temp =
      this->currentProject->getInProgress().at(index1)->popIssue(issueID);
  this->currentProject->getInProgress().at(index2)->addIssue(temp);
}

void FinalProjectModel::updateDay() {
  dayCount++;
  for (auto p : projectList) {
    p->updateDay(dayCount);
  }
}

string FinalProjectModel::showTodo() {
}

string FinalProjectModel::showWorkDone() {
  vector<Issue *> workDone = this->currentProject->getDone();
  stringstream ss;
  for (auto wd : workDone) {
    ss << wd->out_string() << endl;
  }
  return ss.str();
}