#include <stdio.h>
#include <stdlib.h>

// Structure for voters
struct node {
    int id;
    int password; // Password as an integer
    struct node* left;
    struct node* right;
};

// Function to create a new voter node
struct node* createVoter(int id, int password) {
    struct node* newVoter = (struct node*)malloc(sizeof(struct node));
    if (newVoter == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed!\n");
    }
    newVoter->id = id;
    newVoter->password = password; // Store password as an integer
    newVoter->left = NULL;
    newVoter->right = NULL;
    return newVoter;
}

// Function to insert a voter into the BST
struct node* insertVoter(struct node* root, int id, int password) {
    if (root == NULL) {
        return createVoter(id, password);
    }
    if (id < root->id) {
        root->left = insertVoter(root->left, id, password);
    } else if (id > root->id) { 
        root->right = insertVoter(root->right, id, password);
    }
    return root;
}

// Function to authenticate a voter
struct node* authenticate(struct node* root, int id, int password) {
    if (root == NULL) {
        return NULL; // Not found
    }
    if (root->id == id && root->password == password) {
        return root; // Successful authentication
    }
    if (id < root->id) {
        return authenticate(root->left, id, password);
    } else {
        return authenticate(root->right, id, password);
    }
}

// Array to hold vote counts for each candidate
int votes[6];

// Function to cast a vote for a candidate
void castVote() {
    int candidateId;
    printf("\nEnter Candidate ID to vote: ");
    scanf("%d", &candidateId);
    if (candidateId >= 1 && candidateId <= 6) {
        votes[candidateId]++; // Increment vote count for the candidate
        printf("Vote cast successfully for Candidate ID: %d!\n", candidateId);
    } else {
        printf("Invalid Candidate ID! Please enter a valid ID.\n");
        castVote(); 
    }
}

// Function to display results and determine the winner
void displayResults() {
    printf("\nVoting Results\n");
    printf("Bhartiya Janta Party: %d votes\n", votes[1]);
    printf("Congress: %d votes\n", votes[2]);
    printf("Aam Admi Party: %d votes\n", votes[3]);
    printf("Bahujan Samaj Party: %d votes\n", votes[4]);
    printf("Others: %d votes\n", votes[5]);
    printf("NOTA: %d votes\n", votes[6]);
}
  
// Main function
int main() {
    struct node* root = NULL; // Root of the BST
    struct node* authenticated = NULL;
    int choice = 0, id = 0;
    int password = 0; // Password as an integer

    // Insert some voters (id, password)
    root = insertVoter(root, 123, 1);
    root = insertVoter(root, 456, 2);
    root = insertVoter(root, 789, 3);

    printf("\nVoting System\n");
    printf("1. Login and Vote\n");
    printf("2. Display Results\n");
    printf("3. Exit\n");
        
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            printf("Enter Voter ID: ");
            scanf("%d", &id);
            printf("Enter Password: ");
            scanf("%d", &password);

             // Authenticate the voter
            authenticated = authenticate(root, id, password);
            if (authenticated != NULL) {
                printf("Login successful!\n");
                printf("Candidate ID 1 for Bhartiya Janta Party\n");
                printf("Candidate ID 2 for Congress\n");
                printf("Candidate ID 3 for Aam Admi Party\n");
                printf("Candidate ID 4 for Bahujan Samaj Party\n");
                printf("Candidate ID 5 for Others\n");
                printf("Candidate ID 6 for NOTA\n");
                    
                castVote(); // Cast the vote
            } else {
                printf("Authentication failed!\n");
            }
            break;
        }
        case 2:
            displayResults();
            break;

        case 3:
            printf("Exiting the voting system. Goodbye!\n");
            return 0;

        default:
        printf("Invalid choice! Please try again.\n");
    }
    return 0;
}





