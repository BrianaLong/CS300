// CS300 Prj 2.cpp : 
// Briana Long
// CS 300
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Define a structure for courses
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Define a comparison function for sorting courses.
bool compareCourses(const Course& a, const Course& b) {
    return a.courseNumber < b.courseNumber;
}

// Define a Binary Search Tree node for courses
struct TreeNode {
    Course data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const Course& c) : data(c), left(nullptr), right(nullptr) {}
};

// Function to insert a course into the Binary Search Tree
TreeNode* insert(TreeNode* root, const Course& course) {
    if (!root) return new TreeNode(course);
    if (course.courseNumber < root->data.courseNumber)
        root->left = insert(root->left, course);
    else
        root->right = insert(root->right, course);
    return root;
}

// Function to search for a course in the Binary Search Tree
TreeNode* search(TreeNode* root, const std::string& courseNumber) {
    if (!root || root->data.courseNumber == courseNumber)
        return root;
    if (courseNumber < root->data.courseNumber)
        return search(root->left, courseNumber);
    return search(root->right, courseNumber);
}

// Function to print the prerequisites of a course
void printPrerequisites(TreeNode* root, const std::string& courseNumber) {
    TreeNode* courseNode = search(root, courseNumber);
    if (courseNode) {
        std::cout << courseNode->data.courseNumber << ", " << courseNode->data.courseTitle << "\n";
        if (!courseNode->data.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const std::string& prereq : courseNode->data.prerequisites) {
                TreeNode* prereqNode = search(root, prereq);
                if (prereqNode)
                    std::cout << prereqNode->data.courseNumber << ", ";
            }
            std::cout << "\n";
        }
    }
    else {
        std::cout << "Course not found.\n";
    }
}

int main() {
    TreeNode* root = nullptr;

    std::ifstream file("course_data.txt");
    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Course course;
        std::getline(ss, course.courseNumber, ',');
        std::getline(ss, course.courseTitle, ',');
        std::string prereq;
        while (std::getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }
        root = insert(root, course);
    }
    file.close();

    int choice;
    do {
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Data structure loaded.
            break;
        case 2:
            // Print Course List
        {
            std::vector<Course> courses;
            // Traverse the Binary Search Tree and store courses in the array
            void inOrderTraversal(TreeNode * node); {
                if (!node) return;
                inOrderTraversal(node->left);
                courses.push_back(node->data);
                inOrderTraversal(node->right);
            }
            inOrderTraversal(root);

            // Sort courses alphanumerically
            std::sort(courses.begin(), courses.end(), compareCourses);

            // Print sorted courses
            for (const Course& course : courses) {
                std::cout << course.courseNumber << ", " << course.courseTitle << "\n";
            }
        }
        break;
        case 3:
            // Print Course
        {
            std::string courseNumber;
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            printPrerequisites(root, courseNumber);
        }
        break;
        case 4:
            // Exit all other numbers are invalid
            break;
        default:
            std::cout << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 4);

 

    return 0;
}
