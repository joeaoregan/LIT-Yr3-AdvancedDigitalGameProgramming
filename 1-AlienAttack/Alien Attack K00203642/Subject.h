#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <list>
#include <algorithm>	// remove from list

#include "Message.h"

//const static int NUM_OBSERVERS = 1;

class Subject {
public:
	void addWatcher(Message* observer) {
		listOfObservors.push_back(observer);			// Add to list of observers
	}

	void removeWatcher(Message* observer) {
		listOfObservors.erase(std::remove(listOfObservors.begin(), listOfObservors.end(), observer), listOfObservors.end());	// remove observer from list
	}

private:
	std::vector<Message*> listOfObservors;		// list of observers

protected:
	//void sendNotification(const GameObject& gameObject, int action) {		// Only Player
	void notify(int action) {
		for (int i = 0; i < listOfObservors.size(); ++i) {
			listOfObservors[i]->whenNotified(action);						// Send the action for the observer to perform
		}
	}
};

#endif