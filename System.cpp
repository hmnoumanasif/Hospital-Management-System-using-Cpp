#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Hospital
{
    int id;
    char name[50];
    char city[50];
    int availableBeds;
    int bedPrice;
    float rating;
    int reviews;
};

struct Patient
{
    int id;
    char name[50];
    int age;
    char disease[50];
    int hospitalId;
};

void addHospital();
void displayHospitals();
void displayHospitalsByCity();
void addPatient();
void displayPatients();
void sortByBedPrice();
void sortByAvailableBeds();
void sortByHospitalName();
void sortByRatingReviews();
int loadHospitals(struct Hospital h[]);
char *getHospitalName(int id);

int main()
{
    int choice;
    do
    {
        cout << "\n\t\t\tHOSPITAL MANAGEMENT SYSTEM \t\t\t\n\n";
        cout << "1. Add Hospital Data\n";
        cout << "2. Display All Hospitals\n";
        cout << "3. Display Hospitals by City\n";
        cout << "4. Add Patient Data\n";
        cout << "5. Display Patient Data\n";
        cout << "6. Sort Hospitals by Bed Price\n";
        cout << "7. Sort Hospitals by Available Beds\n";
        cout << "8. Sort Hospitals by Name\n";
        cout << "9. Sort Hospitals by Rating & Reviews\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        getchar();

        if (choice == 0)
        {
            cout << "Exiting program...\n";
            break;
        }
        if (choice == 1)
            addHospital();
        if (choice == 2)
            displayHospitals();
        if (choice == 3)
            displayHospitalsByCity();
        if (choice == 4)
            addPatient();
        if (choice == 5)
            displayPatients();
        if (choice == 6)
            sortByBedPrice();
        if (choice == 7)
            sortByAvailableBeds();
        if (choice == 8)
            sortByHospitalName();
        if (choice == 9)
            sortByRatingReviews();
        if (choice < 0 || choice > 9)
            cout << "Invalid Choice!\n";

    } while (choice != 0);

    return 0;
}

void addHospital()
{
    FILE *fp = fopen("hospitals.dat", "ab");
    if (fp == NULL)
    {
        cout << "File error!\n";
        return;
    }

    Hospital h;

    cout << "Enter Hospital ID: ";
    cin >> h.id;
    getchar();

    cout << "Enter Hospital Name: ";
    fgets(h.name, 50, stdin);
    h.name[strcspn(h.name, "\n")] = 0;

    cout << "Enter City Name: ";
    fgets(h.city, 50, stdin);
    h.city[strcspn(h.city, "\n")] = 0;

    cout << "Enter Available Beds: ";
    cin >> h.availableBeds;
    getchar();

    cout << "Enter Bed Price per Day: ";
    cin >> h.bedPrice;
    getchar();

    cout << "Enter Rating (0-5): ";
    cin >> h.rating;
    getchar();

    cout << "Enter Number of Reviews: ";
    cin >> h.reviews;
    getchar();

    fwrite(&h, sizeof(h), 1, fp);
    fclose(fp);

    cout << "Hospital added successfully!\n";
}

void displayHospitals()
{
    Hospital h;
    FILE *fp = fopen("hospitals.dat", "rb");

    if (fp == NULL)
    {
        cout << "No hospitals added yet!\n";
        return;
    }

    cout << "\n\t\tHospital Records\t\t\n";
    while (fread(&h, sizeof(h), 1, fp))
    {
        cout << "\nID: " << h.id << endl;
        cout << "Name: " << h.name << endl;
        cout << "City: " << h.city << endl;
        cout << "Beds: " << h.availableBeds << endl;
        cout << "Price: " << h.bedPrice << endl;
        cout << "Rating: " << h.rating << endl;
        cout << "Reviews: " << h.reviews << endl;
    }

    fclose(fp);
}

