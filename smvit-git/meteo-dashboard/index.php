<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MeteoWiz</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-800 text-white">
    <div class="flex flex-row flex-wrap gap-4 justify-center mt-10">
        <div class="bg-gray-900 min-w-64 p-3 rounded">
            <h1 class="text-2xl mb-3 inline-block">Temperature</h1>
            <h2 id="temp" class="text-center text-8xl">0°C</h2>
        </div>
        
        <div class="bg-gray-900 min-w-64 p-3 rounded">
            <h1 class="text-2xl mb-3 inline-block">Humidity</h1>
            <h2 id="humidity" class="text-center text-8xl">0%</h2>
        </div>

        <div class="bg-gray-900 min-w-64 p-3 rounded">
            <h1 class="text-2xl mb-3 inline-block">Air Quality Index</h1>
            <h2 id="airQualityIndex" class="text-center text-8xl">0</h2>
        </div>

        <div class="bg-gray-900 min-w-64 p-3 rounded">
            <h1 class="text-2xl mb-3 inline-block">TVOC</h1>
            <h2 id="tvoc" class="text-center text-8xl">0</h2>
        </div>

        <div class="bg-gray-900 min-w-64 p-3 rounded">
            <h1 class="text-2xl mb-3 inline-block">eCO2</h1>
            <h2 id="eco2" class="text-center text-8xl">0</h2>
        </div>
    </div>    

    <script>var exports = {};</script>
    <script type="text/javascript" src="js/home.js"></script>
</body>
</html>
