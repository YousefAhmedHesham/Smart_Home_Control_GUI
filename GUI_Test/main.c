#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define UART_BASE UART0_BASE

// Simulated temperature
volatile uint32_t temperature = 25;

// Function to initialize UART
void UART_Init(void) {
    // Enable UART0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure GPIO pins for UART
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure UART for 9600 baud rate
    UARTConfigSetExpClk(UART_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

// Function to send a string via UART
void UART_SendString(const char *str) {
    while (*str) {
        UARTCharPut(UART_BASE, *str++);
    }
}

// Function to handle commands from the GUI
void ProcessCommand(const char *command) {
    if (strcmp(command, "LAMP") == 0) {
        UART_SendString("LAMP TOGGLED\n");
    } else if (strcmp(command, "PLUG") == 0) {
        UART_SendString("PLUG TOGGLED\n");
    } else {
        UART_SendString("UNKNOWN COMMAND\n");
    }
}

// Function to simulate sending data to the GUI
void SendDataToGUI(void) {
    char buffer[32];

    // Send door status
    UART_SendString("DOOR:CLOSED\n");

    // Send temperature
    snprintf(buffer, sizeof(buffer), "TEMP:%d\n", temperature);
    UART_SendString(buffer);

    // Simulate temperature change
    temperature += 1;
    if (temperature > 40) {
        temperature = 25;
    }
}

int main(void) {
    char commandBuffer[32];
    uint32_t commandIndex = 0;

    // Set system clock to 50 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Initialize UART
    UART_Init();

    // Main loop
    while (1) {
        // Check for received characters
        if (UARTCharsAvail(UART_BASE)) {
            char c = UARTCharGet(UART_BASE);

            // End of command
            if (c == '\n' || c == '\r') {
                commandBuffer[commandIndex] = '\0';
                ProcessCommand(commandBuffer);
                commandIndex = 0; // Reset buffer index
            } else if (commandIndex < sizeof(commandBuffer) - 1) {
                commandBuffer[commandIndex++] = c;
            }
        }

        // Periodically send data to GUI
        SendDataToGUI();
        SysCtlDelay(SysCtlClockGet() / 3); // 1-second delay
    }
}
