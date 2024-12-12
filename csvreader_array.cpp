#include "csvreader.hpp"
#include "csvreader2.hpp"
#include "csvreader3.hpp"
#include <chrono>
#define MOVIESANDSERIES "movies_.csv"

int main()
{
    ArregloDinamico<Movie> moviesMap_Arreglo;
    ArregloDinamico<Serie> seriesMap_Arreglo;

    CSVReader3 csvReader3;

    //prueba de rendimiento de arreglo
    auto start = chrono::high_resolution_clock::now();

    csvReader3.loadMoviesAndSeries(MOVIESANDSERIES, moviesMap_Arreglo, seriesMap_Arreglo);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Tiempo insercion Arreglo: " << duration.count() << " ms" << endl;
    
    return 0;
}

