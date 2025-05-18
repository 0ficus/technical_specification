## technical_specification

-----

# Описание проекта

При запуске проекта происходит генерация студентов, аудиторий, занятий. Далее появляется рабочее окно, в котором продемонстрирована таблица с аудиториями. Пользователь может узнать, в какое время проходят занятия в выбранной аудитории (также какой предмет, в какое время, какие студенты будут присутствовать) с помощью двойного клика.

----

На локальном устройстве настроен сервер баз данных Firebird 5.

База данных содержит три таблицы: STUDENTS (студенты), LESSONS (занятия), CLASSROOMS (аудитории).

STUDENTS представляет собой:

 
 
| ID (INTEGER PRIMARY KEY)                         |
|----|
| NAME (VARCHAR(50) NOT NULL)                      |
| GROUP_NAME VARCHAR(20)                           |
 

LESSONS представляет собой:

| ID (INTEGER PRIMARY KEY)                         |
 |----|
| CLASSROOM_ID (INTEGER REFERENCES CLASSROOM (ID)) |
| STUDENT_ID (INTEGER REFERENCES STUDENTS (ID)     |
| SUBJECT (VARCHAR(50) NOT NULL                    |
| LESSON_TIME (TIMESTAMP)                          |

CLASSROOMS представляет собой:

| ID (INTEGER PRIMARY KEY)                         |
 |----|
| NUMBER (VARCHAR(10) NOT NULL                     |
| CAPACITY (INTEGER)                               |
