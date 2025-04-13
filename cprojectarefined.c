
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void addPatients();
void viewPatients();
void addDoctors();
void viewDoctors();
void searchPatient();
void patDel();
void genBill();
char *current_time();
int isFileEmpty(FILE *file);

int main() {
    int index;

        printf("\n****HOSPITAL MANAGEMENT SYSTEM****\n");

        printf("1: Add new patients\n");
        printf("2: View All Patients\n");
        printf("3: Add New Doctor\n");
        printf("4: View All Doctors.\n");
        printf("5: Search Patient\n");
        printf("6: Delete patient's records.\n");
        printf("7: Generate bill.\n");
        printf("0: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &index);

        switch (index) {
            case 1:
                addPatients();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                addDoctors();
                break;
            case 4:
                viewDoctors();
                break;
            case 5:
                searchPatient();
            case 6:
                patDel();
            case 7:
                genBill();

                break;
            case 0:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid input. Please try again.\n");
        }


    return 0;
}
void genBill(){
    struct pat{
        int id;
        char name[100];
        long phone_no;
        char gender[10];
        int age;
        char time[40];
        };
    int patId;
        printf("/n Enter the ID of the patient: ");
        scanf("%d",&patId);
        FILE *file = fopen("patan.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file does not exist.\n");
        return;
    }
    char line[256];
    struct pat patient;


    int found = 0;
    while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d %40[^\t] %ld %d %10s %40[^\n]",
                &patient.id, patient.name, &patient.phone_no,
                &patient.age, patient.gender, patient.time);
                /*printf("\n%d\n",patId);*/
            if (patient.id == patId) {
                found = 1;
                break;
            }
      } 
        if (found != 1){
            printf("\n Patient NOT found.");
            fclose(file);
            return;
        }
        fclose(file);
        struct service{
            char name[25];
            int quantity;
            float price;
            float total;
        };
        int num;
        printf("Enter the number of services: ");
        scanf("%d", &num);

        struct service services[num];

        for (int i = 0; i < num; i++) {
            printf("Enter service %d name: ", i + 1);
            scanf(" %[^\n]", services[i].name);
            printf("Enter quantity for %s: ", services[i].name);
            scanf("%d", &services[i].quantity);
            printf("Enter price per unit for %s: ", services[i].name);
            scanf("%f", &services[i].price);
            services[i].total = services[i].quantity * services[i].price;
        }
        float totalBill=0.00;
        for(int i=0;i<num;i++){
            totalBill += services[i].total;
        }
        printf("\n--- Hospital Bill ---\n");
    printf("Patient ID: %d\n", patient.id);
    printf("Name: %s\n", patient.name);
    printf("\n%-20s%10s%15s%15s\n", "Service", "Quantity", "Price/Unit", "Total");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < num; i++) {
        printf("%-20s%10d%15.2f%15.2f\n",
            services[i].name, services[i].quantity, services[i].price, services[i].total);
    }
    printf("----------------------------------------------------------\n");
    printf("%-20s%10s%15s%15.2f\n", "Total", "", "", totalBill);
     }
 



void addPatients() {
    int nop;
    printf("Enter the number of patients: ");
    scanf("%d", &nop);

    struct patients {
        int id;
        char name[100];
        long phone_no;
        char gender[10];
        int age;
        char time[40];
    };

    struct patients people[nop];

    for (int i = 0; i < nop; i++) {
        printf("Enter the ID of patient %d: ", i + 1);
        scanf("%d", &people[i].id);
        printf("Enter the phone number of patient %d: ", i + 1);
        scanf("%ld", &people[i].phone_no);
        getchar();
        printf("Enter the name of patient %d: ", i + 1);
        scanf("%[^\n]", people[i].name);
        printf("Enter the age of patient %d: ", i + 1);
        scanf("%d", &people[i].age);

        printf("Enter the gender of patient %d (m for male, f for female): ", i + 1);
        char genderInput;
      scanf(" %c", &genderInput);
        if (genderInput == 'm') {
    strcpy(people[i].gender, "male");
} else   {
    strcpy(people[i].gender, "female");
}

        strcpy(people[i].time, current_time());
    }

    FILE *file = fopen("patan.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    if (isFileEmpty(file)) {
        fprintf(file, "%-5s%-20s%-12s%-5s%-10s%-25s\n", "ID", "NAME", "CONTACT NO", "AGE","GENDER","TIME OF ADMISSION");
    }

    for (int i = 0; i < nop; i++) {
        fprintf(file, "%-5d%-20s%-12ld%-5d%-10s%-25s\n",
            people[i].id, people[i].name, people[i].phone_no,
            people[i].age,people[i].gender, people[i].time);
    }

    fclose(file);
    printf("Data saved successfully to 'patan.txt'.\n");
}


