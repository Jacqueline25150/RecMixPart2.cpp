#include <iostream>
#include <string>
using namespace std;

// ==========================================
// Part 1 — Design the Abstract Media Class
// ==========================================
class Media {
protected:
    string title;
    string creator;
    int duration; // Length in seconds

public:
    Media(string t, string c, int d) 
        : title(t), creator(c), duration(d) {}

    virtual ~Media() {}

    string getTitle() const {
        return title;
    }

    virtual void displayInfo() const = 0;
    virtual void play() const = 0;

    // Part 3: Overloaded equality operator to compare object titles
    bool operator==(const Media& other) const {
        return this->title == other.title;
    }
};

// ==========================================
// Part 2 — Create Three Media Types
// ==========================================

// Derived Class: Song
class Song : public Media {
private:
    string genre;

public:
    Song(string t, string c, int d, string g)
        : Media(t, c, d), genre(g) {}

    void displayInfo() const override {
        cout << "[SONG]\n"
             << "Title: " << title << "\n"
             << "Artist: " << creator << "\n"
             << "Genre: " << genre << "\n";
    }

    void play() const override {
        cout << "Now playing: " << title << "\n\n";
    }
};

// Derived Class: Podcast
class Podcast : public Media {
private:
    int episodeNumber;

public:
    Podcast(string t, string c, int d, int e)
        : Media(t, c, d), episodeNumber(e) {}

    void displayInfo() const override {
        cout << "[PODCAST]\n"
             << "Title: " << title << "\n"
             << "Host: " << creator << "\n"
             << "Episode: " << episodeNumber << "\n";
    }

    void play() const override {
        cout << "Playing podcast: " << title << "\n\n";
    }
};

// Derived Class: Audiobook
class Audiobook : public Media {
private:
    string narrator;

public:
    Audiobook(string t, string c, int d, string n)
        : Media(t, c, d), narrator(n) {}

    void displayInfo() const override {
        cout << "[AUDIOBOOK]\n"
             << "Title: " << title << "\n"
             << "Author: " << creator << "\n"
             << "Narrator: " << narrator << "\n";
    }

    void play() const override {
        cout << "Playing audiobook: " << title << "\n\n";
    }
};

// ==========================================
// Part 2 — Function Overloading (Searching)
// ==========================================

// Original string title search function
int searchMedia(Media* library[], int size, const string& target) {
    for (int i = 0; i < size; i++) {
        if (library[i]->getTitle() == target) {
            return i;
        }
    }
    return -1;
}

// Overloaded integer index search function
Media* searchMedia(Media* library[], int size, int index) {
    if (index >= 0 && index < size) {
        return library[index];
    }
    return nullptr;
}

// ==========================================
// Part 4 — Generic Playlist Template
// ==========================================
template <typename T>
class Playlist {
private:
    T items[10];
    int count;

public:
    Playlist() : count(0) {}

    void addItem(T item) {
        if (count < 10) {
            items[count] = item;
            count++;
        }
    }

    void displayPlaylist() const {
        for (int i = 0; i < count; i++) {
            // Because our playlist stores pointers, we use the arrow operator
            items[i]->displayInfo();
            items[i]->play();
        }
    }

    int getCount() const {
        return count;
    }
};

// ==========================================
// Part 5 — Main Program Flow & Demonstration
// ==========================================
int main() {
    const int SIZE = 5;
    Media* library[SIZE] = {};

    // Populating the media library array
    library[0] = new Song("Blinding Lights", "The Weeknd", 200, "Synth-pop");
    library[1] = new Song("Levitating", "Dua Lipa", 203, "Pop");
    library[2] = new Podcast("Tech Talk", "Alex Morgan", 1800, 12);
    library[3] = new Podcast("Science Weekly", "Jordan Lee", 2400, 8);
    library[4] = new Audiobook("The Time Machine", "H. G. Wells", 14400, "Taylor Brooks");

    cout << "=== RECMIX PART 2 ===\n\n";

    // ------------------------------------------
    // Part 2 Demonstration: Function Overloading
    // ------------------------------------------
    cout << "=== FUNCTION OVERLOADING ===\n";
    
    // Test 1: Title Search
    string searchTitle = "Blinding Lights";
    cout << "Searching for: " << searchTitle << "\n";
    int foundIndex = searchMedia(library, SIZE, searchTitle);
    if (foundIndex != -1) {
        cout << "Found at index: " << foundIndex << "\n\n";
    } else {
        cout << "Not found.\n\n";
    }

    // Test 2: Valid Index Search
    int validIdx = 2;
    cout << "Searching index: " << validIdx << "\n";
    Media* itemPtr = searchMedia(library, SIZE, validIdx);
    if (itemPtr != nullptr) {
        cout << "Found: " << itemPtr->getTitle() << "\n\n";
    } else {
        cout << "Invalid index.\n\n";
    }

    // Test 3: Invalid Index Search
    int invalidIdx = 15;
    cout << "Searching index: " << invalidIdx << "\n";
    Media* invalidPtr = searchMedia(library, SIZE, invalidIdx);
    if (invalidPtr != nullptr) {
        cout << "Found: " << invalidPtr->getTitle() << "\n\n";
    } else {
        cout << "Invalid index.\n\n";
    }

    // ------------------------------------------
    // Part 3 Demonstration: Operator Overloading
    // ------------------------------------------
    cout << "=== OPERATOR OVERLOADING ===\n";
    cout << "Comparing media items...\n";
    
    // Testing using the required dereferenced object check pattern
    if (*library[0] == *library[1]) {
        cout << "These items have the same title.\n\n";
    } else {
        cout << "These items have different titles.\n\n";
    }

    // Challenge: Two unique objects sharing the same title
    Media* duplicateSong = new Song("Tech Talk", "Guest Host", 1500, "Tech");
    if (*library[2] == *duplicateSong) {
        cout << "Challenge Success: Overloaded operator matched distinct objects with identical title [Tech Talk].\n\n";
    }
    delete duplicateSong; // Clean up challenge allocation right away

    // ------------------------------------------
    // Parts 4 & 5 Demonstration: Playlist & Polymorphism
    // ------------------------------------------
    cout << "=== FAVORITES PLAYLIST ===\n";

    // Instantiating the Generic Template with a base pointer configuration
    Playlist<Media*> favorites;

    // Populating playlist matching parameters: 2 songs, 1 podcast, 1 audiobook
    favorites.addItem(library[0]); // Song
    favorites.addItem(library[2]); // Podcast
    favorites.addItem(library[4]); // Audiobook

    // Executing the polymorphic list loop internally
    favorites.displayPlaylist();

    cout << "Total playlist items: " << favorites.getCount() << "\n";

    // ------------------------------------------
    // Memory Management: Cleanup
    // ------------------------------------------
    for (int i = 0; i < SIZE; i++) {
        delete library[i];
        library[i] = nullptr;
    }

    return 0;
}
