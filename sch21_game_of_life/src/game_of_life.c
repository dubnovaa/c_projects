#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALIVE 'K'
#define DEATH ' '
#define HEIGHT 25
#define WIDTH 80
#define SPEED_UP 'k'
#define SPEED_DOWN 'm'
#define EXIT_SYMBOL 'q'
#define ASCII_DIFF 32

int input(int rows, int cols, int **data);
void output(int rows, int cols, int **array);
int count_neighbours(int **matrix, int row, int column);

void fill_next_step(int **matrix, int **matrix_next);
void change_speed(double *sleep_const, int input_character);
void draw(int **matrix);
void to_lower_case(int *input);
void read_from_stdin(int **matrix);
void readMap(int **matrix, int choice);
int print_menu(void);

int main() {
  int flag = 1;
  double speed = 1;
  int is_running = 1;
  double speed_control = 1;
  int *field[HEIGHT + WIDTH * HEIGHT];
  int *pointers = (int *)(field + HEIGHT);
  for (int i = 0; i < HEIGHT; i++) {
    field[i] = pointers + WIDTH * i;
  }
  int *matrix_next[HEIGHT + WIDTH * HEIGHT];
  int *pointers3 = (int *)(matrix_next + HEIGHT);
  for (int i = 0; i < HEIGHT; i++) {
    matrix_next[i] = pointers3 + WIDTH * i;
  }
  int choice = print_menu();
  if (choice == 6) {
    read_from_stdin(field);
  } else {
    readMap(field, choice);
  }
  initscr();
  noecho();
  halfdelay(1);
  draw(field);
  while (is_running) {
    int input_character;
    input_character = getch();
    to_lower_case(&input_character);
    if (input_character == EXIT_SYMBOL) {
      is_running = 0;
    } else {
      change_speed(&speed, input_character);
      if (speed_control > 1) {
        if (flag == 1) {
          fill_next_step(field, matrix_next);
          clear();
          draw(matrix_next);
          refresh();
        } else if (flag == -1) {
          fill_next_step(matrix_next, field);
          clear();
          draw(field);
          refresh();
        }
        speed_control = 0;
        flag = flag * -1;
      }
      speed_control += 0.005 * speed * speed;
    }
  }
  endwin();

  return 0;
}

void change_speed(double *sleep_const, int input_character) {
  if (input_character == SPEED_UP && *sleep_const < 15) {
    *sleep_const += 0.45;
  } else if (input_character == SPEED_DOWN && *sleep_const > 1) {
    *sleep_const -= 0.2;
  }
}

void to_lower_case(int *input) {
  if ((*input <= 90) && (*input >= 65)) {
    *input = *input + ASCII_DIFF;
  }
}

void read_from_stdin(int **data) {
  char input_str[80];
  for (int row = 0; row < HEIGHT; row++) {
    scanf("%79s", input_str);
    for (int col = 0; col < WIDTH; col++) {
      if (input_str[col] != '\n') {
        if (input_str[col] == '1') {
          data[row][col] = 1;
        } else {
          data[row][col] = 0;
        }
      }
    }
  }
}

int count_neighbours(int **matrix, int row, int column) {
  int nbrs = 0;
  int rows[3] = {row - 1, row, row + 1};
  int columns[3] = {column - 1, column, column + 1};

  if (row == 0) {
    rows[0] = HEIGHT - 1;
  }
  if (row == HEIGHT - 1) {
    rows[2] = 0;
  }
  if (column == 0) {
    columns[0] = WIDTH - 1;
  }
  if (column == WIDTH - 1) {
    columns[2] = 0;
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if ((rows[i] != row || columns[j] != column) &&
          matrix[rows[i]][columns[j]] == 1) {
        nbrs++;
      }
    }
  }
  return nbrs;
}

void fill_next_step(int **matrix, int **matrix_next) {
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (matrix[row][col] == 1) {
        if (count_neighbours(matrix, row, col) < 2 ||
            count_neighbours(matrix, row, col) > 3) {
          matrix_next[row][col] = 0;
        }

        if (count_neighbours(matrix, row, col) == 2 ||
            count_neighbours(matrix, row, col) == 3) {
          matrix_next[row][col] = 1;
        }
      } else if (matrix[row][col] == 0) {
        if (count_neighbours(matrix, row, col) == 3) {
          matrix_next[row][col] = 1;
        } else {
          matrix_next[row][col] = 0;
        }
      }
    }
  }
}

void draw(int **matrix) {
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (matrix[row][col] == 1) {
        attron(COLOR_PAIR(1));
        printw("%c", ALIVE);
      } else {
        attron(COLOR_PAIR(2));
        printw("%c", DEATH);
      }
    }
    printw("\n");
  }
  printw("\n");
  attron(COLOR_PAIR(3));
  printw("    To quit press - 'q'   To speed up press - 'k'   To speed down "
         "press - 'm'\n");
}

int print_menu() {
  int choice = 0;
  printf("   __            _    _   _      ___  _  _ \n");
  printf("  /__  /\\  |\\/| |_   / \\ |_   |   |  |_ |_ \n");
  printf("  \\_| /--\\ |  | |_   \\_/ |    |_ _|_ |  |_ \n");

  printf("\n");
  printf("Choose a start position of a game:\n");
  printf("1. Vertical spaceship\n");
  printf("2. Gun\n");
  printf("3. Random\n");
  printf("4. Butterfly\n");
  printf("5. Horizontal spaceship\n");
  printf("6. Custom matrix\n");
  printf("> ");
  while (scanf("%d", &choice) != 1) {
    if (scanf("%d", &choice) != 1) {
      printf("Incorrect input!\n");
      printf("> ");
      while (fgetc(stdin) != '\n')
        continue;
    }
  }
  return choice;
}

void readMap(int **matrix, int choice) {
  char input_value = 0;
  FILE *fPointer;
  if (choice == 1) {
    fPointer = fopen("data1.txt", "r");
  } else if (choice == 2) {
    fPointer = fopen("data2.txt", "r");
  } else if (choice == 3) {
    fPointer = fopen("data3.txt", "r");
  } else if (choice == 4) {
    fPointer = fopen("data4.txt", "r");
  } else if (choice == 5) {
    fPointer = fopen("data5.txt", "r");
  }
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH + 1; col++) {
      fscanf(fPointer, "%c", &input_value);
      if (input_value == '1') {
        matrix[row][col] = 1;
      } else {
        matrix[row][col] = 0;
      }
    }
  }
  fclose(fPointer);
}