void viewPatients() {
    FILE *file = fopen("patan.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file does not exist.\n");
        return;
    }

    char line;
    while ((line = fgetc(file)) != EOF) {
        putchar(line);
    }

    fclose(file);
}



void addDoctors() {
    int nod;
    printf("Enter the number of doctors to store records: ");
    scanf("%d", &nod);

    struct doctors {
        int id;
        char name[100];
        long phone_no;
        char specialization[100];
    };

    struct doctors doctors[nod];

    for (int i = 0; i < nod; i++) {
        printf("Enter the ID of doctor %d: ", i + 1);
        scanf("%d", &doctors[i].id);
        printf("Enter the phone number of doctor %d: ", i + 1);
        scanf("%ld", &doctors[i].phone_no);
        getchar();
        printf("Enter the name of doctor %d: ", i + 1);
        scanf("%[^\n]", doctors[i].name);
        getchar();
        printf("Enter the specialization of doctor %d: ", i + 1);
        scanf("%[^\n]", doctors[i].specialization);
    }

    FILE *file = fopen("doctor.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < nod; i++) {
        fprintf(file, "%-5d%-20s%-12ld%-20s\n",
            doctors[i].id, doctors[i].name, doctors[i].phone_no, doctors[i].specialization);
    }

    fclose(file);
    printf("Data saved successfully to 'doctor.txt'.\n");
}



void viewDoctors() {
    FILE *file = fopen("doctor.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file does not exist.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}



void searchPatient() {
    char name[100], line[256];
    printf("Enter the name of the patient you want to search: ");
    getchar();
    scanf("%[^\n]", name);

    FILE *file = fopen("patan.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file does not exist.\n");
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name) != NULL) {
            found = 1;
            printf("Patient found:\n");
            printf("%s", line);
            break;
        }
    }

    if (!found) {
        printf("Patient not found.\n");
    }

    fclose(file);
}



int isFileEmpty(FILE *file) {
    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, currentPos, SEEK_SET);
    return fileSize == 0;
}
char *current_time() {
    time_t now = time(NULL);
    return ctime(&now);
}



void patDel() {
    char name[100], line[256], conf;
    printf("Enter the name of the patient whose details you want to delete: ")   ;
    getchar();
    scanf("%[^\n]", name);

    FILE *file = fopen("patan.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file does not exist.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }
    int found = 0, y_or_no=0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name) != NULL) {
            found = 1;
            printf("Record to delete: %s", line);
            printf("Are you sure you want to delete this record?(y/n)");
            conf = getchar();
            getchar();
            if(conf=='y' || conf=='Y'){
                     y_or_no=1;
                printf("Deleting.......\n");
                continue;
            }
            else{
                printf("Deletion Cancelled.\n");
                fputs(line, tempFile);
            }

        }
        else{
        fputs(line, tempFile);
        }
    }


    fclose(file);
    fclose(tempFile);

    if (found==1) {
        
        if(y_or_no==1){
            remove("patan.txt");
        rename("temp.txt", "patan.txt");
        printf("Record deleted successfully.\n");
        }
    }
    else {
        printf("Patient not found.\n");
        remove("temp.txt");
    }
    return;
}




