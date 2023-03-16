-- Запрос SQL для наполнения базы данных тестами.

DROP TABLE IF EXISTS RESULT_VALUES;
DROP TABLE IF EXISTS TEST_VALUES;
DROP TABLE IF EXISTS PIECES_COLOR;
DROP TABLE IF EXISTS PIECES;

CREATE TABLE PIECES (
    ID BIGINT PRIMARY KEY,
    TITLE VARCHAR NOT NULL
);

CREATE TABLE RESULT_VALUES (
    ID BIGINT PRIMARY KEY AUTO_INCREMENT,
    ANSWER BIGINT NOT NULL
);

INSERT INTO PIECES VALUES (3, 'PAWN'), (5, 'ROOK'), (7, 'BISHOP'), (11, 'KNIGHT'), (13, 'QUEEN'), (17, 'KING');

CREATE TABLE PIECES_COLOR (
    ID    BIGINT PRIMARY KEY,
    TITLE VARCHAR NOT NULL
);

INSERT INTO PIECES_COLOR VALUES (1, 'WHITE'), (2, 'BLACK');

CREATE TABLE TEST_VALUES (
    GAME_ID     BIGINT NOT NULL,
    MOVE_ID     BIGINT NOT NULL,
    PIECE_ID    BIGINT NOT NULL,
    PIECE_COLOR BIGINT NOT NULL,
    XAXISMARKER CHAR   NOT NULL,
    YAXISNUMBER CHAR   NOT NULL,
    CONSTRAINT FK_CHECKS_PIECE_ID FOREIGN KEY (PIECE_ID) REFERENCES PIECES (ID),
    CONSTRAINT FK_CHECKS_PIECE_COLOR FOREIGN KEY (PIECE_COLOR) REFERENCES PIECES_COLOR (ID)
);

INSERT INTO TEST_VALUES VALUES (1, 20, 17, 1, 'F', '2'), (1, 20, 7, 2, 'B', '6');                -- Есть шах от слона

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 32, 17, 1, 'C', '2'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 32, 5, 2, 'D', '4'); -- Нет шаха от ладьи

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 17, 1, 'C', '2'), -- Есть шах от ладьи
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 5, 2, 'C', '4');  -- горизонталь x = 0, y plus

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 17, 1, 'C', '3'), -- Есть шах от ладьи
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 5, 2, 'C', '1');  -- горизонталь x = 0, y minus

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 17, 1, 'C', '2'), -- Есть шах от ладьи
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 5, 2, 'A', '2');  -- горизонталь x minus, y = 0

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 17, 1, 'C', '2'), -- Есть шах от ладьи
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 42, 5, 2, 'E', '2');  -- горизонталь x plus, y = 0

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 17, 1, 'D', '4'), -- Есть шах от слона
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 7, 2, 'C', '3');  -- диагональ x - минус, y - минус

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 17, 1, 'D', '4'), -- Есть шах от слона
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 7, 2, 'E', '3');  -- диагональ x - плюс, y - минус

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 17, 1, 'D', '4'), -- Есть шах от слона
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 7, 2, 'C', '5');  -- диагональ x - минус, y - плюс

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 17, 1, 'D', '4'), -- Есть шах от слона
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 20, 7, 2, 'E', '5');  -- диагональ x - плюч, y - плюс

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 34, 17, 1, 'C', '2'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 34, 3, 2, 'C', '3'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 34, 5, 2, 'C', '4'); -- Нет шаха от ладьи, зыкрывает пешка

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 53, 17, 1, 'C', '2'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 53, 5, 2, 'B', '3'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 53, 7, 2, 'A', '4'); -- Нет шаха от слона, закрывает ладья

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 33, 17, 1, 'F', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 33, 5, 1, 'D', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 33, 5, 2, 'A', '4'); -- Нет шаха от ладьи, закрывает своя ладья

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 55, 17, 1, 'F', '3'), -- Нет шаха от слона, закрывает чужой король
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 55, 17, 2, 'E', '4'), -- Этот тест был создан для проверки будущих ходов
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 55, 7, 2, 'D', '5'); -- К примеру король может подойти к королю или нет. Если шах - то нет

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 77, 17, 1, 'D', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 77, 5, 2, 'C', '8'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 77, 5, 2, 'E', '8'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 77, 7, 2, 'H', '7'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 77, 7, 2, 'G', '8'); -- Нет шахов, ладьи и слоны атакуют поля вокруг

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 24, 17, 1, 'F', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 24, 5, 2, 'D', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 24, 7, 2, 'G', '5'); -- Шахи от обоих фигур, по алгоритму найдет слона сначала

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 25, 17, 1, 'F', '4'), -- Шах от королевы, за ней ладья,
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 25, 13, 2, 'D', '4'),     -- по алгоритму найдет королеву и выдаст королеву.
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 25, 5, 2, 'B', '4');      -- от ладьи шаха нет, так как мешает королева

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 27, 17, 1, 'D', '5'), -- Шах от прешки, за ней слон,
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 27, 3, 2, 'C', '6'),      -- по алгоритму найдет пешку.
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 27, 7, 2, 'B', '7');      -- от слон шаха нет, так как мешает пешка

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 17, 1, 'E', '3'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'D', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'E', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'F', '4'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'D', '3'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'F', '3'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'D', '2'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'E', '2'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 3, 1, 'F', '2'), -- Король окружен своими пешками
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 7, 2, 'C', '5'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 7, 2, 'G', '5'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 7, 2, 'C', '1'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 7, 2, 'G', '1'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 5, 2, 'E', '5'),
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 5, 2, 'E', '1'), -- За пешками находятся ладьи и слоны
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 5, 2, 'C', '3'), -- Которые направлены атакой в сторону короля
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 60, 5, 2, 'G', '3'); -- Шаха нет

INSERT INTO TEST_VALUES VALUES ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 27, 17, 1, 'D', '5'), -- Шах от слона на 27 ходу,
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 26, 3, 2, 'C', '6'),  -- пешка на 26 была, но она в счет не должна идти.
                               ((SELECT MAX(GAME_ID) FROM TEST_VALUES) + 1, 27, 7, 2, 'B', '7');  -- Итого шах от слона

INSERT INTO RESULT_VALUES(ANSWER) VALUES (7, 0, 5, 5, 5, 5, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7);