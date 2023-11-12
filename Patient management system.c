/*
Project title : COVID-19 Patient Management System

Name  : Weerasingha W.K.H.M.
E no. : E/18/383
*/

#include <stdio.h>
#include <string.h>  // string handling and memory handling
#include <stdbool.h>
#include <stdlib.h>

// set default number of patients
#define SIZE 50

// create stuct to store a patient data
typedef struct {
    int NIC;
    char fullName [50];
    int age;
    char gender [10];
    char admissionDate [20];
} patient_t;

// Defife functions
void userInterface();
void quite();
void addNewPatient();
void deletePatient(int firstOrNot);
void patientDetail();
void printAll();
void deleteAll();
void summary();
void pressEnter();
void userOpinion(int funcNo);

// Create global variables
int size = SIZE;
int noOfPatients = 0;
int reallocTimes = 2;
int maleCount = 0;
int femaleCount = 0;
int otherCount = 0;

patient_t *patients;

int main(){
    // Welcome UI
    printf("\n===================================================================\n"
    "\tWelcome to the \"COVID-19 Patient Management System\"\n"
    "===================================================================\n\n");
    userInterface();
    
    // dynamic memory allocation to store patient data as array 
    patients = malloc(sizeof(patient_t) * size);

    int option;
    bool flag = true;
    char temp, *ptr, inputOption[5];

    // While loop for the operator
    while (flag){

        printf("\n");
        printf("Enter option [0 : 4] : ");
        scanf("%s", inputOption);
        option = (int) strtol(inputOption, &ptr, 10);
        if (*ptr == '\0' && option >= 0) {  // Input validation
            
            // Check input to option variable and call suitable functon
            switch (option){
                case 0 : 
                    quite(); break;
                case 1 : 
                    addNewPatient(); break;
                case 2 :
                    patientDetail(); break;
                case 3 : 
                    printAll(); break;
                case 4 : 
                    deletePatient(0); break;
                case 5 : 
                    deleteAll(); break;
                case 6 : 
                    summary(); break;

                default : printf("Invalid input. Please check input and try again.\n");
            }

        }else{
            printf("Invalid input. Please check input and try again.\n");
            scanf("%c", &temp);
        }
    }

    return 0;
}

// Print the user interface ## function number = 0 ##
void userInterface(){
    printf("===================================================================\n"
    "\t\tCOVID-19 Patient Management System\n"
    "===================================================================\n"
    "Options :\n"
    "\t\t0 : Quit\n"
    "\t\t1 : Add a patient record\n"
    "\t\t2 : Print a patient record\n"
    "\t\t3 : Print all patient records\n"
    "\t\t4 : Delete a patient record\n"
    "\t\t5 : Delete all patient records\n"
    "\t\t6 : Summary of the patient records\n"
    "===================================================================\n");
}

// Quite the programme ## function number = 1 ##
void quite(){
    // confirm the process and exit or not
    char yesOrno[5];
    char temp;
    bool flag = true;
    while (flag){
        printf("\nAre you want to exit the Program [Y / N] ? ");
        if (scanf("%s", yesOrno) == 1){
            if (strcmp(yesOrno, "Y") == 0) {
                free(patients);
                printf("\n*******************************************************************\n"
                "\t\tExit the program. - Have a nice day!\n"
                "*******************************************************************\n");
                exit(0); // exit the program
            }else if (strcmp(yesOrno, "N") == 0){
                printf("\n");
                userInterface(); // Back to the UI
                return;
            }else{
                scanf("%c", &temp);
            } 
        }
    }
    
}

