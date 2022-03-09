/*
 * CS 361: Lab02
 *
 * Name: Nic Plybon & Adrien Ponce
 * This code complies with the JMU Honor Code
 */
struct msg {
  char magic[8];
  uint32_t id;
  char now[200];
  char data[36];
};

int main (int argc, char **argv) {

    char* queue_name;

    if (argc != 2) {
        printf("Invalid number of arguments!\n");
        return 1;
    } else {
        // extract filename
        queue_name = argv[1];
    }


}


