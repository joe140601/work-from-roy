//
// Created by איליי on 14/12/2024.
//

#ifndef ALLOJBSV2_EMPLOYER_H
#define ALLOJBSV2_EMPLOYER_H
#include "User.h"
#include "Jobs.h"
#include <string>
#include <vector>
#include "Application.h"
#include <map>
class Jobs;
class Application;
class Employer : public User {
private:
    //vector<Jobs> jobs;
    //map<string, vector<Application>> applications;

public:
    Employer(string first_name, string last_name, string id, string password, string email);
    bool login(const string& input_id, const string& input_password) const;
    void savetofile (const string &filename);
    static vector<Employer> loadfromfile(const string &filename);
    void display_details() const;
    void view_published_jobs(vector <Jobs> &all_jobs) const;
    void manage_jobs(vector <Jobs>& all_jobs);
    void employer_menu(vector<Jobs>& all_jobs, vector <Application>& all_applications);
    //void delete_job ( const string &job_UID);
    //void view_applications(const string &job_UID);
    string get_id() const;
    void view_applications(vector<Application>& all_applications);
};


#endif //ALLOJBSV2_EMPLOYER_H
