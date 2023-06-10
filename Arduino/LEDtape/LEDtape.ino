#include <Adafruit_NeoPixel.h>

const int DIN_PIN = 12;
const int SWITCH_POWER = 2;
const int SWITCH_STATE = 3;
const int LED_COUNT = 125; // the number of LED cell
int light_ratio[200];      // LED lights intensity

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    for (int i = 0; i <= 99; i++)
    {
        light_ratio[i] = i;
    }
    light_ratio[100] = 100;
    for (int i = 101; i <= 199; i++)
    {
        light_ratio[i] = 200 - i;
    }

    pixels.begin();
    Serial.begin(115200);
    pinMode(SWITCH_POWER, INPUT);
    pinMode(SWITCH_STATE, INPUT);

    Serial.println("Hello Arduino!");
}

float ratio = 1;
uint32_t red;
uint32_t orange;
uint32_t yellow;
uint32_t green;
uint32_t cyan;
uint32_t blue;
uint32_t purple;
uint32_t white;
int time_count1 = 0;
int time_count2 = 0;
int value1 = 0;
int value2 = 0;
int push_count = 0;
bool power_LED = true;
int state_LED = 0;
bool rain = false;

void loop()
{
    red = pixels.Color((int)(192 * ratio), 0, 0);
    orange = pixels.Color((int)(192 * ratio), (int)(32 * ratio), 0);
    yellow = pixels.Color((int)(192 * ratio), (int)(192 * ratio), 0);
    green = pixels.Color(0, (int)(192 * ratio), 0);
    cyan = pixels.Color(0, (int)(192 * ratio), (int)(192 * ratio));
    blue = pixels.Color(0, 0, (int)(192 * ratio));
    purple = pixels.Color((int)(192 * ratio), 0, (int)(192 * ratio));
    white = pixels.Color((int)(192 * ratio), (int)(192 * ratio), (int)(192 * ratio));
    uint32_t rainbow_color[] = {red, orange, yellow, green, cyan, blue, purple};

    pixels.clear();

    value1 = digitalRead(SWITCH_POWER);
    value2 = digitalRead(SWITCH_STATE);

    // update the count of time
    time_count1 += 1;
    time_count2 += 1;
    if (time_count1 >= 11)
    {
        time_count1 = 0;
    }
    if (time_count2 >= 200)
    {
        time_count2 = 0;
    }

    // receive information about weather
    if (Serial.available())
    {
        char recv = Serial.read();
        if (recv == 'r')
        {
            rain = true;
        }
        else
        {
            rain = false;
        }
        state_LED = 0;
    }

    // update state by the buttons
    if (value1 == 0)
    {
        power_LED = false;
    }
    else
    {
        power_LED = true;
    }

    if (value2 == 0)
    {
        push_count++;
    }
    else
    {
        push_count = 0;
    }
    if (push_count == 3)
    {
        state_LED++;
        if (state_LED == 6)
        {
            state_LED = 0;
        }
    }

    // change the color of LED according to the state
    if (power_LED == false)
    { // OFF
        for (int i = 0; i < LED_COUNT; i++)
        {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
    }
    else if (power_LED == true)
    { // ON
        // show weather
        if (state_LED == 0)
        {
            if (rain)
            {
                ratio = 1;
                cyan = pixels.Color(0, (int)(192 * ratio), (int)(192 * ratio));
                for (int i = 0; i < LED_COUNT; i++)
                {
                    pixels.setPixelColor(i, cyan);
                }
            }
            else
            {
                ratio = 1;
                orange = pixels.Color((int)(192 * ratio), (int)(32 * ratio), 0);
                for (int i = 0; i < LED_COUNT; i++)
                {
                    pixels.setPixelColor(i, orange);
                }
            }
        }
        else if (state_LED == 1)
        {
            ratio = 1;
            white = pixels.Color((int)(192 * ratio), (int)(192 * ratio), (int)(192 * ratio));
            for (int i = 0; i < LED_COUNT; i++)
            {
                pixels.setPixelColor(i, white);
            }
        }
        else if (state_LED == 2)
        {
            ratio = 1;
            red = pixels.Color((int)(192 * ratio), 0, 0);
            orange = pixels.Color((int)(192 * ratio), (int)(32 * ratio), 0);
            yellow = pixels.Color((int)(192 * ratio), (int)(192 * ratio), 0);
            green = pixels.Color(0, (int)(192 * ratio), 0);
            cyan = pixels.Color(0, (int)(192 * ratio), (int)(192 * ratio));
            blue = pixels.Color(0, 0, (int)(192 * ratio));
            purple = pixels.Color((int)(192 * ratio), 0, (int)(192 * ratio));
            white = pixels.Color((int)(192 * ratio), (int)(192 * ratio), (int)(192 * ratio));
            rainbow_color[0] = red;
            rainbow_color[1] = orange;
            rainbow_color[2] = yellow;
            rainbow_color[3] = green;
            rainbow_color[4] = cyan;
            rainbow_color[5] = blue;
            rainbow_color[6] = purple;
            for (int i = 0; i < LED_COUNT; i++)
            {
                pixels.setPixelColor(i, rainbow_color[i % 7]);
            }
        }
        else if (state_LED == 3)
        {
            for (int i = 0; i < LED_COUNT; i++)
            {
                ratio = (float)(((float)(0) + (float)((i + time_count1) % 11)) / (float)11);
                red = pixels.Color((int)(240 * ratio), 0, 0);
                orange = pixels.Color((int)(240 * ratio), (int)(40 * ratio), 0);
                yellow = pixels.Color((int)(240 * ratio), (int)(240 * ratio), 0);
                green = pixels.Color(0, (int)(240 * ratio), 0);
                cyan = pixels.Color(0, (int)(240 * ratio), (int)(240 * ratio));
                blue = pixels.Color(0, 0, (int)(240 * ratio));
                purple = pixels.Color((int)(240 * ratio), 0, (int)(240 * ratio));
                white = pixels.Color((int)(240 * ratio), (int)(240 * ratio), (int)(240 * ratio));
                rainbow_color[0] = red;
                rainbow_color[1] = orange;
                rainbow_color[2] = yellow;
                rainbow_color[3] = green;
                rainbow_color[4] = cyan;
                rainbow_color[5] = blue;
                rainbow_color[6] = purple;
                pixels.setPixelColor(i, rainbow_color[i % 7]);
            }
            delay(10);
        }
        else if (state_LED == 4)
        {
            for (int i = 0; i < LED_COUNT; i++)
            {
                ratio = (float)(((float)(1) + (float)(light_ratio[time_count2 % 200])) / (float)101);
                red = pixels.Color((int)(240 * ratio), 0, 0);
                orange = pixels.Color((int)(240 * ratio), (int)(40 * ratio), 0);
                yellow = pixels.Color((int)(240 * ratio), (int)(240 * ratio), 0);
                green = pixels.Color(0, (int)(240 * ratio), 0);
                cyan = pixels.Color(0, (int)(240 * ratio), (int)(240 * ratio));
                blue = pixels.Color(0, 0, (int)(240 * ratio));
                purple = pixels.Color((int)(240 * ratio), 0, (int)(240 * ratio));
                white = pixels.Color((int)(240 * ratio), (int)(240 * ratio), (int)(240 * ratio));
                rainbow_color[0] = red;
                rainbow_color[1] = orange;
                rainbow_color[2] = yellow;
                rainbow_color[3] = green;
                rainbow_color[4] = cyan;
                rainbow_color[5] = blue;
                rainbow_color[6] = purple;
                pixels.setPixelColor(i, rainbow_color[i % 7]);
            }
            delay(1);
        }
        else if (state_LED == 5)
        {
            for (int i = 0; i < LED_COUNT; i++)
            {
                pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            }
        }
    }

    pixels.show();
}
