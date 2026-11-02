
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 500
#define FILE_NAME "patients.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[15];
    char disease[60];
    char doctor[50];
    float bill;
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Find a patient by ID
int findPatient(int id) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id)
            return i;
    }
    return -1;
}

// Save patient records to a file
void savePatients(void) {
    FILE *fp = fopen(FILE_NAME, "wb");

    if (fp == NULL) {
        printf("Error saving patient records!\n");
        return;
    }

    fwrite(&patientCount, sizeof(int), 1, fp);
    fwrite(patients, sizeof(Patient), patientCount, fp);

    fclose(fp);
}

// Load patient records from a file
void loadPatients(void) {
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
        return;

    int count;

    if (fread(&count, sizeof(int), 1, fp) != 1 ||
        count < 0 || count > MAX_PATIENTS) {
        fclose(fp);
        printf("Invalid data file. Starting with empty records.\n");
        return;
    }

    if (fread(patients, sizeof(Patient), count, fp) !=
        (size_t)count) {
        patientCount = 0;
        fclose(fp);
        printf("Could not read patient records.\n");
        return;
    }

    patientCount = count;
    fclose(fp);
}

// Add a new patient
void addPatient(void) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient record limit reached!\n");
        return;
    }

    Patient p;

    printf("\nEnter Patient ID: ");
    if (scanf("%d", &p.id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    if (p.id <= 0 || findPatient(p.id) != -1) {
        printf("Invalid or duplicate patient ID!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", p.name);

    printf("Enter Age: ");
    if (scanf("%d", &p.age) != 1 || p.age < 0 ||
        p.age > 130) {
        printf("Invalid age.\n");
        return;
    }

    printf("Enter Gender: ");
    scanf(" %14[^\n]", p.gender);

    printf("Enter Disease/Reason for Visit: ");
    scanf(" %59[^\n]", p.disease);

    printf("Enter Doctor Name: ");
    scanf(" %49[^\n]", p.doctor);

    printf("Enter Bill Amount: ");
    if (scanf("%f", &p.bill) != 1 || p.bill < 0) {
        printf("Invalid bill amount.\n");
        return;
    }

    patients[patientCount++] = p;
    savePatients();

    printf("\nPatient added successfully!\n");
}

// Display a single patient
void displayPatient(Patient p) {
    printf("\n------------------------------\n");
    printf("Patient ID : %d\n", p.id);
    printf("Name       : %s\n", p.name);
    printf("Age        : %d\n", p.age);
    printf("Gender     : %s\n", p.gender);
    printf("Condition  : %s\n", p.disease);
    printf("Doctor     : %s\n", p.doctor);
    printf("Bill       : Rs. %.2f\n", p.bill);
    printf("------------------------------\n");
}

// View all patients
void viewPatients(void) {
    if (patientCount == 0) {
        printf("\nNo patient records found.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++)
        displayPatient(patients[i]);
}

// Search for a patient
void searchPatient(void) {
    int id;

    printf("\nEnter Patient ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1)
        printf("Patient not found.\n");
    else
        displayPatient(patients[index]);
}

// Update patient details
void updatePatient(void) {
    int id;

    printf("\nEnter Patient ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    Patient *p = &patients[index];

    printf("Enter new name: ");
    scanf(" %49[^\n]", p->name);

    printf("Enter new age: ");
    if (scanf("%d", &p->age) != 1 || p->age < 0 ||
        p->age > 130) {
        printf("Invalid age.\n");
        return;
    }

    printf("Enter new gender: ");
    scanf(" %14[^\n]", p->gender);

    printf("Enter new disease/reason: ");
    scanf(" %59[^\n]", p->disease);

    printf("Enter new doctor name: ");
    scanf(" %49[^\n]", p->doctor);

    printf("Enter updated bill amount: ");
    if (scanf("%f", &p->bill) != 1 || p->bill < 0) {
        printf("Invalid bill amount.\n");
        return;
    }

    savePatients();
    printf("Patient record updated successfully!\n");
}

// Delete a patient
void deletePatient(void) {
    int id;

    printf("\nEnter Patient ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    for (int i = index; i < patientCount - 1; i++)
        patients[i] = patients[i + 1];

    patientCount--;
    savePatients();

    printf("Patient record deleted successfully!\n");
}

// Display a basic bill
void generateBill(void) {
    int id;

    printf("\nEnter Patient ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }

    Patient p = patients[index];

    printf("\n========== HOSPITAL BILL ==========\n");
    printf("Patient ID : %d\n", p.id);
    printf("Patient    : %s\n", p.name);
    printf("Doctor     : %s\n", p.doctor);
    printf("Reason     : %s\n", p.disease);
    printf("-----------------------------------\n");
    printf("Total Amount: Rs. %.2f\n", p.bill);
    printf("===================================\n");
    printf("This is a basic project bill, not a tax invoice.\n");
}

int main(void) {
    int choice;

    loadPatients();

    do {
        printf("\n====================================\n");
        printf("     HOSPITAL MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Generate Bill\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please restart the program.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                updatePatient();
                break;
            case 5:
                deletePatient();
                break;
            case 6:
                generateBill();
                break;
            case 0:
                savePatients();
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}


