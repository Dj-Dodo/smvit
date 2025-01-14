"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
function refreshData() {
    return __awaiter(this, void 0, void 0, function* () {
        const url = "get_data.php";
        try {
            const response = yield fetch(url);
            if (!response.ok) {
                throw new Error(`Response status: ${response.status}`);
            }
            const json = yield response.json();
            document.getElementById('temp').innerText = json.temp + "°C";
            document.getElementById('humidity').innerText = json.humidity + "%";
            document.getElementById('airQualityIndex').innerText = json.air_quality;
            document.getElementById('tvoc').innerText = json.tvoc + ' ppb';
            document.getElementById('eco2').innerText = json.eco2 + ' ppm';
            console.log(json);
        }
        catch (error) {
            console.error(error.message);
        }
        setTimeout(() => refreshData(), 1000);
    });
}
setTimeout(() => refreshData(), 1000);
