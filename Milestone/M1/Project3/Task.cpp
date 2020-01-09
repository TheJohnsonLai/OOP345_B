#include <iostream>
#include <string>
#include <iomanip>
#include "Task.h"
#include "Utilities.h"

size_t Task::field_width = 1;

Task::Task(const std::string& stRecord) {

	slots = 1;
	pNextTask[Quality::passed] = nullptr;
	pNextTask[Quality::redirect] = nullptr;

	Utilities uObject;
	std::string token;
	bool anyMore = true;
	size_t pos = 0;

	for(int i = 0; anyMore; i++){
		token = uObject.nextToken(stRecord, pos, anyMore);

		if (pos == stRecord.size()){ 
			anyMore = false; 
		}

		if (!token.empty()) {
			if (i == 0) {
				name = token;
			}
			else if (i == 1) {
				if (anyMore) {
					slots = token;
				}
			}
			else if (i == 2) {
				nextTask[Quality::passed] = token;
			}
			else if (i == 3) {
				nextTask[Quality::redirect] = token;
			}
		}

		if (field_width < uObject.getFieldWidth())
			field_width = uObject.getFieldWidth();
	}

}

bool Task::validate(const Task& task) {

	int emptyTasks = 0;
	for (int i = 0; i < 2; i++) {
		if (nextTask[i].empty()) {
			emptyTasks++;
			if (emptyTasks >= 2)
				return true;
		}else if (nextTask[i] == task.name) {
			pNextTask[i] = &task;
		}
	}

	if (pNextTask[passed] && pNextTask[redirect])
		return true;
	else if (nextTask[passed].empty() && nextTask[redirect].empty())
		return true;
	else
		return false;
}

const std::string& Task::getName() const {
	return name;
}

unsigned int Task::getSlots() const {
	return std::stoul(slots);
}

const Task* Task::getNextTask(Quality quality) const {
	if (pNextTask[quality] == 0) {
		throw std::string("*** Validate [" + nextTask[quality] + "] @ [" + name + "] ***");
	}
	return pNextTask[quality];
}

void Task::display(std::ostream& os) const {

	os << std::left << "Task Name    " << ": " << std::setw(field_width + 1) << "[" + name + "]" << "  [" + slots + "]\n";

	std::string next[] = {" Continue to"," Redirect to"};
	for (int i = 0; i < 2; i++) {
		if (!nextTask[i].empty()) {
			os << " " << std::right << next[i] << " : " << std::left << std::setw(field_width + 1) << "[" + nextTask[i] + "]";
			if (pNextTask[i] == 0) {
				os << " *** to be validated ***";
			}
			os << "\n";
		}
	}
}

size_t Task::getFieldWidth() {
	return field_width;
}

bool operator==(const Task& t1, const Task& t2) {
	return t1.getName().compare(t2.getName()) ? 0 : 1;
}