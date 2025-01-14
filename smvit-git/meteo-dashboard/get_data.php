<?php

const TEMP_FILE = '/tmp/temperature.txt';
const HUM_FILE = '/tmp/humidity.txt';
const AIR_QUALITY_FILE = '/tmp/air_quality.txt';
const TVOC_FILE = '/tmp/tvoc.txt';
const ECO2_FILE = '/tmp/eco2.txt';

const MAPPING = [
    'temp' => TEMP_FILE,
    'humidity' => HUM_FILE,
    'air_quality' => AIR_QUALITY_FILE,
    'tvoc' => TVOC_FILE,
    'eco2' => ECO2_FILE
];

$output = [];
foreach (MAPPING as $key => $file) {
    if (!file_exists($file)) {
        $output[$key] = 0.0;
        continue;
    }

    $content = file_get_contents($file);
    if (empty($content)) {
        $output[$key] = 0.0;
        continue;
    }

    $output[$key] = floatval($content);
}

echo json_encode($output);
