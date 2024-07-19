#include "CSQL.h"

CSQL::CSQL(const string &host, const string &user, const string &password, const string &database)
{
    try{
        //Connexion et utiisation des driver à la BDD
        driver = sql::mysql::get_driver_instance();
        con = driver->connect(host, user, password);
        con->setSchema(database);
    }
    //Gestion des erreurs
    catch(sql::SQLException& e){
        std::cerr<< "Erreur lors de la connexion à la base de données : " << e.what() << std::endl;
        exit(1);
    }
}

CSQL::~CSQL()
{
 delete con;
}

void CSQL::innsertPerson(const string &name, int age)
{
    try {
        pstmt = con->prepareStatement("INSERT INTO PERSON (NAME, AGE) VALUES (?, ?)");
        pstmt->setString(1, name);
        pstmt->setInt(2, age);
        pstmt->execute();
        delete pstmt;
    } catch (sql::SQLException& e) {
        std::cerr << "Erreur lors de l'insertion des données : " << e.what() << std::endl;
    }
}

void CSQL::selectPerson()
{
    try{
    pstmt = con->prepareStatement("SELECT * FROM PERSON");
    sql::ResultSet* res = pstmt->executeQuery();

    while(res->next()){
        std::cout << "ID: " << res->getInt("ID") << ", ";
        std::cout << "Name: " << res->getString("NAME") << ", ";
        std::cout << "Age: " << res->getInt("AGE") << std::endl;
    }
    delete res;
    delete pstmt;
    }
    catch(sql::SQLException& e){
        std::cerr<<e.what()<<std::endl;
    }
    
}
