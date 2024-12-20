#include <iostream>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
#include "Jobs.h"
#include <limits>

#define users_file "users.txt"
#define candidate_file "candidates.txt"
#define employer_file "employers.txt"
#define job_file "jobs.txt"
using namespace std;

vector<Application> all_application;
vector<Jobs> all_jobs;


void register_candidate(vector<Candidate> &candidates, const string &filename) {
    string first_name, last_name, id, password, email, resume, phone_number, job_type;

    cout << "Enter First Name: ";
    cin >> first_name;
    cout << "Enter Last Name: ";
    cin >> last_name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Resume: ";
    cin.ignore();
    getline(cin, resume);
    cout << "Enter Phone Number: ";
    cin >> phone_number;
    cout << "Enter Job Type: ";
    cin >> job_type;

    Candidate new_candidate(first_name, last_name, id, password, email, resume, phone_number, job_type);
    candidates.emplace_back(new_candidate);
    new_candidate.savetofile(filename);
    cout << "Candidate registered successfully!" << endl;
}

void register_employer(vector<Employer> &employers, const string &filename) {
    string first_name, last_name, id, password, email;

    cout << "Enter First Name: ";
    cin >> first_name;
    cout << "Enter Last Name: ";
    cin >> last_name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Email: ";
    cin >> email;

    Employer new_employer(first_name, last_name, id, password, email);
    employers.emplace_back(new_employer);
    new_employer.savetofile(filename);
    cout << "Employer registered successfully!" << endl;
}

void login_candidate(vector<Candidate> &candidates) {
    string id, password;
    cout << "Enter Candidate ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < candidates.size(); i++) {
        if (candidates[i].login(id, password)) {
            cout << "Welcome, " << candidates[i].get_first_name() << " " << candidates[i].get_last_name() << "!\n";
            candidates[i].candidate_menu(all_jobs, all_application);
            return;
        }
    }
    cout << "Login failed. Please check your ID and password.\n";
}

void login_employer(vector<Employer> &employers) {
    string id, password;
    cout << "Enter Employer ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < employers.size(); i++) {
        if (employers[i].login(id, password)) {
            cout << "Welcome, " << employers[i].get_first_name() << " " << employers[i].get_last_name() << "!\n";
            employers[i].employer_menu(all_jobs, all_application);
            return;
        }
    }
    cout << "Login failed. Please check your ID and password.\n";
}

void add_candidate(const string &filename) {
    string id, password, email, first_name, last_name, resume, phone_number, job_type;
    cout << "Enter Candidate ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter First Name: ";
    cin >> first_name;
    cout << "Enter Last Name: ";
    cin >> last_name;
    cout << "Enter Resume: ";
    cin >> resume;
    cout << "Enter Phone Number: ";
    cin >> phone_number;
    cout << "Enter Job Type: ";
    cin >> job_type;

    Candidate candidate(first_name, last_name, id, password, email, resume, phone_number, job_type);
    candidate.savetofile(filename);
    cout << "Candidate added successfully!\n";
}

void add_employer(const string &filename) {
    string id, password, email, first_name, last_name;
    cout << "Enter Employer ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter First Name: ";
    cin >> first_name;
    cout << "Enter Last Name: ";
    cin >> last_name;

    Employer employer(first_name, last_name, id, password, email);
    employer.savetofile(filename);
    cout << "Employer added successfully!\n";
}

void add_job(const string &filename) {
    string location, profession, job_type, jobUID, employer_id;
    int experience;

    cout << "Enter Job Location: ";
    getline(cin, location);

    cout << "Enter Profession: ";
    getline(cin, profession);

    cout << "Enter Job Type: ";
    getline(cin, job_type);

    cout << "Enter Job UID: ";
    getline(cin, jobUID);

    cout << "Enter Required Experience (in years): ";
    cin >> experience;
    cin.ignore(); // לנקות את ה-buffer

    cout << "Enter your ID: ";
    getline(cin, employer_id);

    Jobs new_job(location, profession, job_type, jobUID, experience, employer_id);

    // שמירת העבודה לקובץ
    new_job.savetofile(filename);
}
void display_all_candidates(const vector<Candidate>& candidates) {
    if (candidates.empty()) {
        cout << "No candidates available.\n";
        return;
    }

    cout << "\n===== Candidates List =====\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        cout << "\n----- Candidate #" << (i + 1) << " -----\n";
        candidates[i].display_details();
        cout << "-------------------------\n";
    }
}
void display_all_employers(const vector<Employer> &employers) {
    if (employers.empty()) {
        cout << "No employers available.\n";
        return;
    }

    cout << "\n===== Employers List =====\n";
    for (size_t i = 0; i < employers.size(); ++i) {
        cout << "\n----- Employer #" << (i + 1) << " -----\n";
        employers[i].display_details(); // קריאה לפונקציה להדפסת פרטי המעסיק
        cout << "-------------------------\n";
    }
}


