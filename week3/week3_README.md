# Smart Traffic Light with Pedestrian Control

This Arduino project simulates a **traffic light system with pedestrian crossing support**, demonstrating key **embedded system concepts** such as:

- **GPIO control** (controlling LEDs and reading button input)  
- **Non-blocking timing** using `millis()` instead of `delay()`  
- **Finite State Machine (FSM)** for deterministic state transitions  
- **Event-driven programming** (reacting to button presses)  
- **Software debouncing** to avoid multiple triggers from a single press  

The traffic light cycles automatically: **RED → GREEN → YELLOW → RED**, and pressing the input triggers a pedestrian crossing sequence safely.

---

## Hardware Used

- Arduino board (Uno, Nano, or similar)  
- 3 LEDs (Red, Yellow, Green)  
- Resistors for LEDs (220–330Ω)  
- Joystick module with built-in push button  
- Jumper wires  
- Breadboard (optional)

**Note:** Instead of a regular push button, this project uses the **joystick module’s built-in button** as the pedestrian input. The joystick button functions like a standard push button, setting a `pedestrianRequest` flag that the FSM uses to manage state transitions. This shows how different hardware inputs can be easily integrated into embedded system logic.

---

## Traffic Light Behavior

| Current State           | LED Status        | Duration  | Pedestrian Button Effect            |
|-------------------------|-----------------|----------|------------------------------------|
| **RED**                 | Red ON          | 8 sec    | No effect                          |
| **GREEN**               | Green ON        | 8 sec    | If pressed, triggers YELLOW after minimum 3 sec |
| **YELLOW**              | Yellow ON       | 3 sec    | Prepares for pedestrian RED if requested |
| **PEDESTRIAN RED**      | Red ON          | 6 sec    | Pedestrian crossing active, request cleared afterwards |

---

## How It Works

1. **RED** LED turns on for 8 seconds.  
2. **GREEN** LED turns on for 8 seconds.  
   - If the joystick button is pressed during GREEN (after at least 3 seconds), the system transitions to YELLOW and then PEDESTRIAN RED.  
3. **YELLOW** LED turns on for 3 seconds.  
4. **PEDESTRIAN RED** keeps RED LED on for 6 seconds, allowing safe pedestrian crossing.  
5. After PEDESTRIAN RED, the cycle returns to RED and continues automatically.  

---

## Embedded Concepts Demonstrated

- **GPIO abstraction:** LEDs and button handled through pin definitions.  
- **Super loop architecture:** Main `loop()` continuously checks states and events.  
- **Non-blocking timing:** `millis()` allows monitoring inputs while controlling outputs.  
- **Finite State Machine (FSM):** Ensures predictable and safe traffic light behavior.  
- **Event-driven logic:** Pedestrian requests affect future state transitions.  
- **Software debounce:** Prevents multiple triggers from a single joystick press.  
- **Modular firmware:** Functions separate state management, output control, and input reading.  

---



