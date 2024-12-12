#include "csvreader.hpp"
#include <cstdlib>
#include <iostream>

int main() {

  CSVReader3 csvReader;
  WeightedGraph<Movie> moviesList;
  WeightedGraph<Serie> serieList;

  csvReader.loadMoviesAndSeries("movies_.csv", moviesList, serieList);
  std::cout << "Total de películas cargadas: " << moviesList.getvertex().size()
            << ", Total de series cargadas: " << serieList.getvertex().size()
            << std::endl;

  srand((unsigned)time(NULL));
  int y = 0;

  srand((unsigned)time(NULL));
  int x = rand() % 11000;

  int z = x - 1000;

  if (z < 0) {
    z += 2000;
  }

  if (y == 0) {
    std::cout << "Path desde: " << moviesList.vertex[x].title
              << ", Hasta: " << moviesList.vertex[z].title
              << ", Tipo pelicula. " << std::endl;
    std::vector<Movie> path =
        moviesList.find_path(moviesList.vertex[x], moviesList.vertex[z], "BFS");

    std::cout << "BFS: ";

    for (auto element : path) {
      std::cout << element.title << " -> ";
    }

    std::cout << std::endl;

    // path =
    //     moviesList.find_path(moviesList.vertex[x], moviesList.vertex[z],
    //     "DFS");

    // std::cout << "DFS: ";

    // for (auto element : path) {
    //   std::cout << element.title << " -> ";
    // }

    // std::cout << std::endl;

    // std::cout << "DFS path desde: " << moviesList.vertex[x].title
    //           << ", Tipo pelicula. " << std::endl;
    // path = moviesList.dfs(moviesList.vertex[x]);

    // for (auto element : path) {
    //   std::cout << element.title << " -> ";
    // }

    // std::cout << std::endl;

  } else {
    std::cout << "Path desde: " << serieList.vertex[x].title
              << ", Hasta: " << serieList.vertex[z].title << ", Tipo serie. "
              << std::endl;
    std::vector<Serie> path =
        serieList.find_path(serieList.vertex[x], serieList.vertex[z], "BFS");

    for (auto element : path) {
      std::cout << element.title << " -> ";
    }

    std::cout << std::endl;

    // path = serieList.find_path(serieList.vertex[x], serieList.vertex[z],
    // "DFS");

    // std::cout << "DFS: ";

    // for (auto element : path) {
    //   std::cout << element.title << " -> ";
    // }

    // std::cout << std::endl;
  }

  return 1;
}