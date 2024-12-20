//
// Created by איליי on 14/12/2024.
//
using namespace std;
#include "Candidate.h"
#include "Jobs.h"
#include "User.h"
#include "Employer.h"
#include "Application.h"

Candidate::Candidate() : User() {
    this->resume = nullptr;
    this->job_type = nullptr;
    this->phone_number = nullptr;
}


Candidate::Candidate(string first_name, string last_name, string id, string password, string email, string resume, string phone_number, string job_type ): User(first_name,last_name,id,password,email) {
    this->resume = resume;
    this->phone_number = phone_number;
    this->job_type = job_type;
}

bool Candidate::login(const string& input_id, const string& input_password) const {
    return (id == input_id && password == input_password);
}
void Candidate::savetofile(const string &filename) {
    ofstream outfile(filename,ios::app);
    if (!outfile.is_open()){
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }
    outfile << first_name << endl;
    outfile<< last_name << endl;
    outfile<< id << endl;
    outfile<< password << endl;
    outfile<< email << endl;
    outfile<< phone_number << endl;
    outfile<< job_type << endl;
    outfile<< resume << endl;
    outfile << "--------------------"<<endl;
    outfile.close();
    cout << "Candidate saved to file successfully." << endl;
}
vector<Candidate> Candidate::loadfromfile(const std::string &filename) {
    vector<Candidate>candidates;
//create vector array of employers from employer type
    ifstream infile(filename);
    if (!infile.is_open()){
        cout << "Error: Could not open file " << filename << " for reading." << endl;
        return candidates;
    }
    string first_name,last_name,id,password,email,phone_number,job_type,resume;

    while (getline(infile,first_name)){
        if (first_name=="--------------------"){
            continue;
        }

        getline(infile,last_name);
        getline(infile,id);
        getline(infile,password);
        getline(infile,email);
        getline(infile,phone_number);
        getline(infile,job_type);
        getline(infile,resume);
        candidates.emplace_back(Candidate(first_name,last_name,id,password,email, phone_number, job_type, resume));
    }
    infile.close();
    return candidates;
}
void Candidate::display_details() const {
    cout << "Candidate Details:\n";
    cout << "ID: " << id << "\n"
         << "First Name: " << first_name << "\n"
         << "Last Name: " << last_name << "\n"
         << "Email: " << email << "\n"
         << "Phone Number: " << phone_number << "\n"
         << "Job Type: " << job_type << "\n"
         << "Resume: " << resume << "\n";
}

void Candidate :: view_jobs_and_apply(vector<Jobs>& jobs, vector<Application>& all_applications) {
    /*for (const auto& job : jobs) {
        job.display_jobs();
        cout << "--------------------------\n";
    }*/

    string job_id;
    cout << "Enter the Job ID you want to apply for: ";
    cin >> job_id;

    bool job_found = false;
    for (int i = 0; i < jobs.size() ; i++) {
        if (jobs[i].get_job_UID() == job_id) {
            string employer_id = jobs[i].get_job_UID();
            Application app(first_name, last_name, id, email, phone_number, resume, job_id, employer_id);
            all_applications.push_back(app);
            cout << "Application submitted successfully!\n";
            job_found = true;
            break;
        }
    }
    if (!job_found) {
        cout << "Job ID not found.\n";
    }
}

void Candidate :: view_applications(const vector<Application>& all_applications) {
    cout << "\nYour Applications:\n";
    bool has_applications = false;

    for (int i = 0; i < all_applications.size(); i++) {
        if (all_applications[i].get_candidate_id() == id) {
            all_applications[i].display_application();
            has_applications = true;
        }
    }

    if (!has_applications) {
        cout << "You have not submitted any applications yet.\n";
    }
}


/*void Candidate ::view_application_history()const {
if ( app_history.empty()){
cout << "No application history yet." << endl;
return;
} else {
cout << "Application history:" << endl;
for (int i = 0; i < app_history.size(); ++i) {
cout << i + 1 << ") ";
app_history[i].display_jobs();
cout << endl;
}
}
}*/

