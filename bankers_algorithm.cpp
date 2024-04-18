#include <iostream>
#include <fstream>

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

/*-------- Funtion definitions --------*/

// Function to calculate the need matrix
void calculateNeed(int alloc[][NUM_RESOURCES], int max[][NUM_RESOURCES], int need[][NUM_RESOURCES])
{
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_RESOURCES; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
}

// Function to check if a process can request resources safely
bool canRequest(int need[][NUM_RESOURCES], int avail[], int process)
{
    for (int j = 0; j < NUM_RESOURCES; j++)
    {
        if (need[process][j] > avail[j])
            return false;
    }
    return true;
}

// Function to find a safe sequence
void findSafeSequence(int alloc[][NUM_RESOURCES], int max[][NUM_RESOURCES], int need[][NUM_RESOURCES], int avail[], int finished[], int answer[])
{
    int index = 0;
    for (int k = 0; k < NUM_PROCESSES; k++)
    {
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            if (finished[i] == 0 && canRequest(need, avail, i))
            {
                answer[index++] = i;
                for (int y = 0; y < NUM_RESOURCES; y++)
                    avail[y] += alloc[i][y];
                finished[i] = 1;
            }
        }
    }
}

/*-------- Main driver code --------*/

int main()
{
    // Allocation Matrix
    int alloc[NUM_PROCESSES][NUM_RESOURCES];

    // Max Matrix
    int max[NUM_PROCESSES][NUM_RESOURCES];

    // Available resources
    int avail[NUM_RESOURCES];

    // Open the file
    std::ifstream file("input.txt");
    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read allocation matrix
    for (int i = 0; i < NUM_PROCESSES; i++)
        for (int j = 0; j < NUM_RESOURCES; j++)
            file >> alloc[i][j];

    // Read max matrix
    for (int i = 0; i < NUM_PROCESSES; i++)
        for (int j = 0; j < NUM_RESOURCES; j++)
            file >> max[i][j];

    // Read available resources
    for (int j = 0; j < NUM_RESOURCES; j++)
        file >> avail[j];

    file.close();

    int finished[NUM_PROCESSES], answer[NUM_PROCESSES];
    for (int k = 0; k < NUM_PROCESSES; k++)
        finished[k] = 0;

    // Calculate need matrix
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(alloc, max, need);

    // Find safe sequence
    findSafeSequence(alloc, max, need, avail, finished, answer);

    // Check for safe sequence and print
    int flag = 1;
    for (int i = 0; i < NUM_PROCESSES; i++)
        if (finished[i] == 0)
        {
            flag = 0;
            std::cout << "Sequence isn't safe";
            break;
        }

    if (flag == 1)
    {
        std::cout << "Sequence is safe!\nSafe Sequence: ";
        for (int i = 0; i < NUM_PROCESSES - 1; i++)
            std::cout << " P" << answer[i] << " ->";
        std::cout << " P" << answer[NUM_PROCESSES - 1] << std::endl;
    }

    return 0;
}
