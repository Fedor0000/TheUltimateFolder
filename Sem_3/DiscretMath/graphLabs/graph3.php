<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat+Alternates:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Rubik+Mono+One&display=swap" rel="stylesheet">
    <link rel="icon" href="https://i.pinimg.com/originals/6c/9b/b1/6c9bb186f583850cdf36e5d38930363e.png" type="image/x-icon">
    <script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
    <script id="MathJax-script" async
        src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js">
    </script>
    <title>Графы</title>
    <style>
    html, body {overflow-y: hidden;overflow-x: hidden;}
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
    body::-webkit-scrollbar {width: 10px;height: 10px;}
    body::-webkit-scrollbar-thumb {
        backdrop-filter: blur(15px);
        background: rgba(255, 255, 255, 0.2);
        border-radius: 4px;
    }
    body::-webkit-scrollbar-track {background: transparent;}
    body::-webkit-scrollbar-corner {background: transparent;}
    .header {padding: 10px;}
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
    .section, canvas { margin-left:auto;margin-right:auto; margin-bottom: 30px; padding: 10px; border: none; background: rgba(22, 206, 133, 0.01);backdrop-filter: blur(15px);border-radius: 8px;}
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
    button:hover {transform: translateY(3px);}
    button:active {background: rgba(50, 255, 0, 0.2);box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);}
    input[type="radio"] {
      display: inline-block;
      padding: 10px;
      margin-right: 10px;
      background-color: transparent;
      cursor: pointer;
      position: relative;
      text-align: center;
    }
    table {
        font-family: 'Montserrat Alternates', sans-serif;
        font-weight: 300;
        font-size: 30px;
        padding: 5px;
        margin-left: auto;
        margin-right: auto;
        border-collapse: collapse;
        backdrop-filter: blur(10px);
        border-radius: 15px;
        overflow: hidden;
    }
    th, td {padding: 3px 15px;text-align: center;transition: background-color 0.3s ease;border-bottom: 1px solid black;}
    th {background-color: rgba(0, 0, 0, 0.25);}
    td {background-color: rgba(0, 0, 0, 0.05);}
    td:hover {background-color: rgba(0, 0, 0, 0.3);}
    input[type="text"], input[type="number"], input[type="file"] {
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
        width: 50px;
    }
    input[type="file"] {cursor: pointer; width: 625px;}
    input[type="text"]::placeholder {color: rgba(255, 255, 255, 0.7);}
    input[type="text"]:focus, select:focus {outline: none;box-shadow: 0 0 10px 2px rgba(255, 0, 255, 1), 0 0 10px 2px rgba(0, 0, 255, 1);}
    input[type="number"]::-webkit-outer-spin-button, input[type="number"]::-webkit-inner-spin-button {-webkit-appearance: none;margin: 0;}
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
        backdrop-filter: blur(10px);background: rgba(200, 255, 200, 0.1);color: black;}
    .scroll-container {
        overflow: hidden;
        max-width: 80vw;
        width: min-content;
        height: min-content;
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
        font-size: 30px;
    }
    .scroll-container sk {
        font-family: 'Montserrat Alternates', sans-serif;
        font-weight: 300;
        font-size: 20px;
        text-align: center;
        vertical-align: top;
        line-height: 0;
    }
    .scroll-container::-webkit-scrollbar {height: 10px;}
    .scroll-container::-webkit-scrollbar-thumb {backdrop-filter: blur(10px);background: rgba(0, 0, 0, 0.3);border-radius: 4px;}
    .scroll-container::-webkit-scrollbar-track {background: transparent;}
    #canvasContainer {position: relative;}
    </style>
</head>
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

function getVertexName($index) {
    $letters = range('a','z');
    $name = '';
    do {
        $name = $letters[$index % 26] . $name;
        $index = intdiv($index, 26) - 1;
    } while ($index >= 0);
    return $name;
}

function getVertexIndexByName($name, $n) {
    $name = strtolower(trim($name));
    for ($i = 0; $i < $n; $i++) {
        if (getVertexName($i) === $name) {
            return $i;
        }
    }
    return -1;
}

