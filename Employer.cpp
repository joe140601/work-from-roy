//
// Created by איליי on 14/12/2024.
//
using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>
#include "Jobs.h"
#include "Employer.h"
#include "Application.h"


Employer::Employer(string first_name, string last_name, string id, string password, string email) : User(first_name, last_name,
                                                                                                         id,
                                                                                                         password,
                                                                                                         email) {
}

bool Employer::login(const string &input_id, const string &input_password) const {
    if (id == input_id && password == input_password) {
        return true;
    } else {
        cout << "Checking ID: " << input_id << " vs " << id << endl;
        cout << "Checking Password: " << input_password << " vs " << password << endl;
        return false;
    }

}

void Employer::savetofile(const std::string &filename) {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }
    outfile << first_name << endl;
    outfile << last_name << endl;
    outfile << id << endl;
    outfile << password << endl;
    outfile << email << endl;
    outfile << "--------------------" << endl;
    outfile.close();
    cout << "Employer saved to file successfully." << endl;

}

vector<Employer> Employer::loadfromfile(const string &filename) {
    vector<Employer> employers;
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return employers;
    }

    string first_name, last_name, id, password, email;
    string line;

    while (getline(infile, line)) {
        if (line.empty() || line == "--------------------") {
            // Debug: דילוג על שורות ריקות או שורות הפרדה
            cout << "Skipping line: " << line << endl;
            continue;
        }

        first_name = line; // קריאת שם פרטי
        cout << "First name: " << first_name << endl; // Debug

        if (getline(infile, last_name) &&
            getline(infile, id) &&
            getline(infile, password) &&
            getline(infile, email)) {
            cout << "Loaded Employer: " << first_name << " " << last_name << endl; // Debug
            employers.emplace_back(first_name, last_name, id, password, email);
        } else {
            cerr << "Error: Incomplete data for an employer. Skipping entry." << endl;
            break;
        }
    }

    infile.close();
    return employers;
}


void Employer::view_published_jobs(vector<Jobs> &all_jobs) const {
    bool found = false;
    for (int i = 0; i < all_jobs.size(); ++i) {
        if (all_jobs[i].get_employer_id() == id) {
            all_jobs[i].display_jobs();
            found = true;
        }
    }
    if (!found ) {
        cout << "You have not posted any jobs yet! " << endl;
    }
}


void Employer::manage_jobs(vector<Jobs> &all_jobs) {
    int choice = 0;
    bool run = true;
    while (run) {
        cout << "Choose an option : " << endl << "1.Update job." << endl << "2.Delete job." << endl << "3. Exit ."
             << endl;
        cin >> choice;

        switch (choice) {
            case 1 : {
                string UID;
                cout << "Enter the job UID that you want to update:" << endl;
                cin.ignore();
                getline(cin,UID);

                bool found = false;
                for (int i = 0; i < all_jobs.size(); ++i) {
                    if (all_jobs[i].get_job_UID() == UID) {
                        all_jobs[i].update_job();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Job UID not found. " << endl;
                }
                break;
            }
            case 2: {
                string UID;
                cout << "Enter the job UID you want to delete:";
                cin.ignore();
                getline(cin, UID);

                for (int i = 0; i < all_jobs.size(); ++i) {
                    if (all_jobs[i].get_job_UID() == UID)
                        all_jobs.erase(all_jobs.begin() + i);
                    else {
                        cout << "Job UID not found." << endl;
                        break;
                    }
                }

                cout << "Job deleted successfully" << endl;
                break;
            }

            case 3:
                run = false;
                break;

        }
    }
}


void Employer::display_details() const {
    cout << "First name: " << first_name << endl;
    cout << "Last name: " << last_name << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl;
    cout << "Email: " << email << endl;

}

void Employer::employer_menu(vector<Jobs>& all_jobs, vector<Application>& all_applications ) {
    int choice;
    bool run = true;
    while (run) {
        cout << "\nEmployer Menu: \n";
        cout << "1) Post jobs " << endl;
        cout << "2) View Published jobs " << endl;
        cout << "3) Manage jobs " << endl;
        cout << "4) Search Jobs" << endl;
        cout << "5) View applications for a job." << endl;
        cout << "6) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Jobs newJob = Jobs().create_job(id);
                all_jobs.push_back(newJob);
                cout << "Job posted successfully!";
                break;
            }
            case 2: {
                view_published_jobs(all_jobs);
                break;
            }
            case 3: {
                manage_jobs(all_jobs);
                break;
            }

            case 4: {
                Jobs job_manager;
                vector<Jobs> found_result = job_manager.search_jobs(all_jobs);
                if (found_result.empty()) {
                    cout << "No jobs match the given criteria." << endl;
                    break;
                } else {
                    cout << "Matching jobs:" << endl;
                    for (int i = 0; i < found_result.size(); ++i) {
                        found_result[i].display_jobs();
                        cout << "----------------------" << endl;
                    }
                }
                break;
            }
            case 5: {
                view_applications(all_applications);
                string uid;
                cout << "Enter job UID to view its applications: ";
                cin.ignore();
                getline(cin, uid);

                bool found = false;
                for (int i = 0; i < all_applications.size(); i++) {
                    if (all_applications[i].get_job_uid() == uid ) {
                        found = true;
                        all_applications[i].display_application();

                        int choice;
                        cout << "Do you want to answer to a candidate's application? " << endl;
                        cout << "1. Yes " << endl;
                        cout << "2. No" << endl;
                        cin >> choice;

                        if (choice == 1) {
                            cout << "Enter the Candidate ID to respond: ";
                            string candidateID;
                            cin >> candidateID;
                            if (all_applications[i].get_candidate_id() == candidateID) {
                                cout << "Enter status (Accept/Reject/Skip): ";
                                string status;
                                cin >> status;

                                all_applications[i].set_status(status);
                                cout << "Response successfully sent to the candidate." << endl;
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Job UID not found." << endl;
                        }
                        break; // יציאה מה-case
                    }
                }
                break;
            }
            case 6 : {
                run = false;
                cout << "Goodbye!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice. try again. \n";

            }

        }

    }
}

void Employer::view_applications(vector<Application> &all_applications) {
    for (int i = 0; i < all_applications.size(); i++) {
        if (all_applications[i].get_employer_id() == id) {
            all_applications[i].display_application();
        }
    }
}

/*void Employer::view_applications ( const string &job_UID ){
    auto it = application.find(job_UID);

    if (it != applications.end()) {
        cout << "\nApplications for Job UID \"" << job_UID << "\":\n";

        for (const auto &app: it->second) {
            app.display_application();
        }
        int answer;
        cout << "Do you want to answer to a candidate's application ? " << endl << "1. Yes " << endl << "2.No" << endl;
        if (answer == 1) {
            cout << "Enter the Candidate ID to respond: ";
            string candidateID;
            cin >> candidateID;

            auto app_it = find_if(it->second.begin(), it->second.end(),
                                  [&candidateID](const Application &app) {
                                      return app.get_candidate_id() == candidateID;
                                  });

            if (app_it != it->second.end()) {
                cout << "Application details for candidate ID \"" << candidateID << "\":\n";
                app_it->display_application();
                string status;
                cout << "Enter your response to the candidate: Pending / Accepted / Rejected:\n";
                cin.ignore();
                getline(cin,status);
                app_it->set_status(status);
                cout << "Response successfully sent to Candidate ID: " << candidateID << "\n";
            } else {
                cout << "No application found for Candidate ID: " << candidateID << "\n";

            }
        }

    } else {
        cout << "No applications found for Job UID: " << job_UID << endl;
    }
}*/

string Employer::get_id() const {
    return id;
}
