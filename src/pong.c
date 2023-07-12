#include <stdio.h>
void render_field(int height, int width, int racket_1_x, int racket_2_x, int racket_1_y, int racket_2_y,
                  int ball_move_x, int ball_move_y, int player1, int player2);
int vector_ball_y(int ball_move_y, int height, int vector_y);
int vector_ball_x(int ball_move_x, int ball_move_y, int racket_1_y, int racket_2_y, int vector_x);
int racket_right(char button, int racket_2_y, int height);
int racket_left(char button, int racket_1_y, int height);

int main() {
    // Переменные для отображения
    int height = 25, width = 80;
    int racket_1_x = 2, racket_1_y = height / 2;
    int racket_2_x = width - 3, racket_2_y = height / 2;
    int ball_start_x = width / 2, ball_start_y = height / 2;
    int ball_move_x = ball_start_x, ball_move_y = ball_start_y;
    int win = 21;
    int player_1 = 0, player_2 = 0;
    int vector_x = 1, vector_y = 1;

    while (player_1 != win || player_2 != win) {
        printf("\033[1;1H\033[2J");
        render_field(height, width, racket_1_x, racket_2_x, racket_1_y, racket_2_y, ball_move_x, ball_move_y,
                     player_1, player_2);

        vector_y = vector_ball_y(ball_move_y, height, vector_y);
        vector_x = vector_ball_x(ball_move_x, ball_move_y, racket_1_y, racket_2_y, vector_x);

        // Возращение мяча после забиваний игроков
        if (ball_move_x >= 77) {
            player_1++;
            ball_move_x = ball_start_x;
            ball_move_y = ball_start_y;
            vector_x = -vector_x;
            vector_y = -vector_y;
        } else if (ball_move_x <= 2) {
            player_2++;
            ball_move_x = ball_start_x;
            ball_move_y = ball_start_y;
            vector_x = -vector_x;
            vector_y = -vector_y;
        }
        ball_move_x += vector_x;
        ball_move_y += vector_y;
        char button = getchar();
        racket_2_y = racket_right(button, racket_2_y, height);
        racket_1_y = racket_left(button, racket_1_y, height);

        if (player_1 == win) {
            printf("Celebrities player %d win!!!", 1);
            break;
        } else if (player_2 == win) {
            printf("Celebrities player %d win!!!", 2);
            break;
        }
    }
    return 0;
}

// Отрисовка поля
void render_field(int height, int width, int racket_1_x, int racket_2_x, int racket_1_y, int racket_2_y,
                  int ball_move_x, int ball_move_y, int player1, int player2) {
    int score_1_x = 33;
    int score_2_x = 47;
    int score_y = 3;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (((racket_1_x == x) && (racket_1_y - 1 == y || racket_1_y == y || racket_1_y + 1 == y)) ||
                ((racket_2_x == x) && (racket_2_y - 1 == y || racket_2_y == y || racket_2_y + 1 == y))) {
                printf("|");
            } else if (ball_move_x == x && ball_move_y == y) {
                printf("o");
            } else if (((y == 0)) || (y == height - 1)) {
                printf("-");
            } else if ((x == 0) || (x == width - 1 && y != 3) || ((x == width / 2) && (y != 3)) ||
                       (x == width - 1 && y == 3)) {
                printf("|");
            } else if ((x == width / 2 && y != 3) || (y == 3 && x == width / 2)) {
                printf("|");
            } else if (x == score_1_x && y == score_y) {
                printf("%02d", player1);
                x++;
            } else if (x == score_2_x && y == score_y) {
                printf("%02d", player2);
                x++;
            } else
                printf(" ");
        }
        printf("\n");
    }
}

// Смена направления мяча при отстоке от ракеток
int vector_ball_x(int ball_move_x, int ball_move_y, int racket_1_y, int racket_2_y, int vector_x) {
    if (ball_move_x == 3 &&
        (racket_1_y - 1 == ball_move_y || racket_1_y == ball_move_y || racket_1_y + 1 == ball_move_y)) {
        return vector_x = -vector_x;
    } else if (ball_move_x == 76 && (racket_2_y - 1 == ball_move_y || racket_2_y == ball_move_y ||
                                     racket_2_y + 1 == ball_move_y)) {
        return vector_x = -vector_x;
    } else {
        return vector_x;
    }
}

int vector_ball_y(int ball_move_y, int height, int vector_y) {
    if (ball_move_y == 1 || ball_move_y == height - 2) {
        return vector_y = -vector_y;
    } else {
        return vector_y;
    }
}

int racket_left(char button, int racket_1_y, int height) {
    if ((button == 'a' || button == 'A') && racket_1_y - 1 != 1) {
        return racket_1_y = racket_1_y - 1;
    } else if ((button == 'z' || button == 'Z') && racket_1_y + 1 != height - 2) {
        return racket_1_y += 1;
    } else {
        return racket_1_y;
    }
}
int racket_right(char button, int racket_2_y, int height) {
    if ((button == 'k' || button == 'K') && racket_2_y - 1 != 1) {
        return racket_2_y -= 1;
    } else if ((button == 'm' || button == 'M') && racket_2_y + 1 != height - 2) {
        return racket_2_y += 1;
    } else {
        return racket_2_y;
    }
}
