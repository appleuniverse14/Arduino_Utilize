import scrape
import serCom

rain = scrape.getChanceOfRain()
serCom.serialCommunication(rain)
