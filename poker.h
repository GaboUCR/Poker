    
    typedef struct carta {
        int valor_carta;
        int tipo_carta;
        int eliminado;
    } carta;

    typedef struct list_node {struct list_node* next; carta* carta;} node;
    
    enum valor_cartas {
        StraightFlush = 1,
        FourOfAKind = 2,
        FullHouse = 3,
        Flush = 4,
        Straight = 5,
        ThreeOfAKind = 6,
        TwoPairs = 7,
        OnePair = 8,
        NoPair = 9,
    };

    enum tipo_carta {
        diamantes=0,
        corazones=1,
        trebol=2,
        espadas=3
    };

    enum Bool {
        True = 1,
        False = 0,
    };

    enum valor_carta {
        A=1,
        dos=2,
        tres=3,
        cuatro=4,
        cinco=5,
        seis=6,
        siete=7,
        ocho=9,
        nueve=9,
        diez=10,
        J=11,
        Q=12,
        K=13
    };

    typedef struct mazo {
        struct carta baraja[52];
        int restantes;
    } mazo;

    typedef struct jugador {
        char * nombre;
        node * mano;
        enum Bool en_ronda;
        int dinero;
    } jugador;

    typedef struct juego {
        node *mesa;
        int bote;
        int cantidad_cartas;
        int apuesta_minima;
        int jugadores_en_ronda;
    } juego;



    node* makeListNode (carta* carta);

    node* sliceList (int start, int end, node* head);

    node* insert (carta carta, node * head);

    void getValue(char key[], node* head);

    int imprimir_carta(carta carta);

    void imprimir_mano (node* mano);
    
    void printList(node* head);