void display_all_jobs(const vector<Jobs> &jobs) {
    if (jobs.empty()) {
        cout << "No jobs available.\n";
        return;
    }

    cout << "\n===== Jobs List =====\n";
    for (size_t i = 0; i < jobs.size(); ++i) {
        cout << "\n----- Job #" << (i + 1) << " -----\n";
        jobs[i].display_jobs();
        cout << "-------------------------\n";
    }
}
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void display_menu() {
    clear_screen();
    cout << "Welcome to the Job Management System\n";
    cout << " ============= Menu =============\n";
    cout << "1. Register Candidate\n";
    cout << "2. Register Employer\n";
    cout << "3. Add Job\n";
    cout << "4. Login as Candidate\n";
    cout << "5. Login as Employer\n";
    cout << "6. Display All Candidates\n";
    cout << "7. Display All Employers\n";
    cout << "8. Display All Jobs\n";
    cout << "9. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    display_menu();
}
int main() {

    vector<Candidate> candidate_arr;
    vector<Employer> employer_arr;
    Employer default_employer("John", "Doe", "emp123", "pass123", "john.doe@example.com");
    Candidate default_candidate("Jane", "Smith", "cand123", "pass123", "jane.smith@example.com",
                                "Software Engineer Resume", "123456789", "Software Engineer");
    candidate_arr.push_back(default_candidate);
    employer_arr.push_back(default_employer);

    int choice;
    do {
        cout << "\nMain Menu:\n1. Employer Login\n2. Candidate Login\n3. Exit\n";
        cin >> choice;

        string id, password;
        if (choice == 1) { // Employer Login
            cout << "Enter Employer ID: ";
            cin.ignore(); // ניקוי ה-buffer
            getline(cin, id);

            cout << "Enter Password: ";
            getline(cin, password);

            if (default_employer.login(id, password)) {
                default_employer.employer_menu(all_jobs, all_application);
            } else {
                cout << "Invalid credentials. Try again.\n";
            }
        } else if (choice == 2) { // Candidate Login
            cout << "Enter Candidate ID: ";
            cin.ignore(); // ניקוי ה-buffer
            getline(cin, id);

            cout << "Enter Password: ";
            getline(cin, password);

            if (default_candidate.login(id, password)) {
                default_candidate.candidate_menu(all_jobs, all_application);
            } else {
                cout << "Invalid credentials. Try again.\n";
            }
        }
    } while (choice != 3);

    cout << "Exiting... Goodbye!\n";
    return 0;




    /*int choice;

    do {
        display_menu();
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1-9.\n";
            continue;
        }

        switch (choice) {
            case 1:
                clear_screen();
                register_candidate(candidates, candidate_file);
                pause();
                break;
            case 2:
                clear_screen();
                register_employer(employers, employer_file);
                pause();
                break;
            case 3:
                clear_screen();
                add_job(job_file);
                pause();
                break;
            case 4:
                clear_screen();
                login_candidate(candidate);
                pause();
                break;
            case 5:
                clear_screen();
                login_employer(employer);
                pause();
                break;
            case 6:
                clear_screen();
                display_all_candidates(candidates);
                pause();
                break;
            case 7:
                clear_screen();
                display_all_employers(employers);
                pause();
                break;
            case 8:
                clear_screen();
                display_all_jobs(jobs);
                pause();
                break;
            case 9:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                pause();
        }
    } while (choice != 9);

    return 0;*/
}
