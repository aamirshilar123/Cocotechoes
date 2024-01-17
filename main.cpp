#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct Task {
    int progress;
    std::string endDate;
};

struct Job {
    std::string title;
    std::vector<Task> tasks;
    double overallProgress;
};

Task generateRandomTask() {
    Task task;
    task.progress = rand() % 101;
    task.endDate = "2024-01-" + std::to_string(rand() % 30 + 1);
    return task;
}

void calculateOverallProgress(Job& job) {
    if (job.tasks.empty()) {
        job.overallProgress = 0;
        return;
    }

    double totalProgress = 0;
    for (const Task& task : job.tasks) {
        totalProgress += task.progress;
    }

    job.overallProgress = totalProgress / job.tasks.size();
}

void displayJobs(const std::vector<Job>& jobs) {
    std::vector<Job> sortedJobs = jobs;
    std::sort(sortedJobs.begin(), sortedJobs.end(),
              [](const Job& a, const Job& b) {
                  return a.tasks.front().endDate < b.tasks.front().endDate;
              });

    for (const Job& job : sortedJobs) {
        std::cout << "Job: " << job.title << "\t"
                  << "End Date: " << job.tasks.front().endDate << "\t"
                  << "Overall Progress: " << job.overallProgress << "%" << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    const int numJobs = 10;
    std::vector<Job> jobs;

    for (int i = 1; i <= numJobs; ++i) {
        Job job;
        job.title = "Job" + std::to_string(i);

        const int numTasks = rand() % 11 + 10;
        for (int j = 0; j < numTasks; ++j) {
            job.tasks.push_back(generateRandomTask());
        }

        calculateOverallProgress(job);
        jobs.push_back(job);
    }

    displayJobs(jobs);

    return 0;
}
