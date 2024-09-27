#include "get_next_line.h"

// Read line function
char *ft_read_line(int fd, char *string, char *buffer)
{
    char *tmp;
    int bytes_read;

    while (1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(string);
            return (NULL);
        }

        if (bytes_read == 0) // EOF reached
            break;

        buffer[bytes_read] = '\0';

        if (string == NULL)
            string = ft_strdup("");

        if (!string)
            return (NULL);

        tmp = string;
        string = ft_strjoin(tmp, buffer);
        free(tmp);

        if (!string)
            return (NULL);

        if (ft_strchr(buffer, '\n')) // Newline found
            break;
    }

    return (string);
}

char *ft_extract_line(char *string)
{
    char *line;
    int i = 0;

    if (!string || !*string) // Return NULL for empty strings
        return (NULL);

    while (string[i] != '\0' && string[i] != '\n')
        i++;

    line = malloc((i + 1 + (string[i] == '\n')) * sizeof(char)); // Allocate space for '\0' and '\n' if present
    if (!line)
        return (NULL);

    for (int j = 0; j < i; j++)
        line[j] = string[j];

    if (string[i] == '\n') // Include the newline if present
        line[i++] = '\n';

    line[i] = '\0'; // Null-terminate the line
    return (line);
}

char *ft_update_stash(char *string)
{
    char *new_stash;
    int i = 0, j = 0;

    while (string[i] != '\0' && string[i] != '\n')
        i++;

    // Check if end of string reached, free and return NULL
    if (string[i] == '\0')
    {
        free(string);
        return (NULL);
    }

    new_stash = malloc((ft_strlen(string) - i) * sizeof(char));
    if (!new_stash)
        return (NULL);

    i++; // Skip the newline
    while (string[i] != '\0')
        new_stash[j++] = string[i++];

    new_stash[j] = '\0'; // Null-terminate the new stash
    free(string);
    return (new_stash);
}

// Main function to get the next line
char *get_next_line(int fd)
{
    static char *stash;
    char *line;
    char *buffer;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);

    // Invalid file descriptor or buffer size
    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        free(buffer);
        return (NULL);
    }

    // Read from the file descriptor
    stash = ft_read_line(fd, stash, buffer);
    free(buffer); // Free the buffer after use

    // Handle read errors
    if (!stash)
        return (NULL);

    // Extract the line
    line = ft_extract_line(stash);
    if (!line) // Check if line allocation failed
    {
        free(stash); // Free stash if line allocation failed
        stash = NULL;
        return (NULL);
    }

    // Update the stash
    stash = ft_update_stash(stash);
    return (line);
}

// Implementation of utility function
