#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "Project.hpp"

using namespace std;

class User {
private: 
  string name; 
  string password; 
  vector<Project*> ownerProjects;
  vector<Project*> leadProjects;
  vector<Project*> memberProjects;

public: 
  // the constructor
    User(string s1, string s2) {
    this->name = s1;
    this->password = s2;
  }

  // getters
  string getName();

  string getPassword();

  vector<Project*> getOwnerProjects();

  vector<Project*> getLeadProjects();

  vector<Project*> getMemberProjects();

  // setters
  void setName(string s);

  void setPassword(string s);

  void setOwnerProjects(vector<Project*> p);

  void setLeadProjects(vector<Project*> p);

  void setMemberProjects(vector<Project*> p);

  // determine whether the user enters the correct password, if yes, return true; if no, return false; 
  bool login(string s);

  // add a project for this user 
  void addOwnerProject(Project* p);

  void addLeadProject(Project* p);

  void addMemberProject(Project* p);

  void removeProject(string name);

  ~User() {}
};

#endif