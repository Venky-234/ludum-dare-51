void init_object(
    const char* file_name,
    Vector2 position,
    game_object* game_object_pointer,
    bool hide,
    int col
);

void mov_object(
    game_object* game_object_pointer,
    float speed,
    int keystrokes[4]
);

bool checkCollision(
    game_object* go1,
    game_object* go2
);
bool checkTime(double timeSinceLastCall);
void random_coordinates(game_object* gjp, int min, int max);
void startMenu();