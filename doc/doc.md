Виселица

Простая игра Hangman на базе терминала, написанная на C++. Построен на базе Linux. Довольно интересная игра для убийства времени.

В игре есть базовая система подсчета очков. Игроку начисляется 1 очко, если он правильно угадает слово до того, как у него закончатся догадки. В многопользовательских играх, если угадывающему игроку не удается угадать слово, игрок, который придумал это слово, также получает очко.

Дизайн
Игра построена вокруг 2-х классов, которые контролируют весь процесс:

Game_shell - Содержит каждый игровой экземпляр. 

Game_data - Содержит всю индивидуальную логику игры и необходимые данные для ее запуска.

Игра поддерживает игру против человека или оппонента в виде компьютера. При игре против компьютера игра случайным образом выберет слово из списка из файла words.txt . Список слов можно расширить, однако основную программу потребуется перекомпилировать (подробности см. в разделе Настройка).

Игра против человека позволяет другому игроку ввести слово, чтобы вы попытались его угадать. Одно предостережение заключается в том, что программа не будет проверять орфографию вводимого человеком слова.

Настройка
Есть 2 основных "настраиваемых" элемента, оба в game.cpp . Это:

ПРОДОЛЖИТЕЛЬНОСТЬ игры - определяет количество угадываний, которые вам разрешены до того, как вы проиграете игру, в данный момент установлено равным 9. Может быть легко расширен до 11 путем раскомментирования строк 25 и 27. Большие цифры по-прежнему будут работать, но, вероятно, нарушат изображение виселицы.

ДЛИНА файла - уменьшение размера будет означать, что конечные слова не будут выбираться случайным образом. Превышение длины файла может привести к очень странному поведению и, вероятно, к сбою программы.

Установка
Игру "как есть" можно запустить непосредственно в терминале.