void displayHospitalsByCity()
{
    Hospital h[100];
    char city[50];
    int count = loadHospitals(h);

    if (count == 0)
    {
        cout << "No Hospitals added yet!\n";
        return;
    }

    cout << "Enter City Name: ";
    fgets(city, 50, stdin);
    city[strcspn(city, "\n")] = 0;

    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
            if (strcmp(h[i].name, h[j].name) > 0)
            {
                Hospital temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }

    cout << "\nHospitals in " << city << ":\n";
    for (int i = 0; i < count; i++)
        if (strcmp(h[i].city, city) == 0)
            cout << h[i].name << endl;
}

void addPatient()
{
    FILE *fp = fopen("patients.dat", "ab");
    if (fp == NULL)
    {
        cout << "File error!\n";
        return;
    }

    Patient p;

    cout << "Enter Patient ID: ";
    cin >> p.id;
    getchar();

    cout << "Enter Patient Name: ";
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    cout << "Enter Age: ";
    cin >> p.age;
    getchar();

    cout << "Enter Disease: ";
    fgets(p.disease, 50, stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    cout << "Enter Hospital ID: ";
    cin >> p.hospitalId;
    getchar();

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    cout << "Patient added successfully!\n";
}

void displayPatients()
{
    Patient p;
    FILE *fp = fopen("patients.dat", "rb");

    if (fp == NULL)
    {
        cout << "No patients added yet!\n";
        return;
    }

    cout << "\n\t\tPatient Records\t\t\n";
    while (fread(&p, sizeof(p), 1, fp))
    {
        cout << "Patient: " << p.name << endl;
        cout << "Age: " << p.age << endl;
        cout << "Disease: " << p.disease << endl;
        cout << "Hospital: " << getHospitalName(p.hospitalId) << endl;
    }

    fclose(fp);
}

int loadHospitals(Hospital h[])
{
    FILE *fp = fopen("hospitals.dat", "rb");
    int count = 0;

    if (fp == NULL)
    {
        cout << "File error!\n";
        return 0;
    }

    while (fread(&h[count], sizeof(Hospital), 1, fp))
        count++;

    fclose(fp);
    return count;
}

char *getHospitalName(int id)
{
    static char name[50] = "Unknown";
    Hospital h;
    FILE *fp = fopen("hospitals.dat", "rb");

    if (fp == NULL)
        return name;

    while (fread(&h, sizeof(h), 1, fp))
    {
        if (h.id == id)
        {
            strcpy(name, h.name);
            break;
        }
    }

    fclose(fp);
    return name;
}

void sortByBedPrice()
{
    Hospital h[100];
    int count = loadHospitals(h);

    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
            if (h[i].bedPrice < h[j].bedPrice)
            {
                Hospital t = h[i];
                h[i] = h[j];
                h[j] = t;
            }

    cout << "\nSorted by Bed Price (High --> Low)\n";
    for (int i = 0; i < count; i++)
        cout << h[i].name << " - " << h[i].bedPrice << endl;
}

void sortByAvailableBeds()
{
    Hospital h[100];
    int count = loadHospitals(h);

    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
            if (h[i].availableBeds < h[j].availableBeds)
            {
                Hospital t = h[i];
                h[i] = h[j];
                h[j] = t;
            }

    for (int i = 0; i < count; i++)
        cout << h[i].name << " - Beds: " << h[i].availableBeds << endl;
}

void sortByHospitalName()
{
    Hospital h[100];
    int count = loadHospitals(h);

    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
            if (strcmp(h[i].name, h[j].name) > 0)
            {
                Hospital t = h[i];
                h[i] = h[j];
                h[j] = t;
            }

    for (int i = 0; i < count; i++)
        cout << h[i].name << endl;
}

void sortByRatingReviews()
{
    Hospital h[100];
    int count = loadHospitals(h);

    for (int i = 0; i < count; i++)
        for (int j = i; j < count; j++)
            if (h[i].rating < h[j].rating ||
                (h[i].rating == h[j].rating && h[i].reviews < h[j].reviews))
            {
                Hospital t = h[i];
                h[i] = h[j];
                h[j] = t;
            }

    for (int i = 0; i < count; i++)
        cout << h[i].name << " - Rating: " << h[i].rating << " Reviews: " << h[i].reviews << endl;
}
