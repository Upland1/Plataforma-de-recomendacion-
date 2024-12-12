#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include "ArregloDinamico.hpp"

class Movie{
public:
    std::string title;
    std::string genres;
    int releaseYear;
    double ratingAvg;
    ArregloDinamico<std::string> genres_sep;

    // Constructores
    Movie() : title(""), genres(""), releaseYear(0), ratingAvg(0.0) { separateGenres(); }
    Movie(const std::string &t, const std::string &g, int r, double rg) : title(t), genres(g), releaseYear(r), ratingAvg(rg) { separateGenres(); }

    //sobrecarga < y > para comparar
    bool operator>(const Movie& other) const {
        std::string genre1 = genres.substr(0, genres.find(','));
        std::string genre2 = other.genres.substr(0, other.genres.find(','));
        return genre1 > genre2;
    }

    bool operator<(const Movie& other) const {
        std::string genre1 = genres.substr(0, genres.find(','));
        std::string genre2 = other.genres.substr(0, other.genres.find(','));
        return genre1 < genre2;
    }
    
    // Sobrecargar << para imprimir
    friend std::ostream &operator<<(std::ostream &os, const Movie &movie)
    {
        os << "Titulo: " << movie.title << ", Generos: " << movie.genres << ", Anio de lanzamiento: " << movie.releaseYear
           << ", Calificacion (IMDB): " << movie.ratingAvg;
        return os;
    }
    
private:

    void separateGenres(){
        std::istringstream stream(genres);
        std::string genre;

        while(std::getline(stream, genre, ',')){
            genres_sep.push_back(genre);
        }
    }

};

class Serie{
public:
    std::string title;
    std::string genres;
    int releaseYear;
    double ratingAvg;
    ArregloDinamico<std::string> genres_sep;

    // Constructores
    Serie() : title(""), genres(""), releaseYear(0), ratingAvg(0.0) { separateGenres(); }
    Serie(const std::string &t, const std::string &g, int r, double rg) : title(t), genres(g), releaseYear(r), ratingAvg(rg) { separateGenres();}

    //sobrecarga < y > para comparar
    bool operator>(const Serie& other) const {
        std::string genre1 = genres.substr(0, genres.find(','));
        std::string genre2 = other.genres.substr(0, other.genres.find(','));
        return genre1 > genre2;
    }

    bool operator<(const Serie& other) const {
        std::string genre1 = genres.substr(0, genres.find(','));
        std::string genre2 = other.genres.substr(0, other.genres.find(','));
        return genre1 > genre2;
    }

    // Sobrecargar << para imprimir
    friend std::ostream &operator<<(std::ostream &os, const Serie &serie)
    {
        os << "Titulo: " << serie.title << ", Generos: " << serie.genres << ", Anio de lanzamiento: " << serie.releaseYear
           << ", Calificacion (IMDB): " << serie.ratingAvg;
        return os;
    }

private:

    void separateGenres(){
        std::istringstream stream(genres);
        std::string genre;

        while(std::getline(stream, genre, ',')){
            genres_sep.push_back(genre);
        }
    }

};



#endif