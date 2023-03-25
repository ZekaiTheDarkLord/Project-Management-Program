// Final Project
// Tianye Ding
// 5/1/2022
#include "Project.hpp"
#include "Issue.hpp"
#include "User.hpp"
#include "UserRole.hpp"
#include <stdexcept>

using namespace std;

User *Project::searchName(string name) {
  if (name == this->owner->getName()) {
    return this->owner;
  }

  for (auto i : this->lead) {
    if (name == i->getName()) {
      return i;
    }
  }

  for (auto i : this->member) {
    if (name == i->getName()) {
      return i;
    }
  }
}

void Project::invite(User *other, UserRole role) {
  if (role == UserRole::owner) {
    cout << "Project can only have one owner" << endl;
    return;
  }

  if (role == UserRole::lead) {
    lead.push_back(other);
    other->addLeadProject(this);
  } else {
    member.push_back(other);
    other->addMemberProject(this);
  }
}

bool Project::containsUser(string id) {
    if (owner->getName() == id)
        return true;
    for (auto l : lead) {
        if (l->getName() == id)
            return true;
    }
    for (auto m : member) {
        if (m->getName() == id)
            return true;
    }

    return false;
}

UserRole Project::getRole(string id) {
  if (owner->getName() == id)
    return UserRole::owner;
  for (auto l : lead) {
    if (l->getName() == id)
      return UserRole::lead;
  }
  for (auto m : member) {
    if (m->getName() == id)
      return UserRole::member;
  }

  cout << "User(" + id + ") cannot be found" << endl;
}

void Project::promoteMember(string id) {
  for (int i = 0; i < member.size(); i++) {
    User *temp = member.at(i);
    if (temp->getName() == id) {
      lead.push_back(temp);
      member.erase(member.begin() + i);
      temp->removeProject(this->name);
      temp->addLeadProject(this);
      return;
    }
  }

  cout << "User(" + id + ") cannot be found" << endl;
}

void Project::downgradeLead(string id) {
  for (int i = 0; i < lead.size(); i++) {
    User *temp = lead.at(i);
    if (temp->getName() == id) {
      member.push_back(temp);
      lead.erase(lead.begin() + i);
      temp->removeProject(this->name);
      temp->addMemberProject(this);
      return;
    }
  }

  cout << "User(" + id + ") cannot be found" << endl;
}

void Project::removeMember(string id) {
  if (owner->getName() == id) {
    cout << "Owner cannot be removed" << endl;
    return;
  }

  for (int i = 0; i < lead.size(); i++) {
    if (lead.at(i)->getName() == id) {
      lead.at(i)->removeProject(this->name);
      lead.erase(lead.begin() + i);
      return;
    }
  }
  for (int i = 0; i < member.size(); i++) {
    if (member.at(i)->getName() == id) {
      member.at(i)->removeProject(this->name);
      member.erase(member.begin() + i);
      return;
    }
  }

  cout << "User(" + id + ") cannot be found" << endl;
}

Issue *Project::getIssue(string id) {
  for (auto i : todo) {
    if (i->getId() == id)
      return i;
  }
  for (auto s : inProgress) {
    for (auto i : s->getTodo()) {
      if (i->getId() == id)
        return i;
    }
  }
  for (auto i : done) {
    if (i->getId() == id)
      return i;
  }

  cout << "Issue(" + id + ") cannot be found" << endl;
}

void Project::addTodo(int in_prior, User *in_report, int in_create, int in_due,
                      IssueType in_type, string in_des) {
  string id = name + '-' + to_string(issueCount);
  Issue *temp = new Issue(id, in_prior, in_report, in_create, in_due, this,
                          in_type, in_des);

  bool pushFlag = true;
  for (int i = 0; i < todo.size(); i++) {
    Issue *current = todo.at(i);
    if ((in_prior == current->getPriority() && in_due < current->getDue()) ||
        (in_prior > current->getPriority())) {
      todo.insert(todo.begin() + i, temp);
      pushFlag = false;
      break;
    }
  }
  if (pushFlag)
    todo.push_back(temp);

  issueCount++;
}

void Project::addTodo(Issue *other) {
  bool pushFlag = true;
  for (int i = 0; i < todo.size(); i++) {
    Issue *current = todo.at(i);
    if ((other->getPriority() == current->getPriority() &&
         other->getDue() < current->getDue()) ||
        (other->getPriority() > current->getPriority())) {
      todo.insert(todo.begin() + i, other);
      pushFlag = false;
      break;
    }
  }
  if (pushFlag)
    todo.push_back(other);
}

Issue *Project::popTodo(string id) {
  for (int i = 0; i < todo.size(); i++) {
    if (todo.at(i)->getId() == id) {
      Issue *temp = todo.at(i);
      todo.erase(todo.begin() + i);
      return temp;
    }
  }

  cout << "Issue(" + id + ") cannot be found" << endl;
  return nullptr;
}

void Project::pushSprint(int duration) {
  int start = 0;
  if (inProgress.size() > 0)
    start = inProgress.at(inProgress.size() - 1)->getEnd() + 1;
  Sprint *temp = new Sprint(this, start, duration);
  inProgress.push_back(temp);
}

Sprint *Project::popSprint() {
  Sprint *temp = inProgress.at(0);
  inProgress.erase(inProgress.begin());
  return temp;
}

string Project::out_string() const {
  string output = name + '\n' + owner->getName() + '\n' + description + '\n' +
                  to_string(issueCount) + '\n';
  output += "lead:\n";
  for (auto u : lead)
    output += u->getName() + '\n';
  output += "member:\n";
  for (auto u : member)
    output += u->getName() + '\n';

  output += "todo:\n";
  for (auto i : todo)
    output += i->out_string();

  output += "inProgress:\n";
  for (auto s : inProgress)
    output += s->out_string();

  output += "done:\n";
  for (auto i : done)
    output += i->out_string();

  return output + '\n';
}

void Project::updateDay(int dayCount) {
  // update from todo list
  if (todo.size() > 0) {
    vector<Issue *> overTodo = vector<Issue *>();
    for (int i = todo.size() - 1; i >= 0; i--) {
      if (todo.at(i)->getDue() < dayCount) {
        Issue *temp = todo.at(i);
        temp->setStatus(IssueStatus::overdue);
        temp->setPriority(temp->getPriority() + 1);
        overTodo.push_back(temp);
        todo.erase(todo.begin() + i);
      }
    }
    for (auto i : overTodo)
      this->addTodo(i);
  }
  // update from Sprints
  if (inProgress.size() > 0) {
    if (inProgress.at(0)->getEnd() < dayCount) {
      Sprint *temp = popSprint();
      for (auto i : temp->getTodo()) {
        Issue *current = temp->popIssue(i->getId());
        if (current->getStatus() == IssueStatus::done)
          this->addDone(current);
        else {
          current->setPriority(current->getPriority() + 1);
          if (current->getDue() < dayCount)
            current->setStatus(IssueStatus::overdue);
          this->addTodo(current);
        }
      }
      delete temp;
    }
  }
}
