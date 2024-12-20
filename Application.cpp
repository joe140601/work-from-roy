//
// Created by bensi on 16/12/2024.
//
#include <iostream>
#include "Application.h"
#include "Jobs.h"

using namespace std;

Application::Application(string &candidate_first_name, string &candidate_last_name, string &candidate_id, string &candidate_email,string &candidate_phone_number,string &resume, string &job_UID, string &employer_id)
{
    this->candidate_first_name = candidate_first_name;
    this->candidate_last_name = candidate_last_name;
    this->candidate_id = candidate_id;
    this->candidate_email = candidate_email;
    this->candidate_phone_number = candidate_phone_number;
    this->resume = resume;
    this->job_UID = job_UID;
    this->employer_id =employer_id;
    status = "Pending... ";
}
void Application::display_application()const {
    cout << "Name: " << candidate_first_name << " " << candidate_last_name << endl;
    cout << "Candidate ID : " << candidate_id << endl << "Resume:" << resume << endl << "Phone number:" << candidate_phone_number << endl << "Email:" << candidate_email << endl << "Status: " << status << endl;
    cout << "Job UID: " << job_UID << endl;
}

void Application :: set_status (const string &new_status){
    status = new_status;
}

string Application::get_job_uid() const {return job_UID; }

string Application::get_employer_id() const {return employer_id; }