// Function to record a new patient's information ## function number = 2 ##
void addNewPatient(){
    printf("\n---------Enter patient information.---------\n\n");
    
    patient_t p;
    int funcNo = 2; // set function number

    // Increse the dynamic memory allocation
    if (noOfPatients == size){
        size = SIZE * reallocTimes;
        patients = realloc(patients, sizeof(patient_t) * size);
        reallocTimes++;
    }

    char temp;
    /* Get patient information*/

    // Get input for patient's NIC and validate it 
    bool flag1 = true;
    int nic;
    char *ptr, inputNic[15];
    while (flag1){
        printf("Enter patient NIC number : ");
        scanf("%s", inputNic);
        nic = (int)strtol(inputNic, &ptr, 10);
        if (*ptr == '\0' && nic > 0){ // for only integers
            int end = noOfPatients/2;
            int fromLeft = noOfPatients;
            if (noOfPatients > 0){
                for (int i = 0; i <= end; i++){
                    // Check that input NIC already recorded or not
                    if ((nic == patients[i].NIC) || (nic == patients[fromLeft - 1].NIC)){
                        printf(">>>> WARNING - This NIC alredy recorded\n");
                        userOpinion(funcNo);
                        return;
                    }
                    fromLeft--;
                } 
            }
            
            p.NIC = nic;
            flag1 = false;
            
        }else {
            printf(">>>> WARNING - Input is not correct, Please check your input and try again\n\n");
            scanf("%c", &temp);
        }
    }

    // Get input for patient's name
    scanf("%c", &temp);
    printf("Enetr patient ful name   : ");
    scanf("%[^\n]", p.fullName);

    // Get input for patient's age and validate it
    char inputAge[5];
    flag1 = true;
    while (flag1){
        printf("Enter patient age        : ");
        scanf("%s", inputAge);
        p.age = (int)strtol(inputAge, &ptr, 10);
        if (*ptr == '\0' && p.age > 0){
            flag1 = false;
        }else {
            printf(">>>> WARNING - Input is not correct, Please check your input and try again\n\n");
            scanf("%c", &temp);
        }
    }

    // Get input for patient's gender and validate it
    flag1 = true;
    while (flag1) {
        scanf("%c", &temp);
        printf("Enter patient gender [Male - 'M'/ Female - 'F'/ Other - 'O'] : ");
        if (scanf("%s", p.gender) == 1){
            if (*p.gender == 'M'){
                maleCount++;
                flag1 = false;
            }else if (*p.gender == 'F'){
                femaleCount++;
                flag1 = false;
            }else if (*p.gender == 'O'){
                otherCount++;
                flag1 = false;
            }else{
                printf(">>>> WARNING - Input is not in correct format, Please check your input and try again\n\n");
            }
        }else {
            printf(">>>> WARNING - Input is not in correct format, Please check your input and try again\n\n");
            scanf("%c", &temp);
        }
        
    }

    // Get input for patient's addmission date
    scanf("%c", &temp);
    printf("Enter patient addmission date (dd/mm/yyyy) : ");
    scanf("%[^\n]", p.admissionDate);
       
    scanf("%c", &temp);

    // add collected information to array of patients
    patients[noOfPatients] = p;
    noOfPatients++;  

    printf("\n---> New patient information recorded successfully\n");

    // get user opinion 
    userOpinion(funcNo);
    return;

}

// Function to show patient data which want ## function number = 3 ##
void patientDetail(){
   int funcNo = 3; // Set function number
   
    // If there are no patients added
    if (noOfPatients == 0){
        printf("\n---> No patient records.\n");
        return;
    }

    // Get input for patient's NIC and validate it 
    bool flag1 = true;
    char temp, *ptr, inputNic[15];
    int id;
    while (flag1){
        printf("\nEnter patient id number : ");
        scanf("%s", inputNic);
        id = (int) strtol(inputNic, &ptr, 10);
        if (*ptr == '\0' && id >= 0){
            flag1 = false;   
        }else {
            printf(">>>> WARNING - Input is not correct, Please check your input and try again");
            scanf("%c", &temp);
        }
    }

    // Show the patient information
    int i;
    for (i = 0; i < noOfPatients; i++){
        patient_t p = patients[i];
        if (p.NIC == id){
            printf("\nPatent information -\n");
            printf("\tPatient name             : %s\n", p.fullName);
            printf("\tPatient age              : %d\n", p.age);
            if (*p.gender == 'M'){
                printf("\tPatient gender           : Male\n");
            }else if (*p.gender == 'F'){
                printf("\tPatient gender           : Female\n");
            }else {
                printf("\tPatient gender           : Other\n");
            }
            printf("\tPatient addmission date  : %s\n", p.admissionDate);
            // to stop the for loop 
            i = noOfPatients + 2; 
        }
    }
    // if no patient found
    if (i == noOfPatients) printf("---> ALLERT - There is no patient with this NIC\n");

    // get user opinion 
    userOpinion( funcNo);
    return;

}

// function to delete a patient record ## function number = 4 ##
void deletePatient(int firstOrNot){
    int funcNo = 4;
    char temp;

    // If there are no patients added
    if (noOfPatients == 0){
        if (firstOrNot == 0){ // call this function from directly int main
            printf("\n---> No patient records.\n");
            return;
        }else{ // call this function from userOpinion
            printf("\n---> No patient records.\n");
            pressEnter();
            return;
        }
    }

    printf("\n---------Delete a patient record---------\n");

    // Get input for patient's NIC and validate it 
    bool flag1 = true;
    char *ptr, inputNic[15];
    int id;
    while (flag1){
        printf("\nEnter patient NIC number which want to delete : ");
        scanf("%s", inputNic);
        id = (int) strtol(inputNic, &ptr, 10);
        if (*ptr == '\0' && id >= 0){
            flag1 = false;   
        }else {
            printf(">>>> WARNING - Input is not correct, Please check your input and try again");
            scanf("%c", &temp);
        }
    }

    // delete the patient
    int i;
    for (i=0; i < noOfPatients; i++){
        if (id == patients[i].NIC){
            // Update the patients according to gender
            if (*patients[i].gender == 'M'){
                maleCount--;
            }else if (*patients[i].gender == 'F'){
                femaleCount--; 
            }else{
                otherCount--;
            }
            // deleting process
            for (int j = i; j < noOfPatients - 1; j++){
                patients[j] = patients[j+1];
            }
            printf("\n---> Patient information records were deteted successfully\n");

            noOfPatients--;
            // to stop the for loop 
            i = noOfPatients + 2;
        }
    }

    // if no patient found
    if (i == noOfPatients) printf("---> ALLERT - There is no patient with this NIC\n");

    // get user opinion 
    userOpinion(funcNo);
    return;

}

