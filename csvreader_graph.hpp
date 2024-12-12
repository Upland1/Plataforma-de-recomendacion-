#ifndef CSVREADER3_HPP
#define CSVREADER3_HPP

#include "WeightGraph.hpp"
#include "models.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <future>
#include <sstream>
#include <thread>
#include <vector>

class CSVReader3 {
public:
  // cargar peliculas y series
  void loadMoviesAndSeries(const std::string &filename,
                           WeightedGraph<Movie> &moviesList,
                           WeightedGraph<Serie> &seriesList) {

    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
      return;
    }

    std::string line;
    std::getline(file, line); // Saltar encabezado

    while (std::getline(file, line)) {
      // Reemplazar dobles comillas "" por comillas simples ' para evitar
      // problemas en parsing
      size_t pos = 0;
      while ((pos = line.find("\"\"", pos)) != std::string::npos) {
        line.replace(pos, 2, "'"); // Reemplaza "" con '
        pos += 1;                  // Avanza para evitar un bucle infinito
      }

      std::istringstream ss(line);
      std::string title, type, genres, releaseYear, ratingAvg;

      // Leer el título y manejar posibles comillas
      if (line.front() == '"') {
        std::getline(ss, title, '"');
        std::getline(ss, title, '"'); // Leer entre comillas
        ss.ignore(1);                 // Saltar la coma que sigue
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
      if (title.empty() || type.empty() || genres.empty() ||
          releaseYear.empty() || ratingAvg.empty()) {
        continue;
      }

      try {
        int releaseYear_ = std::stoi(releaseYear);
        double ratingAvg_ = std::stod(ratingAvg);

        if (type == "movie") {
          Movie movie(title, genres, releaseYear_, ratingAvg_);
          moviesList.add_vertex(movie);
          // addedges(moviesList, movie);

        } else if (type == "tv") {
          Serie serie(title, genres, releaseYear_, ratingAvg_);
          seriesList.add_vertex(serie);
          // addedges(seriesList, serie);
        }
      } catch (const std::invalid_argument &e) {
        // std::cerr << "Error de conversión en la línea: " << line << "\n";
      } catch (const std::out_of_range &e) {
        std::cerr << "Número fuera de rango en la línea: " << line << "\n";
      }
    }
    file.close();
  }

};

#endif
