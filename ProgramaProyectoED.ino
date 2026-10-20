#include <EEPROM.h>
#include <Stepper.h>

int StepsPerLoop = 2048;
const int MotorSpeed = 6;
int MaxGrades = 360;
int LuxometerStepGrades = 30;
int GeneralPosition;

//int n;
//int MotorPosition;
//int X;


//= n*LuxometerStepGrades;


Stepper Motor(StepsPerLoop, 8, 10, 9, 11);


void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  Motor.setSpeed(MotorSpeed);
  //EEPROM.write(0, 0); //Activar solo la primera vez para configurar el valor inicial del motor.
  Serial.begin(9600);
}

void loop() {
  int Power = digitalRead(2);
  int Mode = digitalRead(3);
  int L_Rot = digitalRead(4);
  int R_Rot = digitalRead(5);
  int Saved = EEPROM.read(0);
  
  Serial.println(Saved);
  //Serial.println(Mode);
  //Serial.println(GeneralPosition);
  //Serial.println(L_Rot);
  //Serial.println(R_Rot);
  if (Power == HIGH){

    //Caso en el que la posición angular del motor se encuentra al interior del intervalo entre 0 y 150 grados.
    if (GeneralPosition > 0 && GeneralPosition < 150){
      
      //Manual Mode
      if (Mode == LOW){
        //Serial.println(String(L_Rot) + "          " + String(R_Rot));
        int n = ManualMode(L_Rot, R_Rot);
        int Grades = n*LuxometerStepGrades;
        int Steps = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
        Motor.step(Steps);
        //Actualiza la posición general del motor
        GeneralPosition = GeneralPosition + Grades;
        EEPROM.update(0, GeneralPosition);
      }
      //Automatic Mode
      if (Mode == HIGH){
        if (Serial.available()){
          int X = Serial.parseInt();
          int Grades = X*LuxometerStepGrades;
          int Position = GeneralPosition + Grades;
          if (Position >= 0 && Position <= 150){
            //int n = AutoMode(X);
            int Step = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
            Motor.step(Step);
            GeneralPosition = GeneralPosition + Grades;
            EEPROM.update(0, GeneralPosition);
          }
          else{Serial.println("Error, valor no permitido");}
        }
      }
    }

    //Caso en el que el motor se encuentra en el limite inferior de 0 grados.
    if (GeneralPosition == 0){
      L_Rot = LOW;
      //Manual Mode
      if (Mode == LOW){
        //Serial.println(String(L_Rot) + "          " + String(R_Rot));
        int n = ManualMode(L_Rot, R_Rot);
        int Grades = n*LuxometerStepGrades;
        int Steps = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
        Motor.step(Steps);
        //Actualiza la posición general del motor
        GeneralPosition = GeneralPosition + Grades;
        EEPROM.update(0, GeneralPosition);
      }
      //Automatic Mode
      if (Mode == HIGH){
        if (Serial.available()){
          int X = Serial.parseInt();
          int Grades = X*LuxometerStepGrades;
          int Position = GeneralPosition + Grades;
          if (Position >= 0 && Position <= 150){
            //int n = AutoMode(X);
            int Step = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
            Motor.step(Step);
            GeneralPosition = GeneralPosition + Grades;
            EEPROM.update(0, GeneralPosition);
          }
          else{Serial.println("Error, valor no permitido");}
        }
      }
    }

    //Caso en el que el motor se encuentra en el limite superior de 150 grados.
    if (GeneralPosition == 150){
      R_Rot = LOW;

      //Manual Mode
      if (Mode == LOW){
        //Serial.println(String(L_Rot) + "          " + String(R_Rot));
        int n = ManualMode(L_Rot, R_Rot);
        int Grades = n*LuxometerStepGrades;
        int Steps = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
        Motor.step(Steps);
        //Actualiza la posición general del motor
        GeneralPosition = GeneralPosition + Grades;
        EEPROM.update(0, GeneralPosition);
      }
      //Automatic Mode
      if (Mode == HIGH){
        if (Serial.available()){
          int X = Serial.parseInt();
          int Grades = X*LuxometerStepGrades;
          int Position = GeneralPosition + Grades;
          if (Position >= 0 && Position <= 150){
            //int n = AutoMode(X);
            int Step = map(Grades, 0, MaxGrades, 0, StepsPerLoop);
            Motor.step(Step);
            GeneralPosition = GeneralPosition + Grades;
            EEPROM.update(0, GeneralPosition);
          }
          else{Serial.println("Error, valor no permitido");}
        }
      }
    }
  }
  
  else{
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

}

int ManualMode(int Left, int Right){
  int n;
  if (Left == HIGH && Right == HIGH){n = 0;}
  if (Left == HIGH && Right == LOW){n = -1;}
  if (Left == LOW && Right == HIGH){n = 1;}
  if (Left == LOW && Right == LOW){n = 0;}
  //else{n = 0;}
  return n;
}

int AutoMode(int X_Variable){
  int n;
  if (X_Variable == HIGH){n = 1;}
  else{n = 0;}
  return n;
}


  // if (Serial.available()){
  //   int Grades = Serial.parseInt();
  //   int Step = map(Grades, 0, MaxGrade, 0, StepsPerLoop);
  //   Serial.println(String(Grades) + "->" + String(Step));
  //   Motor.step(Step);
  //   digitalWrite(8, LOW);
  //   digitalWrite(9, LOW);
  //   digitalWrite(10, LOW);
  //   digitalWrite(11, LOW);
  // }