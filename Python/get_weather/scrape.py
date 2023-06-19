import urllib

import requests

URL_API = "https://weather.tsukumijima.net/api/forecast"
PARAMS = {"city": "130010"}  # Tokyo
PARAMS_ENCODED = urllib.parse.urlencode(PARAMS)
URL = URL_API + "?" + PARAMS_ENCODED


def getChanceOfRain():
    try:
        response = requests.get(URL)
        response.raise_for_status()  # raise an error except for 200
    except requests.exceptions.RequestException as err:
        print("Error: {}".format(err))
    else:
        weather = response.json()
        rain = False
        for val in weather["forecasts"][0]["chanceOfRain"].values():
            # get the value of the chance of rain
            try:
                chance = int(val[:-1])  # remove the letter "%"
            except ValueError:  # this error will raise if "val" is "--%"
                pass
            else:
                if chance >= 50:
                    rain = True
        return rain


# test
if __name__ == "__main__":
    print(getChanceOfRain())
