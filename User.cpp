#include "User.hpp"
#include "Project.hpp"
#include <iostream>
#include <vector>

string User::getName() { return this->name; }

string User::getPassword() { return this->password; }

vector<Project *> User::getOwnerProjects() { return this->ownerProjects; }

vector<Project *> User::getLeadProjects() { return this->leadProjects; }

vector<Project *> User::getMemberProjects() { return this->memberProjects; }

void User::setName(string s) { this->name = s; }

void User::setPassword(string s) { this->password = s; }

void User::setOwnerProjects(vector<Project *> p) { this->ownerProjects = p; }

void User::setLeadProjects(vector<Project *> p) { this->leadProjects = p; }

void User::setMemberProjects(vector<Project *> p) { this->memberProjects = p; }

bool User::login(string s) { return this->password == s; }

void User::addOwnerProject(Project *p) { this->ownerProjects.push_back(p); }

void User::addLeadProject(Project *p) { this->leadProjects.push_back(p); }

void User::addMemberProject(Project *p) { this->memberProjects.push_back(p); }

void User::removeProject(string name) {
  for (int i = 0; i < this->ownerProjects.size(); i++) {
    if (this->ownerProjects.at(i)->getName() == name) {
      this->ownerProjects.erase(this->ownerProjects.begin() + i);
      return;
    }
  }
  for (int i = 0; i < this->leadProjects.size(); i++) {
    if (this->leadProjects.at(i)->getName() == name) {
      this->leadProjects.erase(this->leadProjects.begin() + i);
      return;
    }
  }
  for (int i = 0; i < this->memberProjects.size(); i++) {
    if (this->memberProjects.at(i)->getName() == name) {
      this->memberProjects.erase(this->memberProjects.begin() + i);
      return;
    }
  }
}