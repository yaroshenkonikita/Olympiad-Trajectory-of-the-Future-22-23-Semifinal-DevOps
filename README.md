## Задание

Выполнение задания от эксперта по теме DevOps. Полуфинал Олимпиады "Траектория Будущего" 2022-2023 гг. \
Определить на неком шахматном поле наличие угроз у белого короля от черной ладьи или слона. \
По выполнению задания сформировать отчет по описанию из файла pdf в директории materials/task.

## Стек

Во время разработки будет использоваться стек: \
Язык разработки: C++; \
Операционная система: Ubuntu Server 20.04 LTS; \
Система контроля версий: Git, платформа GitLab; \
Система автоматизации локальных действий: Make; \
Система автоматизации: GitLab-CI; \
Библиотека для написания тестов: GTest; \
Средства автоматизированного создания документации: Doxygen; \
Система хранения тестовых данных: PostgreSQL.

На виртуальной машине должен быть создан пользователь gitlab-runner и установлен сам gitlab-runner. Через sudo зарегистрировать раннер к проекту. \
У пользователя gitlab-runner должны быть зависимости: postgresql, postgresql-contrib, make, g++, \
clang-format, pkg-config, doxygen, libpqxx-dev, libgtest-dev, lcov. Так же через chown нужно дать доступ к директории /usr/lib. \
В psql(postgresql) должен быть добавлен пользователь gitlab-runner как superuser с паролем '1'.

Стандарт компиляции исходного кода C++17. \
Doxyfile версия 1.9.5 \
Версии всего ПО явно не указанного в проекте latest. \
Стиль кода - Google style.

## Решение

Отчет помещен в директорию materials/report. \
Исходный код находится в директорию src. \
Цели make для сборки проекта: \
chess.so - собирает математическую часть проекта в виде динамической библиотеки; \
test - собирает решение проекта с математической частью и запускает тестирование; \
gcov_report - собирает отчет об покрытии кода тестами; \
style - корректирует исходные файлы .cpp/.h с соответствием Google style; \
dvi - собирает документацию из комментариев в файлах .h; \
dist - архивирует весь исходный код; \
clean - очищает репозиторий от всего что сгенирировали цели выше.