/*
 * 🚨 WARNING: CHALLENGE MODE ACTIVATED 🚨
 * 
 * 1️⃣ Sit back, take a deep breath, and **THINK**.
 * 2️⃣ For the next **10 minutes**, avoid using **Gen AI, ChatGPT, or any shortcuts**.
 * 3️⃣ Trust your **brain**—you’re smarter than you think!
 * 4️⃣ Consider yourself a **LOSER** if you cheat. Seriously, promise yourself you won't. 😤
 * 5️⃣ If you solve it on your own, **you WIN** and level up as a true programmer and come and meet me ! 
 * 
 * 
 * 💡 Remember: The best coders aren’t the ones who copy-paste. They are the ones who **struggle, think, fail, and then succeed.** 
 *    
 * Now, write your code! You got this! 💪🔥
 */

#include <stdio.h>

#define MAX_ROOMS 5  //  max number of rooms

// Function prototypes
void initializeSystem(int lights[], int temps[], int motion[], int locks[], int counters[]);
void displayMenu();
void controlLights(int lights[]);
void readTemperature(int temps[]);
void detectMotion(int motion[], int counters[], int locks[]);
void securitySystem(int locks[]);
void analyzeHouseStatus(int lights[], int temps[], int motion[], int locks[]);

int main() {
    int lights[MAX_ROOMS];
    int temps[MAX_ROOMS];
    int motion[MAX_ROOMS];
    int locks[MAX_ROOMS];
    int counters[2]; 
    

    initializeSystem(lights, temps, motion, locks, counters);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                controlLights(lights);
                counters[1]++; 
                break;
            case 2:
                readTemperature(temps);
                break;
            case 3:
                detectMotion(motion, counters, locks);
                break;
            case 4:
                securitySystem(locks);
                break;
            case 5:
                analyzeHouseStatus(lights, temps, motion, locks);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void initializeSystem(int lights[], int temps[], int motion[], int locks[], int counters[]) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        lights[i] = 0;
        temps[i] = 22 + i; 
        motion[i] = 0;
        locks[i] = 1;
    }
    counters[0] = 0;
    counters[1] = 0;
    printf("System initialized. Lights OFF, Doors LOCKED, No Motion.\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

void controlLights(int lights[]) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", MAX_ROOMS);
    scanf("%d", &room);
    if (room >= 1 && room <= MAX_ROOMS) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number.\n");
    }
}

void readTemperature(int temps[]) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", MAX_ROOMS);
    scanf("%d", &room);
    if (room >= 1 && room <= MAX_ROOMS) {
        printf("Temperature in Room %d is %d°C.\n", room, temps[room - 1]);
        if (temps[room - 1] > 30) {
            printf(" Warning: Temperature above 30°C!\n");
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void detectMotion(int motion[], int counters[], int locks[]) {
    int room, detected;
    printf("Enter room number to update motion (1-%d): ", MAX_ROOMS);
    scanf("%d", &room);
    if (room >= 1 && room <= MAX_ROOMS) {
        printf("Motion detected in Room %d? (1 = Yes, 0 = No): ", room);
        scanf("%d", &detected);
        motion[room - 1] = detected;

        if (detected == 0) {
            counters[0]++;
        } else {
            counters[0] = 0;
        }

        if (counters[0] >= 5) {
            for (int i = 0; i < MAX_ROOMS; i++) {
                locks[i] = 1;
            }
            printf("Auto-lock: No motion for 5 checks. Doors locked.\n");
            counters[0] = 0; 
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void securitySystem(int locks[]) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", MAX_ROOMS);
    scanf("%d", &room);
    if (room >= 1 && room <= MAX_ROOMS) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number.\n");
    }
}

void analyzeHouseStatus(int lights[], int temps[], int motion[], int locks[]) {
    int allLightsOn = 1;
    printf("\nHouse Status:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: Light %s, Temp %d°C, Motion %s, %s\n",
               i + 1,
               lights[i] ? "ON" : "OFF",
               temps[i],
               motion[i] ? "Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");

        if (!lights[i]) {
            allLightsOn = 0;
        }

        if (temps[i] > 30) {
            printf("Room %d temperature is high!\n", i + 1);
        }
    }

    if (allLightsOn) {
        printf("All lights are ON. Consider Energy Saving Mode!\n");
    }
}