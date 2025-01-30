# vector

Реализация шаблонного класса vector с соблюдением гарантий безопасности

# Introduction

vector – шаблонный контейнер в стиле STL

Данный проект представляет собой реализацию шаблонного контейнера vector, повторяющего поведение std::vector из стандартной библиотеки C++. Реализация включает:

✅ Динамическое управление памятью с использованием аллокации и освобождения ресурсов через allocator.

✅ Гарантии безопасности исключений, включая strong exception safety при изменении размера контейнера.

✅ Оптимизацию перемещения (move-конструктор и move-оператор присваивания).

✅ Эффективные операции вставки, удаления и доступа к элементам.

✅ Поддержку итераторов для работы с алгоритмами STL.

Этот проект полезен для изучения работы стандартных контейнеров, управления памятью в C++ и шаблонного программирования. 🚀
