struct Usuario {
    int id;
    char nombre[50];
    int vida;
};

struct Dato {
    int id_user;
    char mapa[50];
    int posx;
    int posy;
};

struct Paquete {
    int tipo; //1 dato 2 usuario
    union {
        struct Dato dato;
        struct Usuario usuario;
    };
};