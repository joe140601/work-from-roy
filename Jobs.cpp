//
// Created by איליי on 14/12/2024.
//

#include "Jobs.h"
#include <vector>



Jobs::Jobs() {
    this->location = "";
    this->profession = "";
    this->job_type = "";
    this->jobUID = "";
    this->experience = 0;
    this->employer_id = "";
    //this->current_applications = 0;
}

Jobs::Jobs(string location, string profession, string job_type, string jobUID, int experience, string employer_id)
{
    this->location = location;
    this->profession = profession;
    this->job_type = job_type;
    this->jobUID = jobUID;
    this->experience = experience;
    this->employer_id =employer_id;

}


void Jobs::savetofile(const string &filename) {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }
    outfile << location << endl
            << profession << endl
            << job_type << endl
            << jobUID << endl
            << experience << endl
            << "--------------------" << endl;
    if (outfile.fail()) {
        cerr << "Error: Failed to write to file." << endl;
        outfile.close();
        return;
    }

    outfile.close();
    cout << "Job saved to file successfully." << endl;
}

vector<Jobs> Jobs::loadfromfile(const std::string &filename) {
    vector<Jobs> jobs;
//create vector array of employers from employer type
    ifstream infile(filename);
    if (infile.is_open()) {
        string location, profession, job_type, jobUID;
        int experience;
        while (getline(infile, location)) {
            if (location == "--------------------") {
                continue;
            }
            getline(infile, profession);
            getline(infile, job_type);
            getline(infile, jobUID);
            infile >> experience;
            infile.ignore();
            Jobs temp(location, profession, job_type, jobUID, experience, "");
            jobs.emplace_back(temp);
        }
        infile.close();
    } else
        cout << "Error,Could not open file!" << endl;
    return jobs;
}

void Jobs::display_jobs() const {
    cout << "Job Details:\n";
    cout << "Location: " << location << "\n"
         << "Profession: " << profession << "\n"
         << "Job Type: " << job_type << "\n"
         << "Job UID: " << jobUID << "\n"
         << "Experience: " << experience << "\n";
}

void Jobs::update_job() {
    int choice = 0;
    bool run = true;
    while (run) {
        cout << "What do tou want to update?:" << endl;
        cout << "1. Job location :" << endl;
        cout << "2. Job profession (job title):" << endl;
        cout << "3. Job type (full time / part time):" << endl;
        cout << "4. Required experience:" << endl;
        cout << "5 .Exit." << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                string new_location;
                cout << "Enter the new location:" << endl;
                cin.ignore();
                getline(cin, new_location);
                location = new_location;
                break;
            }
            case 2: {
                string new_profession;
                cout << "Enter the new profession:" << endl;
                cin.ignore();
                getline(cin, new_profession);
                profession = new_profession;
                break;
            }
            case 3: {
                string new_job_type;
                cout << "Enter the new job-type :" << endl;
                cin.ignore();
                getline(cin, new_job_type);
                job_type = new_job_type;
                break;
            }
            case 4: {
                int new_experience;
                cout << "Enter the new required experience:" << endl;
                cin >> new_experience;
                experience = new_experience;
                break;
            }
            case 5 : {
                run = false;
                cout << "Updated successfully completed!" << endl;
                break;
            }
            default:
                cout << "Invalid choice." << endl;

        }
    }
}


vector<Jobs> Jobs::search_jobs(vector <Jobs> & all_jobs) {
    string filter_location, filter_job_type, filter_profession;
    int filter_experience;
    bool use_location = false, use_job_type = false, use_experience = false, use_profession = false;
    cout << "By which criteria do you want to search a job?" << endl;
    int choice;
    bool run = true;
    while (choice != 5 ) {
        cout << "Choose an option:" << endl;
        cout << "1. By location." << endl;
        cout << "2. By job type (full-time/part-time)." << endl;
        cout << "3. Required experience ." << endl;
        cout << "4. Profession." << endl;
        cout << "5. Search." << endl;
        cin >> choice;
        switch (choice) {

            case 1: {
                cout << "Enter a location:" << endl;
                cin.ignore();
                getline(cin, filter_location);
                use_location = true;
                break;
            }

            case 2: {
                cout << "Enter the job-type:" << endl;
                cin.ignore();
                getline(cin, filter_job_type);
                use_experience = true;
                break;
            }
            case 3: {
                cout << "Enter your experience:" << endl;
                cin >> filter_experience;
                use_experience = true;
                break;
            }
            case 4: {
                cout << "Enter your profession:" << endl;
                cin.ignore();
                getline(cin, filter_profession);
                use_profession = true;
                break;
            }
            case 5: {
                run = false;
                break;
            }
            default: {
                cout << "Invalid choice try again ";
            }
        }
    }
    vector<Jobs> results;
    for (int i = 0; i < all_jobs.size(); ++i) {
        Jobs job = all_jobs[i];
        bool match = true;
        if (use_location && job.get_location() != filter_location)
            match = false;
        if (use_job_type && job.get_job_type() != filter_job_type)
            match = false;
        if (use_experience && job.get_experience() != filter_experience)
            match = false;
        if (use_profession && job.get_profession() != filter_profession)
            match = false;
        if (match)
            results.push_back(job);
    }
    return results;

}

Jobs Jobs::create_job(const string& employer_id1) const {
    string profession1, location1, job_type1, jobUID1;
    int experience1;
    cout << "Enter the location: " << endl;
    cin.ignore();
    getline(cin, location1);
    cout << "Enter the profession:" << endl;
    getline(cin, profession1);
    cout << "Enter the job type:" << endl;
    getline(cin, job_type1);
    cout << " Enter jobUID: " << endl;
    getline(cin, jobUID1);
    cout << " Enter required experience: " << endl;
    cin >> experience1;


    return Jobs(location1, profession1, job_type1, jobUID1, experience1 , employer_id1);
}



