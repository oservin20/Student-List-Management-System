// CSE240 Fall 2022 HW 7 & 8
// Osman Servin
// Write the compiler used: GCC
// Command to compile: gcc -g -Wall hw7_8.c -o output
// Executable command: ./output


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME 30

// global linked list 'list' contains the list of students
struct studentList {
	struct student* student;
	struct studentList* next;
} *list = NULL;				// currently empty list

// structure "student" contains the student's name, id and linked list of courses
struct student {
	char name[MAX_NAME];
	unsigned int id;
	struct course* courses;		// linked list 'courses' contains names of courses
};

//  structure 'course' contains course's name
struct course {
	char name[MAX_NAME];
	struct course* next;
};

// forward declaration of functions (already implemented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:

void addStudent(char* studentNameInput, unsigned int idInput); 
void displayStudentList(struct studentList* tempList);	      	
struct student* searchStudent(char* studentNameInput);	      	

void addCourse(char* studentNameInput, char* courseNameInput);	
void displayStudentCourseList(struct studentList* tempList);	
void removeStudent(char* studentNameInput);			

int main()
{
	char selection = 'a';		// initialized to a dummy value
	do
	{
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new student to the list\n");
		printf("\t d: display student list (no courses)\n");
		printf("\t b: search for an student on the list\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a course of a student\n");
		printf("\t l: display students who has a specific course\n");
		printf("\t r: remove an student\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char studentNameInput[MAX_NAME], courseNameInput[MAX_NAME];
	unsigned int idInput;


	switch (c)
	{
	case 'a':	// add student
		// input student details from user
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter id: ");
		scanf("%d", &idInput);
		flushStdIn();

		if (searchStudent(studentNameInput) == NULL)
		{
			addStudent(studentNameInput, idInput);
			printf("\nStudent successfully added to the list!\n\n");
		}
		else
			printf("\nThat student is already on the list!\n\n");
		break;

	case 'd':		// display the list
		displayStudentList(list);
		break;

	case 'b':		// search for an student on the list
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nStudent name exists on the list! \n\n");
		}
		break;

	case 'r':		// remove student
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			removeStudent(studentNameInput);
			printf("\nStudent successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add course
		printf("\nPlease enter student's name: ");
		fgets(studentNameInput, sizeof(studentNameInput), stdin);
		studentNameInput[strlen(studentNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchStudent(studentNameInput) == NULL)
			printf("\nStudent name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter course's name: ");
			fgets(courseNameInput, sizeof(courseNameInput), stdin);
			courseNameInput[strlen(courseNameInput) - 1] = '\0';	// discard the trailing '\n' char

			addCourse(studentNameInput, courseNameInput);
			printf("\nCourse added! \n\n");
		}
		break;

	case 'l':		// list course's students
		displayStudentCourseList(list);
		break;

	case 'q':		// quit
		break;

	default: printf("%c is invalid input!\n", c);
	}
}


// This function is used to insert a new student in the linked list.
void addStudent(char* studentNameInput, unsigned int idInput)
{
	// ALLOCATE MEMORY FOR THE NEW STUDENTLIST AND STUDENT
	struct studentList* newStudent = (struct studentList*)malloc(sizeof(struct studentList));
	newStudent->student = (struct student*)malloc(sizeof(struct student)); 
	
	// ADDS THE NAME AND ID NUMBER TO THE STUDENT INFORMATION
	strcpy(newStudent->student->name, studentNameInput);
	newStudent->student->id = idInput;
	
	// SETTING THE NEXT POINTER TO NULL AND THE COURSES LIST SET TO NULL
	newStudent->next = NULL;
	newStudent->student->courses = NULL;

	// STUDENT IS THE FIRST IN THE LIST ADD HIM TO BEGINNING OF THE LIST
	if(list == NULL)
	{
		list = newStudent;
	}
	// STUDENT IS NOT HTE FIRST IN LIST THEN ADD HIM TO THE HEAD OF THE LIST
	else
	{
		// NEW NODE POINTS TO THE HEAD
		newStudent->next = list;
		// LIST POINTS TO THE NEW NODE AND INSERTS IT TO THE LIST
		list = newStudent;
	}
	return;
}



// This function displays the student details (struct elements) of each student.
void displayStudentList(struct studentList* tempList)
{
	// STOPPING CONDITION
	if(tempList == NULL)
	{
		printf("\n(end of list)\n\n");
		return; // BASE CASE TO END RECURSION
	}
	//
	else
	{
		// PRINT THE STUDENT INFORMATION
		printf("\nStudent Name: %s\n", tempList->student->name);
		printf("Student Id: %d\n", tempList->student->id);
		
		// RECURSIVE CALL (e.g. n-1)
		displayStudentList(tempList->next);		
		}	
}



// This function searches the 'list' to check if the given student exists in the list. Search by student name.
struct student* searchStudent(char* studentNameInput)
{
	struct studentList* tempList = list;  // work on a copy of 'list'
	// write the code below.

	// PARSE THROUGH THE LIST UNTIL END OF LIST IS REACHED
	while(tempList != NULL)
	{	
		// COMPARES IF THE NAME IN NODE IS THE SAME AS THE NAME IT IS SEARCHING FOR
		if(strcmp(tempList->student->name, studentNameInput) == 0)
		{
			// IF THE STUDENT WAS FOUND THEN LEAVE FUNCTION AND RETURN THE STRUCT
			return tempList->student;
		}
		// MOVES TO THE NEXT NODE TO SEARCH FOR STUDENT
		tempList = tempList->next; 
	}

	// IF THE NAME IS NOT IN THE LIST THEN RETURN NULL
	return NULL;
}



// This function adds course's name to a student node.
void addCourse(char* studentNameInput, char* courseNameInput)
{
	struct studentList* tempList = list;  // work on a copy of 'list'

	// CREATES A NEW NODE AND ALLOCATES MEMORY
	struct course* newCourse = (struct course*)malloc(sizeof(struct course));	

	// LOOP THAT PARSES UNTIL THE NODE WITH STUDENT NAME IS REACHED
	while( strcmp(tempList->student->name, studentNameInput) != 0)
	{
		// MOVES TO THE NEXT NODE
		tempList = tempList->next;
	}

	// ADD INFORMATION TO THE COURSE NODE
	strcpy(newCourse->name, courseNameInput);
	
	// LINKS THE NODE TO THE LIST
	newCourse->next = tempList->student->courses; 
	tempList->student->courses = newCourse;
	
	return;
}



// This function prompts the user to enter a course name. This function then searches for students with this course.
void displayStudentCourseList(struct studentList* tempList)
{
	struct studentList* temp = tempList; // WORKING ON WITH A COPY OF LIST

	// ASK FOR COURSE NAME
	char courseNameInput[MAX_NAME];
	printf("\nPlease enter course's name: ");
	fgets(courseNameInput, sizeof(courseNameInput), stdin);
	courseNameInput[strlen(courseNameInput) - 1] = '\0'; // DISCARDS THE TRAILING '\n' TERMINATOR

	// CHECK IF THE LIST IS EMPTY	
	if(temp != NULL)
	{
		// PARSES THROUGH EACH STUDENT UNTIL THE END OF LIST IS REACHED
		while(temp != NULL)
		{	
			struct course* tempCourse = temp->student->courses;
			
			// PARSES THROUGH EACH COURSE A STUDENT HAS UNTIL THE END OF LIST OR COURSE IS FOUND
			while(tempCourse != NULL)
			{
				if(strcmp(tempCourse->name, courseNameInput) == 0)
				{
					// PRINT STUDENT INFORMATION
					printf("\nStudent Name: %s\n", temp->student->name);
					printf("Student Id: %d\n", temp->student->id);
					
					// IF COURSE IS FOUND THEN BREAK FROM THIS LOOP
					tempCourse = NULL;
				}
				else
				{
					// GOES TO THE NEXT STUDENT COURSE
					tempCourse = tempCourse->next;
				}
			}

			// GOES TO THE NEXT NODE
			temp = temp->next;
		}

		printf("\n(end of list of students in course)\n\n");
		return;
	}
	// IF THE LIST IS NULL/EMPTY THEN LEAVE FUNCTION
	else
	{
		return;
	}
	
}



// This function removes an student from the list.
// The function will remove courses of the student too.
void removeStudent(char* studentNameInput)
{
	struct studentList* tempList = list;	// work on a copy of 'list'
	struct studentList* tempListPrev = list; // USED TO POINT TO THE NODE BEFORE THE ONE IM TRYING TO DELETE
	struct course* tempCourse;

	// IF THE STUDENT IS THE FIRST IN THE LIST
	if(strcmp(tempList->student->name, studentNameInput) == 0)
	{
		// DELETE AND FREE MEMORY IF THE FIRST NODE IS THE STUDENT WE ARE LOOKING FOR
		tempList = list;
		list = tempList->next;
		free(tempList);

		// LEAVE FUNCTION ONCE STUDENT IS DELETED
		return;	
	}
	// IF THE STUDENT ISNT FIRST IN THE LIST	
	else
	{
		tempCourse = tempList->student->courses;

		// PARSE LIST TO FIND THE STUDENT
		while(tempList != NULL)
		{
			// SKIPS THE FIRST NODE AND INCREMENTS
			tempCourse = tempList->student->courses;
			tempListPrev = tempList;
			tempList =  tempList->next;		
	
			// COMPARE THE NAMES OF STUDENT AND THE INPUT
			if(strcmp(tempList->student->name, studentNameInput) == 0)
			{
				// REMOVE THE STUDENT COURSES
				while(tempCourse != NULL)
				{
					// REMOVE THE COURSE NODE
					tempCourse = tempList->student->courses;
					tempList->student->courses = tempCourse->next;
					free(tempCourse);
			
					// MOVE TO NEXT COURSE NODE
					tempCourse = tempCourse->next;
				}
			
				//IF STUDENT IS FOUND DELETE THE STUDENT INFORMATION
				tempList = tempListPrev->next;
				tempListPrev->next = tempList->next;
				free(tempList);

				// LEAVE FUNCTION
				return;
			}
		}
	}
}








