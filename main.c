#include <stdio.h>
#define MAX_BOOKINGS 100
typedef struct {
    char name[50];
    int age;
    char passport_number[20];
    char contact_number[20];
    char flight_details[200];
} Booking;
Booking bookings[MAX_BOOKINGS];
int booking_count = 0;
void displayFlight();
void displayBooking();
void customer(const char *flight);
void saveBookingsToFile();
void loadBookingsFromFile();
int main() {
    loadBookingsFromFile();
    int selection;
    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Display Flights\n");
        printf("2. Display Bookings\n");
        printf("3. Exit\n");
        printf("Enter your selection: ");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                displayFlight();
                break;
            case 2:
                displayBooking();
                break;
            case 3:
                printf("Exiting the program. Thank you!\n");
                saveBookingsToFile();
                return 0;
            default:
                printf("Invalid selection. Please try again.\n");
        }
    }
}
void displayFlight() {
    const char *flights[] = {
        "Kuwait Airways: Karachi (KHI) to Kuwait City (KWI), Flight KU 204, 5th Jan 2025, 12:30 PM - 2:30 PM, 2h, Luggage: 2x23kg + 7kg, PKR 60,000",
        "Qatar Airways: Karachi (KHI) to Doha (DOH), Flight QR 610, 6th Jan 2025, 3:00 PM - 5:00 PM, 2h, Luggage: 2x30kg + 7kg, PKR 75,000",
        "Emirates: Karachi (KHI) to Dubai (DXB), Flight EK 601, 7th Jan 2025, 10:00 AM - 11:45 AM, 1h 45m, Luggage: 2x25kg + 7kg, PKR 65,000"
    };
    int flightCount = sizeof(flights) / sizeof(flights[0]);
    char option;
    printf("\n--- Available Flights ---\n");
    int i = 0;
    do {
        printf("%d) %s\n", i + 1, flights[i]);
        i++;
    } while (i < flightCount);
    printf("Enter your option (1-%d): ", flightCount);
    scanf(" %c", &option);
    if (option >= '1' && option <= '0' + flightCount) {
        int index = option - '1';
        printf("You selected:\n%s\n", flights[index]);
        customer(flights[index]);
    } else {
        printf("Invalid option selected. Returning to main menu.\n");
    }
}
void customer(const char *flight) {
    if (booking_count >= MAX_BOOKINGS) {
        printf("Booking limit reached. Cannot add more bookings.\n");
        return;
    }
    Booking new_booking;
    strcpy(new_booking.flight_details,flight);
    printf("\n--- Customer Details ---\n");
    printf("Enter your name: ");
    scanf(" %[^\n]s", &new_booking.name);
    printf("Enter your age: ");
    scanf("%d", &new_booking.age);
    printf("Enter your passport number: ");
    scanf(" %s", &new_booking.passport_number);
    printf("Enter your contact number: ");
    scanf(" %s", &new_booking.contact_number);
    bookings[booking_count++] = new_booking;
    printf("\n--- Booking Confirmed ---\n");
    printf("Name: %s\n", new_booking.name);
    printf("Flight: %s\n", new_booking.flight_details);
    printf("Booking has been saved. Returning to main menu.\n");
    saveBookingsToFile();
}
void displayBooking() {
    if (booking_count == 0) {
        printf("\nNo bookings available at the moment.\n");
        return;
    }
    printf("\n--- Current Bookings ---\n");
    int i = 0;
    do {
        printf("\nBooking %d:\n", i + 1);
        printf("Name: %s\n", bookings[i].name);
        printf("Age: %d\n", bookings[i].age);
        printf("Passport Number: %s\n", bookings[i].passport_number);
        printf("Contact Number: %s\n", bookings[i].contact_number);
        printf("Flight: %s\n", bookings[i].flight_details);
        i++;
    } while (i < booking_count);
}
void saveBookingsToFile() {
    FILE *fptr;
    fptr = fopen("booking.txt", "wb");
    if (fptr == NULL) {
        printf("Error saving bookings to file.\n");
        return;
  }
    fwrite(&booking_count, sizeof(booking_count), 1, fptr);
    fwrite(bookings, sizeof(Booking), booking_count, fptr);
    fclose(fptr);
    printf("Bookings have been saved to file.\n");
}
void loadBookingsFromFile() {
    FILE *fptr;
    fptr = fopen("booking.txt", "rb");
    if (fptr == NULL) {
        printf("No existing bookings found.\n");
        return;
    }
    fread(&booking_count, sizeof(booking_count), 1, fptr);
    fread(bookings, sizeof(Booking), booking_count, fptr);
    fclose(fptr);
    printf("Bookings have been loaded from file.\n");
}

