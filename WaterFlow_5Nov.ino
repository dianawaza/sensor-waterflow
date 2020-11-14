volatile int NbTopsFan1;                                 //measuring the rising edges of the signal sensor 1
volatile int NbTopsFan2;                                //measuring the rising edges of the signal sensor 2
volatile int NbTopsFan3;                                //measuring the rising edges of the signal sensor 3
                              //measuring the rising edges of the signal sensor 5
float Calc11, Calc22, Calc33, Flow1, Flow2, Flow3, Volume1, Volume2, Volume3, Kebocoran;           //untuk variabel nilai perhitungan semua sensor

int hallsensor1  = 2;                                    //The pin location of the sensor 1
int hallsensor2 = 3;                                    //The pin location of the sensor 2
int hallsensor3 = 21;                                   //The pin location of the sensor 3
                                  //The pin location of the sensor 5


void setup() //
{ 
//-------------------------------------------------------------------------------------------------------------------------
//FLOW SENSOR
//-------------------------------------------------------------------------------------------------------------------------  pinMode(hallsensor1, INPUT);   //initializes digital pin 2 as an input
  pinMode(hallsensor1, INPUT);  //initializes digital pin 2 as an input
  pinMode(hallsensor2, INPUT);  //initializes digital pin 3 as an input
  pinMode(hallsensor3, INPUT);  //initializes digital pin 21 as an input
  Serial.begin(9600);           //This is the setup function where the serial port is initialised,
}

void rpm1()            //This is the function that the interupt calls sensor 1
    { 
      NbTopsFan1++;    //This function measures the rising and falling edge of the hall effect sensors signal sensor 1
    } 
void rpm2()           //This is the function that the interupt calls sensor 2
    { 
      NbTopsFan2++;   //This function measures the rising and falling edge of the hall effect sensors signal sensor 2
    }
void rpm3()           //This is the function that the interupt calls sensor 3
    { 
      NbTopsFan3++;   //This function measures the rising and falling edge of the hall effect sensors signal sensor 3
    } 

void loop (){
//FLOW SENSOR
//-------------------------------------------------------------------------------------------------------------------------
  NbTopsFan1  = 0;   //Set NbTops to 0 ready for calculations
  NbTopsFan2  = 0;   //Set NbTops to 0 ready for calculations
  NbTopsFan3  = 0;   //Set NbTops to 0 ready for calculations

  
  //---------------------------------interrupt 0--hallsensor_1-----------------------------------------------//  
  detachInterrupt(digitalPinToInterrupt(hallsensor2));
  detachInterrupt(digitalPinToInterrupt(hallsensor3));
  attachInterrupt(digitalPinToInterrupt(hallsensor1), rpm1, RISING); //and the interrupt is attached
  delay (1000);   //Wait 1 second
 
  Calc11 = (NbTopsFan1 * 60 / 9.0); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/min 
  Flow1 = (Calc11 / 60) * 1000;
  Volume1 += Flow1;
  
  Serial.print ("sensor 1: ");
  Serial.print (Calc11, DEC); //Prints the number calculated above
  Serial.println (" L/minute"); //Prints "L/hour"
  Serial.print ("Volume :");
  Serial.print (Volume1);
  Serial.println (" mL");
  
  //---------------------------------interrupt 1--hallsensor_2-------------------------------------------------//
  detachInterrupt(digitalPinToInterrupt(hallsensor1));
  detachInterrupt(digitalPinToInterrupt(hallsensor3));
  attachInterrupt(digitalPinToInterrupt(hallsensor2), rpm2, RISING); //and the interrupt is attached  
  delay (1000);   //Wait 1 second
 
  Calc22 = (NbTopsFan2 * 60 / 9.0); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/min 
  Flow2 = (Calc22 / 60) * 1000;
  Volume2 += Flow2;
  
  Serial.print ("   ");
  Serial.print ("sensor 2: ");
  Serial.print (Calc22, DEC); //Prints the number calculated above
  Serial.println (" L/minute"); //Prints "L/hour"
  Serial.print ("Volume :");
  Serial.print (Volume2);
  Serial.println (" mL");
  
  //-----------------------------------interrupt 2--hallsensor_3------------------------------------------------//
  detachInterrupt(digitalPinToInterrupt(hallsensor1));
  detachInterrupt(digitalPinToInterrupt(hallsensor2));
  attachInterrupt(digitalPinToInterrupt(hallsensor3), rpm3, RISING); //and the interrupt is attached
  delay (1000);   //Wait 1 second

  Calc33 = (NbTopsFan3 * 60 / 9.0); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/min 
  Flow3 = (Calc33 / 60) * 1000;
  Volume3 += Flow3;
  
  Serial.print ("   ");
  Serial.print ("sensor 3: ");
  Serial.print (Calc33, DEC); //Prints the number calcula ted above
  Serial.println (" L/minute"); //Prints "L/hour"
  Serial.print ("Volume :");
  Serial.print (Volume3);
  Serial.println (" mL");

  Kebocoran = Volume1 - (Volume2 + Volume3);
  Serial.print("Kebocoran :");
  Serial.print(Kebocoran);
  Serial.println(" mL");
}
