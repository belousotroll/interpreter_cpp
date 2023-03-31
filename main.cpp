#include <iostream>
#include <type_traits>

#include <Interpreter.h>

#include <Content/Content.h>
#include <Formats/Formats.h>
#include <Storage/Storage.h>

using Storage = List<content::Content>;

int main() {
    auto storage = Storage{};

    auto interpreter = Interpreter<Storage>{};
    interpreter(storage, "ADD Plane (1, 2) (3, 6)");
    interpreter(storage, "ADD Plane (1, 2) (3, 6)");
    interpreter(storage, "PRINT");

    return 0;
}


