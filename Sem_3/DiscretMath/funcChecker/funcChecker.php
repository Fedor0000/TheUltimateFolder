<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat+Alternates:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Rubik+Mono+One&display=swap" rel="stylesheet">
    <link rel="icon" href="https://i.pinimg.com/originals/6c/9b/b1/6c9bb186f583850cdf36e5d38930363e.png" type="image/x-icon">
    <title>Проверка полноты</title>
    <style>
        html, body {
            overflow-y: hidden;
            overflow-x: hidden;
        }
        body {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            margin: 0;
            padding: 0;
            background: url('https://i.pinimg.com/originals/f3/3e/6e/f33e6e5c2c9d258544da903d094fda49.jpg') no-repeat center center fixed;
            background-size: cover;
            color: white;
            text-align: center;
            height: 100vh;
            display: flex;
            flex-direction: column;
            justify-content: flex-start;
            align-items: center;
            overflow-y: scroll;
            overflow-x: scroll;
        }
        body::-webkit-scrollbar {
            width: 10px;
            height: 10px;
        }
        body::-webkit-scrollbar-thumb {
            backdrop-filter: blur(15px);
            background: rgba(255, 255, 255, 0.2);
            border-radius: 4px;
        }
        body::-webkit-scrollbar-track {
            background: transparent;
        }
        body::-webkit-scrollbar-corner {
            background: transparent;
        }
        .header {
            padding: 10px;
        }
        h1 {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 40px;
            margin: 0px;
            padding: 5px 9px;
            background: rgba(0, 0, 0, 0);
            border-radius: 20px;
            backdrop-filter: blur(10px);
        }
        h2, label {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 30px;
            text-align: center;
            margin: 0px 0;
        }
        h4 {
            word-break: break-all;
            font-family: "Rubik Mono One", monospace;
            font-weight: 400;
            font-size: 24px;
            padding: 1px;
            margin: 0;
            background: linear-gradient(to right, rgba(255, 0, 255, 1), rgba(0, 0, 255, 1));
            -webkit-background-clip: text;
            color: transparent;
        }
        h3 {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 500;
            font-size: 32px;
            padding: 1px;
            margin: 4px;
            background: linear-gradient(to right, rgba(255, 0, 255, 1), rgba(0, 0, 255, 1));
            -webkit-background-clip: text;
            color: transparent;
            border-radius: 20px;
            backdrop-filter: blur(5px);
        }
        .inline-heading {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 40px;
            background: linear-gradient(to right, rgba(255, 0, 255, 1), rgba(0, 0, 255, 1));
            -webkit-background-clip: text;
            color: transparent;
        }
        button {
            margin: 3px;
            padding: 5px 7px;
            font-size: 24px;
            cursor: pointer;
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            background: rgba(200, 255, 200, 0.1);
            color: white;
            border: none;
            border-radius: 8px;
            backdrop-filter: blur(10px);
            transition: transform 0.2s, box-shadow 0.2s, background-color 0.2s;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }
        button:hover {
            transform: translateY(3px);
        }
        button:active {
            background: rgba(50, 255, 0, 0.2);
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
        }
        table {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 30px;
            margin-left: auto;
            margin-right: auto;
            border-collapse: collapse;
            backdrop-filter: blur(10px);
            border-radius: 15px;
            overflow: hidden;
        }
        th, td {
            padding: 3px 15px;
            text-align: center;
            transition: background-color 0.3s ease;
            border: none;
        }
        th {
            background-color: rgba(0, 0, 0, 0.25);
        }
        td {
            background-color: rgba(0, 0, 0, 0.05);
        }
        td:hover {
            background-color: rgba(0, 0, 0, 0.3);
        }
        input[type="text"] {
            margin: 3px;
            padding: 5px 7px;
            font-size: 24px;
            cursor: Ibeam;
            font-family: "Rubik Mono One", monospace;
            font-weight: 400;
            font-style: normal;
            background: rgba(200, 255, 200, 0.1);
            color: white;
            border: none;
            border-radius: 8px;
            backdrop-filter: blur(10px);
            transition: transform 0.2s, box-shadow 0.2s;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            width: 1050px;
        }
        input[type="text"]::placeholder {
            color: rgba(255, 255, 255, 0.7);
        }
        input[type="text"]:focus, select:focus {
            outline: none;
            box-shadow: 0 0 10px 2px rgba(255, 0, 255, 1), 0 0 10px 2px rgba(0, 0, 255, 1);
        }
        select {
            margin: 3px 0;
            padding: 5px 7px;
            font-size: 24px;
            font-family: "Rubik Mono One", monospace;
            font-weight: 400;
            font-style: normal;
            background: rgba(200, 255, 200, 0.1);
            color: white;
            border: none;
            border-radius: 8px;
            backdrop-filter: blur(10px);
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }
        select option {
            backdrop-filter: blur(10px);
            background: rgba(200, 255, 200, 0.1);
            color: black;
        }
        .scroll-container {
            overflow: hidden;
            width: 80%;
            height: auto;
            overflow-x: auto;
            overflow-y: hidden;
            white-space: nowrap;
            border: none;
            border-radius: 8px;
            padding: 30px;
            margin: 10px;
            background-color: rgba(0, 0, 0, 0.05);
            backdrop-filter: blur(10px);
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }
        .scroll-container::-webkit-scrollbar {
            height: 10px;
        }
        .scroll-container::-webkit-scrollbar-thumb {
            backdrop-filter: blur(10px);
            background: rgba(0, 0, 0, 0.3);
            border-radius: 4px;
        }
        .scroll-container::-webkit-scrollbar-track {
            background: transparent;
        }
        .scroll-container sk {
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 30px;
            text-align: center;
            vertical-align: top;
            line-height: 0;
        }
        .inline-negator {
            text-decoration: overline;
            font-family: 'Montserrat Alternates', sans-serif;
            font-weight: 300;
            font-size: 30px;
        }
        .inline-bigcross {
            font-family: "Rubik Mono One", monospace;
            font-weight: 400;
            font-size: 30px;
        }
        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
        }
        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(200, 255, 200, 0.1);
            backdrop-filter: blur(3px);
            transition: .4s;
            border-radius: 34px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: rgba(100, 255, 100, 0.5);;
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        .container {
            max-width: 80%;
            border: none;
            border-radius: 8px;
            background-color: rgba(0, 0, 0, 0.05);
            backdrop-filter: blur(10px);
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            padding: 10px;
            margin: 5px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .content {
            max-height: 0;
            overflow: hidden;
            transition: max-height 0.3s ease;
        }
        .container.open .content {
            max-height: 90vh;
            overflow: auto;
        }
        .content::-webkit-scrollbar {
            width: 12px;
            height: 12px;
        }
        .content::-webkit-scrollbar-track {
            background: transparent;
        }
        .content::-webkit-scrollbar-thumb {
            backdrop-filter: blur(10px);
            background: rgba(255, 255, 255, 0.3);
            border-radius: 4px;
        }
        .content::-webkit-scrollbar-thumb:hover {
            background: rgba(255, 255, 255, 0.5);
        }
        .content::-webkit-scrollbar-corner {
            background: transparent;
        }
    </style>
</head>
<body>
    <div class="header">
        <h1>Лабораторная работа №4: <span class="inline-heading">Южаков Ф.А.</span></h1>
        <h2>Проверка полноты системы функций</h2>
    </div>
    <form>
        <label>Разрешить неограниченный ввод (опасно):</label>
        <label class="switch">
        <input type="checkbox" id="toggleMaxLength" unchecked>
        <span class="slider"></span>
        </label>
    </form>
    <div>
        <label for="operators">Выберите оператор:</label>
        <select id="operators">
            <option value="0000">0</option>
            <option value="1111">1</option>
            <option value="0001">&</option>
            <option value="0111">∨</option>
            <option value="1101">→</option>
            <option value="1001">∾</option>
            <option value="0110">⊕</option>
            <option value="1000">↓</option>
            <option value="1110">|</option>
        </select>
        <button onclick="copyToClipboard()">Копировать</button>
    </div>
    <form method="post" action="">
        <button type="button" id="addButton" onclick="addField()">Добавить функцию</button>
        <button type="submit" name="goBTN">Проверить полноту</button>
        <button type="submit" name="goBTNwithfile">Проверить полноту и сохранить в файл</button>
    </form>
    <script>
        function saveHtml(con) {
            const content = con;
            const blob = new Blob([content], { type: 'text/html' });
            const url = URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.href = url;
            a.download = 'hello.html';
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);
        }
        function copyToClipboard() {
            const select = document.getElementById('operators');
            const value = select.value;
            navigator.clipboard.writeText(value).catch(err => {
                console.error('Ошибка копирования: ', err);
            });
        }
        function addField(value = "") {
            var newDiv = document.createElement("div");
            var fileButton = document.createElement("button");
            fileButton.type = "button";
            fileButton.innerHTML = "Из файла";
            fileButton.onclick = function() {
                var fileInput = document.createElement("input");
                fileInput.type = "file";
                fileInput.accept = ".txt";
                fileInput.onchange = function(event) {
                    var file = event.target.files[0];
                    var reader = new FileReader();
                    reader.onload = function(e) {
                        var lines = e.target.result.split('\n');
                        newInput.value = lines[0];
                    };
                    reader.readAsText(file);
                };
                fileInput.click();
            };
            newDiv.appendChild(fileButton);
            var rndButton = document.createElement("button");
            rndButton.type = "button";
            rndButton.innerHTML = "Рандом";
            rndButton.onclick = function() {
                var length = parseInt(select.value);
                var randomString = Array.from({ length: length }, () => Math.floor(Math.random() * 2)).join('');
                newInput.value = randomString;
            };
            newDiv.appendChild(rndButton);
            var select = document.createElement("select");
            [2, 4, 8, 16, 32, 64].forEach(function(num) {
                var option = document.createElement("option");
                option.value = num;
                option.text = num;
                if (num === 16) {
                    option.selected = true;
                }
                select.appendChild(option);
            });
            newDiv.appendChild(select);
            var newInput = document.createElement("input");
            newInput.type = "text";
            newInput.name = "fields[]";
            newInput.placeholder = "Введите функцию в виде вектора...";
            newInput.pattern = "[01]+";
            newInput.required = true;
            newInput.value = value;
            if (!document.getElementById('toggleMaxLength').checked) {
                newInput.maxLength = 64;
            }

            newDiv.appendChild(newInput);

            var clearButton = document.createElement("button");
            clearButton.type = "button";
            clearButton.innerHTML = "×";
            clearButton.onclick = function() {
                newInput.value = "";
            };
            newDiv.appendChild(clearButton);

            var removeButton = document.createElement("button");
            removeButton.type = "button";
            removeButton.innerHTML = "Убрать";
            removeButton.onclick = function() {
                if (document.querySelectorAll('input[name="fields[]"]').length > 1) {
                    newDiv.remove();
                } else {
                    alert("Должно остаться хотя бы одно поле.");
                }
            };
            newDiv.appendChild(removeButton);

            var addButton = document.getElementById("addButton");
            addButton.parentNode.insertBefore(newDiv, addButton);
        }
        function toggleContainer(event) {
            var container = event.currentTarget;
            container.classList.toggle('open');
        }
        document.getElementById('toggleMaxLength').addEventListener('change', function() {
            var inputFields = document.querySelectorAll('input[name="fields[]"]');
            inputFields.forEach(function(inputField) {
                if (!this.checked) {
                    inputField.setAttribute('maxlength', '64');
                    if (inputField.value.length > 64) {
                        inputField.value = inputField.value.substring(0, 64);
                    }
                } else {
                    inputField.removeAttribute('maxlength');
                }
            }, this);
        });
    </script>
    <?php
    $content = '';
    if (isset($_POST['goBTN'])) {
        if (!isset($_POST['fields'])) {
            echo '<h2>Вы ничего не ввели</h2>';
            return;
        }
        $fields = $_POST['fields']; $error = false; $tables = [];
        foreach ($fields as $index => $input) {
            if (!empty($input) && preg_match('/^[01]*$/', $input) && validateInput($input)) {
                echo '<script type="text/javascript">addField("'.$input.'");</script>';
                $tables[] = createTable($input);
                echo containedTable($tables[$index], htmlspecialchars($input));
            }
            else {
                echo '<h2>Ошибка ввода в функции "', htmlspecialchars($input), '".</h2>'; $error = true;
                echo '<script type="text/javascript">addField("'.$input.'");</script>';
                $tables[] = createTable('Error');
                echo containedTable($tables[$index], htmlspecialchars($input));
            }
        }
        if (!$error) {
            $zhigs = [];
            foreach ($fields as $indeh => $input) {
                $zhigs[] = getZhegalkin($input, $tables[$indeh]);
            }
            echo containedZhigalkin($zhigs, $fields);
            echo '<h3>Таблица проверки полноты</h3>';
            $poln = tableOfPolnotaConstructor($fields, $tables, $zhigs);
            echo displayTable($poln);
            if (checkColumns($poln)) echo '<h3>Система функций НЕ является полной.</h3>';
            else { 
                echo '<h3>Система функций полная.</h3>';
                $bas = '<h3>Базис(ы) системы функций:</h3>';
                $bas.= '<div class="scroll-container"><sk>'.implode(', ', getBasis($poln)).'</sk></div>';
                echo $bas;
            }
        }
    }
    if (isset($_POST['goBTNwithfile'])) {
        if (!isset($_POST['fields'])) {
            echo '<h2>Вы ничего не ввели</h2>';
            return;
        }
        $content = '<!DOCTYPE html><html lang="ru"><head><meta charset="UTF-8"><link rel="preconnect" href="https://fonts.googleapis.com"><link rel="preconnect" href="https://fonts.gstatic.com" crossorigin><link href="https://fonts.googleapis.com/css2?family=Montserrat+Alternates:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet"><link href="https://fonts.googleapis.com/css2?family=Rubik+Mono+One&display=swap" rel="stylesheet"><link rel="icon" href="https://i.pinimg.com/originals/6c/9b/b1/6c9bb186f583850cdf36e5d38930363e.png" type="image/x-icon"><title>Сохраненный файл</title><style>html, body {overflow-y: hidden;overflow-x: hidden;} body {font-family: "Montserrat Alternates", sans-serif;font-weight: 300;margin: 0;padding: 0;background: url("https://i.pinimg.com/originals/f3/3e/6e/f33e6e5c2c9d258544da903d094fda49.jpg") no-repeat center center fixed;background-size: cover;color: white;text-align: center;height: 100vh;display: flex;flex-direction: column;justify-content: flex-start;align-items: center;overflow-y: scroll;overflow-x: scroll;}body::-webkit-scrollbar {width: 10px;height: 10px;}body::-webkit-scrollbar-thumb {backdrop-filter: blur(15px);background: rgba(255, 255, 255, 0.2);border-radius: 4px;}body::-webkit-scrollbar-track {background: transparent;}body::-webkit-scrollbar-corner {background: transparent;}.header {padding: 10px;}h4 {word-break: break-all;font-family: "Rubik Mono One", monospace;font-weight: 400;font-size: 24px;padding: 1px;margin: 0;background: linear-gradient(to right, rgba(255, 0, 255, 1), rgba(0, 0, 255, 1));-webkit-background-clip: text;color: transparent;}h2 {font-family: "Montserrat Alternates", sans-serif;font-weight: 300;font-size: 30px;text-align: center;margin: 0px 0;}h3 {font-family: "Montserrat Alternates", sans-serif;font-weight: 500;font-size: 32px;padding: 1px;margin: 4px;background: linear-gradient(to right, rgba(255, 0, 255, 1), rgba(0, 0, 255, 1));-webkit-background-clip: text;color: transparent;border-radius: 20px;backdrop-filter: blur(5px);}table {font-family: "Montserrat Alternates", sans-serif;font-weight: 300;font-size: 30px;margin-left: auto;margin-right: auto;border-collapse: collapse;backdrop-filter: blur(10px);border-radius: 15px;overflow: hidden;}th, td {padding: 3px 15px;text-align: center;transition: background-color 0.3s ease;border: none;}th {background-color: rgba(0, 0, 0, 0.25);}td {background-color: rgba(0, 0, 0, 0.05);}td:hover {background-color: rgba(0, 0, 0, 0.3);}.inline-bigcross {font-family: "Rubik Mono One", monospace;font-weight: 400;font-size: 30px;}.container {max-width: 80%;border: none;border-radius: 8px;background-color: rgba(0, 0, 0, 0.05);backdrop-filter: blur(10px);box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);padding: 10px;margin: 5px;cursor: pointer;transition: all 0.3s ease;}.content {max-height: 0;overflow: hidden;transition: max-height 0.3s ease;}.container.open .content {max-height: 90vh;overflow: auto;}.content::-webkit-scrollbar {width: 12px;height: 12px;}.content::-webkit-scrollbar-track {background: transparent;}.content::-webkit-scrollbar-thumb {backdrop-filter: blur(10px);background: rgba(255, 255, 255, 0.3);border-radius: 4px;}.content::-webkit-scrollbar-thumb:hover {background: rgba(255, 255, 255, 0.5);}.content::-webkit-scrollbar-corner {background: transparent;}.scroll-container {overflow: hidden;width: 80%;height: auto;overflow-x: auto;overflow-y: hidden;white-space: nowrap;border: none;border-radius: 8px;padding: 30px;margin: 10px;background-color: rgba(0, 0, 0, 0.05);backdrop-filter: blur(10px);box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);}.scroll-container::-webkit-scrollbar {height: 10px;}.scroll-container::-webkit-scrollbar-thumb {backdrop-filter: blur(10px);background: rgba(0, 0, 0, 0.3);border-radius: 4px;}.scroll-container::-webkit-scrollbar-track {background: transparent;}.scroll-container sk {font-family: "Montserrat Alternates", sans-serif;font-weight: 300;font-size: 30px;text-align: center;vertical-align: top;line-height: 0;}</style></head><script>function toggleContainer(event){var container = event.currentTarget;container.classList.toggle("open");}<\/script>';
        $fields = $_POST['fields']; $error = false; $tables = [];
        foreach ($fields as $index => $input) {
            if (!empty($input) && preg_match('/^[01]*$/', $input) && validateInput($input)) {
                echo '<script type="text/javascript">addField("'.$input.'");</script>';
                $tables[] = createTable($input);
                $conten = containedTable($tables[$index], htmlspecialchars($input)); echo $conten; $content.= $conten;
            }
            else {
                echo '<h2>Ошибка ввода в функции "', htmlspecialchars($input), '".</h2>'; $error = true;
                echo '<script type="text/javascript">addField("'.$input.'");</script>';
                $tables[] = createTable('Error');
                echo containedTable($tables[$index], htmlspecialchars($input));
            }
        }
        if (!$error) {
            $zhigs = [];
            foreach ($fields as $indeh => $input) {
                $zhigs[] = getZhegalkin($input, $tables[$indeh]);
            }
            $conten = containedZhigalkin($zhigs, $fields); echo $conten; $content.= $conten;
            echo '<h3>Таблица проверки полноты</h3>'; $content.= '<h3>Таблица проверки полноты</h3>';
            $poln = tableOfPolnotaConstructor($fields, $tables, $zhigs);
            $conten = displayTable($poln); echo $conten; $content.= $conten;
            if (checkColumns($poln)) {
                echo '<h3>Система функций НЕ является полной.</h3>'; $content.= '<h3>Система функций НЕ является полной.</h3>';
            }
            else {
                echo '<h3>Система функций полная.</h3>'; $content.= '<h3>Система функций полная.</h3>';
                $bas = '<h3>Базис(ы) системы функций:</h3>';
                $bas.= '<div class="scroll-container"><sk>'.implode(', ', getBasis($poln)).'</sk></div>';
                echo $bas; $content.= $bas;
            }
            echo '<script type="text/javascript">'."saveHtml('".$content."')".';</script>';
            $content = '';
        }
    }

    function isPowerOfTwo($n) {return ($n > 1) && (($n & ($n - 1)) == 0);}
    function validateInput($input) {
        $length = strlen($input);
        if ($length == 1) return false;
        else return isPowerOfTwo($length);
    }
    function logbase($a, $base) {return log($a) / log($base);} 
    function variableName($number) {
        if ($number == 0) return "";
        $alphabet = " abcdefghijklmnopqrstuvwxyz";
        $result = "";
        if ($number <= 26) {
            $result = $alphabet[$number];
        } else {
            $i = 0;
            do {
                $i = $number % 26;
                if ($i == 0) {
                    $result = 'z' . $result;
                    $number = ($number / 26) - 1;
                } else {
                    $result = $alphabet[$i] . $result;
                    $number = floor($number / 26);
                }
            } while ($number > 26);
            $result = $alphabet[$number] . $result;
        }
        return $result;
    }
    function binIncr(&$input) {
        if (strpos($input, '0') === false) return;
        $mem = false;
        if ($input[strlen($input) - 1] == '0') {
            $input[strlen($input) - 1] = '1';
        } else {
            $input[strlen($input) - 1] = '0';
            $mem = true;
        }
        if ($mem) {
            for ($i = strlen($input) - 2; $i >= 0; $i--) {
                if ($input[$i] == '0') {
                    $input[$i] = '1';
                    break;
                } else {
                    $input[$i] = '0';
                }
            }
        }
    }
    function createTable($input) {
        $rows = strlen($input) + 1;
        $columns = floor(logbase(strlen($input), 2)) + 1;
        $table = array_fill(0, $rows, array_fill(0, $columns, ""));
        for ($i = 0; $i < $columns - 1; $i++) {
            $table[0][$i] = variableName($i + 1);
        }
        $table[0][$columns - 1] = "Функция";
        $binNum = str_repeat('0', $columns - 1);
        for ($i = 1; $i < $rows; $i++) {
            for ($j = 0; $j < $columns - 1; $j++) {
                $table[$i][$j] = $binNum[$j];
            }
            binIncr($binNum);
        }
        for ($i = 1; $i < $rows; $i++) {
            $table[$i][$columns - 1] = $input[$i - 1];
        }
        return $table;
    }
    function displayTable($table) {
        if ($table === null) return;
        $cont = '<table border="1">';
        foreach ($table as $rowIndex => $row) {
            $cont.= '<tr>';
            foreach ($row as $cellIndex => $cell) {
                if ($rowIndex == 0) {
                    $cont.= '<th>' .$cell . '</th>';
                } else {
                    $cont.= '<td>' .$cell . '</td>';
                }
            }
            $cont.= '</tr>';
        }
        $cont.= '</table>';
        return $cont;
    }
    function containedTable($table, $tableName = 'имятаблицы') {
        $result = '<div class="container" onclick="toggleContainer(event)"><h4>Таблица истинности для функции «'.$tableName.'»</h4><div class="content"><table border="1">';
        foreach ($table as $rowIndex => $row) {
            $result.= '<tr>';
            foreach ($row as $cellIndex => $cell) {
                if ($rowIndex == 0) {
                    $result.= '<th>' .$cell . '</th>';
                } else {
                    $result.= '<td>' .$cell . '</td>';
                }
            }
            $result.= '</tr>';
        }
        $result.= '</table></div></div>';
        return $result;
    }
    function containedZhigalkin($zhigi, $fields) {
        $result = '<div class="container" onclick="toggleContainer(event)"><h4>Полиномы Жегалкина</h4><div class="content">';
        foreach ($zhigi as $indeh => $zhiga) {
            $result.= '<h4>Полином Жегалкина для функции «'.$fields[$indeh].'»<h4>';
            $result.= $zhiga;
        }
        $result.= '</table></div></div>';
        return $result;
    }
    function nullOrOneCheck($input, $checker = 0) {
        if ($checker == 0 && $input[0] == 0) return true;
        if ($checker == 1 && $input[strlen($input)-1] == 1) return true;
        return false;
    }
    function isSelfDual($input) {
        $length = strlen($input);
        if ($length % 2 != 0) return false;
        for ($i = 0; $i < $length / 2; $i++) {
            if ($input[$i] == $input[$length - 1 - $i]) {
                return false;
            }
        }
        return true;
    }
    function sortTruthTable($truthTable) {
        // Удаляем заголовок таблицы
        $header = array_shift($truthTable);
        // Сортируем строки таблицы по количеству единиц в переменных
        usort($truthTable, function($a, $b) {
            $countA = array_sum(array_slice($a, 0, -1));
            $countB = array_sum(array_slice($b, 0, -1));
            return $countA - $countB;
        });
        // Возвращаем заголовок на место
        array_unshift($truthTable, $header);
        return $truthTable;
    }
    function filterTruthTable($truthTable, $columnIndex) {
        // Инициализируем массив для хранения отфильтрованных строк
        $filteredTable = [];
        // Добавляем шапку в отфильтрованный массив
        $filteredTable[] = $truthTable[0];
        // Проходим по каждой строке таблицы истинности
        foreach ($truthTable as $index => $row) {
            // Пропускаем шапку
            if ($index === 0) {
                continue;
            }
            // Проверяем, стоит ли 1 в указанном столбце
            if (isset($row[$columnIndex]) && $row[$columnIndex] == 1) {
                $filteredTable[] = $row;
            }
        }
        return $filteredTable;
    }
    function countOnesIgnoringLast($array) {
        array_pop($array);
        $count = 0;
        foreach ($array as $value) {
            if ($value == 1) $count++;
        }
        return $count;
    }
    function overBranch(&$indeh, $branch) {
        $overBranch = [];
        while (countOnesIgnoringLast($branch[$indeh]) == countOnesIgnoringLast($branch[$indeh+1])) { // пока идет разветвление, нужно его запоминать
            $overBranch[] = $branch[$indeh];
            $indeh++;
        }
        $overBranch[] = $branch[$indeh]; // цикл не закидывает последнее разветвление, так как после него единиц уже больше
        return $overBranch;
    }
    function compareRows($firstBatch, $secondBatch) {
        foreach ($firstBatch as $firstRow) {
            $firstRowWithoutLast = substr($firstRow, 0, -1);
            $firstRowLastChar = substr($firstRow, -1);
            $matched = false;
            foreach ($secondBatch as $secondRow) {
                $secondRowWithoutLast = substr($secondRow, 0, -1);
                $secondRowLastChar = substr($secondRow, -1);
                // Проверяем, чтобы количество единиц во второй строке было больше на одну
                if (substr_count($secondRowWithoutLast, '1') == substr_count($firstRowWithoutLast, '1') + 1) {
                    $match = true;
                    // Проверяем, чтобы единицы совпадали по позициям
                    for ($i = 0; $i < strlen($firstRowWithoutLast); $i++) {
                        if ($firstRowWithoutLast[$i] == '1' && $secondRowWithoutLast[$i] == '0') {
                            $match = false;
                            break;
                        }
                    }
                    // Проверяем последний символ
                    if ($match && $firstRowLastChar > $secondRowLastChar) {
                        $matched = true;
                        break; // Найдена строка, нарушающая монотонность
                    }
                }
            }
            if ($matched) {
                return false; // Если хотя бы одна строка нарушила монотонность, возвращаем false
            }
        }
        return true; // Все строки из первой пачки нашли подходящие пары
    }
    function monotonousCheck($tables) {
        $allBranches = []; $result = [];
        foreach ($tables as $table) {
            $branches = []; // в каждом элементе массива массив с таблицами-ветками
            for ($i = 0; $i < count($table[0])-1; $i++) {
                $branchTable = filterTruthTable(sortTruthTable($table), $i);
                array_splice($branchTable, 1, 0, [$table[1]]);
                $branches[] = $branchTable;
            }
            $allBranches[] = $branches;
        }
        foreach ($allBranches as $branches) { // проверяет все функции
            $okOrNot = true;
            foreach ($branches as $branch) { // проверяет одну функцию (все ветки)
                $overBranch = [];
                for ($indeh = 1; $indeh < count($branch); $indeh++) { // проверяет одну ветку в функции на монотонность
                    $row = $branch[$indeh]; $end = false;
                    if ($indeh == count($branch)-1) $end = true;
                    if ((isset($branch[$indeh+1]) && (countOnesIgnoringLast($row) < countOnesIgnoringLast($branch[$indeh+1]))) || $end) { // если в следующей строке больше единиц, чем в текущей
                        if (isset($branch[$indeh+1]) && ($overBranch == [])) { // если строка после строки
                            $overBranch = []; // раз встали в простую строку, значит можно убрать запомненное разветвление
                            if ($row[count($row)-1] > $branch[$indeh+1][count($branch[$indeh+1])-1]) {
                                $okOrNot = false;
                                break; // если в ветке уже есть нарушение монотонности
                            }
                        } else { // если строка после развевления нужно проверить все его части с текущей строкой
                            foreach ($overBranch as $over) {
                                if ($row[count($row)-1] < $over[count($over)-1]) {
                                    $okOrNot = false;
                                    break;
                                }
                            }
                            $overBranch = []; // мы сейчас в строке, а вследующий раз будут смотреть на то, была ли строка или разветвление
                        }
                    } else { // если единиц одинаковое кол-во, то мы наступили на разветвление, нужно его выделить
                        if ($overBranch == []) { // если разветвление после строки
                            $mindIndehBeforeOB = $indeh-1; // индекс строки перед разветвлением
                            $overBranch = overBranch($indeh, $branch); // выделяем разветвление, индекс на последнем элементе разветвления
                            foreach ($overBranch as $over) {
                                if ($branch[$mindIndehBeforeOB][count($branch[$mindIndehBeforeOB])-1] > $over[count($over)-1]) { // если в каком либо из разветлений не выполнилось условие с местом до разветвления
                                    $okOrNot = false;
                                    break;
                                }
                            }
                            if (!$okOrNot) break; // смысл проверять ветку дальше, если на разветвлении завалилось
                            // после разветвления ничего не делаем встать в следующую строку поможет итератор цикла
                        } else { // если разветвление после разветвления
                            $newOverBranch = overBranch($indeh, $branch); // разветвление после разветвления
                            // а вот тут уже приколы, проверять нужно не каждого с каждым,
                            // а только тех, у кого в старом разветвлении и в новом единицы на тех же местах, но в новом на одну больше
                            $oldOver = [];
                            foreach ($overBranch as $over) {
                                $oldOver[] = implode('', $over);
                            }
                            $newOver = [];
                            foreach ($newOverBranch as $over) {
                                $newOver[] = implode('', $over);
                            }
                            $overBranch = $newOverBranch;
                            if (!compareRows($oldOver, $newOver)) {
                                $okOrNot = false;
                                break;
                            }
                        }
                    }
                }
                if (!$okOrNot) { // если в одной ветке уже нарушение, остальные проверять бессмысленно, брейкаем и этот цикл
                    break;
                }
            }
            $result[] = $okOrNot;
        }
        return $result;
    }
    function xorr($bool, $boool) {return ((!$bool && $boool) || ($bool && !$boool)) ? '1' : '0';}
    function getFirstChars($array) {
        $firstChars = '';
        foreach ($array as $str) {
            if (strlen($str) > 0) {
                $firstChars .= $str[0];
            }
        }
        return $firstChars;
    }
    function getZhegalkin($input, $table) { // Метод треугольника Паскаля
        $triangle = [$input];
        while (strlen($triangle[count($triangle)-1]) != 1) {
            $toTriangle = '';
            for ($i = 0; $i < strlen($triangle[count($triangle)-1])-1; $i++) {
                $toTriangle.= xorr($triangle[count($triangle) -1][$i], $triangle[count($triangle) -1][$i+1]);
            }
            $triangle[] = $toTriangle;
        }
        $vector = getFirstChars($triangle);
        if (strpos($vector,'1') !== false) {
            $poly = [];
            for ($i = 0; $i < strlen($input); $i++) {
                if ($vector[$i] == 1) {
                    $obj = [];
                    for ($j = 0; $j < count($table[0])-1; $j++) {
                        if ($table[$i+1][$j] == 1) $obj[] = $table[0][$j];
                    }
                    if ($obj !== []) $obj = implode('&', $obj);
                    else $obj = '1';
                    $poly[] = $obj;
                }
            }
        } else $poly = [0];
        return '<h2>'.implode('⊕', $poly).'</h2>';
    }
    function tableOfPolnotaConstructor($fields, $tables, $zhigs) {
        $tabl = array_fill(0, count($fields)+1, array_fill(0, 6, ''));
        $tabl[0] = ['', '<span class="inline-bigcross" title="Функция, сохраняющая ноль">Т<sub>0</sub></span>', '<span class="inline-bigcross" title="Функция, сохраняющая единицу">Т<sub>1</sub></span>', '<span class="inline-bigcross" title="Самодвойственная функция">S</span>', '<span class="inline-bigcross" title="Монотонная функция">M</span>', '<span class="inline-bigcross" title="Линейная функция">L</span>'];
        $mono = monotonousCheck($tables);
        for ($i = 0; $i < count($fields); $i++) {
            $table = $tables[$i];
            $tabl[$i+1][0] = '<span class="inline-bigcross" title="'.$fields[$i].'">F<sub>'.($i+1).'</sub></span>';
            if (nullOrOneCheck($fields[$i], 0)) $tabl[$i+1][1] = '<span class="inline-bigcross">+</span>';
            if (nullOrOneCheck($fields[$i], 1)) $tabl[$i+1][2] = '<span class="inline-bigcross">+</span>';
            if (isSelfDual($fields[$i])) $tabl[$i+1][3] = '<span class="inline-bigcross">+</span>';
            if (strpos($zhigs[$i], '&') === false) $tabl[$i+1][5] = '<span class="inline-bigcross">+</span>';
            if ($mono[$i] == true) $tabl[$i+1][4] = '<span class="inline-bigcross">+</span>';
        }
        return $tabl;
    }
    function checkColumns($table) {
        $numRows = count($table);
        if ($numRows < 2) return true;
        $numCols = count($table[0]);
    
        for ($col = 1; $col < $numCols; $col++) { // Начинаем с 1, чтобы пропустить боковую шапку
            $allPluses = true;
            for ($row = 1; $row < $numRows; $row++) { // Начинаем с 1, чтобы пропустить верхнюю шапку
                if (!isset($table[$row][$col]) || $table[$row][$col] != '<span class="inline-bigcross">+</span>') {
                    $allPluses = false;
                    break;
                }
            }
            if ($allPluses) {
                return true; // Найден столбец, полностью заполненный плюсами
            }
        }
        return false; // Нет столбцов, полностью заполненных плюсами
    }
    
    function getCombinations($items, $minItems = 1) { // выдает все комбинации функций для поиска базисов
        $result = [];
        $numItems = count($items);
        $combinations = pow(2, $numItems);
        for ($i = 0; $i < $combinations; $i++) {
            $combination = [];
            for ($j = 0; $j < $numItems; $j++) {
                if ($i & (1 << $j)) {
                    $combination[] = $items[$j];
                }
            }
            if (count($combination) >= $minItems) {
                $result[] = $combination;
            }
        }
        return $result;
    }
    function removeRowWithFirstElement($array, $value) {
        $filteredArray = array_filter($array, function($row) use ($value) {
            return $row[0] !== $value;
        });
        return array_values($filteredArray);
    }
    function shortBasis($array) {
        $minPluses = min(array_map(function($row) {
            return substr_count($row, '+');
        }, $array));
        return array_filter($array, function($row) use ($minPluses) {
            return substr_count($row, '+') === $minPluses;
        });
    }
    function getBasis($poln) {
        $functions = [];
        for ($i = 1; $i < count($poln); $i++) {
            $functions[] = $poln[$i][0];
        }
        if (count($functions) == 1) return $functions;
        $allCombs = getCombinations($functions);
        $polnCombs = [];
        foreach ($allCombs as $comb) {
            $tempPoln = $poln;
            foreach ($comb as $combItem) {
                $tempPoln = removeRowWithFirstElement($tempPoln, $combItem);
            }
            if (!checkColumns($tempPoln)) {
                $polnCombs[] = implode('+', array_values(array_diff($functions, $comb)));
            }
        }
        if (count($polnCombs) > 0) $polnCombs = shortBasis($polnCombs);
        else $polnCombs = $functions;
        return $polnCombs;
    }
    ?>
</body>
</html>