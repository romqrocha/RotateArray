#include <stdio.h>
#include <stdlib.h>

void rotateArray(int arr[10][10], int n, int rows, int cols) {
    // Calculate the number of clockwise 90-degree rotations necessary
    int rotations = (n / 90) % 4;
    if (rotations < 0) {
        rotations += 4;
    }

    // Rotate the array as many times as necessary (min 0, max 3)
    int rotated[rows][cols];
    while (rotations) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                rotated[c][rows - r - 1] = arr[r][c];
            }
        }
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                arr[r][c] = rotated[r][c];
            }
        }

        rotations--;
    }

    // Output the rotated array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = 0;
    int dimensions = 0;
    int arr[10][10] = {0};  // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the first line for angle of rotation and second line for array dimensions
    fscanf(file, "%d", &rotationAngle);
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; //To skip first two lines in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E') {
        if (inputChar == '\n'){counter++;}
        if (inputChar == '\n' && counter>=2) {
            rows++;
            cols = 0;
        } else if (cols < 10 && inputChar >= '0' && inputChar <= '9') {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);
    // Actual dimensions of the input array
    rows = cols = dimensions;

    printf("Input array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}
