async function refreshData() {
    const url = "get_data.php";
    try {
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error(`Response status: ${response.status}`);
        }

        const json = await response.json();
        document.getElementById('temp')!!.innerText = (json.temp as string) + "°C";
        document.getElementById('humidity')!!.innerText = json.humidity + "%";
        document.getElementById('airQualityIndex')!!.innerText = json.air_quality;
        document.getElementById('tvoc')!!.innerText = json.tvoc + ' ppb';
        document.getElementById('eco2')!!.innerText = json.eco2 + ' ppm';
        console.log(json);
    } catch (error: any) {
        console.error(error.message);
    }

    setTimeout(() => refreshData(), 1000);
}

setTimeout(() => refreshData(), 1000);