void Candidate::edit_profile(Candidate &candidate) {
    int choice;
    bool run = true;
    while (run) {
        cout << "Manage profile menu:" << endl;
        cout << "1. Change my first name:" << endl;
        cout << "2. Change my last name:" << endl;
        cout << "3. Change my email address:" << endl;
        cout << "4. Change my phone number:" << endl;
        cout << "5. Display my profile's details:" << endl;
        cout << "6.Exit." << endl;
        cout << "Please choose an option:" << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                string new_first_name;
                cout << "Enter the new first name :";
                cin.ignore();
                getline(cin, new_first_name);
                candidate.set_first_name(new_first_name);
                this->first_name = new_first_name;
                cout << "First name updated successfully!";
                break;
            }
            case 2: {
                string new_last_name;
                cout << "Enter the new last name : ";
                cin.ignore();
                getline(cin, new_last_name);
                candidate.set_last_name(new_last_name);
                this->last_name = new_last_name;
                cout << "Last name updated successfully!";
                break;
            }
            case 3: {
                string new_email;
                cout << "Enter the new email:";
                cin.ignore();
                getline(cin, new_email);
                candidate.set_email(new_email);
                this->email = new_email;
                cout << "Email updated successfully!";
                break;
            }
            case 4: {
                string new_phone_number;
                cout << "Enter the new phone number:";
                cin.ignore();
                getline(cin, new_phone_number);
                candidate.set_phone_number(new_phone_number);
                this->phone_number = new_phone_number;
                cout << "Phone number updated successfully!";
                break;
            }
            case 5: {
                display_details();
                break;
            }
            case 6:
                cout << "Goodbye!" << endl;
                run = false;
                break;
            default:
                cout << "invalid option , please try again.";
        }
    }
}

void Candidate::candidate_menu(vector<Jobs>& all_jobs, vector <Application>& all_applications) {
    int choice;
    bool run = true;
    while (run) {
        cout << "\nCandidate Menu: \n";
        cout << "1) Search jobs."<< endl;   // from this option we call the functions( add to favourite, add application)
        cout << "2) Edit profile." << endl;
        cout << "3) View favorites." << endl;
        cout << "4) View application history." << endl;
        cout << "5) View profile." << endl;
        cout << "6) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Jobs job_manager;
                vector<Jobs> found_result = job_manager.search_jobs(all_jobs);
                if (found_result.empty()) {
                    cout << "No jobs match the given criteria." << endl;
                    break;
                }

                else {
                    cout << "Matching jobs:" << endl;
                    for (int i = 0; i < found_result.size(); ++i) {
                        found_result[i].display_jobs();
                        cout << "----------------------" << endl;
                    }
                }
                int num;
                cout << "Do you want to apply for a job or mark as favorite( 1-Apply | 2-Favorite ): ";
                cin >> num;
                if (num == 1) {
                    view_jobs_and_apply(all_jobs, all_applications);
                } else if (num == 2) {
                    string temp_uid;
                    cout << "Enter Job UID that you want to mark as favorite: ";
                    cin.ignore();
                    getline(cin, temp_uid);
                    for (int i = 0; i < all_jobs.size(); ++i) {
                        if (temp_uid == all_jobs[i].get_job_UID()) {
                            favorites.push_back(temp_uid);
                            cout << "The job added to your favorites! " << endl;
                            break;
                        }
                    }
                    cout << "There is no job with that UID! " << endl;
                }
                /*int apply_choice;
                string UID;
                if ( !found_result.empty())
                    cout << "Do you want to apply for the job ?\n1.yes\n2.no" << endl;
                cin >> apply_choice;
                if (apply_choice == 1) {
                    cout << "Enter the UID of the job you want to apply for:";
                    cin >> UID;
                    bool job_found = false;
                    for (int i = 0; i < found_result.size(); ++i) {
                        if (found_result[i].get_job_UID() == UID) {
                            job_found = true;
                            Application app(get_first_name(), get_last_name(), get_id(), get_email(),
                                            get_phone_number(), get_resume());
                            found_result[i].set_application(app);
                            .push_back(found_result[i]);
                            cout << "Application added successfully for the job with UID" << UID << "!" << endl;
                            break;
                        }
                    }
                    if (!job_found) {
                        cout << "Invalid job UID. No job matching." << endl;
                    }
                }
                if (apply_choice == 2)*/
                break;
            }
            case 2: {
                edit_profile(*this);
                break;
            }
            case 3: {
                if (favorites.empty()) {
                    cout << "No job in your favorite list " << endl;
                    break;
                }
                bool job_found = false;
                for (int i = 0; i < all_jobs.size(); ++i) {
                    for (int j = 0; j < favorites.size(); ++j) {
                        if (all_jobs[i].get_job_UID() == favorites[j] ) {
                            all_jobs[i].display_jobs();
                            job_found = true;
                        }
                    }
                }
                if (!job_found) {
                    cout << "No matching jobs found in your favorite list" << endl;
                }
                break;
            }
            case 4: {
                view_applications(all_applications);
                break;
            }
            case 5:
                display_details();
                break;
            case 6:
                run = false;
                break;

            default:
                cout << "Invalid choice. try again. \n";
        }
    }
}

