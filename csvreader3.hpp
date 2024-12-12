#ifndef CSVREADER3_HPP
#define CSVREADER3_HPP

#include <fstream>
#include <sstream>
#include "ArregloDinamico.hpp"
#include "models.hpp"

class CSVReader3
{
public:

//cargar peliculas y series
void loadMoviesAndSeries(const std::string &filename, ArregloDinamico<Movie> &moviesList, ArregloDinamico<Serie> &seriesList) {
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Saltar encabezado

    while (std::getline(file, line)) {
        // Reemplazar dobles comillas "" por comillas simples ' para evitar problemas en parsing
        size_t pos = 0;
        while ((pos = line.find("\"\"", pos)) != std::string::npos) {
            line.replace(pos, 2, "'"); // Reemplaza "" con '
            pos += 1; // Avanza para evitar un bucle infinito
        }

        std::istringstream ss(line);
        std::string title, type, genres, releaseYear, ratingAvg;

        // Leer el título y manejar posibles comillas
        if (line.front() == '"') {
            std::getline(ss, title, '"');
            std::getline(ss, title, '"'); // Leer entre comillas
            ss.ignore(1); // Saltar la coma que sigue
        } else {
            std::getline(ss, title, ',');
        }

        // Leer el resto de los datos
        std::getline(ss, type, ',');

        // Leer géneros y manejar posibles comillas
        if (ss.peek() == '"') {
            ss.ignore(1);
            std::getline(ss, genres, '"');
            ss.ignore(1); // Saltar la coma que sigue
        } else {
            std::getline(ss, genres, ',');
        }

        std::getline(ss, releaseYear, ',');
        std::getline(ss, ratingAvg);

        // Validar que no haya campos vacíos
        if (title.empty() || type.empty() || genres.empty() || releaseYear.empty() || ratingAvg.empty()) {
            continue;
        }

        try {
            int releaseYear_ = std::stoi(releaseYear);
            double ratingAvg_ = std::stod(ratingAvg);

            if (type == "movie") {
                moviesList.push_back(Movie(title, genres, releaseYear_, ratingAvg_));
            } else if (type == "tv") {
                seriesList.push_back(Serie(title, genres, releaseYear_, ratingAvg_));
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error de conversión en la línea: " << line << "\n";
        } catch (const std::out_of_range &e) {
            std::cerr << "Número fuera de rango en la línea: " << line << "\n";
        }
    }
    file.close();
}


};

#endif
