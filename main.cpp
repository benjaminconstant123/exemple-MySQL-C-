#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <iostream>

int main() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;

        // Création de l'objet driver
        driver = sql::mysql::get_mysql_driver_instance();

        // Connexion à la base de données
        con = driver->connect("tcp://127.0.0.1:3306", "testuser", "password");

        // Sélection de la base de données
        con->setSchema("testdb");

        // Création de la table si elle n'existe pas
        pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS PERSON("
                                      "ID INT PRIMARY KEY AUTO_INCREMENT, "
                                      "NAME VARCHAR(255), "
                                      "AGE INT)");
        pstmt->execute();
        delete pstmt;

        // Préparation de l'insertion de données
        pstmt = con->prepareStatement("INSERT INTO PERSON (NAME, AGE) VALUES (?, ?)");
        pstmt->setString(1, "Alice");
        pstmt->setInt(2, 25);
        pstmt->execute();

        pstmt->setString(1, "Bob");
        pstmt->setInt(2, 30);
        pstmt->execute();

        std::cout << "Données insérées avec succès." << std::endl;

        // Libération des ressources
        delete pstmt;
        delete con;
    } catch (sql::SQLException& e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
