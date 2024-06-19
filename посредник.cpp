#include <iostream>
#include <string>
#include <vector>

// Абстрактный класс Посредник
class Mediator {
public:
    virtual void notify(const std::string& sender, const std::string& event) = 0;
    virtual ~Mediator() {}
};

// Абстрактный класс Компонент
class Component {
protected:
    Mediator* mediator;
public:
    Component(Mediator* med = nullptr) : mediator(med) {}
    void setMediator(Mediator* med) {
        mediator = med;
    }
};

// Конкретный класс File, представляющий файл
class File : public Component {
private:
    std::string filename;
public:
    File(Mediator* med = nullptr) : Component(med) {}

    void open(const std::string& filename) {
        this->filename = filename;
        std::cout << "Opening file: " << filename << std::endl;
        if (mediator) {
            mediator->notify("File", "open");
        }
    }

    void edit() {
        std::cout << "Editing file: " << filename << std::endl;
        if (mediator) {
            mediator->notify("File", "edit");
        }
    }

    void print() {
        std::cout << "Printing file: " << filename << std::endl;
        if (mediator) {
            mediator->notify("File", "print");
        }
    }
};

// Конкретный класс Highlighter, представляющий подсветку текста
class Highlighter : public Component {
public:
    Highlighter(Mediator* med = nullptr) : Component(med) {}

    void highlight(const std::string& text) {
        std::cout << "Highlighting text: " << text << std::endl;
        if (mediator) {
            mediator->notify("Highlighter", "highlight");
        }
    }
};

// Конкретный класс TextEditor, представляющий текстовый редактор
class TextEditor : public Mediator {
private:
    File* file;
    Highlighter* highlighter;
public:
    TextEditor() {
        file = new File(this);
        highlighter = new Highlighter(this);
    }

    void notify(const std::string& sender, const std::string& event) override {
        if (sender == "File" && event == "open") {
            std::cout << "Mediator reacts to File open and triggers highlighter." << std::endl;
            highlightText("File content to highlight.");
        }
        // Другие условия для уведомлений можно добавить здесь
    }

    void openFile(const std::string& filename) {
        file->open(filename);
    }

    void editFile() {
        file->edit();
    }

    void printFile() {
        file->print();
    }

    void highlightText(const std::string& text) {
        highlighter->highlight(text);
    }

    ~TextEditor() {
        delete file;
        delete highlighter;
    }
};

// Главная функция, демонстрирующая использование паттерна "Посредник"
int main() {
    TextEditor editor;

    editor.openFile("example.txt");
    editor.editFile();
    editor.printFile();
    editor.highlightText("This is some text to highlight.");

    return 0;
}
