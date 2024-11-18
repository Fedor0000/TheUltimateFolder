<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat+Alternates:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Rubik+Mono+One&display=swap" rel="stylesheet">
    <link rel="icon" href="https://i.pinimg.com/originals/6c/9b/b1/6c9bb186f583850cdf36e5d38930363e.png" type="image/x-icon">
    <title>Минимизатор Квайна</title>
    <script>
        document.addEventListener('DOMContentLoaded', function() {
            var input = document.getElementById('inputField');
            var button = document.getElementById('submitButton');

            input.addEventListener('keypress', function(event) {
                if (event.key === 'Enter') {
                    event.preventDefault();
                    button.click();
                }
            });
        });
    </script>
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
        p {
            font-size: 1.5em;
        }
        button {
            margin: 3px 0;
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
            border-bottom: 1px solid black;
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
            margin: 3px 0;
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
            width: 1100px;
            height: 200px;
            max-height: 100%;
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
    </style>
</head>
<body>
    <div class="header">
        <h1>Лабораторная работа №3: <span class="inline-heading">Южаков Ф.А.</span></h1>
        <h2>Минимизация методом Квайна</h2>
    </div>
    <form method="post">
        <input type="text" name="inputField" placeholder="Введите функцию в виде вектора..." pattern="[01]*" title="Только 0 и 1" maxlength = 64 value="<?php echo isset($_POST['inputField']) ? htmlspecialchars($_POST['inputField']) : ''; ?>">
        <button type="button" id="clearButton">×</button>
        <button type="submit" name="goBTN" id="submitButton">Вперёд</button>
    </form>
    <form>  
        <button type="button" id="fileButton">Из файла</button>  
        <label for="numberSelect">Выберите число случайных символов: </label>
        <select id="numberSelect" name="numberSelect">
            <option value="2">2</option>
            <option value="4">4</option>
            <option value="8">8</option>
            <option value="16" selected>16</option>
            <option value="32">32</option>
            <option value="64">64</option>
        </select>
        <button type="button" id="fillButton">Заполнить</button>
        <input type="file" id="fileInput" style="display: none;">
    </form>
    <form>
        <label>Разрешить неограниченный ввод (опасно):</label>
        <label class="switch">
        <input type="checkbox" id="toggleMaxLength" unchecked>
        <span class="slider"></span>
        </label>
    </form>
    <script>
        document.getElementById('clearButton').addEventListener('click', function() {
            document.querySelector('input[name="inputField"]').value = '';
        });

        document.getElementById('fillButton').addEventListener('click', function() {
            var length = document.getElementById('numberSelect').value;
            var randomString = '';
            for (var i = 0; i < length; i++) {
                randomString += Math.floor(Math.random() * 2);
            }
            document.querySelector('input[name="inputField"]').value = randomString;
        });

        document.getElementById('fileButton').addEventListener('click', function() {
            document.getElementById('fileInput').click();
        });

        document.getElementById('fileInput').addEventListener('change', function(event) {
            var file = event.target.files[0];
            if (file) {
                var reader = new FileReader();
                reader.onload = function(e) {
                    var lines = e.target.result.split('\n');
                    if (lines.length > 0) {
                        document.querySelector('input[name="inputField"]').value = lines[0];
                    }
                };
                reader.readAsText(file);
            }
        });

        document.getElementById('toggleMaxLength').addEventListener('change', function() {
            var inputField = document.querySelector('input[name="inputField"]');
            if (!this.checked) {
                inputField.setAttribute('maxlength', '64');
                inputField.value = '';
            } else {
                inputField.removeAttribute('maxlength');
            }
        });
    </script>
    <?php
    if (isset($_POST['goBTN'])) {
        $input = $_POST['inputField'];
        if (!empty($input) && preg_match('/^[01]*$/', $input) && validateInput($input)) {
            echo '<h3>Таблица истинности для функции "', htmlspecialchars($input), '":</h3>';
            $table = createTable($input);
            displayTable($table);
            echo '<h3>СДНФ для функции "', htmlspecialchars($input), '":</h3>';
            $sdnf = buildSDNF($table);
            $sknf = buildSKNF($table);
            if (strlen($sdnf) === 0) {
                echo '<div class="scroll-container"><sk>СДНФ не существует.</sk></div>';
            }
            else {
                echo '<div class="scroll-container"><sk>', $sdnf, '</sk></div>';
            }
            echo '<h3>СКНФ для функции "', htmlspecialchars($input), '":</h3>';
            if (strlen($sknf) === 0) {
                echo '<div class="scroll-container"><sk>СКНФ не существует.</sk></div>';
            }
            else {
                echo '<div class="scroll-container"><sk>', $sknf, '</sk></div>';
            }
            if (strlen($sdnf) !== 0) {
                echo '<h3>Cклейки для функции "', htmlspecialchars($input), '":</h3>';
                $matrix = buildCoverageTable($sdnf);
                echo '<h3>Импликантная матрица для функции "', htmlspecialchars($input), '":</h3>';
                displayMatr($matrix);
                echo '<h3>Тупиковые и минимальные формы для функции "', htmlspecialchars($input), '":</h3>';
                findMinimalAndRedundantForms($matrix);
            }
            else {
                echo '<h2>Метод минимизация Квайна не работает с функциями, не имеющими СДНФ.</h2>';
            }
        }
        else if (empty($input)) {
            echo '<h2>Ошибка. Вы ничего не ввели.</h2>';
        }
        else if (!validateInput($input)) {
            echo '<h2>Ошибка. Введённая функция "', htmlspecialchars($input), '" некорректна.</h2>';
        }
        else {
            echo '<h2>Ошибка. Вы ввели символы, отличные от 1 или 0.</h2>';
        }
    }

    function isPowerOfTwo($n) {
        return ($n > 1) && (($n & ($n - 1)) == 0);
    }
    function validateInput($input) {
        $length = strlen($input);
        return isPowerOfTwo($length);
    }
    function logbase($a, $base) {
        return log($a) / log($base);
    } 
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
    
        echo '<table border="1">';
        foreach ($table as $rowIndex => $row) {
            echo '<tr>';
            foreach ($row as $cellIndex => $cell) {
                if ($rowIndex == 0) {
                    echo '<th>' .$cell . '</th>';
                } else {
                    echo '<td>' .$cell . '</td>';
                }
            }
            echo '</tr>';
        }
        echo '</table>';
    }

    function buildSDNF($table) {
        $sdnf = [];
        $columns = count($table[0]) - 1; // Количество переменных
        for ($i = 1; $i < count($table); $i++) {
            if ($table[$i][$columns] == '1') {
                $term = [];
                for ($j = 0; $j < $columns; $j++) {
                    $term[] = $table[$i][$j] == '1' ? $table[0][$j] : '<span class="inline-negator">'.$table[0][$j].'</span>';
                }
                $sdnf[] = '(' . implode('&', $term) . ')';
            }
        }
        return implode('∨', $sdnf);
    }
    
    function buildSKNF($table) {
        $sknf = [];
        $columns = count($table[0]) - 1; // Количество переменных
        for ($i = 1; $i < count($table); $i++) {
            if ($table[$i][$columns] == '0') {
                $term = [];
                for ($j = 0; $j < $columns; $j++) {
                    $term[] = $table[$i][$j] == '0' ? $table[0][$j] : '<span class="inline-negator">'.$table[0][$j].'</span>';
                }
                $sknf[] = '(' . implode('∨', $term) . ')';
            }
        }
        return implode('&', $sknf);
    }

    function combineTerms($term1, $term2) {
        if ($term1 == null || $term2 == null) return false;
        $variables1 = []; $variables2 = [];
        if (strpos($term1, '&') != false) $variables1 = explode('&', $term1);
        else return false;
        if (strpos($term2, '&') != false) $variables2 = explode('&', $term2);
        else return false;
        if (count($variables1) != count($variables2)) return false;
        if (count($variables1) == 1 || count($variables2) == 1) return false;
        if ($variables1 == $variables2) return false;
        
        $diffCount = 0;
        $combinedTerm = [];
        foreach ($variables1 as $index => $var1) {
            $var2 = $variables2[$index];
            if ((($var1[0] == '0' && $var2[0] != '0') || ($var1[0] != '0' && $var2[0] == '0')) && (str_replace('0', '', $var1) == str_replace('0', '', $var2))) {
                $diffCount++;
            } else if ($var1 != $var2) {
                return false;
            } else {
                $combinedTerm[] = $var1;
            }
        }
        return $diffCount == 1 ? implode('&', $combinedTerm) : false;
    }
    
    function buildCoverageTable($sdnf) {
        $terms = explode('∨', $sdnf);
        $implicantMatrix = [];
        
        foreach ($terms as $term) {
            $implicantMatrix[] = str_replace(['(', ')', '<span class="inline-negator">', '</span>'], ['', '', '0', ''], $term);
        }
        
        echo '<h2>Части СДНФ до склейки:</h2>';
        echo '<div class="scroll-container"><sk>';
        $lastIndex = count($implicantMatrix) - 1;
        foreach ($implicantMatrix as $index => $term) {
            $vars = explode('&', $term);
            $corvar = $vars;
            for ($i = 0; $i < count($vars); $i++) {
                if ($vars[$i][0] == 0) {
                    $corvar[$i] = str_replace('0', '<span class="inline-negator">', $vars[$i]).'</span>';
                }
            }
            $corvar = implode('&', $corvar);
            echo $corvar;
            if ($index !== $lastIndex) { 
                echo ', ';
            }
        }
        echo '</sk></div>';

        $newMatrix = [];
        $used = array_fill(0, count($implicantMatrix), false);
        
        $numsOfmerge = 0;
        do {
            $numsOfmerge++;
            $currentMatrix = $implicantMatrix;
            $newMatrix = [];
            $used = array_fill(0, count($implicantMatrix), false);
            
            for ($i = 0; $i < count($implicantMatrix); $i++) {
                for ($j = $i + 1; $j < count($implicantMatrix); $j++) {
                    if (!isset($implicantMatrix[$i]) || !isset($implicantMatrix[$j])) {
                        continue;
                    } else {
                        $combined = combineTerms($implicantMatrix[$i], $implicantMatrix[$j]);
                    }
                    if ($combined !== false) {
                        $newMatrix[] = $combined;
                        $used[$i] = true;
                        $used[$j] = true;
                    }
                }
            }
            
            foreach ($implicantMatrix as $index => $term) {
                if (isset($used[$index])) {
                    if (!$used[$index]) {
                        $newMatrix[] = $term;
                    }
                } else {
                    $newMatrix[] = $term;
                }
            }
            
            $implicantMatrix = array_unique($newMatrix);
            $implicantMatrix = arrayFilter($implicantMatrix);
            if ($implicantMatrix == $currentMatrix) break;

            echo '<h2>Результат ', $numsOfmerge, ' склейки:</h2>';
            echo '<div class="scroll-container"><sk>';
            $lastIndex = count($implicantMatrix) - 1;
            foreach ($implicantMatrix as $index => $term) {
                $vars = explode('&', $term);
                $corvar = $vars;
                for ($i = 0; $i < count($vars); $i++) {
                    if ($vars[$i][0] == 0) {
                        $corvar[$i] = str_replace('0', '<span class="inline-negator">', $vars[$i]).'</span>';
                    }
                }
                $corvar = implode('&', $corvar);
                echo $corvar;
                if ($index !== $lastIndex) { 
                    echo ', ';
                }
            }
            echo '</sk></div>';
        } while ($implicantMatrix != $currentMatrix);
        
        $input = $_POST['inputField'];
        if (strpos($input, '0') === false) {
            echo '<h2>Результат склейки в константу:</h2>';
            echo '<div class="scroll-container"><sk>';
            echo '1';
            echo '</sk></div>';
            $implicantMatrix = [1];
        }

        $matrix = $implicantMatrix;
        $table = [];
    
        // замена негатора на 0
        for ($i = 0; $i < count($terms); $i++) {
            $terms[$i] = str_replace(['(', ')', '<span class="inline-negator">', '</span>'], ['', '', '0', ''], $terms[$i]);
        }
        for ($i = 0; $i < count($matrix); $i++) {
            $matrix[$i] = str_replace(['(', ')', '<span class="inline-negator">', '</span>'], ['', '', '0', ''], $matrix[$i]);
        }
    
        // работа с крестиками
        $header = array_merge([''], $terms);
        $table[] = $header;
        foreach ($matrix as $implicant) {
            $row = [$implicant];
            $variables = explode('&', $implicant);
            foreach ($terms as $term) {
                $boo = true;
                for ($i = 0; $i < count($variables); $i++) {
                    $pos = strpos($term, $variables[$i]);
                    if ($pos !== false && $boo !== false) {
                        if ($pos > 0 && isset($term[$pos-1]) && $term[$pos-1] === '0') {
                            $boo = false;
                        }
                    } else {
                        $boo = false;
                    }
                    if ($variables[$i] == 1) $boo = 1;
                }
                $row[] = $boo ? '<span class="inline-bigcross">+</span>' : '';
            }
            $table[] = $row;
        }
    
        // Возвращаем негатор
        for ($i = 0; $i < count($terms); $i++) {
            $verniteNegator = explode('&', $terms[$i]);
            for ($j = 0; $j < count($verniteNegator); $j++) {
                if (strpos($verniteNegator[$j], '0') !== false) {
                    $verniteNegator[$j] = str_replace('0', '<span class="inline-negator">', $verniteNegator[$j]);
                    $verniteNegator[$j].='</span>';
                }
            }
            $terms[$i] = implode('&', $verniteNegator);
        }
        $header = array_merge([''], $terms);
        $table[0] = $header;
        for ($i = 0; $i < count($matrix); $i++) {
            $verniteNegator = explode('&', $matrix[$i]);
            for ($j = 0; $j < count($verniteNegator); $j++) {
                if (strpos($verniteNegator[$j], '0') !== false) {
                    $verniteNegator[$j] = str_replace('0', '<span class="inline-negator">', $verniteNegator[$j]);
                    $verniteNegator[$j].='</span>';
                }
            }
            $matrix[$i] = implode('&', $verniteNegator);
        }
        // чиним боковую шапку
        for ($i = 1; $i < count($table); $i++) {
            $table[$i][0] = $matrix[$i-1];
        }
        
        return $table;
    }
    
    function displayMatr($table) {
        if ($table === null) return;
        echo '<table border="1">';
        foreach ($table as $rowIndex => $row) {
            echo '<tr>';
            foreach ($row as $cellIndex => $cell) {
                echo '<td>' .$cell . '</td>';
            }
            echo '</tr>';
        }
        echo '</table>';
    }

    function findMinimalAndRedundantForms($table) { 
        $coreImplicantsInd = [];
        for ($i = 1; $i < count($table[0]); $i++) {
            $onlyPlus = 0;
            foreach (array_column($table, $i) as $value) {
                if (strpos($value, '+')) {
                    $onlyPlus++;
                }
            }
            if ($onlyPlus == 1) {
                $coreImplicantsInd[] = array_search('<span class="inline-bigcross">+</span>', array_column($table, $i));
            }
        }
        $allForms = minimazeAllCovers($table, find_all_covers($table, $coreImplicantsInd, array_values(array_diff(range(1, count($table)-1), $coreImplicantsInd))));
        $allIn = [];
        if (count($allForms) == 1) {
            $newFormer = [];
            $form = $allForms[0];
            foreach ($form as $ind) {
                $newFormer[] = '('.array_column($table, 0)[$ind].')';
            }
            $allIn = [implode('∨', $newFormer)];
        }
        else {
            foreach ($allForms as $form) {
            $newFormer = [];
            foreach ($form as $ind) {
                $newFormer[] = '('.array_column($table, 0)[$ind].')';
            }
            if (count($newFormer) > 1) {
                $allIn[] = implode('∨', $newFormer);
            }
            else {
                $allIn[] = $newFormer;
            }
            }
        }
        $minimalForms = findMinOrStrings($allIn);
        $tupicalForms = array_diff($allIn, $minimalForms);
        $minimalForms = arrayFilter($minimalForms);
        $tupicalForms = arrayFilter($tupicalForms);
        $tupicalForms = array_unique($tupicalForms);
        $minimalForms = array_unique($minimalForms);
        echo '<h2>Тупиковые формы:</h2>';
        echo '<div class="scroll-container"><sk>';
        if (count($tupicalForms) > 0) {
            $lastIndex = count($tupicalForms) - 1;
            foreach ($tupicalForms as $indeh => $form) {
                echo $form;
                if ($indeh !== $lastIndex) { 
                    echo ', ';
                }
            }
        }
        else {
            echo 'Нет тупиковых форм.';
        }
        echo '</sk></div>';

        echo '<h2>Минимальные формы:</h2>';
        echo '<div class="scroll-container"><sk>';
        $lastIndex = count($minimalForms) - 1;
        foreach ($minimalForms as $indeh => $form) {
            echo $form;
            if ($indeh !== $lastIndex) { 
                echo ', ';
            }
        }
        echo '</sk></div>';
    }

    function arrayFilter($array) {
        $filteredArray = [];
            foreach ($array as $value) {
                if (!is_null($value) && $value !== '') {
                    $filteredArray[] = $value;
                }
            }
            return $filteredArray;
        }

    function findMinOrStrings($arrayOfStrings) {
        $minCount = PHP_INT_MAX;
        $result = [];
    
        foreach ($arrayOfStrings as $string) {
            $count = substr_count($string, '∨');
            if ($count < $minCount) {
                $minCount = $count;
                $result = [$string];
            } elseif ($count == $minCount) {
                $result[] = $string;
            }
        }
    
        return $result;
    }

    function remove_redundant_elements($table, $cover) {
        foreach ($cover as $element) {
            $new_cover = array_diff($cover, [$element]);
            if (coverCheck($table, $new_cover)) {
                $cover = $new_cover;
            }
        }
        return $cover;
    }
    
    function minimazeAllCovers($table, $covers) {
        $minimizedCovers = [];
        foreach ($covers as $cover) {
            $cover = remove_redundant_elements($table, $cover);
            sort($cover); // Сортируем элементы во вложенных массивах
            if (!in_array($cover, $minimizedCovers)) {
                $minimizedCovers[] = $cover;
            }
        }
        return remove_duplicate_arrays(remove_duplicate_elements($minimizedCovers));
    }
    
    function find_all_covers($table, $requiredImplicants, $optionalImplicants, $current_cover = [], $all_covers = []) {
        $current_cover = array_merge($current_cover, $requiredImplicants);
    
        if (coverCheck($table, $current_cover)) {
            $all_covers[] = $current_cover;
        }
    
        for ($i = 0; $i < count($optionalImplicants); $i++) {
            if (isset($optionalImplicants[$i])) {
                $new_cover = array_merge($current_cover, [$optionalImplicants[$i]]);
                $remaining_elems = array_slice($optionalImplicants, $i + 1);
                $all_covers = find_all_covers($table, [], $remaining_elems, $new_cover, $all_covers);
            }
        }
    
        return $all_covers;
    }

    function coverCheck($table, $rowNum) { // проверяет, есть ли полное покрытие импликантами с индексами rownum
        $tableColumns = array_fill(0, count($table[0]), false); $tableColumns[0] = true;
        for ($i = 1; $i < count($table[0]); $i++) {
            if (in_array($i, $rowNum)) {
                for ($j = 1; $j < count($table[$i]); $j++) {
                    if (strpos($table[$i][$j], '+')) $tableColumns[$j] = true;
                }
            }
        }
        if (in_array(false, $tableColumns)) return false;
        else return true;
    }

    function remove_duplicate_arrays($arrays) {
        $unique_arrays = [];
        foreach ($arrays as $array) {
            sort($array); // Сортируем элементы во вложенных массивах
            if (!in_array($array, $unique_arrays)) {
                $unique_arrays[] = $array;
            }
        }
        return $unique_arrays;
    }

    function remove_duplicate_elements($array) {
        $unique_array = [];
        foreach ($array as $subarray) {
            $unique_subarray = array_unique($subarray);
            sort($unique_subarray); // Сортируем элементы во вложенных массивах
            $unique_array[] = $unique_subarray;
        }
        return $unique_array;
    }
    ?>
</body>
</html>