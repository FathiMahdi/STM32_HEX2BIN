#include <stdio.h>
#include <stdlib.h>

// Function to convert a single ASCII character to its corresponding integer value
int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') 
    {
        return c - '0';
    } 
    
    else if (c >= 'A' && c <= 'F') 
    {
        return 10 + (c - 'A');
    } 
    
    else if (c >= 'a' && c <= 'f')
    {
        return 10 + (c - 'a');
    } 
    
    else 
    {
        return -1;  // Invalid character
    }
}

// Function to convert a two-character HEX string to its corresponding integer value
int hexStrToByte(const char* hex) 
{
    return (hexCharToInt(hex[0]) << 4) | hexCharToInt(hex[1]);
}

int main() 
{
    FILE *inputFile, *outputFile;
    char line[100];
    
    // Open the HEX file for reading
    inputFile = fopen("input.hex", "r");
    if (inputFile == NULL) 
    {
        perror("Error opening input file");
        return 1;
    }

    // Open the binary file for writing
    outputFile = fopen("output.bin", "wb+");
    if (outputFile == NULL) 
    {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    while (fgets(line, sizeof(line), inputFile)) 
    {
        // Check if the line starts with a colon (indicating an Intel HEX record)
        if (line[0] == ':') 
        {
            // Parse the HEX record
            int dataLength = hexStrToByte(line + 1);
            int address = (hexStrToByte(line + 3) << 8) | hexStrToByte(line + 5);
            int recordType = hexStrToByte(line + 7);

            // Process data records (recordType == 0)
            if (recordType == 0) 
            {
                for (int i = 0; i < dataLength; i++) 
                {
                    int byte = hexStrToByte(line + 9 + i * 2);
                    fputc(byte, outputFile);
                }
            }
            // You can handle other record types (e.g., end of file, extended segments, etc.) if needed.

        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion completed successfully.\n");

    return 0;
}
