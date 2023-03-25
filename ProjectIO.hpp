void projectOutput(Project * pro){
    ofstream projectOutput("project.txt");
    if(!projectOutput){
    cout<<"can't open file" << endl;
    EXIT_FAILURE;
    }
    projectOutput << pro->out_string() << endl;
    return true;
  }