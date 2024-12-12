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
    std::string mediaTitle;
    int mediaType;

    std::cout << "Media a buscar: " << std::endl;
    std::getline(std::cin, mediaTitle);

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
        auto result = moviesMap_avl.find(mediaTitle);

        if (result == nullptr){
            std::cout << "Pelicula no encontrada" << std::endl;
            end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Tiempo de busqueda: " << duration.count() << " us" << std::endl;

        } else{
            std::cout << "Pelicula encontrada: " << result->value << std::endl;
            end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Tiempo de busqueda: " << duration.count() << " us" << std::endl;

        }

    } else if (mediaType == 1) {
        start = std::chrono::high_resolution_clock::now();
        auto result = seriesMap_avl.find(mediaTitle);
        
        if (result == nullptr){
            std::cout << "Serie no encontrada" << std::endl;
            end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Tiempo de busqueda: " << duration.count() << " us" << std::endl;

        } else{
            std::cout << "Serie encontrada: " << result->value << std::endl;
            end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Tiempo de busqueda: " << duration.count() << " us" << std::endl;

        }
    }



    return 0;

}

