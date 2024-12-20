//
// Created by איליי on 14/12/2024.
//
#ifndef ALLOJBSV2_CANDIDATE_H
#define ALLOJBSV2_CANDIDATE_H
#include <algorithm>
#include "User.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Jobs.h"
class Application;
class Jobs;
class Candidate : public User
{
private:
    string resume;
    string phone_number;
    string job_type;
    string first_name;
    vector <string> favorites;
    //vector <Jobs> app_history;
    //map<string, vector<Application>> applications;

public:
    Candidate();
    Candidate(string first_name, string last_name, string id, string password, string email, string resume, string phone_number, string job_type);
    bool login(const string& input_id, const string& input_password) const;
    void savetofile (const string &filename);
    static vector<Candidate> loadfromfile(const string &filename);
    string get_resume() const { return resume; }
    string get_phone_number() const { return phone_number; }
    string get_job_type() const { return job_type; }
    void set_resume(const string& res) { resume = res; }
    void set_phone_number(const string& phone) { phone_number = phone; }
    void set_job_type(const string& job) { job_type = job; }
    void display_details() const;
    void view_favorites(vector <Application> all_applications) const;
    void view_application_history() const;
    // void delete_candidate(Candidate &c);
    void edit_profile (Candidate &candidate);
    void candidate_menu(vector<Jobs>& all_jobs , vector <Application>& all_applications) ;
    void view_jobs_and_apply(vector<Jobs>& jobs, vector<Application>& all_applications);
    void view_applications(const vector<Application>& all_applications);
};


#endif //ALLOJBSV2_CANDIDATE_H
