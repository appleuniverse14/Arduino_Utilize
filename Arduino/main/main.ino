#include <Adafruit_NeoPixel.h>

const int DIN_PIN = 12; // D1
const int SWITCH_POWER = 2;
const int SWITCH_STATE = 3;
const int LED_COUNT = 125; // LEDの数
int light_ratio[200];

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    pixels.begin();
    for (int i = 0; i <= 99; i++)
    {
        light_ratio[i] = i;
    }
    light_ratio[100] = 100;
    for (int i = 101; i <= 199; i++)
    {
        light_ratio[i] = 200 - i;
    }

    pinMode(SWITCH_POWER, INPUT);
    pinMode(SWITCH_STATE, INPUT);
    Serial.begin(115200);
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
int state_LED = 0;

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
    //    Serial.println( value1);
    //    Serial.println( value2);
    Serial.println(push_count);
    Serial.println(state_LED);

    // update state
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
        if (state_LED == 4)
        {
            state_LED = 0;
        }
    }

    // change LED state
    if (value1 == 0)
    { // OFF
        for (int i = 0; i < LED_COUNT; i++)
        {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
    }
    else if (value1 == 1)
    { // ON
        if (state_LED == 0)
        {
            for (int i = 0; i < LED_COUNT; i++)
            {
                ratio = 1;
                pixels.setPixelColor(i, white);
                white = pixels.Color((int)(192 * ratio), (int)(192 * ratio), (int)(192 * ratio));
            }
        }
        else if (state_LED == 1)
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
        else if (state_LED == 2)
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
        else if (state_LED == 3)
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
        else if (state_LED == 4)
        {
        }
    }

    pixels.show();

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
}
