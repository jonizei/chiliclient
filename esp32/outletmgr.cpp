#include "chiliclient.h"
#include "outletmgr.h"

const int MAX_OUTLET = 3;

int outlet_count = 0;

const int outlet_pin_1 = 14;
const int outlet_pin_2 = 27;
const int outlet_pin_3 = 26;

/*
 * Array of outlets
 */
Outlet outlet_list[MAX_OUTLET];

/**
 * Initializes new outlet and adds it to the outlet array
 * Requires name of the outlet, number of the pin controlling the outlet
 * and boolean which tells if relay turns on either LOW or HIGH signal
 */
void add_outlet(std::string name, int pin, bool is_reverse)
{
  Outlet outlet;
  outlet.id = outlet_count + 1;
  outlet.name = name;
  outlet.pin = pin;
  outlet.is_reverse = is_reverse;
  
  if(outlet_count > -1 && outlet_count < MAX_OUTLET)
  {
    outlet_list[outlet_count] = outlet;
    outlet_count++;
  }
}

/*
 * Initializes all the outlets and
 * adds them to the array of outlets.
 * Then initializes the pins of the outlets.
 */
void init_outlets()
{
  add_outlet("Outlet_1", outlet_pin_1, false);
  add_outlet("Outlet_2", outlet_pin_2, false);
  add_outlet("Outlet_3", outlet_pin_3, false);

  init_outlet_pins();
}

/*
 * Sets all outlets pin as OUTPUT pins
 */
void init_outlet_pins()
{
  for(int i = 0; i < outlet_count; i++)
  {
    if(outlet_list[i].pin > 0)
    {
      pinMode(outlet_list[i].pin, OUTPUT);
    }
  }
}

/*
 * Checks all outlets if any of them is set to on or off.
 * Some relays works that HIGH is on and LOW is off and 
 * some works the other way around.
 * Is_reverse determines how the relay works.
 */
void check_outlets()
{
  for(int i = 0; i < outlet_count; i++)
  {
    if(outlet_list[i].pin > 0)
    {
      Outlet* outlet = &(outlet_list[i]);
      bool isOn = outlet->is_on;
      bool isReverse = outlet->is_reverse;
      bool isHigh = isOn != isReverse;

      if(isHigh) {
        digitalWrite(outlet->pin, HIGH);
      } else {
        digitalWrite(outlet->pin, LOW);
      }
    }
  }
}

/*
 * Takes json document as a parameter.
 * Tries to find outlet with the same id
 * and then copies the data from the json document.
 */
void update_outlet_list(DynamicJsonDocument jsonDoc)
{
  
  for(int i = 0; i < outlet_count; i++)
  {
    for(int j = 0; j < jsonDoc.size(); j++)
    {
      JsonObject jsonObject = jsonDoc[j];
      
      if(jsonObject["id"] == outlet_list[i].id)
      {
        outlet_list[i].is_on = jsonObject["is_on"];
      }
      
    }
  }
}




  
