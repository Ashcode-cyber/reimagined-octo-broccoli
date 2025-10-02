#include <iostream>
#include <fstream>//files
#include <vector>
#include <string>
using std::cout;
using std::cin;
                            //7 * 15 *25				
	// reorganize the app by adding switch statements for each block of code

// a struct for tasks
struct Task {
	int id;
	std::string description;
	int status;

};
// A printing a  task function
void viewTasks(const std::vector<Task>& myTasks) {
	for (int i{ 0 }; i < myTasks.size(); ++i) {
		cout << "Number: " << myTasks.at(i).id << ", "
			<< "Description: " << myTasks.at(i).description << ", "
			<< "status: " << " " << (myTasks.at(i).status ? "completed" : "incomplete") << std::endl;
	}
};

void addTask(std::vector<Task>& myTasks) {
	int id = myTasks.size()+1;
	int	status;
	std::string description;
	std::string response;
	// Prompting to add a task (reviewed)  
	while (true) {
		cout << "Will you like to add a task\n (yes or no)";
		cin >> response;
		if (response == "yes") {
			cout << "Enter the task in this format\n" << "'1' 'task' '0 or 1' \n";
			cin >> id >> description >> status;
			bool completed = (status == 1);
			myTasks.push_back(Task{ id, description, completed });
			cout << "task added\n";
		}
		else if (response == "no") {
			break;
		}
		else {
			cout << "Enter yes or no\n";
		}
	}
};
void deleteTask(std::vector<Task>& myTasks, int id) {
	//deleting a task
	for (auto it = myTasks.begin(); it != myTasks.end(); ++it) {
		if (it->id == id) {
			myTasks.erase(it);
			cout << "Task with ID " << id << " has been deleted.\n";
			return; // Exit the function after deleting the task
		}
	}
	cout << "Task with ID " << id << " not found.\n";
}

void saveTasksToFile(const std::vector<Task>& myTasks, const std::string& Taskfile) {
	std::ofstream outFile(Taskfile);
	if (!outFile) {
		std::cerr << "Can't open file " << Taskfile << " for writing.\n";
		return;
	}
	for (const auto& t : myTasks) {
		outFile << t.id << " " << t.description << " " << t.status << "\n";
	}
	outFile.close();
}


int main() {
	//To do list.
	std::string Taskfile; // the users file.
	cout << "Enter the file name: ";
	cin >> Taskfile;
	std::ifstream inFile{ Taskfile };
	if (!inFile) {
		std::cerr << "Can't open file " << Taskfile;
		return 1;
	}

	std::vector<Task> myTasks;
	int id, status;
	std::string description;

	while (inFile >> id >> description >> status) {
		//conversion from int to bool.
		bool completed = (status == 1);
		myTasks.push_back(Task{ id, description, completed });
	}
	inFile.close();

	//displaying the file - for loop and for each loop.
	//call 
	cout << "This is your file: \n";
	viewTasks(myTasks);

	//displaying the menu
	int option;
	while (true)
	{
		cout << "Welcome to your To Do List\n";
		cout << "1. Add a task\n";
		cout << "2. View tasks\n";
		cout << "3. Delete a task\n";
		cout << "4. Exit\n";
		cout << "Please select an option: ";
		cin >> option;
		if (cin.fail()) {
			cin.clear(); // clear the error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
			cout << "Invalid input. Please enter a number.\n";
			continue; // restart the loop
		}
		
		//switch statement for the options
		switch (option) {
		case 1: { // Adding a block scope to ensure proper initialization  
			// Adding a task  
			addTask(myTasks);

			//Saving task back in file  
			saveTasksToFile(myTasks, Taskfile);
			break;
		}
		case 2: { // Adding a block scope to ensure proper initialization  
			// View tasks  
			viewTasks(myTasks);
			break;
		}
		case 3: { // Adding a block scope to ensure proper initialization 
			// delete task
			cout << "Enter the Id of your Task\n";
			cin >> id;
			deleteTask(myTasks, id);

			//saving task back in file
			saveTasksToFile(myTasks, Taskfile);
			break;
		}
		case 4: { // Exit the program
			cout << "Exiting the program. Goodbye!\n";
			return 0; // Exit the program
		}

		default:
			cout << "Invalid option. Please try again.\n";
			break;
		}


	}
}
		