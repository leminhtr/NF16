    #ifndef TP3_H_INCLUDED
    #define TP3_H_INCLUDED

    #define STRING_MAX 50
    #define ROOM_MAX 200

    struct Client{
        char* nom;
        char* prenom;
        int age;
        int numero_chambre;
        char *ville_site;
        struct Client* suivant;
    };
    typedef struct Client T_Client;

    struct Site{
        char* ville;
        int nombre_client;
        T_Client* premier;
        struct Site* suivant;
    };
    typedef struct Site T_Site;

    struct Hotel{
        char* nom;
        T_Site * premier;
    };
    typedef struct Hotel T_Hotel;

    T_Client *creerClient(char *nom, char *prenom, int age, int numero_chambre);
    int print_available_room(T_Site *site);
    int search_room_availability(T_Site *site, int numero_ch);
    T_Site *creerSite(char *ville);
    T_Site *rechercherSite(T_Hotel *hotel, char *ville);
    T_Hotel *creerHotel(char *nom);
    int ajouterClient(T_Site *site, T_Client *client);
    int ajouterSite(T_Hotel *hotel, T_Site *site);
    int supprimerClient(T_Site *site, char *nom, char *prenom);
    int supprimerSite(T_Hotel *hotel, char *ville);
    void afficherHotel(T_Hotel *hotel);
    void afficherSite(T_Site *site);
    void rechercherClients(T_Hotel *hotel, char *critereNom);

    #endif // TP3_H_INCLUDED
