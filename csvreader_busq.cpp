#include "csvreader3.hpp"
#include "models.hpp"
#define MOVIESANDSERIES "movies_.csv"
#include <chrono>

template <typename T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
int partition(ArregloDinamico<T> &arr, int low, int high)
{
    double pivot = arr[high].ratingAvg; // Elegimos el último elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].ratingAvg <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// quicksort
template <typename T>
void quickSort(ArregloDinamico<T> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Ordenar elementos antes del pivote
        quickSort(arr, pi + 1, high); // Ordenar elementos después del pivote
    }
}

template <typename T>
ArregloDinamico<T> binarySearch_Rating(ArregloDinamico<T> &list, double rating)
{
    ArregloDinamico<T> result;
    int left = 0;
    int right = list.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (list[mid].ratingAvg == rating)
        {
            int index = mid;

            while (index >= 0 && list[index].ratingAvg == rating)
            {
                result.push_back(list[index]);
                --index;
            }

            index = mid + 1;

            while (index < list.size() && list[index].ratingAvg == rating)
            {
                result.push_back(list[index]);
                ++index;
            }

            break;
        }
        else if (list[mid].ratingAvg < rating)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return result;
}

template <typename T>
ArregloDinamico<T> sequentialSearch_Rating(ArregloDinamico<T> &list, double rating)
{
    ArregloDinamico<T> result;
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].ratingAvg == rating)
        {
            result.push_back(list[i]);
        }
    }
    return result;
}

int main()
{

    ArregloDinamico<Movie> moviesMap_Arreglo;
    ArregloDinamico<Serie> seriesMap_Arreglo;

    CSVReader3 csvReader3;

    csvReader3.loadMoviesAndSeries(MOVIESANDSERIES, moviesMap_Arreglo, seriesMap_Arreglo);

    // busqueda secuencial
    auto start = std::chrono::high_resolution_clock::now();

    ArregloDinamico<Movie> result_busq_sec_movie = sequentialSearch_Rating(moviesMap_Arreglo, 8.8);
    ArregloDinamico<Serie> result_busq_sec_serie = sequentialSearch_Rating(seriesMap_Arreglo, 8.8);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Tiempo busqueda secuencial: " << duration_micro.count() << " us" << std::endl;

    // busqueda binaria
    quickSort(moviesMap_Arreglo, 0, moviesMap_Arreglo.size() - 1);
    quickSort(seriesMap_Arreglo, 0, seriesMap_Arreglo.size() - 1);
    start = std::chrono::high_resolution_clock::now();

    // csvReader3.quickSortMovie(moviesMap_Arreglo, 0, moviesMap_Arreglo.size() - 1);
    ArregloDinamico<Movie> result_busq_bin_movie = binarySearch_Rating(moviesMap_Arreglo, 8.8);

    // csvReader3.quickSortSerie(seriesMap_Arreglo, 0, seriesMap_Arreglo.size() - 1);
    ArregloDinamico<Serie> result_busq_bin_serie = binarySearch_Rating(seriesMap_Arreglo, 8.8);

    end = std::chrono::high_resolution_clock::now();
    duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Tiempo busqueda binaria: " << duration_micro.count() << " us" << std::endl;

    return 0;
}