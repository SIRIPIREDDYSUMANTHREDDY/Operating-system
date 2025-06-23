#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main() {
    int source_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }
    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening/creating destination file");
        close(source_fd);
        return 1;
    }
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }
    close(source_fd);
    close(dest_fd);
    printf("File copied successfully.\n");
    return 0;
}