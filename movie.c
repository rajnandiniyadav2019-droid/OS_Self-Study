#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct movie {
    int id;
    char name[50];
    float rating;
};

// Function to add record
void addMovie() {
    int fd = open("movies.dat", O_WRONLY | O_CREAT | O_APPEND, 0666);
    struct movie m;

    printf("Enter ID: ");
    scanf("%d", &m.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", m.name);
    printf("Enter Rating: ");
    scanf("%f", &m.rating);

    write(fd, &m, sizeof(m));
    close(fd);

    printf("Movie added successfully!\n");
}

// Display all records
void displayMovies() {
    int fd = open("movies.dat", O_RDONLY);
    struct movie m;

    printf("\nMovie Records:\n");

    while (read(fd, &m, sizeof(m)) > 0) {
        if (m.id != -1) {
            printf("ID: %d | Name: %s | Rating: %.2f\n", m.id, m.name, m.rating);
        }
    }
    close(fd);
}

// Search by ID
void searchMovie() {
    int fd = open("movies.dat", O_RDONLY);
    struct movie m;
    int id, found = 0;

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (read(fd, &m, sizeof(m)) > 0) {
        if (m.id == id) {
            printf("Found -> ID: %d | Name: %s | Rating: %.2f\n", m.id, m.name, m.rating);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Movie not found!\n");

    close(fd);
}

// Update record
void updateMovie() {
    int fd = open("movies.dat", O_RDWR);
    struct movie m;
    int id;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (read(fd, &m, sizeof(m)) > 0) {
        if (m.id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", m.name);
            printf("Enter new rating: ");
            scanf("%f", &m.rating);

            lseek(fd, -sizeof(m), SEEK_CUR);
            write(fd, &m, sizeof(m));

            printf("Record updated!\n");
            close(fd);
            return;
        }
    }

    printf("Movie not found!\n");
    close(fd);
}

// Delete record (mark as deleted)
void deleteMovie() {
    int fd = open("movies.dat", O_RDWR);
    struct movie m;
    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (read(fd, &m, sizeof(m)) > 0) {
        if (m.id == id) {
            m.id = -1;  // mark as deleted

            lseek(fd, -sizeof(m), SEEK_CUR);
            write(fd, &m, sizeof(m));

            printf("Record deleted!\n");
            close(fd);
            return;
        }
    }

    printf("Movie not found!\n");
    close(fd);
}

// Count records
void countMovies() {
    int fd = open("movies.dat", O_RDONLY);
    struct movie m;
    int count = 0;

    while (read(fd, &m, sizeof(m)) > 0) {
        if (m.id != -1)
            count++;
    }

    printf("Total Movies: %d\n", count);
    close(fd);
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n--- Movie Management ---\n");
        printf("1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Search Movie\n");
        printf("4. Update Movie\n");
        printf("5. Delete Movie\n");
        printf("6. Count Movies\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMovie(); break;
            case 2: displayMovies(); break;
            case 3: searchMovie(); break;
            case 4: updateMovie(); break;
            case 5: deleteMovie(); break;
            case 6: countMovies(); break;
            case 7: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}













