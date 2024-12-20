//
// Created by איליי on 14/12/2024.
//

#ifndef ALLOJBSV2_JOBS_H
#define ALLOJBSV2_JOBS_H


using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Employer.h"
#include "Application.h"


class Jobs
{
protected:
    string location;
    string profession;
    string job_type;
    string jobUID;
    int experience;   // change to string
    string employer_id;
    // vector <Application> list_of_applications;


public:
    Jobs();
    Jobs(string location, string profession, string job_type, string jobUID, int experience, string employer_id);
    void savetofile (const string &filename);
    static vector<Jobs> loadfromfile(const string &filename);
    string get_location() const { return location; }
    string get_profession() const { return profession; }
    string get_job_type() const { return job_type; }
    string get_job_UID() const { return jobUID; }
    string get_employer_id() const {return employer_id; }
    int get_experience() const { return experience; }
    void set_location(const string& loc) { location = loc; }
    void setProfession(const string& prof) { profession = prof; }
    void set_job_type(const string& type) { job_type = type; }
    void set_job_UID(const string& uid) { jobUID = uid; }
    void set_experience(int exp) { experience = exp; }
    void display_jobs() const;
    void update_job();
    void set_application (const Application& app);
    vector <Jobs> search_jobs(vector <Jobs> & all_jobs);
    Jobs create_job(const string &employer_id) const;
    void set_job();


};


#endif //ALLOJBSV2_JOBS_H