// Function to print all the patients data ## function number = 5 ##
void printAll(){
    // If there no patients added
    if (noOfPatients == 0){
        printf("\n");
        printf("---> No patient records.\n");
        return;
    }
    printf("\n---------All patient records---------\n");
    // print information of the patients
    for (int i = 0; i < noOfPatients; i++){
        printf("\nPatient no. %d\n", i+1);
        
        patient_t p = patients[i];
        printf("\t\tPatient NIC             : %d\n", p.NIC);
        printf("\t\tPatient full name       : %s\n", p.fullName);
        printf("\t\tPatient age             : %d\n", p.age);
        if (*p.gender == 'M'){
            printf("\t\tPatient gender          : Male\n");
        }else if (*p.gender == 'F'){
            printf("\t\tPatient gender          : Female\n");
        }else {
            printf("\t\tPatient gender          : Other\n");
        }
        printf("\t\tPatient admission date  : %s\n", p.admissionDate);
        
    }

    // Back to the main menu
    pressEnter();
}

// Function to delete all the patients data ## function number = 6 ##
void deleteAll(){
    // If there are no patients added
    if (noOfPatients == 0){
        printf("\n---> No patient records.\n");
        return;
    }

    // confirm the process and delete all or not
    char yesOrno[5];
    char temp;
    bool flag3 = true;
    while (flag3){
        printf("\nAre you want to delete all patient records [Y / N] ? ");
        if (scanf("%s", yesOrno) == 1){
            if (strcmp(yesOrno, "Y") == 0) {
                noOfPatients = 0;
                maleCount = 0;
                femaleCount = 0;
                otherCount = 0;
                printf("\n---> All patient records have been deleted.\n\n");
                userInterface(); // Back to the UI
                flag3 = false;
            }else if (strcmp(yesOrno, "N") == 0){
                printf("\n");
                userInterface(); // Back to the UI
                return;
            }else{
                scanf("%c", &temp);
            } 
        }
    }
    
}

// Function to print summary of all patient records ## function number = 7 ##
void summary(){
    // If there are no patients added
    if (noOfPatients == 0){
        printf("\n---> No patient records.\n");
        return;
    }

    printf("\nSummary of all patient records.\n\n");
    printf("\tNumber of patient records : %d\n", noOfPatients);
    printf("\tNumber of Male patients   : %d\n", maleCount);
    printf("\tNumber of Female patients : %d\n", femaleCount);
    printf("\tNumber of Other patients  : %d\n", otherCount);

    // Back to the main menu
    pressEnter();
}

// Function to check Enter key press ## function number = 8 ##
void pressEnter(){
    // Back to the main menu
    char enter;
    enter = fgetc(stdin);
	//infinite loop
	while(true){
        printf("\nPress 'Enter' key to continue : ");
		enter = fgetc(stdin);
		if(enter == 10){
			printf("\n");
            userInterface(); // Back to the UI
            return;
		}
		enter = getchar();
	}
}

// function to check user opinion ## function number = 9 ##
void userOpinion(int funcNo){
    // get user opinion 
    char yesOrno[5];
    char temp;
    bool flag3 = true;
    while (flag3){
        if (funcNo == 2) printf("\nAre you want to add a new patient [Y / N] ? ");
        if (funcNo == 3) printf("\nAre you want to get information about another patient [Y / N] ? ");
        if (funcNo == 4) printf("\nAre you want to delete another patient [Y / N] ? ");
        if (scanf("%s", yesOrno) == 1){
            if (strcmp(yesOrno, "Y") == 0) {
                if (funcNo == 2) addNewPatient(); // recall the function to add new patient
                if (funcNo == 3) patientDetail(); // recall the function to get patient detail
                if (funcNo == 4) deletePatient(1); // recall the function to delete patient
                flag3 = false;
            }else if (strcmp(yesOrno, "N") == 0){
                printf("\n");
                userInterface(); // Back to the UI
                return;
            }else{
                scanf("%c", &temp);
            } 
        }
    }
}