function isMatrixSymmetric($matrix) {
    $n = count($matrix);
    for ($i = 0; $i < $n; $i++) {
        for ($j = 0; $j < $n; $j++) {
            if (abs($matrix[$i][$j] - $matrix[$j][$i]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

function computeBinaryMatrix($matrix) {
    $n = count($matrix);
    $binary = [];
    for ($i = 0; $i < $n; $i++) {
        $binary[$i] = [];
        for ($j = 0; $j < $n; $j++) {
            $binary[$i][$j] = (abs(floatval($matrix[$i][$j])) > 1e-9) ? 1 : 0;
        }
    }
    return $binary;
}

function matrixMultiply($A, $B) {
    $n = count($A);
    $C = array();
    for ($i = 0; $i < $n; $i++) {
        $C[$i] = array_fill(0, $n, 0);
        for ($j = 0; $j < $n; $j++) {
            for ($k = 0; $k < $n; $k++) {
                $C[$i][$j] += $A[$i][$k] * $B[$k][$j];
            }
        }
    }
    return $C;
}

function minC($a, $b) {
  if ($a != 0 && $b != 0) return min($a, $b);
  elseif ($a == 0 && $b != 0) return $b;
  elseif ($a != 0 && $b == 0) return $a;
  else return 0;
}
function addC($a, $b) {
  if ($a != 0 && $b != 0) return $a + $b;
  else return 0;
}
function shimbel($A, $min, $power) {
  if ($power == 0) return 0;
  if ($power == 1) return $A;
  $B = $A; // Исходная матрица
  $current = $A; // Текущая матрица (A^1)
  for ($pow = 2; $pow <= $power; $pow++) {
    $C = [];
    for ($i = 0; $i < count($current); $i++) {
      $row = [];
      for ($k = 0; $k < count($B); $k++) {
        $elems = 0;
        for ($j = 0; $j < count($B); $j++) {
          $elem = addC($current[$i][$j], $B[$j][$k]);
          if ($min) {
            $elems = minC($elems, $elem);
          } else {
            $elems = max($elems, $elem);
          }
        }
        $row[] = $elems;
      }
      $C[] = $row;
    }
    $current = $C; // Обновляем текущую матрицу для следующей итерации
  }
  return $current;
}

function matrixAdd($A, $B) {
    $n = count($A);
    $C = array();
    for ($i = 0; $i < $n; $i++) {
        $C[$i] = array();
        for ($j = 0; $j < $n; $j++) {
            $C[$i][$j] = $A[$i][$j] + $B[$i][$j];
        }
    }
    return $C;
}

function matrixToLatex($matrix) {
    $lines = [];
    foreach ($matrix as $row) {
        $lines[] = implode(" & ", $row);
    }
    return "\\begin{pmatrix}" . implode(" \\\\ ", $lines) . "\\end{pmatrix}";
}

function computePathsCount($binary) {
    $n = count($binary);
    $paths = $binary;
    $power = $binary;
    $explanation = "";
    $explanation .= " \\(A = " . matrixToLatex($binary) . "\\) ; ";
    for ($p = 2; $p <= $n; $p++) {
        $power = matrixMultiply($power, $binary);
        $paths = matrixAdd($paths, $power);
        $explanation .= " \\(A^{$p} = " . matrixToLatex($power) . "\\) ; ";
    }
    return [$paths, $explanation];
}

function getConnectedComponentsUndirected($binary) {
    $n = count($binary);
    $visited = array_fill(0, $n, false);
    $components = [];
    for ($i = 0; $i < $n; $i++) {
        if (!$visited[$i]) {
            $component = [];
            dfsUndirected($i, $binary, $visited, $component);
            $components[] = $component;
        }
    }
    return $components;
}
function dfsUndirected($v, $binary, &$visited, &$component) {
    $visited[$v] = true;
    $component[] = $v;
    $n = count($binary);
    for ($w = 0; $w < $n; $w++) {
        if ($binary[$v][$w] && !$visited[$w]) {
            dfsUndirected($w, $binary, $visited, $component);
        }
    }
}

function getStronglyConnectedComponents($binary) {
    $n = count($binary);
    $visited = array_fill(0, $n, false);
    $order = [];
    for ($i = 0; $i < $n; $i++) {
        if (!$visited[$i]) {
            dfsOrder($i, $binary, $visited, $order);
        }
    }
    $transpose = [];
    for ($i = 0; $i < $n; $i++) {
        $transpose[$i] = array_fill(0, $n, 0);
    }
    for ($i = 0; $i < $n; $i++) {
        for ($j = 0; $j < $n; $j++) {
            $transpose[$j][$i] = $binary[$i][$j];
        }
    }
    $visited = array_fill(0, $n, false);
    $components = [];
    while ($order) {
        $v = array_pop($order);
        if (!$visited[$v]) {
            $component = [];
            dfsUndirected($v, $transpose, $visited, $component);
            $components[] = $component;
        }
    }
    return $components;
}
function dfsOrder($v, $binary, &$visited, &$order) {
    $visited[$v] = true;
    $n = count($binary);
    for ($w = 0; $w < $n; $w++) {
        if ($binary[$v][$w] && !$visited[$w]) {
            dfsOrder($w, $binary, $visited, $order);
        }
    }
    $order[] = $v;
}

function dijkstra($matrix, $source) {
    $n = count($matrix);
    $dist = array_fill(0, $n, INF);
    $prev = array_fill(0, $n, null);
    $dist[$source] = 0;
    $Q = range(0, $n - 1);
    while (!empty($Q)) {
        $min = INF;
        $u = null;
        foreach ($Q as $v) {
            if ($dist[$v] < $min) {
                $min = $dist[$v];
                $u = $v;
            }
        }
        if ($u === null) break;
        $index = array_search($u, $Q);
        if ($index !== false) {
            array_splice($Q, $index, 1);
        }
        for ($v = 0; $v < $n; $v++) {
            if (abs(floatval($matrix[$u][$v])) > 1e-9) {
                $alt = $dist[$u] + floatval($matrix[$u][$v]);
                if ($alt < $dist[$v]) {
                    $dist[$v] = $alt;
                    $prev[$v] = $u;
                }
            }
        }
    }
    return [$dist, $prev];
}
function reconstructPath($prev, $source, $target) {
    $path = [];
    for ($v = $target; $v !== null; $v = $prev[$v]) {
        array_unshift($path, $v);
        if ($v == $source) break;
    }
    if (reset($path) != $source) {
        return [];
    }
    return $path;
}

function bfsTraversal($binary, $start) {
    $n = count($binary);
    $visited = array_fill(0, $n, false);
    $queue = [];
    $order = [];
    $visited[$start] = true;
    $queue[] = $start;
    while (!empty($queue)) {
        $v = array_shift($queue);
        $order[] = $v;
        for ($w = 0; $w < $n; $w++) {
            if ($binary[$v][$w] && !$visited[$w]) {
                $visited[$w] = true;
                $queue[] = $w;
            }
        }
    }
    return $order;
}

function dfsTraversal($binary, $start) {
    $n = count($binary);
    $visited = array_fill(0, $n, false);
    $order = [];
    dfsRecursive($start, $binary, $visited, $order);
    return $order;
}
function dfsRecursive($v, $binary, &$visited, &$order) {
    $visited[$v] = true;
    $order[] = $v;
    $n = count($binary);
    for ($w = 0; $w < $n; $w++) {
        if ($binary[$v][$w] && !$visited[$w]) {
            dfsRecursive($w, $binary, $visited, $order);
        }
    }
}

function getWeakComponents($binary) {
    $n = count($binary);
    $undirected = [];
    for($i=0; $i<$n; $i++){
        $undirected[$i] = [];
        for($j=0; $j<$n; $j++){
            $undirected[$i][$j] = ($binary[$i][$j] || $binary[$j][$i]) ? 1 : 0;
        }
    }
    return getConnectedComponentsUndirected($undirected);
}

function prim($matrix) {
  $n = count($matrix);
  $selected = array_fill(0, $n, false);
  $mst = array_fill(0, $n, array_fill(0, $n, 0));
  $total = 0;
  
  $selected[0] = true;
  for ($count = 0; $count < $n-1; $count++) {
      $min = INF;
      $x = $y = 0;
      for ($i = 0; $i < $n; $i++) {
          if ($selected[$i]) {
              for ($j = 0; $j < $n; $j++) {
                  if (!$selected[$j] && $matrix[$i][$j] > 0) {
                      if ($matrix[$i][$j] < $min) {
                          $min = $matrix[$i][$j];
                          $x = $i;
                          $y = $j;
                      }
                  }
              }
          }
      }
      $mst[$x][$y] = $min;
      $mst[$y][$x] = $min;
      $selected[$y] = true;
      $total += $min;
  }
  return [$mst, $total];
}

function kruskal($matrix) {
  $n = count($matrix);
  $edges = [];
  for ($i = 0; $i < $n; $i++) {
      for ($j = $i+1; $j < $n; $j++) {
          if ($matrix[$i][$j] > 0) {
              $edges[] = [$i, $j, $matrix[$i][$j]];
          }
      }
  }
  
  usort($edges, function($a, $b) { return $a[2] - $b[2]; });
  
  $parent = range(0, $n-1);
  $rank = array_fill(0, $n, 0);
  
  $find = function($u) use (&$parent, &$find) {
      if ($parent[$u] != $u) {
          $parent[$u] = $find($parent[$u]);
      }
      return $parent[$u];
  };

  $union = function($u, $v) use (&$parent, &$rank, $find) { // Добавлено $find в use
      $uRoot = $find($u);
      $vRoot = $find($v);
      if ($uRoot == $vRoot) return false;
      if ($rank[$uRoot] < $rank[$vRoot]) {
          $parent[$uRoot] = $vRoot;
      } else {
          $parent[$vRoot] = $uRoot;
          if ($rank[$uRoot] == $rank[$vRoot]) $rank[$uRoot]++;
      }
      return true;
  };
  
  $mst = array_fill(0, $n, array_fill(0, $n, 0));
  $total = 0;
  foreach ($edges as $edge) {
      list($u, $v, $w) = $edge;
      if ($union($u, $v)) {
          $mst[$u][$v] = $w;
          $mst[$v][$u] = $w;
          $total += $w;
      }
  }
  return [$mst, $total];
}

function isGraphConnected($matrix) {
  $n = count($matrix);
  if ($n === 0) return false;
  
  // Создаем бинарную матрицу смежности
  $binary = [];
  foreach ($matrix as $row) {
      $binary[] = array_map(function($w) { return $w > 0 ? 1 : 0; }, $row);
  }
  
  // Запускаем обход из первой вершины
  $order = dfsTraversal($binary, 0);
  return count(array_unique($order)) === $n;
}

$step = isset($_POST['step']) ? $_POST['step'] : 'start';

if ($step === 'save_matrix') {
    if (!isset($_REQUEST['matrix_json'])) {
        echo "<p style='color:red;'>Нет данных для сохранения.</p><a href='?'>Вернуться</a>";
        exit;
    }
    $matrixData = json_decode($_REQUEST['matrix_json'], true);
    $output = "";
    foreach ($matrixData as $row) {
        $output .= implode(" ", $row) . "\n";
    }
    header('Content-Type: text/plain');
    header('Content-Disposition: attachment; filename="matrix.txt"');
    echo $output;
    exit;
}

$matrixData = [];
if (isset($_POST['matrix_json'])) {
    $matrixData = json_decode($_POST['matrix_json'], true);
}
$vertexPositions = [];
if (isset($_POST['vertex_positions'])) {
    $vertexPositions = json_decode($_POST['vertex_positions'], true);
}
?>
<script>
    function fileChanged(input) {
      if(input.files.length) { input.form.submit(); }
    }
    function randomizeMatrix() {
      const inputs = document.querySelectorAll("table input[type='text']");
      inputs.forEach(input => { input.value = Math.round(Math.random()); });
    }
    function saveMatrix() {
    const table = document.querySelector("table");
    const rows = table.querySelectorAll("tr");
    let content = "";
    // Пропускаем первую строку (заголовок)
    for (let i = 1; i < rows.length; i++) {
      const inputs = rows[i].querySelectorAll("input[type='text']");
      let rowValues = [];
      inputs.forEach(input => {
        rowValues.push(input.value);
      });
      content += rowValues.join(" ") + "\n";
    }
    const blob = new Blob([content], {type: "text/plain"});
    const a = document.createElement("a");
    a.href = URL.createObjectURL(blob);
    a.download = "matrix.txt";
    a.click();
    URL.revokeObjectURL(a.href);
  }
  function saveMST(matrix) {
    let content = "";
    // Проходим по каждой строке матрицы
    matrix.forEach(row => {
      // Объединяем элементы строки через пробел и добавляем перевод строки
      content += row.join(" ") + "\n";
    });
    // Создаем Blob из сформированного текста
    const blob = new Blob([content], { type: "text/plain" });
    // Создаем временную ссылку для скачивания файла
    const a = document.createElement("a");
    a.href = URL.createObjectURL(blob);
    a.download = "mst.txt";
    a.click();
    // Освобождаем ресурсы
    URL.revokeObjectURL(a.href);
  }
  // Функция переиндексации таблицы: обновляет атрибуты name и текст заголовков
  function reindexTable() {
  const table = document.querySelector("table");
  const rows = table.querySelectorAll("tr");
  // Обновляем первую строку (заголовки столбцов)
  const headerRow = rows[0];
  const headerCells = headerRow.querySelectorAll("th");
  for (let j = 1; j < headerCells.length; j++) {
    headerCells[j].textContent = getVertexNameJS(j - 1);
  }
  // Обновляем каждую последующую строку:
  for (let i = 1; i < rows.length; i++) {
    const cells = rows[i].querySelectorAll("th, td");
    // Первая ячейка строки – заголовок строки
    cells[0].textContent = getVertexNameJS(i - 1);
    // Остальные ячейки – input-поля
    for (let j = 1; j < cells.length; j++) {
      const input = cells[j].querySelector("input");
      input.name = `cell[${i - 1}][${j - 1}]`;
    }
  }
}

// Ищет индекс вершины по тексту в заголовке первой строки, затем удаляет соответствующий столбец из всех строк.
function removeVertex() {
  const name = document.querySelector("input[name='remove_name']").value.trim().toLowerCase();
  if (!name) { 
    alert("Введите имя вершины для удаления."); 
    return; 
  }
  const table = document.querySelector("table");
  const headerCells = table.querySelector("tr").querySelectorAll("th");
  let idx = -1;
  headerCells.forEach((th, i) => {
    if (i > 0 && th.textContent.trim().toLowerCase() === name) {
      idx = i - 1;
    }
  });
  if (idx === -1) {
    alert("Вершина не найдена.");
    return;
  }
  // Удаляем столбец idx+1 из каждой строки
  const rows = table.querySelectorAll("tr");
  rows.forEach(row => {
    const cells = row.querySelectorAll("th, td");
    if (cells[idx + 1]) {
      cells[idx + 1].remove();
    }
  });
  reindexTable();
}

// Добавляет новый столбец к каждой строке и новую строку в конец таблицы, затем переиндексирует.
function reindexTable() {
  const table = document.querySelector("table");
  const rows = table.querySelectorAll("tr");
  // Обновляем первую строку (заголовки столбцов)
  const headerRow = rows[0];
  const headerCells = headerRow.querySelectorAll("th");
  for (let j = 1; j < headerCells.length; j++) {
    headerCells[j].textContent = getVertexNameJS(j - 1);
  }
  // Обновляем каждую строку данных
  for (let i = 1; i < rows.length; i++) {
    const cells = rows[i].querySelectorAll("th, td");
    // Первая ячейка – заголовок строки
    cells[0].textContent = getVertexNameJS(i - 1);
    // Остальные ячейки – input-поля
    for (let j = 1; j < cells.length; j++) {
      const input = cells[j].querySelector("input");
      input.name = `cell[${i - 1}][${j - 1}]`;
    }
  }
}

// Ищет индекс вершины по заголовку первой строки, затем удаляет соответствующий столбец во всех строках.
function removeVertex() {
  const name = document.querySelector("input[name='remove_name']").value.trim().toLowerCase();
  if (!name) { 
    alert("Введите имя вершины для удаления."); 
    return; 
  }
  const table = document.querySelector("table");
  const headerCells = table.querySelector("tr").querySelectorAll("th");
  let idx = -1;
  // Ищем нужный столбец по заголовку (начиная со второго элемента)
  headerCells.forEach((th, i) => {
    if (i > 0 && th.textContent.trim().toLowerCase() === name) { 
      idx = i - 1; 
    }
  });
  if (idx === -1) { 
    alert("Вершина не найдена."); 
    return; 
  }
  // Получаем все строки таблицы
  const rows = table.querySelectorAll("tr");
  // Удаляем столбец с индексом idx+1 из каждой строки (если существует)
  rows.forEach(row => {
    const cells = row.querySelectorAll("th, td");
    if (cells[idx+1]) { 
      cells[idx+1].remove(); 
    }
  });
  // Удаляем строку данных с индексом idx+1 (первая строка – заголовок, далее данные)
  if (rows.length > idx+1) {
    rows[idx+1].remove();
  }
  // Даем браузеру время обновить DOM, затем переиндексируем таблицу
  setTimeout(reindexTable, 0);
}

// Добавляет новый столбец во все строки и новую строку в конец таблицы, затем переиндексирует.
function addVertex() {
  const table = document.querySelector("table");
  const rows = table.querySelectorAll("tr");
  const headerCells = rows[0].querySelectorAll("th");
  const colCount = headerCells.length - 1; // без первой пустой ячейки
  
  // Добавляем новый заголовочный столбец в первую строку
  const newTh = document.createElement("th");
  newTh.textContent = getVertexNameJS(colCount);
  rows[0].appendChild(newTh);
  
  // Для каждой строки (кроме первой) добавляем новую ячейку с input
  for (let i = 1; i < rows.length; i++) {
    const td = document.createElement("td");
    const input = document.createElement("input");
    input.type = "text";
    input.value = "0";
    input.pattern = "^-?\\d+(\\.\\d+)?$";
    td.appendChild(input);
    rows[i].appendChild(td);
  }
  
  // Добавляем новую строку со всеми ячейками
  const newRow = document.createElement("tr");
  const newRowHeader = document.createElement("th");
  newRowHeader.textContent = getVertexNameJS(rows.length - 1);
  newRow.appendChild(newRowHeader);
  for (let j = 0; j < colCount + 1; j++){
    const td = document.createElement("td");
    const input = document.createElement("input");
    input.type = "text";
    input.value = "0";
    input.pattern = "^-?\\d+(\\.\\d+)?$";
    td.appendChild(input);
    newRow.appendChild(td);
  }
  table.appendChild(newRow);
  setTimeout(reindexTable, 0);
}

// Простая JavaScript-версия функции getVertexName (аналог PHP)
function getVertexNameJS(index) {
  const letters = "abcdefghijklmnopqrstuvwxyz";
  let name = "";
  do {
    name = letters[index % 26] + name;
    index = Math.floor(index / 26) - 1;
  } while (index >= 0);
  return name;
}
</script>
<body>
<?php
if ($step === 'start'):
?>
  <h1>Лабораторная работа Графы: <span class="inline-heading">Южаков Ф.А.</span></h1>
  <h3>Построение графа по матрице смежности:</h3>
  <form method="post" enctype="multipart/form-data">
    <input type="hidden" name="step" value="matrix">
    <h2>Выберите способ задания матрицы:</h2>
    <label><input type="radio" name="input_method" value="manual" checked onclick="document.getElementById('manual_input').style.display='block';document.getElementById('file_input').style.display='none';"> Ввести вручную</label><br>
    <label><input type="radio" name="input_method" value="file" onclick="document.getElementById('manual_input').style.display='none';document.getElementById('file_input').style.display='block';"> Загрузить файл</label><br><br>
    <div id="manual_input">
      <label>Число вершин (целое, от 1 до 30): 
        <input type="number" name="matrix_size" min="1" max="30" step="1" required>
      </label>
    </div>
    <div id="file_input" style="display:none;">
      <label>Выберите файл с матрицей (только цифры, пробелы, точки): 
        <input type="file" name="matrix_file" accept=".txt" onchange="fileChanged(this)">
      </label>
    </div>
    <br>
    <button type="submit">Далее</button>
  </form>
<?php
elseif ($step === 'matrix'):
  if (isset($_POST['input_method']) && $_POST['input_method'] === 'file') {
      if (!isset($_FILES['matrix_file']) || $_FILES['matrix_file']['error'] != UPLOAD_ERR_OK) {
          echo "<p style='color:red;'>Ошибка загрузки файла.</p><a href='?'>Вернуться</a>";
          exit;
      }
      $content = file_get_contents($_FILES['matrix_file']['tmp_name']);
      $lines = preg_split('/\r\n|\r|\n/', trim($content));
      $matrix = [];
      foreach ($lines as $line) {
          if (!preg_match('/^[0-9.\s]+$/', $line)) {
              echo "<p style='color:red;'>Файл содержит недопустимые символы.</p><a href='?'>Вернуться</a>";
              exit;
          }
          $row = preg_split('/\s+/', trim($line));
          $matrix[] = $row;
      }
      $n = count($matrix);
      if ($n > 30) {
          echo "<p style='color:red;'>Максимальное число вершин – 30.</p><a href='?'>Вернуться</a>";
          exit;
      }
      foreach ($matrix as $row) {
          if (count($row) != $n) {
              echo "<p style='color:red;'>Матрица должна быть квадратной, а в строках должно быть одинаковое число элементов.</p><a href='?'>Вернуться</a>";
              exit;
          }
      }
      $matrixData = $matrix;
      $matrix_size = $n;
  } else {
      if (!isset($_POST['matrix_size']) || intval($_POST['matrix_size']) < 1 || intval($_POST['matrix_size']) > 30) {
          echo "<p style='color:red;'>Неверное число вершин.</p><a href='?'>Вернуться</a>";
          exit;
      }
      $matrix_size = intval($_POST['matrix_size']);
      $matrixData = [];
      for ($i = 0; $i < $matrix_size; $i++) {
          $matrixData[$i] = array_fill(0, $matrix_size, 0);
      }
  }
  ?>
  <h1>Лабораторная работа Графы: <span class="inline-heading">Южаков Ф.А.</span></h1>
  <h2>Заполните матрицу смежности</h2>
  <p>Вводите только числа (целые или вещественные). Значение 0 означает отсутствие ребра.</p>
  <div class="section">
  <form method="post">
    <input type="hidden" name="step" value="draw">
    <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
    <input type="hidden" name="vertex_positions" value='<?php echo json_encode([]); ?>'>
    <table>
      <tr>
        <th></th>
        <?php for ($j = 0; $j < $matrix_size; $j++): ?>
          <th><?php echo getVertexName($j); ?></th>
        <?php endfor; ?>
      </tr>
      <?php for ($i = 0; $i < $matrix_size; $i++): ?>
        <tr>
          <th><?php echo getVertexName($i); ?></th>
          <?php for ($j = 0; $j < $matrix_size; $j++): 
              $val = isset($matrixData[$i][$j]) ? $matrixData[$i][$j] : 0;
          ?>
            <td>
              <input type="text" name="cell[<?php echo $i; ?>][<?php echo $j; ?>]" value="<?php echo htmlspecialchars($val); ?>" pattern="^-?\d+(\.\d+)?$" required>
            </td>
          <?php endfor; ?>
        </tr>
      <?php endfor; ?>
    </table>
    <button type="submit" class="button">Вперед</button>
    &nbsp;&nbsp;
    <button type="button" onclick="randomizeMatrix()" class="button">Заполнить рандомом</button>
  </form>
  </div>
  <br>
  <form method="post">
    <input type="hidden" name="step" value="start">
    <button type="submit" class="button">Создать другой граф</button>
  </form>
<?php
elseif ($step === 'draw'):
    if (isset($_POST['subaction'])) {
        if (isset($_POST['cell'])) {
            $matrixData = $_POST['cell'];
        }
        $n = count($matrixData);
        if ($_POST['subaction'] === 'remove_vertex') {
            $removeName = strtolower(trim($_POST['remove_name']));
            $idxToRemove = -1;
            for ($i = 0; $i < $n; $i++) {
                if (getVertexName($i) === $removeName) {
                    $idxToRemove = $i;
                    break;
                }
            }
            if ($idxToRemove >= 0) {
                array_splice($matrixData, $idxToRemove, 1);
                foreach ($matrixData as &$row) {
                    array_splice($row, $idxToRemove, 1);
                }
            }
        }
        if ($_POST['subaction'] === 'add_vertex') {
            $n = count($matrixData);
            if ($n < 30) {
                for ($i = 0; $i < $n; $i++) {
                    $matrixData[$i][] = 0;
                }
                $matrixData[] = array_fill(0, $n+1, 0);
            }
        }
    }
    if (isset($_POST['cell'])) {
        $matrixData = $_POST['cell'];
    }
    $n = count($matrixData);
    for ($i = 0; $i < $n; $i++) {
        for ($j = 0; $j < $n; $j++) {
            if (!is_numeric($matrixData[$i][$j])) {
                echo "<p style='color:red;'>Все значения должны быть числами.</p><a href='?'>Вернуться</a>";
                exit;
            }
            $matrixData[$i][$j] = floatval($matrixData[$i][$j]);
        }
    }
    if ($n > 30) {
        echo "<p style='color:red;'>Максимальное число вершин – 30.</p><a href='?'>Вернуться</a>";
        exit;
    }
    $isSymmetric = isMatrixSymmetric($matrixData);
    $graphType = $isSymmetric ? "Неориентированный" : "Ориентированный";
    $vertices = [];
    for ($i = 0; $i < $n; $i++) {
        if (isset($vertexPositions[$i])) {
            $vertices[] = [
                'name' => getVertexName($i),
                'x' => $vertexPositions[$i]['x'],
                'y' => $vertexPositions[$i]['y']
            ];
        } else {
            $vertices[] = [
                'name' => getVertexName($i),
                'x' => 0,
                'y' => 0
            ];
        }
    }
    $edges = [];
    for ($i = 0; $i < $n; $i++) {
        for ($j = 0; $j < $n; $j++) {
            if (abs($matrixData[$i][$j]) < 1e-9) continue;
            if ($isSymmetric && $i > $j) continue;
            $edges[] = [
                'from' => $i,
                'to'   => $j,
                'weight' => $matrixData[$i][$j]
            ];
        }
    }
    $binary = computeBinaryMatrix($matrixData);
    list($pathsCount, $pathsExplanation) = computePathsCount($binary);
    if ($isSymmetric) {
        $groups = getConnectedComponentsUndirected($binary);
        $connectivityGroups = [];
        foreach ($groups as $g) {
            sort($g);
            $connectivityGroups[] = ['vertices' => $g, 'type' => "сильная"];
        }
    } else {
        $weakComponents = getWeakComponents($binary);
        $strongComponents = getStronglyConnectedComponents($binary);
        $connectivityGroups = [];
        foreach ($weakComponents as $wc) {
            foreach ($strongComponents as $sc) {
                if (in_array($wc[0], $sc)) {
                    $type = (count($wc) === count($sc) && !array_diff($wc, $sc)) ? 'сильная' : 'слабая';
                    break;
                }
            }
            sort($wc);
            $connectivityGroups[] = ['vertices' => $wc, 'type' => $type];
        }
    }
    $shortestTable = [];
    for ($i = 0; $i < $n; $i++) {
        list($dist, $prev) = dijkstra($matrixData, $i);
        $shortestTable[$i] = $dist;
    }
    $dijkstraResult = "";
    if (isset($_POST['subaction']) && $_POST['subaction'] === 'dijkstra') {
        $srcName = strtolower(trim($_POST['dijkstra_source']));
        $dstName = strtolower(trim($_POST['dijkstra_target']));
        $src = getVertexIndexByName($srcName, $n);
        $dst = getVertexIndexByName($dstName, $n);
        if ($src < 0 || $dst < 0) {
            $dijkstraResult = "Неверное имя вершины.";
        } else {
            list($dist, $prev) = dijkstra($matrixData, $src);
            $path = reconstructPath($prev, $src, $dst);
            if (empty($path)) {
                $dijkstraResult = "Путь не найден.";
            } else {
                $names = array_map('getVertexName', $path);
                $dijkstraResult = "Кратчайший путь: " . implode(" -> ", $names) . " (длина: " . $dist[$dst] . ")";
            }
        }
    }
    $bfsResult = "";
    if (isset($_POST['subaction']) && $_POST['subaction'] === 'bfs') {
        $startName = strtolower(trim($_POST['traversal_start']));
        $start = getVertexIndexByName($startName, $n);
        if ($start < 0) {
            $bfsResult = "Неверное имя вершины.";
        } else {
            $order = bfsTraversal($binary, $start);
            $names = array_map('getVertexName', $order);
            $bfsResult = "Обход в ширину: " . implode(" -> ", $names);
        }
    }
    $dfsResult = "";
    if (isset($_POST['subaction']) && $_POST['subaction'] === 'dfs') {
        $startName = strtolower(trim($_POST['traversal_start']));
        $start = getVertexIndexByName($startName, $n);
        if ($start < 0) {
            $dfsResult = "Неверное имя вершины.";
        } else {
            $order = dfsTraversal($binary, $start);
            $names = array_map('getVertexName', $order);
            $dfsResult = "Обход в глубину: " . implode(" -> ", $names);
        }
    }
    $mstError = ""; $mstMatrix = ""; $mstTotal = "";
    if (isset($_POST['subaction']) && in_array($_POST['subaction'], ['prim', 'kruskal'])) {
        if (!$isSymmetric) {
            $mstError = "Алгоритмы Прима и Краскала работают только с неориентированными графами";
        } else {
            $algorithm = $_POST['subaction'];
            
            // Проверка связности только для Прима
            if ($algorithm === 'prim' && !isGraphConnected($matrixData)) {
                $mstError = "Алгоритм Прима требует связный граф!";
            } else {
                list($mstMatrix, $mstTotal) = $algorithm == 'prim' ? prim($matrixData) : kruskal($matrixData);
            }
        }
    }
    $shimbResult = ""; $shimbMode = ""; $shimbError = ""; $pow = "";
    if (isset($_POST['subaction']) && in_array($_POST['subaction'], ['shimb'])) {
      $pow = strtolower(trim($_POST['paths']));
      if ($pow <= 0) $shimbError = "Введите число, большее нуля!";
      elseif (filter_var($pow, FILTER_VALIDATE_INT) === false) $shimbError = "Введите целое число!";
      else {
        $shimbMode = strtolower(trim($_POST['modes'])) == "false" ? false : true;
        $shimbResult = shimbel($matrixData, $shimbMode, $pow);
      }
    }
    ?>
    <h1>Лабораторная работа Графы: <span class="inline-heading">Южаков Ф.А.</span></h1>
    <h3>Граф. Тип: <?php echo $graphType; ?></h3>
    <form method="post" style="margin-bottom:10px;">
      <button type="submit" onclick="location.href='?'" class="button">Создать другой граф</button>
    </form>
    
    <div class="section">
      <h3>Редактирование матрицы смежности</h3>
      <form method="post" id="editForm">
        <input type="hidden" name="step" value="draw">
        <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
        <input type="hidden" name="vertex_positions" id="vertex_positions" value='<?php echo json_encode($vertexPositions); ?>'>
        <table>
          <tr>
            <th></th>
            <?php for ($j = 0; $j < $n; $j++): ?>
              <th><?php echo getVertexName($j); ?></th>
            <?php endfor; ?>
          </tr>
          <?php for ($i = 0; $i < $n; $i++): ?>
            <tr>
              <th><?php echo getVertexName($i); ?></th>
              <?php for ($j = 0; $j < $n; $j++): ?>
                <td>
                  <input type="text" name="cell[<?php echo $i; ?>][<?php echo $j; ?>]" value="<?php echo htmlspecialchars($matrixData[$i][$j]); ?>" pattern="^-?\d+(\.\d+)?$" required>
                </td>
              <?php endfor; ?>
            </tr>
          <?php endfor; ?>
        </table>
        <br>
        <button type="submit" class="button">Пересчитать</button>
        &nbsp;&nbsp;
        <label>Убрать вершину (напр. "b"):
          <input type="text" name="remove_name">
        </label>
        <button type="button" onclick="removeVertex()" class="button">Убрать вершину</button>
        &nbsp;&nbsp;
        <button type="button" onclick="addVertex()" class="button">Добавить вершину</button>
        &nbsp;&nbsp;
        <button type="button" onclick="randomizeMatrix()" class="button">Заполнить рандомом</button>
      </form>
    </div>
    
    <div id="canvasContainer">
      <canvas id="graphCanvas" width="900" height="700"></canvas>
    </div>
    
    <script>
      const vertices = <?php echo json_encode($vertices); ?>;
      const edges = <?php echo json_encode($edges); ?>;
      const vertexRadius = 20;
      const isUndirected = <?php echo $isSymmetric ? 'true' : 'false'; ?>;
      
      function initVertices() {
        const canvas = document.getElementById('graphCanvas');
        const cx = canvas.width / 2;
        const cy = canvas.height / 2;
        const radius = Math.min(cx, cy) - 50;
        const n = vertices.length;
        for (let i = 0; i < n; i++) {
          if (!vertices[i].x || !vertices[i].y) {
            const angle = 2 * Math.PI * i / n - Math.PI/2;
            vertices[i].x = cx + radius * Math.cos(angle);
            vertices[i].y = cy + radius * Math.sin(angle);
          }
        }
      }

      const canvas = document.getElementById('graphCanvas');
      const ctx = canvas.getContext('2d');
      
      ctx.lineWidth = 4;
      ctx.shadowBlur = 15;
      ctx.shadowColor = "rgba(49, 255, 227, 0.5)";
      
      function drawEdge(fromX, fromY, toX, toY, weight) {
        const headLength = 10;
        const dx = toX - fromX;
        const dy = toY - fromY;
        const angle = Math.atan2(dy, dx);
        const startX = fromX + vertexRadius * Math.cos(angle);
        const startY = fromY + vertexRadius * Math.sin(angle);
        const endX = toX - vertexRadius * Math.cos(angle);
        const endY = toY - vertexRadius * Math.sin(angle);
        ctx.strokeStyle = "#fff";
        ctx.fillStyle = "#fff";
        ctx.beginPath();
        ctx.moveTo(startX, startY);
        ctx.lineTo(endX, endY);
        ctx.stroke();
        if (!isUndirected) {
          ctx.beginPath();
          ctx.moveTo(endX, endY);
          ctx.lineTo(endX - headLength * Math.cos(angle - Math.PI/6),
                     endY - headLength * Math.sin(angle - Math.PI/6));
          ctx.lineTo(endX - headLength * Math.cos(angle + Math.PI/6),
                     endY - headLength * Math.sin(angle + Math.PI/6));
          ctx.lineTo(endX, endY);
          ctx.fill();
        }
        const labelX = startX + 0.75 * (endX - startX);
        const labelY = startY + 0.75 * (endY - startY);
        ctx.font = "24px Rubik Mono One";
        ctx.fillStyle = "#f0f";
        ctx.fillText(weight, labelX + 5, labelY - 5);
      }
      
      function drawLoop(x, y, weight) {
        ctx.strokeStyle = "#fff";
        ctx.fillStyle = "#fff";
        ctx.beginPath();
        ctx.arc(x, y - vertexRadius, vertexRadius/2, 0, 2*Math.PI);
        ctx.stroke();
        ctx.font = "24px Rubik Mono One";
        ctx.fillStyle = "#f0f";
        ctx.fillText(weight, x - 5, y - vertexRadius - vertexRadius/2 - 5);
      }
      
      function drawGraph() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        edges.forEach(edge => {
          const from = vertices[edge.from];
          const to = vertices[edge.to];
          if (edge.from === edge.to) {
            drawLoop(from.x, from.y, edge.weight);
          } else {
            drawEdge(from.x, from.y, to.x, to.y, edge.weight);
          }
        });
        vertices.forEach(vertex => {
          ctx.beginPath();
          ctx.arc(vertex.x, vertex.y, vertexRadius, 0, 2 * Math.PI);
          ctx.fillStyle = "rgba(255,255,255,0.3)";
          ctx.fill();
          ctx.strokeStyle = "#fff";
          ctx.stroke();
          ctx.font = "24px Rubik Mono One";
          const textWidth = ctx.measureText(vertex.name).width;
          ctx.fillStyle = "#f0f";
          ctx.fillText(vertex.name, vertex.x - textWidth/2, vertex.y + 10);
        });
      }
      
      let draggingVertex = null, offsetX, offsetY;
      canvas.addEventListener('mousedown', function(e) {
        const rect = canvas.getBoundingClientRect();
        const mouseX = e.clientX - rect.left;
        const mouseY = e.clientY - rect.top;
        vertices.forEach(vertex => {
          const dx = mouseX - (vertex.x + 9);
          const dy = mouseY - (vertex.y + 9);
          if (dx*dx + dy*dy <= Math.pow(vertexRadius * 1.6, 2)) {
            draggingVertex = vertex;
            offsetX = dx;
            offsetY = dy;
          }
        });
      });
      canvas.addEventListener('mousemove', function(e) {
        if (draggingVertex) {
          const rect = canvas.getBoundingClientRect();
          draggingVertex.x = e.clientX - rect.left - offsetX - 5;
          draggingVertex.y = e.clientY - rect.top - offsetY - 5;
          drawGraph();
        }
      });
      canvas.addEventListener('mouseup', () => { draggingVertex = null; });
      canvas.addEventListener('mouseleave', () => { draggingVertex = null; });
      
      initVertices();
      drawGraph();
      document.getElementById("editForm")?.addEventListener("submit", function(e) {
          document.getElementById("vertex_positions").value = JSON.stringify(vertices);
      });
    </script>
    
    <div class="section">
      <h3>Бинарная матрица существования дорог</h3>
      <table>
        <tr>
          <th></th>
          <?php for ($j = 0; $j < $n; $j++): ?>
            <th><?php echo getVertexName($j); ?></th>
          <?php endfor; ?>
        </tr>
        <?php for ($i = 0; $i < $n; $i++): ?>
          <tr>
            <th><?php echo getVertexName($i); ?></th>
            <?php for ($j = 0; $j < $n; $j++): ?>
              <td><?php echo $binary[$i][$j]; ?></td>
            <?php endfor; ?>
          </tr>
        <?php endfor; ?>
      </table>
    </div>
    
    <div class="section">
      <h3>Матрица достижимости (количество путей)</h3>
      <table>
        <tr>
          <th></th>
          <?php for ($j = 0; $j < $n; $j++): ?>
            <th><?php echo getVertexName($j); ?></th>
          <?php endfor; ?>
        </tr>
        <?php for ($i = 0; $i < $n; $i++): ?>
          <tr>
            <th><?php echo getVertexName($i); ?></th>
            <?php for ($j = 0; $j < $n; $j++): ?>
              <td><?php echo $pathsCount[$i][$j]; ?></td>
            <?php endfor; ?>
          </tr>
        <?php endfor; ?>
      </table>
      <div class="scroll-container"><sk><?php echo $pathsExplanation; ?></sk></div>
    </div>
    
    <div class="section">
      <h3>Компоненты связности</h3>
      <?php 
        if ($isSymmetric) {
            $groups = getConnectedComponentsUndirected($binary);
            $connectivityGroups = [];
            foreach ($groups as $g) {
                sort($g);
                $connectivityGroups[] = ['vertices' => $g, 'type' => "сильная"];
            }
        } else {
            $weakComponents = getWeakComponents($binary);
            $strongComponents = getStronglyConnectedComponents($binary);
            $connectivityGroups = [];
            foreach ($weakComponents as $wc) {
                foreach ($strongComponents as $sc) {
                    if (in_array($wc[0], $sc)) {
                        $type = (count($wc) === count($sc) && !array_diff($wc, $sc)) ? 'сильная' : 'слабая';
                        break;
                    }
                }
                sort($wc);
                $connectivityGroups[] = ['vertices' => $wc, 'type' => $type];
            }
        }
      ?>
      <table>
        <tr>
          <th>Номер группы</th>
          <th>Вершины</th>
          <th>Тип связности</th>
        </tr>
        <?php foreach ($connectivityGroups as $idx => $group): 
                $names = array_map('getVertexName', $group['vertices']);
        ?>
          <tr>
            <td><?php echo ($idx+1); ?></td>
            <td><?php echo implode(", ", $names); ?></td>
            <td><?php echo $group['type']; ?></td>
          </tr>
        <?php endforeach; ?>
      </table>
    </div>
    
    <div class="section">
      <h3>Таблица кратчайших расстояний (Дейкстра)</h3>
      <table>
        <tr>
          <th>От \ До</th>
          <?php for ($j = 0; $j < $n; $j++): ?>
            <th><?php echo getVertexName($j); ?></th>
          <?php endfor; ?>
        </tr>
        <?php for ($i = 0; $i < $n; $i++): ?>
          <tr>
            <th><?php echo getVertexName($i); ?></th>
            <?php for ($j = 0; $j < $n; $j++): ?>
              <td><?php echo ($shortestTable[$i][$j]===INF) ? "∞" : $shortestTable[$i][$j]; ?></td>
            <?php endfor; ?>
          </tr>
        <?php endfor; ?>
      </table>
      <label>Найти кратчайший маршрут:</label>
      <form method="post">
        <input type="hidden" name="step" value="draw">
        <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
        <input type="hidden" name="vertex_positions" id="vertex_positions2" value='<?php echo json_encode($vertexPositions); ?>'>
        <label>От (имя вершины, напр. "a"): <input type="text" name="dijkstra_source" required></label>
        <label>До: <input type="text" name="dijkstra_target" required></label>
        <input type="hidden" name="subaction" value="dijkstra">
        <button type="submit" class="button">Найти маршрут</button>
      </form>
      <?php if ($dijkstraResult): ?>
        <div class="scroll-container"><sk><?php echo $dijkstraResult; ?></sk></div>
      <?php endif; ?>
    </div>
    
    <div class="section">
      <h3>Обходы</h3>
      <form method="post" style="margin-bottom:10px;">
        <input type="hidden" name="step" value="draw">
        <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
        <input type="hidden" name="vertex_positions" value='<?php echo json_encode($vertexPositions); ?>'>
        <label>Начальная вершина (имя, напр. "a"): <input type="text" name="traversal_start" required></label>
        <input type="hidden" name="subaction" value="bfs">
        <button type="submit" class="button">Обход в ширину (BFS)</button>
      </form>
      <?php if ($bfsResult): ?>
        <div class="scroll-container"><sk><?php echo $bfsResult; ?></sk></div>
      <?php endif; ?>
      <form method="post">
        <input type="hidden" name="step" value="draw">
        <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
        <input type="hidden" name="vertex_positions" value='<?php echo json_encode($vertexPositions); ?>'>
        <label>Начальная вершина (имя, напр. "a"): <input type="text" name="traversal_start" required></label>
        <input type="hidden" name="subaction" value="dfs">
        <button type="submit" class="button">Обход в глубину (DFS)</button>
      </form>
      <?php if ($dfsResult): ?>
        <div class="scroll-container"><sk><?php echo $dfsResult; ?></sk></div>
      <?php endif; ?>
    </div>

    <div class="section">
        <h3>Построение остовного дерева</h3>
        <form method="post">
          <input type="hidden" name="step" value="draw">
          <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
          <input type="hidden" name="vertex_positions" id="vertex_positions2" value='<?php echo json_encode($vertexPositions); ?>'>
          <input type="hidden" name="subaction" value="prim">
          <button type="submit" class="button">Алгоритм Прима</button>
        </form>
        <form method="post">
          <input type="hidden" name="step" value="draw">
          <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
          <input type="hidden" name="vertex_positions" id="vertex_positions2" value='<?php echo json_encode($vertexPositions); ?>'>
          <input type="hidden" name="subaction" value="kruskal">
          <button type="submit" class="button">Алгоритм Краскала</button>
        </form>

        <?php if ($mstError !== ""): ?>
            <p style="color: red"><?= $mstError ?></p>
        <?php elseif ($mstMatrix): ?>
            <div>
                <label>Матрица остовного дерева:</label>
                <table>
                    <tr><th></th><?php for ($i=0; $i<$n; $i++) echo "<th>".getVertexName($i)."</th>"; ?></tr>
                    <?php for ($i=0; $i<$n; $i++): ?>
                        <tr>
                            <th><?= getVertexName($i) ?></th>
                            <?php for ($j=0; $j<$n; $j++): ?>
                                <td><?= $mstMatrix[$i][$j] ?: 0 ?></td>
                            <?php endfor; ?>
                        </tr>
                    <?php endfor; ?>
                </table>
                <label>Вес остовного дерева: <?= $mstTotal ?></label>
            </div>
            <form method="post">
              <input type="hidden" name="step" value="draw">
              <input type="hidden" name="matrix_json" value='<?php echo json_encode($mstMatrix); ?>'>
              <button type="submit">Открыть матрицу дерева как граф</button>
            </form>
            <button type="button" onclick=<?php echo "saveMST(".json_encode($mstMatrix).")"?>>Сохранить матрицу дерева</button>
        <?php endif; ?>
    </div>

    <div class="section">
        <h3>Алгоритм Шимбелла</h3>
        <form method="post">
          <input type="hidden" name="step" value="draw">
          <input type="hidden" name="matrix_json" value='<?php echo json_encode($matrixData); ?>'>
          <input type="hidden" name="vertex_positions" id="vertex_positions2" value='<?php echo json_encode($vertexPositions); ?>'>
          <input type="hidden" name="subaction" value="shimb">
          <label>Количество переходов: <input type="number" name="paths" min="1" step="1" required></label>
          <button type="submit" name="modes" value="true" class="button">Минимальные пути</button>
          <button type="submit" name="modes" value="false" class="button">Максимальные пути</button>
        </form>
        <?php if ($shimbError !== ""): ?>
          <p style="color: red"><?= $shimbError ?></p>
        <?php elseif ($shimbResult): ?>
            <div>
                <label>Матрица путей Шимбелла (Режим: <?= $shimbMode ? "минимальные пути" : "максимальные пути" ?>, переходов: <?= $pow ?>):</label>
                <table>
                    <tr><th></th><?php for ($i=0; $i<$n; $i++) echo "<th>".getVertexName($i)."</th>"; ?></tr>
                    <?php for ($i=0; $i<$n; $i++): ?>
                        <tr>
                            <th><?= getVertexName($i) ?></th>
                            <?php for ($j=0; $j<$n; $j++): ?>
                                <td><?= $shimbResult[$i][$j] ?: 0 ?></td>
                            <?php endfor; ?>
                        </tr>
                    <?php endfor; ?>
                </table>
            </div>
        <?php endif; ?>
    </div>
    
    <button type="button" onclick="saveMatrix()" class="button">Сохранить таблицу смежности</button>  
<?php
endif;
?>
</body>
</html>