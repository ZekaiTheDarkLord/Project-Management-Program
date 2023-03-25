#include "FinalProjectModel.hpp"
#include "Issue.hpp"
#include "IssueType.hpp"
#include "Project.hpp"
#include "Sprint.hpp"
#include "User.hpp"
#include "UserPassword.hpp"
#include "UserRole.hpp"
#include <iostream>
#include <string>

IssueType stringToType(string s);
string statusToString(IssueStatus i);
IssueStatus stringToStatus(string s);

void projectOutput(Project *pro) {
  ofstream projectOutput("project.txt");
  if (!projectOutput) {
    cout << "can't open file" << endl;
    EXIT_FAILURE;
  }
  projectOutput << pro->out_string() << endl;
}
IssueType stringToType(string s) {
  if (s == "userStory") {
    return IssueType::userStory;
  } else if (s == "task") {
    return IssueType::task;
  } else if (s == "build") {
    return IssueType::build;
  } else if (s == "test") {
    return IssueType::test;
  } else if (s == "debug") {
    return IssueType::debug;
  } else if (s == "documentation") {
    return IssueType::documentation;
  } else if (s == "other") {
    return IssueType::other;
  }
}

string typeToString(IssueType type) {
  string output = "";
  switch (type) {
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
  return output;
}

void errorCheckingMessage(string message) { cout << message << endl; }

IssueStatus stringToStatus(string s) {
  if (s == "open") {
    return IssueStatus::open;
  } else if (s == "inProgress") {
    return IssueStatus::inProgress;
  } else if (s == "done") {
    return IssueStatus::done;
  } else if (s == "overdue") {
    return IssueStatus::overdue;
  }
}

string statusToString(IssueStatus i) {
  if (i == IssueStatus::open) {
    return "open";
  } else if (i == IssueStatus::inProgress) {
    return "inProgress";
  } else if (i == IssueStatus::done) {
    return "done";
  } else if (i == IssueStatus::overdue) {
    return "overDue";
  }
}

int main() {
  User *zekai = new User("zekai", "123123");
  User *tianye = new User("tianye", "789789");
  User *su = new User("su", "1313131");
  User *wyz = new User("wyz", "789789");
  User *john = new User("john", "1313131");

  Project *p1 = new Project("p1", zekai, "des1");
  Project *p2 = new Project("p2", tianye, "des2");
  Project *p3 = new Project("p3", su, "des3");

  zekai->addOwnerProject(p1);
  tianye->addLeadProject(p1);
  tianye->addOwnerProject(p2);
  su->addMemberProject(p1);
  su->addOwnerProject(p3);
  zekai->addLeadProject(p3);
  wyz->addMemberProject(p1);
  john->addMemberProject(p1);
  wyz->addLeadProject(p2);
  john->addLeadProject(p3);
  /*
  Issue *i1 = new Issue("001", 1, zekai, 0, 10, p1, IssueType::task, "des1");
  Issue *i2 = new Issue("002", 1, tianye, 0, 10, p1, IssueType::task, "des1");
  Issue *i3 = new Issue("002", 1, su, 0, 10, p1, IssueType::task, "des1");
  */

  FinalProjectModel *model = new FinalProjectModel();

  model->addUser(zekai);
  model->addUser(tianye);
  model->addUser(su);
  model->addUser(wyz);
  model->addUser(john);

  model->addProject(p1);
  model->addProject(p2);
  model->addProject(p3);

  string menu =
      "----------------------------------------------------------\n"
      "1. change user\n2. change project\n3. read data "
      "from local file\n4. write data to local file\n5. create a project\n6. "
      "see current project information\n7. see todo list \n8. see sprints \n9. "
      "see work done\n10. create an issue \n11. update an issue \n12. change "
      "current project name\n13. change project description\n14. promote a "
      "member\n15. downgrade a lead \n16. remove a member\n17. invite a user "
      "to the project\n18. create a sprint\n19. change a sprint duration\n20. "
      "add issue to sprint\n21. "
      "delete the current project\n22. see issue information \n23. change "
      "issue id\n24. change issue priority \n25. change issue assignee\n26. "
      "change issue due date\n27. change issue status\n28. change issue "
      "type\n29. change issue description\n30. remove an issue from todo "
      "list\n31. move issues between sprint.\n32. move to next day\n33. quit "
      "and save";

  while (1) {
    if (model->getCurrentUser() == nullptr) {

      cout << "Please login!" << endl;

      cout << "User list: \n";

      int index = 0;
      for (auto i : model->getUserList()) {
        cout << index + 1 << ". " << i->getName() << endl;
        index++;
      }
      index = 0;

      int inputIndex;
      cin >> inputIndex;
      if (!cin) {
        cout << "Plese enter correct value" << endl;
        cin.clear();
        cin.ignore();
        continue;
      }
      model->changeCurrentUser(inputIndex - 1);

    } else if (model->getCurrentProject() == nullptr) {
      cout << "Please select a project to start" << endl;
      int projectIndex = 1;

      cout << "As owner: " << endl;
      for (auto i : model->getCurrentUser()->getOwnerProjects()) {
        cout << projectIndex << ". " << i->getName() << endl;
        projectIndex++;
      }

      projectIndex = 1;
      cout << "As leader: " << endl;
      for (auto i : model->getCurrentUser()->getLeadProjects()) {
        cout << projectIndex << ". " << i->getName() << endl;
        projectIndex++;
      }

      projectIndex = 1;
      cout << "As member: " << endl;
      for (auto i : model->getCurrentUser()->getMemberProjects()) {
        cout << projectIndex << ". " << i->getName() << endl;
        projectIndex++;
      }

      int role;
      cout << "Please choose which kind of project."
           << "\n"
           << "Type 0 for member project"
           << "\n"
           << "1 for lead project"
           << "\n"
           << "2 for owner project "
           << "\n";
      cin >> role;
      if (!cin) {
        cout << "Plese enter correct value" << endl;
        cin.clear();
        cin.ignore();
        continue;
      }
      int inputIndex;
      cout << "Please type the project index. " << endl;
      cin >> inputIndex;
      if (!cin) {
        cout << "Plese enter correct value" << endl;
        cin.clear();
        cin.ignore();
        continue;
      }
      if (role > 2) {
        cout << "Please enter correct value!" << endl;
        continue;
      }
      if (!cin) {
        cout << "Plese enter correct value" << endl;
        cin.clear();
        cin.ignore();
        continue;
      }
      model->changeCurrentProject(role, inputIndex - 1);
      model->updatePermissionLevel();
    } else {
      int command;

      cout << "Welcome to the system!" << endl;
      cout << "Current User: " << model->getCurrentUser()->getName() << endl;
      cout << "Current Project: " << model->getCurrentProject()->getName()
           << endl;
      cout << "Current date: " << model->getDayCount() << endl;
      cout << menu << endl;
      cout << "Please type the command: " << endl;
      cin >> command;
      if (!cin) {
        cout << "Plese enter correct value" << endl;
        cin.clear();
        cin.ignore();
        continue;
      }
      if (command == 33) {
        break;
      } else {
        switch (command) {
        case 1: { // change user
          cout << "User list: \n";

          int index = 0;
          for (auto i : model->getUserList()) {
            cout << index + 1 << ". " << i->getName() << endl;
            index++;
          }
          index = 0;

          int inputIndex;
          cin >> inputIndex;

          model->changeCurrentUser(inputIndex - 1);
          model->setCurrentProject(nullptr);

          cout << "Please select a project to start" << endl;
          int projectIndex = 1;

          cout << "As owner: " << endl;
          for (auto i : model->getCurrentUser()->getOwnerProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          projectIndex = 1;
          cout << "As leader: " << endl;
          for (auto i : model->getCurrentUser()->getLeadProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          projectIndex = 1;
          cout << "As member: " << endl;
          for (auto i : model->getCurrentUser()->getMemberProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          int role;
          cout << "Please choose which kind of project. Type 0 for member  "
                  "project, 1 for lead project, 2 for owner project.(if there "
                  "are no project under the field, please do not enter the "
                  "corresponding number)"
               << endl;
          cin >> role;

          int inputIndex2;
          cout << "Please type the project index. " << endl;
          cin >> inputIndex2;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->changeCurrentProject(role, inputIndex2 - 1);
          model->updatePermissionLevel();
          break;
        }
        case 2: { // change project
          cout << "Please select a project to start" << endl;
          int projectIndex = 1;

          cout << "As owner: " << endl;
          for (auto i : model->getCurrentUser()->getOwnerProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          projectIndex = 1;
          cout << "As leader: " << endl;
          for (auto i : model->getCurrentUser()->getLeadProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          projectIndex = 1;
          cout << "As member: " << endl;
          for (auto i : model->getCurrentUser()->getMemberProjects()) {
            cout << projectIndex << ". " << i->getName() << endl;
            projectIndex++;
          }

          int role;
          cout << "Please choose which kind of project. Type 0 for member  "
                  "project, 1 for lead project, 2 for owner project.(if there "
                  "are no project under the field, please do not enter the "
                  "corresponding number)"
               << endl;
          cin >> role;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          int inputIndex;
          cout << "Please type the project index. " << endl;
          cin >> inputIndex;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->changeCurrentProject(role, inputIndex - 1);
          model->updatePermissionLevel();
          break;
        }
        case 3: { // read data from local file
          break;
        }
        case 4: { // write data to local file
          projectOutput(model->getCurrentProject());
          break;
        }
        case 5: { // create a project
          string inputName;
          string inputDescription;
          cout << "Please enter a name for this project." << endl;
          cin >> inputName;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please enter the description for this project." << endl;
          cin >> inputDescription;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->createProject(inputName, inputDescription);
          break;
        }
        case 6: { // see current project information
          // cout <<model->getCurrentProject()->out_string() << endl;
          cout << "Project Name: " << model->getCurrentProject()->getName()
               << endl;
          cout << "Project Description: "
               << model->getCurrentProject()->getDescription() << endl;
          cout << "Owner: " << model->getCurrentProject()->getOwner()->getName()
               << endl;
          cout << "Leaders:" << endl;
          for (auto i : model->getCurrentProject()->getLead()) {
            cout << i->getName() << "    ";
          }
          cout << endl;
          cout << "Members:" << endl;
          for (auto i : model->getCurrentProject()->getMember()) {
            cout << i->getName() << "    ";
          }
          cout << endl;
          break;
        }
        case 7: { // see the todo list
            vector<Issue *> todo = model->getCurrentProject()->getTodo();
            for (auto issue : todo) {
              cout <<"ID:"<< issue->getId() << endl;
              cout <<"Priority:"<< issue->getPriority() << endl;
              cout << "Asignee:" << issue->getAssignee()->getName() << endl;
              cout << "Reporter:" << issue->getReporter()->getName() << endl;
              cout << "Due:" << issue-> getDue() << endl;
              cout << "Status:" << statusToString(issue-> getStatus()) << endl;
              cout << "Type:" << typeToString(issue->getType())<< endl;
              cout << "Description:" << issue-> getDescription() << endl;
              cout << "Comments";
              for (auto c : issue->getComments()){
                cout << c->out_string()<<endl;
              }
            }
          break;
        }
        case 8: { // see sprints
          vector<Sprint *> sprints =
              model->getCurrentProject()->getInProgress();
          for (auto s : sprints) {
            cout << s->out_string() << endl;
          }
          break;
        }
        case 9: { // see work done
          string wordDone = model->showWorkDone();
          cout << wordDone << endl;
          break;
        }
        case 10: { // create an issue
          int in_prior;
          string reporter;
          int in_create;
          int in_due;
          string type;
          string in_des;
          string assignee;

          cout << "Please input the priority(int): " << endl;
          cin >> in_prior;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the reporter name(must exist as user): "
               << endl;
          cin >> reporter;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the create date(int from 0): " << endl;
          cin >> in_create;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the due date(int from 0): " << endl;
          cin >> in_due;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the type: (userStory, task, build, test, "
                  "debug, documentation, other)"
               << endl;
          cin >> type;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the description: " << endl;
          cin.ignore();
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          getline(cin, in_des);
          cout << "Please input the assignee name (note: if you are not a "
                  "leader, the issue will be automatically self-assigned): "
               << endl;
          cin >> assignee;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->createIssue(in_prior,
                             model->getCurrentProject()->searchName(reporter),
                             in_create, in_due, stringToType(type), in_des,
                             model->getCurrentProject()->searchName(assignee));
          break;
        }
        case 11: { // update an issue
          string issueID;
          string assigneeName;
          string comment;
          cout << "Note: if you are a member, you can only update problem that "
                  "assigned to you. "
               << endl;
          cout << "Please input the issue id you want to update. " << endl;
          cin >> issueID;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Please input the assignee name." << endl;
          cin >> assigneeName;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cin.ignore();
          cout << "Please input the comment." << endl;
          getline(cin,comment);
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->updateIssue(
              issueID, model->getCurrentProject()->searchName(assigneeName),
              comment);
          break;
        }
        case 12: { // change current project name
          if (model->isLeader()) {
            string newName;
            cout << "Please enter the new project name: " << endl;
            cin >> newName;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeProjectName(newName);

          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 13: { // change project description
          if (model->isLeader()) {
            string newDes;
            cout << "Please enter the new project description: " << endl;
            cin >> newDes;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeProjectDes(newDes);
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 14: { // promote a member
          if (model->isOwner()) {
            string memberName;
            cout << "Please enter a member name: " << endl;
            cin >> memberName;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->promoteMember(memberName);
            model->updatePermissionLevel();
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 15: { // downgrade a leader
          if (model->isOwner()) {
            string leadName;
            cout << "Please enter a leader name: " << endl;
            cin >> leadName;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->downgradeLead(leadName);
            model->updatePermissionLevel();
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 16: { // remove a member
          if (model->isLeader()) {
            string memberName;
            cout << "Please enter a member name: " << endl;
            cin >> memberName;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->kick(memberName);
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 17: { // invite a user to the project
          if (model->isOwner()) {
            int level;
            string memberName;

            cout << "Please enter the user name you want to invite(user must "
                    "exist): "
                 << endl;
            cin >> memberName;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the permission level you wanto to give. 0 "
                    "for member; 1 for leader."
                 << endl;
            cin >> level;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }

            if (model->getCurrentProject()->containsUser(memberName)) {

            } else {
              model->invite(memberName, level);
              cout << model->getPermissionLevel() << endl;
            }
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 18: { // create a sprint
          if (model->isLeader()) {
            int duration;
            cout << "Please enter the duration of the sprint." << endl;
            cin >> duration;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->createSprint(duration);
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 19: { // change a sprint duration
          if (model->isLeader()) {
            int index;
            int duration;
            cout << "Please enter the index of the sprint." << endl;
            cin >> index;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the new duration of the sprint." << endl;
            cin >> duration;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeSprintDuration(index, duration);
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 20: {
          string issueID;
          int sprintIndex;
          cout << "Plesase enter issue id:" << endl;
          cin >> issueID;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          cout << "Plesase enter sprint index:" << endl;
          cin >> sprintIndex;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          model->addToSprint(issueID, sprintIndex);
          break;
        }
        case 21: { // delete current project
          if (model->isOwner()) {
            model->deleteProject();
          } else {
            cout << "No enough permission." << endl;
          }
          break;
        }
        case 22: { // see issue information
          string issueID;
          cout << "Please input the issue ID. " << endl;
          cin >> issueID;
          if (!cin) {
            cout << "Plese enter correct value" << endl;
            cin.clear();
            cin.ignore();
            continue;
          }
          if (model->isLeader()) {
            cout << "IssueID: "
                 << model->getCurrentProject()->getIssue(issueID)->getId()
                 << endl;
            cout << "Priority: "
                 << model->getCurrentProject()->getIssue(issueID)->getPriority()
                 << endl;
            cout << "Assignee: "
                 << model->getCurrentProject()
                        ->getIssue(issueID)
                        ->getAssignee()
                        ->getName()
                 << endl;
            cout << "reporter: "
                 << model->getCurrentProject()
                        ->getIssue(issueID)
                        ->getReporter()
                        ->getName()
                 << endl;
            cout << "create date: "
                 << model->getCurrentProject()->getIssue(issueID)->getCreate()
                 << endl;
            cout << "Status: "
                 << statusToString(model->getCurrentProject()
                                       ->getIssue(issueID)
                                       ->getStatus())
                 << endl;
            cout
                << "Type: "
                << typeToString(
                       model->getCurrentProject()->getIssue(issueID)->getType())
                << endl;
          } else if (model->getCurrentProject()
                         ->getIssue(issueID)
                         ->getAssignee()
                         ->getName() == model->getCurrentUser()->getName()) {
            cout << "IssueID: "
                 << model->getCurrentProject()->getIssue(issueID)->getId()
                 << endl;
            cout << "Priority: "
                 << model->getCurrentProject()->getIssue(issueID)->getPriority()
                 << endl;
            cout << "Assignee: "
                 << model->getCurrentProject()
                        ->getIssue(issueID)
                        ->getAssignee()
                        ->getName()
                 << endl;
            cout << "reporter: "
                 << model->getCurrentProject()
                        ->getIssue(issueID)
                        ->getReporter()
                        ->getName()
                 << endl;
            cout << "create date: "
                 << model->getCurrentProject()->getIssue(issueID)->getCreate()
                 << endl;
            cout << "Status: "
                 << statusToString(model->getCurrentProject()
                                       ->getIssue(issueID)
                                       ->getStatus())
                 << endl;
            cout
                << "Type: "
                << typeToString(
                       model->getCurrentProject()->getIssue(issueID)->getType())
                << endl;
          } else {
            cout << "You cannot view the issue assigned to others!" << endl;
          }
          break;
        }
        case 23: { // change issue ID
          if (model->isLeader()) {
            string issueIDold;
            string issueID;
            cout << "Please enter the issue ID." << endl;
            cin >> issueIDold;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the new issue ID. " << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeIssueID(issueIDold, issueID);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 24: { // change issue priority
          if (model->isLeader()) {
            string issueID;
            int priority;
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the priority" << endl;
            cin >> priority;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeIssuePriority(issueID, priority);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 25: { // change assignee
          if (model->isLeader()) {
            string issueID;
            string assginee;
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the assignee" << endl;
            cin >> assginee;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeIssueAssignee(
                issueID, model->getCurrentProject()->searchName(assginee));
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 26: { // change issue due date
          if (model->isLeader()) {
            string issueID;
            int due;
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the due date" << endl;
            cin >> due;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeIssueDueDate(issueID, due);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 27: { // change issue status
          if (model->isLeader()) {
            string issueID;
            string status;
            cout << "Please enter the issue ID." << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout
                << "Please enter the new status. (open/inProgress/done/overdue)"
                << endl;
            cin >> status;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            model->changeIssueStatus(issueID, stringToStatus(status));
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 28: { // change issue type
          if (model->isLeader()) {
            string issueID;
            string type;
            cout << "Please enter the issue ID." << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              cin.clear();
              cin.ignore();
              continue;
            }
            cout << "Please enter the new type. (userStory, task, build, test, "
                    "debug, documentation, other)"
                 << endl;
            cin >> type;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            model->changeIssueType(issueID, stringToType(type));
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 29: { // change issue description
          if (model->isLeader()) {
            string issueID;
            string description;
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            cout << "Please enter the description" << endl;
            cin >> description;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            model->changeIssueDescription(issueID, description);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 30: { // remove a issue
          if (model->isLeader()) {
            string issueID;
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            model->removeTodo(issueID);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }
        case 31: { // move issue between sprint
          if (model->isLeader()) {
            int sprintIndex1;
            int sprintIndex2;
            string issueID;
            cout << "Please enter the sprintIndex1" << endl;
            cin >> sprintIndex1;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            cout << "Please enter the sprintIndex1" << endl;
            cin >> sprintIndex2;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            cout << "Please enter the issueID" << endl;
            cin >> issueID;
            if (!cin) {
              cout << "Plese enter correct value" << endl;
              continue;
            }
            model->moveBetween(issueID, sprintIndex1, sprintIndex2);
          } else {
            cout << "No enough permission!" << endl;
          }
          break;
        }

        case 32: {
          cout << "update date" << endl;
          model->updateDay();
        }
        }
      }
    }
  }

  delete model;
}
