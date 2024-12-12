# Streaming-Recommendation-Platform
A platform developed in C++ to recommend movies and series based on user preferences and content similarities.

Built a recommendation engine using a similarity graph, assigning weights between 0 (highly similar) and 1 (minimally similar), with 999 indicating no similarity.

Filtered connections to include only movies with a release date gap ≤10 years and rating differences ≤2 points. Highly similar content (difference <0.2) was treated as neighboring nodes in the graph.

Utilized dynamic arrays to store and manage movie and series data, categorized by genre and subgenre.

Implemented AVL trees for efficient insertion, deletion, and searching of movies and series
