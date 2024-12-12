#include "csvreader3.hpp"
#include <chrono>
#define MOVIESANDSERIES "movies_.csv"

int main()
{
    KeyValueAVLTree<std::string, Movie> moviesMap_avl;
    KeyValueAVLTree<std::string, Serie> seriesMap_avl;

    CSVReader3 csvReader3;

    //prueba de rendimiento de arbol
    auto start = std::chrono::high_resolution_clock::now();

    csvReader3.loadMoviesAndSeries(MOVIESANDSERIES, moviesMap_avl, seriesMap_avl);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tiempo de busqueda: " << duration.count() << " ms" << std::endl;

    //Busqueda de productos
    std::string mediaCategory;
    int mediaType;

    std::cout << "Media a buscar por categoria: " << std::endl;
    std::getline(std::cin, mediaCategory);

    std::cout << "Es 1. serie o 2. pelicula?: " << std::endl;
    std::cin >> mediaType;


    // Verificar tipo de medio
    if (mediaType != 1 && mediaType != 2) {
        std::cout << "Tipo de medio no válido. Por favor ingrese 'pelicula' o 'serie'.\n";
        return 1; // Salir si el tipo no es válido
    }

    // Buscar película o serie
    if (mediaType == 2) {
        start = std::chrono::high_resolution_clock::now();
        auto result = csvReader3.allMoviesFromCategory(moviesMap_avl, mediaCategory);
        end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tiempo de busqueda: " << duration.count() << " ms" << std::endl;

        if (result.empty()){
            std::cout << "No existe peliculas del genero " << mediaCategory << std::endl;

        } else{
            std::cout << "Todas las peliculas que son de " << mediaCategory << ": " << std::endl;
            result.print();
        }

    } else if (mediaType == 1) {
        start = std::chrono::high_resolution_clock::now();
        auto result = csvReader3.allSerieFromCategory(seriesMap_avl, mediaCategory);
        end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Tiempo de busqueda: " << duration.count() << " ms" << std::endl;
        
        if (result.empty()){
            std::cout << "No existe series del genero " << mediaCategory << std::endl;

        } else{
            std::cout << "Todas las series que son de " << mediaCategory << ": " << std::endl;
            result.print();

        }
    }



    return 0;

}

